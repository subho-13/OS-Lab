#pragma once

#include "Semaphore.hpp"
#include "Mutex.hpp"
#include "Switch.hpp"
#include <bits/stdint-uintn.h>
#include <vector>
#include "Error.hpp"

using namespace std;

int SIZE = 16;

template <typename T>
class DBBlock {
    vector<T> items;
    Mutex readers;
    Mutex writers;
    Switch readSwitch;
    Switch writeSwitch;
public:
    DBBlock();
    void write(uint64_t index, const T& item);
    void read (uint64_t index, T& item) ;
};

template <typename T>
inline DBBlock<T>::DBBlock():items(SIZE) {}

template <typename T>
inline void DBBlock<T>::read(uint64_t index, T &item) {
    if(index >= SIZE) {
        Error e;
        e.className = "DBBlock";
        e.funcName = "read";
        e.problem = "Out of index";
    }

    readers.lock();
        readSwitch.lock(writers);
    readers.unlock();
    
    item = items[index];

    readSwitch.unlock(writers);
}

template <typename T>
inline void DBBlock<T>::write(uint64_t index, const T &item) {
    if(index >= SIZE) {
    Error e;
    e.className = "DBBlock";
    e.funcName = "read";
    e.problem = "Out of index";
    }
    
    writeSwitch.lock(readers);

    writers.lock();
    items[index] = item;
    writers.unlock();

    writeSwitch.unlock(readers);
}