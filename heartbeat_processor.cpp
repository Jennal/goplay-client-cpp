// Copyright (C) 2017 Jennal(jennalcn@gmail.com). All rights reserved.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#include "heartbeat_processor.hpp"
#include "thread.hpp"
#include "client.hpp"
#include "heartbeat.hpp"
#include <vector>

#include "test_common.hpp"
#include <stdio.h>
#include <iostream>

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
                interval = std::chrono::milliseconds(0);

                HeartBeat hb(DEFAULT_ENCODING);
                Bytes b;

                m_timePointsMutex.lock();
                m_timePoints[hb.ID] = std::chrono::steady_clock::now();
                m_timePointsMutex.unlock();

                tcpClient.Send(hb, b);
            }

            if(timeOut >= m_timeOut) {
                timeOut = std::chrono::milliseconds(0);

                auto isDisconnect = false;
                std::vector<TimePointMap::value_type> list;
                m_timePointsMutex.lock(); 
                for(auto val : m_timePoints) {
                    auto prevTime = val.second;
                    auto now = std::chrono::steady_clock::now();
                    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(now - prevTime);
                    if(dur > m_timeOut) {
                        list.push_back(val);
                        m_timeOutCount++;
                        std::cout << " ==> [timeout]: " << (int)val.first << " -> " << prevTime.time_since_epoch().count() << std::endl
                                    << "\t\t-> " << now.time_since_epoch().count() << " | " << dur.count() << std::endl
                                    << "\t\t-> " <<  m_timeOutCount << std::endl;
                    }

                    if (m_timeOutCount > m_maxTimeout) {
                        isDisconnect = true;
                        break;
                    }
                }

                for(auto val : list) {
                    auto iter = m_timePoints.find(val.first);
                    if (iter != m_timePoints.end())
                        m_timePoints.erase(iter);
                }
                m_timePointsMutex.unlock();

                if (isDisconnect) {
                    std::cout << "[timeout]: " << timeOut.count() << "ms" << std::endl;
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

    // std::cout << "<<<<<<<<< Recv HeartBeat Response: " << std::endl;
    // std::cout << "\t => "; header_print(header);
    // std::cout << "===============================" << std::endl;

    m_timePoints.erase(iter);
    m_timeOutCount = 0;
    m_timePointsMutex.unlock();
}