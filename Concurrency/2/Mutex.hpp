#pragma once

#include "Semaphore.hpp"

class Mutex {
    Semaphore sem;
public:
    Mutex();
    void lock();
    void unlock();
};

inline Mutex::Mutex():sem(1) {}

inline void Mutex::lock() {
    sem.wait();
}

inline void Mutex::unlock() {
    sem.signal();
}