#ifndef THREAD_TEST_HPP
#define THREAD_TEST_HPP

#include <cstdio>
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int count = 0;

void endless() {
    int i=0;
    while(i < 2) printf("i = %d\n", i++);
}

void inc() {
    std::lock_guard<std::mutex> lck(mtx);

    ++count;
    std::cout << count << std::endl;
}

void thread_test() {
    std::thread t(endless);
    std::cout << t.joinable() << std::endl;
    t.detach();
    std::cout << t.joinable() << std::endl;

    std::thread threads[10];
    for(int i=0; i<10; ++i) {
        threads[i] = std::thread(inc);
    }

     for (auto& th : threads) th.join();
}

#endif