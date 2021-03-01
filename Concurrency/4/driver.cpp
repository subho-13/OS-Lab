#include "DB.hpp"
#include "Semaphore.hpp"
#include <bits/stdint-uintn.h>
#include <csignal>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <thread>
#include <chrono>
#include <random>
#include <atomic>

using namespace std;
uint64_t dbsize = 64;

Mutex read;
Mutex write;
Mutex output;
Semaphore waitToEnd(0);

uint64_t throughput = 0;
uint64_t latency = 0;

void reader(DB<uint64_t>* db) {
    minstd_rand0 generator(random_device{}());
    uint64_t tmp, index;
    auto id = this_thread::get_id();
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point end;
    while(true) {
        index = generator()%dbsize;
        start = chrono::high_resolution_clock::now();
        db->read(index, tmp);
        end = chrono::high_resolution_clock::now();
        output.lock();
        cout << id << ":  "<<  "Read " << tmp << " at index " << index << "\n";
        output.unlock();
        read.lock();
        throughput = throughput + (end-start).count();
        throughput /= 2;
        read.unlock();
    }
} 

void writer(DB<uint64_t>* db) {
    minstd_rand0 generator(random_device{}());
    uint64_t tmp, index;
    auto id  = this_thread::get_id();
    tmp = generator()%dbsize;
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point end;
    while(true) {
        index = generator()%dbsize;
        start = chrono::high_resolution_clock::now();
        db->write(index, tmp);
        end = chrono::high_resolution_clock::now();
        output.lock();
        cout << id << ":  "<<  "Written " << tmp << " at index " << index << "\n";
        output.unlock();
        write.lock();
        latency = latency + (end-start).count();
        latency /= 2;
        write.unlock();
        tmp++;
    }
}

void handle(int sig) {
    output.lock();
    printf("throughput = %lu ns, latency = %lu ns \n", throughput, latency);
    output.unlock();
    exit(1);
}

/* 
 *Input should be of format :: 
 *(./driver numReaders, numWriters, blocksize, databasesize) 
 */

int main(int argc, char ** argv) {
    signal(SIGINT, handle);
    vector<thread> threads;

    int numWriters = stoi(argv[1]);
    int numReaders = stoi(argv[2]);
    SIZE = stoi(argv[3]);
    dbsize = stoi(argv[4]);

    DB<uint64_t> db(dbsize);

    for(int i = 0; i < numWriters; i++) {
        threads.push_back(thread(writer, &db));
    }

    this_thread::sleep_for(chrono::seconds(1));

    for(int i = 0; i < numReaders; i++) {
        threads.push_back(thread(reader, &db));
    }

    waitToEnd.wait();
}
