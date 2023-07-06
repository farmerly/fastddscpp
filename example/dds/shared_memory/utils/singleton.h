#ifndef _SINGLETON_H_H_H
#define _SINGLETON_H_H_H

#include <mutex>

template <typename T>
class Singleton
{
protected:
    Singleton() noexcept(true){};
    ~Singleton() noexcept(true){};

private:
    Singleton(const Singleton &signleton){};
    const Singleton &operator=(const Singleton &signleton){};

public:
    static T *getInstance()
    {
        if (_instance == nullptr) {
            std::lock_guard<std::mutex> guard(_mutex);
            if (_instance == nullptr) {
                _instance = new T();
            }
        }
        return _instance;
    };

    static void destroy()
    {
        if (_instance != nullptr) {
            std::lock_guard<std::mutex> guard(_mutex);
            if (_instance != nullptr) {
                delete _instance;
            }
            _instance = nullptr;
        }
    }

private:
    static T *_instance;
    static std::mutex _mutex;
};

template <typename T>
T *Singleton<T>::_instance = nullptr;

template <typename T>
std::mutex Singleton<T>::_mutex;

#endif // _SINGLETON_H_H_H