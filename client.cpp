#include "client.hpp"
#include "test_common.hpp"
#include <chrono>
#include <iostream>

Client::Client() {
    
}

Client::~Client() {

}

void Client::onConnected() {
    if(cb_onConnected) cb_onConnected();
}

void Client::onConnectRetry() {
    if(cb_onConnectRetry) cb_onConnectRetry();
}

void Client::onConnectFailed(Status s) {
    if(cb_onConnectFailed) cb_onConnectFailed(s);
}

void Client::onDisconnected() {
    if(cb_onDisconnected) cb_onDisconnected();
}


void Client::Connect(const std::string& host, const std::string& port, int retry) {
    Thread::Do([=](){
        int remain = retry;
        auto s = m_client.Connect(host, port);
        while(s != STAT_OK && remain-- > 0) {
            onConnectRetry();
            s = m_client.Connect(host, port);
        }

        if (s == STAT_OK) {
            Thread::Daemon([=](){
                while(true) {
                    Header h;
                    Bytes b;
                    auto s = m_client.Recv(h, b);
                    if(s == STAT_ERR_RECV_AGAIN) continue;
                    if (s != STAT_OK) {
                        std::cout << "Err: " << s << std::endl;
                        Disconnect();
                        break;
                    }

                    switch(h.Type){
                        case PKG_RESPONSE:
                            break;
                        case PKG_NOTIFY:
                            //on push
                            break;
                        case PKG_NOTIFY_RESPONSE:
                            break;
                        case PKG_HEARTBEAT_RESPONSE:
                            break;
                        default: break;
                    }
                    //TODO:
                    std::cout << "Recv: " << std::endl;
                    std::cout << "\t => "; header_print(h);
                    std::cout << "\t => "; bytes_print(b);
                    std::cout << "===============================" << std::endl;
                }
            });
            onConnected();
        } else {
            onConnectFailed(s);
        }
    });
}

void Client::Disconnect() {
    /* disconnect never failed */
    m_client.Disconnect();
    onDisconnected();
}

Status Client::Request(const std::string& route, const Bytes& data, DataCallbackType cb) {
    Header h(PKG_REQUEST, ENCODING_JSON, data.Size(), route);

    m_requestCBMutex.lock();
    m_requestCallbacks[h.ID] = cb;
    m_requestCBMutex.unlock();

    return m_client.Send(h, data);
}

Status Client::Notify(const std::string& route, const Bytes& data) {
    Header h(PKG_NOTIFY, ENCODING_JSON, data.Size(), route);
    return m_client.Send(h, data);
}

Status Client::AddListener(const std::string& route, DataCallbackType cb) {
    m_pushCBMutex.lock();
    auto iter = m_pushCallbacks.find(route);
    if(iter == m_pushCallbacks.end()) {
        m_pushCallbacks[route] = std::vector<DataCallbackType>();
    }
    m_pushCallbacks[route].push_back(cb);
    m_pushCBMutex.unlock();

    return STAT_OK;
}
