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

#ifndef THREAD_HPP
#define THREAD_HPP

#include <thread>
#include <mutex>
#include <functional>
#include <queue>
#include <map>

class Thread;

class RemoveThread {
private:
    std::thread m_thread;
private:
    RemoveThread();
    ~RemoveThread();

friend class Thread;
};

class Thread {
public:
    typedef std::function<void()> ThreadFunc;

private:
    static std::mutex s_pendingsMutex;
    static std::mutex s_workingThreadMutex;
    static std::mutex s_daemonThreadMutex;

    static std::queue<ThreadFunc> s_pendings;
    static std::map<std::thread::id, std::thread*> s_workingThreads;
    static std::map<std::thread::id, std::thread*> s_daemonThreads;

    static std::queue<std::thread*> s_pendingRemoveThread;
    static RemoveThread s_removeThread;
public:
    static void Do(const ThreadFunc&);
    static void Daemon(const ThreadFunc&);
    static void Sleep(unsigned int millisecond);

friend class RemoveThread;
};

#endif
