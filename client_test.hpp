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
        cli.Notify("test.push", b);
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
        printf("OnPush-0: %s => %s\n", route.c_str(), b.Ptr());
    });

    cli.AddListener("test.push", [](const std::string& route, const Bytes& data){
        Bytes b(data);
        b.Write((unsigned char)0);
        printf("OnPush-1: %s => %s\n", route.c_str(), b.Ptr());
    });

    cli.Connect("10.0.75.1", "9999");

    while(true) {
        if( ! cli.IsConnected()) continue;

        std::string line;
        std::cin >> line;

        Bytes b(line);
        cli.Notify("test.push", b);
        cli.Request("test.request", b, [=](const std::string& route, const Bytes& data){
            Bytes b(data);
            b.Write((unsigned char)0);
            printf("Request callback: %s => %s\n", route.c_str(), b.Ptr());
        });
    }
}

#endif
