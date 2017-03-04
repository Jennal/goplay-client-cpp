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

friend class RemoveThread;
};

#endif
