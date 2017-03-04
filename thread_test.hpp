#ifndef THREAD_TEST_HPP
#define THREAD_TEST_HPP

#include <iostream>
#include "thread.hpp"

void thread_test() {
    Thread::Daemon([](){
        for(int i=0; i<10; ++i) {
            std::cout << "in daemon func: " << i << std::endl;
        }
    });

    for(int i=0; i<10; ++i) {
        Thread::Do([i](){
            std::cout << i << std::endl;
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
}

#endif