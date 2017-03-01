#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include <string>

#include "common.h"
#include "header.hpp"

class TcpClient {
private:
    int m_socketID;
    std::string m_host;
    int m_port;

public:
    TcpClient();
    ~TcpClient();

    bool IsConnected();

    Status Connect(const std::string& host, int port);
    Status Disconnect();

    Status Recv(Header& header, Bytes bytes);
    Status Send(Header& header, Bytes bytes);
};

#endif /* TCPCLIENT_HPP */