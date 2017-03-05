#ifndef TEST_COMMON_HPP
#define TEST_COMMON_HPP

#include <string>
#include <cstdio>
#include "bytes.hpp"
#include "header.hpp"
#include "common.h"

void bytes_print(const Bytes& b);
void header_print(const Header& header);
std::string status_str(Status s);

#endif