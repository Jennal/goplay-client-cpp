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