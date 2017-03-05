#ifndef CLIENT_TEST_HPP
#define CLIENT_TEST_HPP

#include "Thread.hpp"
#include "client.hpp"
#include <iostream>
#include <cstdio>
#include <thread>

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
        printf("OnPush: %s => %s\n", route.c_str(), data.Ptr());
    });
    cli.Connect("localhost", "9999");

    while(true) {
        if( ! cli.IsConnected()) continue;

        std::string line;
        std::cin >> line;

        Bytes b(line);
        cli.Notify("test.push", b);
    }
}

#endif
