#ifndef HEARTBEAT_PROCESSOR_HPP
#define HEARTBEAT_PROCESSOR_HPP

#include "common.h"
#include "header.hpp"
#include <chrono>
#include <map>
#include <mutex>

class Client;

class HeartbeatProcessor {
private:
    std::chrono::milliseconds m_timeOut;
    std::chrono::milliseconds m_interval;
    int m_maxTimeout;
    int m_timeOutCount;

    std::map<PackageIDType, std::chrono::steady_clock::time_point> m_timePoints;
    std::mutex m_timePointsMutex;

    bool m_recvStopSignal;

public:
    HeartbeatProcessor(const std::chrono::milliseconds timeOut, const std::chrono::milliseconds interval, int maxTimeout);
    ~HeartbeatProcessor();

    void Start(Client& cli);
    void Stop();

    void Recv(const Header& header);
};

#endif /* HEARTBEAT_PROCESSOR_HPP */
