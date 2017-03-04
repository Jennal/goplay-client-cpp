#ifndef CLIENT_TEST_HPP
#define CLIENT_TEST_HPP

#include "client.hpp"
#include <iostream>
#include <thread>

void client_test() {
    Client cli;
    cli.Connect("localhost", "9999");
    std::this_thread::sleep_for (std::chrono::seconds(10));
}

#endif
