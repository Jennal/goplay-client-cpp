#ifndef HEARTBEAT_HPP
#define HEARTBEAT_HPP

#include "common.h"
#include "header.hpp"
#include <string>

class HeartBeat : public Header {
public:
    HeartBeat(EncodingType e);
};

#endif /* HEARTBEAT_HPP */
