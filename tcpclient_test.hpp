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

#ifndef TCPCLIENT_TEST_HPP
#define TCPCLIENT_TEST_HPP

#include "test_common.hpp"
#include "tcpclient.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>

void tcpclient_test() {
    // net_dns_resolve("localhost");
    // return;

    TcpClient tcp;
    Status s = tcp.Connect("localhost", "9990");
    if(s != STAT_OK) {
        printf("Conenct Err: %d\n", s);
        return;
    }

    while(true) {
        std::string line;
        std::cin >> line;
        std::cout << "Read Line: " << line << std::endl;
        
        Header header(PKG_REQUEST, ENCODING_JSON, line.size(), "test.hi");
        Bytes body(line.c_str(), line.size());
        Status s = tcp.Send(header, body);
        if(s != STAT_OK) {
            printf("Send error: %d\n", s);
        }
        std::cout << "Send: " << std::endl;
        std::cout << "\t => "; header_print(header);
        std::cout << "\t => "; bytes_print(body);
    }
}

#endif