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