#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <functional>
#include <string>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include "common.h"
#include "tcpclient.hpp"

class Client {
typedef std::function<void(const std::string&, const Bytes&)> DataCallbackType;

public:
    /* connect status callbacks */
    std::function<void()> cb_onConnected;
    std::function<void()> cb_onConnectRetry;
    std::function<void(Status)> cb_onConnectFailed;
    std::function<void()> cb_onDisconnected;

private:
    void onConnected();
    void onConnectRetry();
    void onConnectFailed(Status);
    void onDisconnected();

private:
    /* tcp request/push callbacks */
    TcpClient m_client;
    std::thread m_recvThread;
    std::mutex m_mutex;
    std::map<PackageIDType, DataCallbackType> m_requestCallbacks;
    std::map<std::string, std::vector<DataCallbackType> > m_pushCallbacks;

public:
    Client();
    ~Client();

    void Connect(const std::string& host, const std::string& port, int retry=5);
    void Disconnect();

    Status Request(const std::string& route, const Bytes& data, DataCallbackType);
    Status Notify(const std::string& route, const Bytes& data);

    Status AddListener(const std::string& route, DataCallbackType);
};

#endif
