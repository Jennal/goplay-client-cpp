#include "tcpclient.hpp"
#include "tcpclient.h"

TcpClient::TcpClient()
    : m_socketID(-1),
      m_host(""),
      m_port(-1)
{}

~TcpClient::TcpClient() {
    Disconnect();
}

bool TcpClient::IsConnected() {
    return this->m_socketID >= 0;
}

Status TcpClient::Connect(const std::string& host, int port) {
    if (this->IsConnected()) {
        if (this->m_host == host && this->m_port == port) return STAT_OK;
        else this->Disconnect();
    }

    this->m_host = host;
    this->m_port = port;

    int status = tcp_client(this->m_host.c_str(), this->m_port);
    if(status < 0) return (Status)status;

    this->m_isConnected = true;
    this->m_socketID = status;

    return STAT_OK;
}

Status TcpClient::Disconnect() {
    if ( ! this->IsConnected()) return;

    close(this->m_socketID);
    this->m_socketID = -1;
}

Status TcpClient::Recv(Header& header, Bytes bytes) {

}

Status TcpClient::Send(Header& header, Bytes bytes) {

}
