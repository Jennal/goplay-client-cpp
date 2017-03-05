#ifndef THREAD_TEST_HPP
#define THREAD_TEST_HPP

#include <iostream>
#include <cstdio>
#include <thread>
#include "thread.hpp"

void thread_test() {
    printf("main thread[%p]\n", std::this_thread::get_id());

    Thread::Daemon([](){
        for(int i=0; i<10; ++i) {
            printf("in daemon func[%p]: %d\n", std::this_thread::get_id(), i);
        }
    });

    for(int i=0; i<10; ++i) {
        Thread::Do([i](){
            printf("in do func[%p]: %d\n", std::this_thread::get_id(), i);
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
}

#endif