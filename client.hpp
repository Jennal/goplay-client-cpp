#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <functional>
#include <string>
#include <map>
#include <vector>
#include <mutex>
#include "common.h"
#include "tcpclient.hpp"
#include "thread.hpp"
#include "heartbeat_processor.hpp"

class Client {
typedef std::function<void(const std::string&, const Bytes&)> DataCallbackType;
typedef std::pair<DataCallbackType, DataCallbackType> RequestCallbackPair;

private:
    /* connect status callbacks */
    std::function<void(Client&)> cb_onConnected;
    std::function<void(Client&)> cb_onConnectRetry;
    std::function<void(Client&, Status)> cb_onConnectFailed;
    std::function<void(Client&)> cb_onDisconnected;

private:
    void onConnected();
    void onConnectRetry();
    void onConnectFailed(Status);
    void onDisconnected();

private:
    /* tcp request/push callbacks */
    TcpClient m_client;
    std::mutex m_requestCBMutex;
    std::mutex m_pushCBMutex;
    std::map<PackageIDType, RequestCallbackPair> m_requestCallbacks;
    std::map<std::string, std::vector<DataCallbackType> > m_pushCallbacks;

    HeartbeatProcessor m_heartbeatProcessor;

public:
    Client(
        std::function<void(Client&)> onConnected,
        std::function<void(Client&)> onConnectRetry,
        std::function<void(Client&, Status)> onConnectFailed,
        std::function<void(Client&)> onDisconnected
    );
    ~Client();

    void Connect(const std::string& host, const std::string& port, int retry=5);
    void Disconnect();

    bool IsConnected() const;
    TcpClient& GetTcpClient();

    Status Request(const std::string& route, const Bytes& data, DataCallbackType succCB, DataCallbackType failCB);
    Status Notify(const std::string& route, const Bytes& data);

    Status AddListener(const std::string& route, DataCallbackType);
};

#endif
