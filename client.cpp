#include "client.hpp"

Client::Client() {

}

Client::~Client() {

}

Status Client::Connect(const std::string& host, const std::string& port, int retry) {
    //TODO: retry
    return m_client.Connect(host, port);
}

Status Client::Disconnect() {
    return m_client.Disconnect();
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
