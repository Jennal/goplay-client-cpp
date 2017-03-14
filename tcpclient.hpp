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

#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include <thread>
#include <mutex>
#include <string>

#include "common.h"
#include "header.hpp"
#include "bytes.hpp"

class TcpClient {
private:
    int m_socketID;
    std::string m_host;
    std::string m_port;

public:
    TcpClient();
    ~TcpClient();

    bool IsConnected() const;

    Status Connect(const std::string& host, const std::string& port);
    Status Disconnect();

    Status Recv(Header& header, Bytes& bytes);
    Status Send(Header& header, const Bytes& bytes);
};

#endif /* TCPCLIENT_HPP */