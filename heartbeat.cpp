#include "heartbeat.hpp"

HeartBeat::HeartBeat(EncodingType e)
    : Header(PKG_HEARTBEAT, e, 0, std::string(""))
{}