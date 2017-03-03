#include "tcpclient.hpp"
#include "tcp.h"
#include <cstring>
#include "bytes.hpp"
#include "header.hpp"

TcpClient::TcpClient()
    : m_socketID(-1),
      m_host(""),
      m_port("")
{}

TcpClient::~TcpClient() {
    Disconnect();
}

bool TcpClient::IsConnected() {
    return this->m_socketID >= 0;
}

Status TcpClient::Connect(const std::string& host, const std::string& port) {
    if (this->IsConnected()) {
        if (this->m_host == host && this->m_port == port) return STAT_OK;
        else this->Disconnect();
    }

    this->m_host = host;
    this->m_port = port;

    int status = tcp_client(this->m_host.c_str(), this->m_port.c_str());
    if(status < 0) return (Status)status;

    this->m_socketID = status;

    return STAT_OK;
}

Status TcpClient::Disconnect() {
    if ( ! this->IsConnected()) return STAT_OK;

    close(this->m_socketID);
    this->m_socketID = -1;

    return STAT_OK;
}

Status TcpClient::Recv(Header& header, Bytes& bytes) {
    unsigned char buf[Header::HeaderSize];
    memset(buf, 0, Header::HeaderSize);
    size_t n = recv(m_socketID, buf, Header::HeaderSize, 0);
    if(n < 0) return (Status)errno;

    Bytes b(buf, Header::HeaderSize);
    header.SetBytes(b);

    unsigned char content[header.ContentSize];
    memset(content, 0, header.ContentSize);
    n = recv(m_socketID, content, header.ContentSize, 0);
    if(n < 0) return (Status)errno;

    bytes.Write(content, n);

    return STAT_OK;
}

Status TcpClient::Send(const Header& header, const Bytes& body) {
    Bytes headerBytes;
    header.GetBytes(headerBytes);
    size_t n = send(m_socketID, headerBytes.Ptr(), headerBytes.Size(), 0);
    printf("write header: %d\n", n);
    if(n < 0) return (Status)errno;

    n = send(m_socketID, body.Ptr(), body.Size(), 0);
    printf("write body: %d\n", n);
    if(n < 0) return (Status)errno;

    return STAT_OK;
}
