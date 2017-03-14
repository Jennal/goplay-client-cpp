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

#ifndef CLIENT_TEST_HPP
#define CLIENT_TEST_HPP

#include "Thread.hpp"
#include "client.hpp"
#include <iostream>
#include <cstdio>
#include <thread>
#include <cstring>

void client_test() {
    Client cli([=](Client& cli){
        printf("Connected!\n");

        Bytes b("Hello");
        // cli.Notify("test.handler.test", b);
    }, [=](Client& cli){
        printf("onConnectRetry!\n");
    }, [=](Client& cli, Status s){
        printf("Connecte Failed: %d!\n", s);
    }, [=](Client& cli){
        printf("Disconnected!\n");
    });
    cli.AddListener("test.push", [](const std::string& route, const Bytes& data){
        Bytes b(data);
        b.Write((unsigned char)0);
        printf("OnPush-0: %s => %s\n", route.c_str(), (char*)b.Ptr());
    });

    cli.AddListener("test.push", [](const std::string& route, const Bytes& data){
        Bytes b(data);
        b.Write((unsigned char)0);
        printf("OnPush-1: %s => %s\n", route.c_str(), (char*)b.Ptr());
    });

    cli.Connect("10.0.75.1", "9999");

    while(true) {
        if( ! cli.IsConnected()) continue;

        std::string line;
        std::cin >> line;

        Bytes b("\""+line+"\"");
        cli.Notify("test.handler.test", b);

        Bytes n("1");
        cli.Request("test.handler.add", n, [=](const std::string& route, const Bytes& data){
            Bytes b(data);
            b.Write((unsigned char)0);
            printf("[Success] Request callback: %s => %s\n", route.c_str(), (char*)b.Ptr());
        }, [=](const std::string& route, const Bytes& data){
            Bytes b(data);
            b.Write((unsigned char)0);
            printf("[Failed] Request callback: %s => %s\n", route.c_str(), (char*)b.Ptr());
        });
    }
}

#endif
