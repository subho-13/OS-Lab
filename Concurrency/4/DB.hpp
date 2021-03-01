#pragma once

#include "DBBlock.hpp"
#include <bits/stdint-uintn.h>
#include <cstdint>
#include <utility>

template<typename T>
class DB {
    vector<DBBlock<T>> dbblocks;
    uint64_t size;

    pair<uint64_t, uint64_t> mapVR(uint64_t index);
public:
    DB(uint64_t size);
    void write(uint64_t index, const T& item);
    void read(uint64_t index, T& item);
};

template<typename T>
DB<T>::DB(uint64_t size) {
    this->size = (size + SIZE-(size%SIZE))/SIZE;
    dbblocks.resize(this->size);
}

template<typename T>
pair<uint64_t, uint64_t> DB<T>::mapVR(uint64_t index) {
    return make_pair(index/SIZE, index%SIZE);
}

template<typename T>
void DB<T>::write(uint64_t index, const T &item) {
    pair<uint64_t, uint64_t> tmp;
    tmp = mapVR(index);

    dbblocks[tmp.first].write(tmp.second, item);
}

template<typename T>
void DB<T>::read(uint64_t index, T &item) {
    pair<uint64_t, uint64_t> tmp;
    tmp = mapVR(index);

    dbblocks[tmp.first].read(tmp.second, item);
}