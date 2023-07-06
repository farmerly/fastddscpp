#pragma once

#include <condition_variable>
#include <list>
#include <mutex>

template <typename T>
class DDSSynchronizedQueue
{
    DDSSynchronizedQueue()
    {
        m_stopFlag = false;
    }

    ~DDSSynchronizedQueue()
    {
    }

public:
    void enqueue(const T &data)
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        m_queue.push(data);
        m_cond.notify_one();
    }

    bool dequeue(T &data, bool nonblock = false)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        while (!nonblock && m_queue.size() == 0) {
            m_cond.wait(lock);
            if (m_stopFlag) {
                break;
            }
        }
        if (m_queue.size()) {
            data = m_queue.front();
            m_queue.pop();
        }
        return true;
    }

    void stop()
    {
        m_stopFlag = true;
        m_cond.notify_all();
    }

private:
    bool m_stopFlag;
    std::list<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cond;
};