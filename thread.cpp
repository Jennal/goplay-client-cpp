#include "thread.hpp"
#include <chrono>
#include <iostream>

#define MAX_THREAD 2

std::mutex Thread::s_pendingsMutex;
std::mutex Thread::s_workingThreadMutex;
std::mutex Thread::s_daemonThreadMutex;

std::queue<Thread::ThreadFunc> Thread::s_pendings;
std::map<std::thread::id, std::thread*> Thread::s_workingThreads;
std::map<std::thread::id, std::thread*> Thread::s_daemonThreads;

std::queue<std::thread*> Thread::s_pendingRemoveThread;
RemoveThread Thread::s_removeThread;

RemoveThread::RemoveThread() {
    m_thread = std::thread([](){
        while(true) {
            // std::cout << "s_removeThread before while: " << Thread::s_pendingRemoveThread.empty() << std::endl;
            while( ! Thread::s_pendingRemoveThread.empty()) {
                auto ptr = Thread::s_pendingRemoveThread.front();
                Thread::s_pendingRemoveThread.pop();
                // std::cout << "before delete ptr: " << ptr << std::endl;
                ptr->detach();
                delete ptr;
                // std::cout << "after delete ptr" << std::endl;
                break;
            }

            // std::cout << "s_removeThread after while: " << Thread::s_pendingRemoveThread.empty() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });
}

RemoveThread::~RemoveThread() {
    m_thread.detach();
}

void Thread::Do(const ThreadFunc& func) {
    s_pendingsMutex.lock();
    if(Thread::s_workingThreads.size() >= MAX_THREAD) {
        Thread::s_pendings.push(func);
        s_pendingsMutex.unlock();
        return;
    }
    s_pendingsMutex.unlock();

    auto th = new std::thread([=](){
        func();
        
        while( ! s_pendings.empty()) {
            s_pendingsMutex.lock();
            auto nextFunc = s_pendings.front();
            s_pendings.pop();
            s_pendingsMutex.unlock();
            nextFunc();
        }

        s_workingThreadMutex.lock();
        auto id = std::this_thread::get_id();
        auto iter = s_workingThreads.find(id);
        s_workingThreadMutex.unlock();
        while(iter == s_workingThreads.end()) {
            std::this_thread::sleep_for (std::chrono::seconds(1));
            s_workingThreadMutex.lock();
            iter = s_workingThreads.find(id);
            s_workingThreadMutex.unlock();
        }

        auto thPtr = iter->second;
        s_workingThreadMutex.lock();
        s_workingThreads.erase(iter);
        s_workingThreadMutex.unlock();
        s_pendingRemoveThread.push(thPtr);
    });

    auto id = th->get_id();
    s_workingThreadMutex.lock();
    s_workingThreads[id] = th;
    s_workingThreadMutex.unlock();
}

void Thread::Daemon(const ThreadFunc& func) {
    auto th = new std::thread([=](){
        // std::cout << "before func" << std::endl;
        func();
        
        // std::cout << "after func: " << std::this_thread::get_id() << std::endl;
        auto id = std::this_thread::get_id();
        // std::cout << "before find" << std::endl;
        s_daemonThreadMutex.lock();
        auto iter = s_daemonThreads.find(id);
        s_daemonThreadMutex.unlock();
        // std::cout << "after find" << std::endl;
        while(iter == s_daemonThreads.end()) {
            // std::cout << "find loop" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            s_daemonThreadMutex.lock();
            iter = s_daemonThreads.find(id);
            s_daemonThreadMutex.unlock();
        }

        // std::cout << "before remove" << std::endl;
        auto thPtr = iter->second;
        s_daemonThreadMutex.lock();
        s_daemonThreads.erase(iter);
        s_daemonThreadMutex.unlock();
        // std::cout << "after erase/before delete: " << id << " | " << thPtr << std::endl;
        s_pendingRemoveThread.push(thPtr);
        // std::cout << "after delete" << std::endl;
    });

    s_daemonThreadMutex.lock();
    auto id = th->get_id();
    s_daemonThreads[id] = th;
    s_daemonThreadMutex.unlock();
    // std::cout << "deamon map: " << id << " | " << th << std::endl;
}
