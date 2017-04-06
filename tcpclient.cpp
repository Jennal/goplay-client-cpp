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

#include "tcpclient.hpp"
#include "tcp.h"
#include <cstring>
#include "bytes.hpp"
#include "header.hpp"

#include <iostream>
#include "test_common.hpp"

TcpClient::TcpClient()
    : m_socketID(-1),
      m_host(""),
      m_port("")
{}

TcpClient::~TcpClient() {
    Disconnect();
}

bool TcpClient::IsConnected() const {
    return m_socketID >= 0;
}

Status TcpClient::Connect(const std::string& host, const std::string& port) {
    if (IsConnected()) {
        if (m_host == host && m_port == port) return STAT_OK;
        else Disconnect();
    }

    m_host = host;
    m_port = port;

    int status = tcp_client(m_host.c_str(), m_port.c_str());
    if(status < 0) return (Status)status;

    //setup socket
    m_socketID = status;

    return STAT_OK;
}

Status TcpClient::Disconnect() {
    if ( ! IsConnected()) return STAT_OK;

    //close socket
    close(m_socketID);
    m_socketID = -1;

    return STAT_OK;
}

Status TcpClient::Recv(Header& header, Bytes& bytes) {
    Bytes b;

    //recv static header
    unsigned char buf[Header::HeaderSize];
    memset(buf, 0, Header::HeaderSize);
    int n = recv(m_socketID, buf, Header::HeaderSize, 0);
    if(n <= 0) { /*printf("Err-0\n");*/ return (Status)errno; }

    b.Write(buf, Header::HeaderSize);
    // printf("Header(%d) => ", n); bytes_print(b);

    //recv route
    unsigned char routeSize = 0;
    n = recv(m_socketID, &routeSize, 1, 0);
    // printf("routeSize => %d, %d\n", n, routeSize);
    if(n <= 0) { /*printf("Err-1\n");*/ return (Status)errno; }
    b.Write(routeSize);
    /* heartbeat/heartbeat_response has no route */
    if(routeSize > 0) {
        char route[routeSize + 1];
        memset(route, 0, routeSize + 1);
        n = recv(m_socketID, route, routeSize, 0);
        if(n <= 0) return (Status)errno;
        b.Write(route, n);
    }

    header.SetBytes(b);

    //recv content
    if (header.ContentSize > 0) {
        unsigned char content[header.ContentSize];
        memset(content, 0, header.ContentSize);
        int recvedSize = 0;
        while (recvedSize < header.ContentSize) {
            // std::cout << "****** Before Recv: " << std::endl;
            // std::cout << "\trecvedSize=" << recvedSize << ", n=" << n << std::endl;
            // std::cout << "===============================" << std::endl;
            n = recv(m_socketID, content+recvedSize, header.ContentSize-recvedSize, 0);
            if(n <= 0) { /*printf("Err-3\n");*/ return (Status)errno; }
            recvedSize += n;
            // std::cout << "****** After Recv: " << std::endl;
            // std::cout << "\trecvedSize=" << recvedSize << ", n=" << n << std::endl;
            // std::cout << "===============================" << std::endl;
        }

        bytes.Write(content, recvedSize);
    }

    if(header.Type != PKG_HEARTBEAT && header.Type != PKG_HEARTBEAT_RESPONSE) {
        std::cout << "<<<<<<<<< Recv: " << std::endl;
        std::cout << "\t => "; header_print(header);
        std::cout << "\t => "; bytes_print(bytes);
        std::cout << "===============================" << std::endl;
    }

    return STAT_OK;
}

Status TcpClient::Send(Header& header, const Bytes& body) {
    header.ContentSize = body.Size();

    // header_print(header);
    // bytes_print(body);

    Bytes headerBytes;
    header.GetBytes(headerBytes);
    int n = send(m_socketID, headerBytes.Ptr(), headerBytes.Size(), 0);
    // printf("write header: %d\n", n);
    if(n < headerBytes.Size()) return (Status)errno;

    if (header.ContentSize > 0) {
        int sentSize = 0;
        while (sentSize < body.Size()) {
            n = send(m_socketID, (void*)((size_t)body.Ptr()+sentSize), body.Size()-sentSize, 0);
            // printf("write body: %d\n", n);
            if(n < body.Size()) return (Status)errno;

            sentSize += n;
        }
    }

    if(header.Type != PKG_HEARTBEAT && header.Type != PKG_HEARTBEAT_RESPONSE) {
        std::cout << ">>>>>>>>> Write: " << std::endl;
        std::cout << "\t => "; header_print(header);
        std::cout << "\t => "; bytes_print(body);
        std::cout << "===============================" << std::endl;
    }

    return STAT_OK;
}
