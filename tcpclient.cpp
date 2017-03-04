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

bool TcpClient::IsConnected() {
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

    //setup thread
    m_recvThread = std::thread([this](){
        while(true) {
            Header header;
            Bytes body;
            Status s = this->Recv(header, body);
            //TODO:
            if (s == STAT_OK) {
                std::cout << "Recv: " << std::endl;
                std::cout << "\t => "; header_print(header);
                std::cout << "\t => "; bytes_print(body);
                std::cout << "===============================" << std::endl;
            } else if(s == STAT_ERR_RECV_AGAIN) {
                continue;
            } else {
                std::cout << "Err: " << s << std::endl;
            }
        }
    });

    return STAT_OK;
}

Status TcpClient::Disconnect() {
    if ( ! IsConnected()) return STAT_OK;

    //close thread
    if(m_recvThread.joinable()) m_recvThread.detach();

    //close socket
    close(m_socketID);
    m_socketID = -1;

    return STAT_OK;
}

Status TcpClient::Recv(Header& header, Bytes& bytes) {
    unsigned char buf[Header::HeaderSize];
    memset(buf, 0, Header::HeaderSize);
    size_t n = recv(m_socketID, buf, Header::HeaderSize, 0);
    if(n <= 0) return (Status)errno;

    Bytes b(buf, Header::HeaderSize);
    header.SetBytes(b);

    unsigned char content[header.ContentSize];
    memset(content, 0, header.ContentSize);
    n = recv(m_socketID, content, header.ContentSize, 0);
    if(n <= 0) return (Status)errno;

    bytes.Write(content, n);

    return STAT_OK;
}

Status TcpClient::Send(Header& header, const Bytes& body) {
    header.ContentSize = body.Size();

    Bytes headerBytes;
    header.GetBytes(headerBytes);
    size_t n = send(m_socketID, headerBytes.Ptr(), headerBytes.Size(), 0);
    // printf("write header: %d\n", n);
    if(n < headerBytes.Size()) return (Status)errno;

    n = send(m_socketID, body.Ptr(), body.Size(), 0);
    // printf("write body: %d\n", n);
    if(n < body.Size()) return (Status)errno;

    return STAT_OK;
}
