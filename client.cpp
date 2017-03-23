// Copyright (C) 2017 Jennal(jennalcn@gmail.com). All rights reserved.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#include "client.hpp"
#include "test_common.hpp"
#include <chrono>
#include <iostream>

Client::Client(
    std::function<void(Client&)> onConnected,
    std::function<void(Client&)> onConnectRetry,
    std::function<void(Client&, Status)> onConnectFailed,
    std::function<void(Client&)> onDisconnected
)
    : cb_onConnected(onConnected),
      cb_onConnectRetry(onConnectRetry),
      cb_onConnectFailed(onConnectFailed),
      cb_onDisconnected(onDisconnected),
      m_heartbeatProcessor(
          std::chrono::milliseconds(HEARTBEAT_TIMEOUT), 
          std::chrono::milliseconds(HEARTBEAT_INTERVAL), 
          HEARTBEAT_MAX_TIMEOUT
      )
{}

Client::~Client() {

}

void Client::onConnected() {
    if(cb_onConnected) cb_onConnected(*this);
}

void Client::onConnectRetry() {
    if(cb_onConnectRetry) cb_onConnectRetry(*this);
}

void Client::onConnectFailed(Status s) {
    if(cb_onConnectFailed) cb_onConnectFailed(*this, s);
}

void Client::onDisconnected() {
    if(cb_onDisconnected) cb_onDisconnected(*this);
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
                        std::cout << "Err: " << status_str(s) << std::endl;
                        Disconnect();
                        break;
                    }

                    std::cout << "Recv: " << std::endl;
                    std::cout << "\t => "; header_print(h);
                    std::cout << "\t => "; bytes_print(b);
                    std::cout << "===============================" << std::endl;

                    if(h.Type == PKG_RESPONSE) {
                        //on request callback
                        m_requestCBMutex.lock();
                        auto rcbIter = m_requestCallbacks.find(h.ID);
                        m_requestCBMutex.unlock();
                        if(rcbIter == m_requestCallbacks.end()) continue;

                        auto funcPair = rcbIter->second;
                        m_requestCBMutex.lock();
                        m_requestCallbacks.erase(rcbIter);
                        m_requestCBMutex.unlock();
                        if(h.Stat == STAT_OK) {
                            //success callback
                            funcPair.first(h.Route, b);
                        } else {
                            //failed callback
                            funcPair.second(h.Route, b);
                        }
                        
                    } else if(h.Type == PKG_PUSH) {
                        //on push callback
                        m_pushCBMutex.lock();
                        auto pcbIter = m_pushCallbacks.find(h.Route);
                        m_pushCBMutex.unlock();
                        if(pcbIter == m_pushCallbacks.end()) continue;

                        auto list = pcbIter->second;
                        for(auto func : list) {
                            func(h.Route, b);
                        }
                    } else if(h.Type == PKG_HEARTBEAT) {
                        //send response
                        h.Type = PKG_HEARTBEAT_RESPONSE;
                        m_client.Send(h, b); /* b should be empty */
                    } else if(h.Type == PKG_HEARTBEAT_RESPONSE) {
                        m_heartbeatProcessor.Recv(h);
                    } else {
                        // case PKG_REQUEST:
                        continue;
                    }
                }
            });

            m_heartbeatProcessor.Start(*this);

            onConnected();
        } else {
            onConnectFailed(s);
        }
    });
}

void Client::Disconnect() {
    m_heartbeatProcessor.Stop();
    /* disconnect never failed */
    m_client.Disconnect();
    //TODO:fail all request
    m_requestCBMutex.lock();
    m_requestCallbacks.clear();
    m_requestCBMutex.unlock();
    onDisconnected();
}

bool Client::IsConnected() const {
    return m_client.IsConnected();
}

TcpClient& Client::GetTcpClient() {
    return m_client;
}

Status Client::Request(const std::string& route, const Bytes& data, DataCallbackType succCB, DataCallbackType failCB) {
    Header h(PKG_REQUEST, ENCODING_JSON, data.Size(), route);

    m_requestCBMutex.lock();
    m_requestCallbacks[h.ID] = RequestCallbackPair(succCB, failCB);
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
