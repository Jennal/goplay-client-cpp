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
