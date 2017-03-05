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
    //recv header
    unsigned char buf[Header::HeaderSize];
    memset(buf, 0, Header::HeaderSize);
    int n = recv(m_socketID, buf, Header::HeaderSize, 0);
    if(n <= 0) { /*printf("Err-0\n");*/ return (Status)errno; }

    Bytes b(buf, Header::HeaderSize);
    // printf("Header(%d) => ", n); bytes_print(b);
    header.SetBytes(b);

    //recv route
    unsigned char routeSize = 0;
    n = recv(m_socketID, &routeSize, 1, 0);
    // printf("routeSize => %d, %d\n", n, routeSize);
    if(n <= 0) { /*printf("Err-1\n");*/ return (Status)errno; }
    if(routeSize <= 0) { /*printf("Err-2\n");*/ return STAT_ERR_RECV_FAULT; }

    char route[routeSize + 1];
    memset(route, 0, routeSize + 1);
    n = recv(m_socketID, route, routeSize, 0);
    header.Route = route;

    //recv content
    unsigned char content[header.ContentSize];
    memset(content, 0, header.ContentSize);
    n = recv(m_socketID, content, header.ContentSize, 0);
    if(n <= 0) { /*printf("Err-3\n");*/ return (Status)errno; }

    bytes.Write(content, n);

    return STAT_OK;
}

Status TcpClient::Send(Header& header, const Bytes& body) {
    header.ContentSize = body.Size();

    header_print(header);
    bytes_print(body);

    Bytes headerBytes;
    header.GetBytes(headerBytes);
    int n = send(m_socketID, headerBytes.Ptr(), headerBytes.Size(), 0);
    printf("write header: %d\n", n);
    if(n < headerBytes.Size()) return (Status)errno;

    n = send(m_socketID, body.Ptr(), body.Size(), 0);
    printf("write body: %d\n", n);
    if(n < body.Size()) return (Status)errno;

    return STAT_OK;
}
