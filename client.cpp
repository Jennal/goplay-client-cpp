#include "client.hpp"
#include <chrono>

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
    std::thread th([=](){
        int remain = retry;
        auto s = m_client.Connect(host, port);
        while(s != STAT_OK && remain-- > 0) {
            onConnectRetry();
            s = m_client.Connect(host, port);
        }

        if (s == STAT_OK) {
            onConnected();
        } else {
            onConnectFailed(s);
        }
    });
    th.join();
}

void Client::Disconnect() {
    /* disconnect never failed */
    m_client.Disconnect();
    onDisconnected();
}

Status Client::Request(const std::string& route, const Bytes& data, DataCallbackType) {
    return STAT_OK;
}

Status Client::Notify(const std::string& route, const Bytes& data) {
    return STAT_OK;
}

Status Client::AddListener(const std::string& route, DataCallbackType) {
    return STAT_OK;
}
