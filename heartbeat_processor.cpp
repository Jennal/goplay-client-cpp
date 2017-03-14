#include "heartbeat_processor.hpp"
#include "thread.hpp"
#include "client.hpp"
#include "heartbeat.hpp"

#define DELTA_TIME (1000)

HeartbeatProcessor::HeartbeatProcessor(const std::chrono::milliseconds timeOut, const std::chrono::milliseconds interval, int maxTimeout)
    : m_timeOut(timeOut),
      m_interval(interval),
      m_maxTimeout(maxTimeout),
      m_timeOutCount(0),
      m_recvStopSignal(false)
{

}

HeartbeatProcessor::~HeartbeatProcessor()
{
}

void HeartbeatProcessor::Start(Client& cli) {
    if( ! cli.IsConnected()) return;

    m_recvStopSignal = false;
    Thread::Daemon([this, &cli](){
        auto timeOut = std::chrono::milliseconds(0);
        auto interval = std::chrono::milliseconds(0);
        auto tcpClient = cli.GetTcpClient();

        while(true) {
            if (m_recvStopSignal) {
                m_recvStopSignal = false;
                return;
            }

            if(interval >= m_interval) {
                HeartBeat hb(DEFAULT_ENCODING);
                Bytes b;

                m_timePointsMutex.lock();
                m_timePoints[hb.ID] = std::chrono::steady_clock::now();
                m_timePointsMutex.unlock();

                tcpClient.Send(hb, b);
                interval = std::chrono::milliseconds(0);
            }

            if(timeOut >= m_timeOut) {
                auto isDisconnect = false;
                m_timePointsMutex.lock();
                for(auto iter : m_timePoints) {
                    auto prevTime = iter.second;
                    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - prevTime);
                    if(dur > m_timeOut) {
                        m_timeOutCount++;
                    }

                    if (m_timeOutCount > m_maxTimeout) {
                        isDisconnect = true;
                        break;
                    }
                }
                m_timePointsMutex.unlock();

                if (isDisconnect) {
                    cli.Disconnect();
                    return;
                }
            }

            Thread::Sleep(DELTA_TIME);
            timeOut += std::chrono::milliseconds(DELTA_TIME);
            interval += std::chrono::milliseconds(DELTA_TIME);
        }
    });
}

void HeartbeatProcessor::Stop() {
    m_recvStopSignal = true;
}

void HeartbeatProcessor::Recv(const Header& header) {
    m_timePointsMutex.lock();
    auto iter = m_timePoints.find(header.ID);
    if(iter == m_timePoints.end()) {
        m_timePointsMutex.unlock();
        return;
    }

    m_timePoints.erase(iter);
    m_timeOutCount = 0;
    m_timePointsMutex.unlock();
}