#pragma once

#include "Mutex.hpp"
#include "Semaphore.hpp"
#include <bits/stdint-uintn.h>

class Switch {
    Mutex mutex;
    uint64_t counter;
public:
    Switch();
    void lock(Mutex &hold);
    void unlock(Mutex &hold);
};

inline Switch::Switch() { counter = 0; }

inline void Switch::lock(Mutex &hold) {
    mutex.lock();
    counter++;

    if(counter == 1) {
        hold.lock();
    }

    mutex.unlock();
}

inline void Switch::unlock(Mutex &hold) {
    mutex.lock();
    counter--;

    if(counter == 0) {
        hold.unlock();
    }

    mutex.unlock();
}