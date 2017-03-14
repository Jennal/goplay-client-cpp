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