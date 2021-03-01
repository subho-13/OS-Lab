#include <bits/stdint-uintn.h>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <thread>
#include <random>
#include <atomic>
#include <chrono>
#include <signal.h>
#include "Buffer.hpp"

using namespace std;

Semaphore print(1);

atomic<uint64_t> numTransfers(0);
chrono::high_resolution_clock::time_point start;


void producer(int id, shared_ptr<Buffer> buffer) {
    Item tmp;
    int i = 0;
    while(true) {
        tmp.id = i;
        i++;
        tmp.producerId = id;
        tmp.payload = i*2;
        buffer->add(tmp);
    }
}

void consumer(int id, shared_ptr<Buffer> buffer) {
    Item tmp;
    while(true) {
        tmp = buffer->get();
        print.wait();
        printf("%d, %d, %d, %d \n", id, tmp.id, tmp.producerId, tmp.payload);
        print.signal();
        numTransfers++;
    }
}

void handle(int sig) {
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    uint64_t nanosecs = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
    uint64_t tmp = numTransfers;
    print.wait();
    printf("%lu,%lu\n", tmp, nanosecs);
    print.signal();
    exit(1);
}

int main(int argc, char** argv) {
    int numProducers = stoi(argv[1]);
    int numConsumers = stoi(argv[2]);
    int buffSize = stoi(argv[3]);

    if (numConsumers == 0 || numProducers == 0 || buffSize == 0) {
        printf("Incorrect parameters \n");
        exit(0);
    }

    signal(SIGINT, handle);

    vector<thread> producers;
    vector<thread> consumers;
    Buffer buffer(buffSize);

    shared_ptr<Buffer> ptr(&buffer);

    for(int id = 1; id <= numProducers; id++) {
        producers.push_back(thread(&producer, id, ptr));
    }

    start = chrono::high_resolution_clock::now();

    for(int id = 1; id <= numConsumers; id++) {
        consumers.push_back(thread(&consumer, id, ptr));
    }

    for(int id = 1; id <= numProducers; id++) {
        producers[id-1].join();
    }

    for(int id = 1; id <= numConsumers; id++) {
        consumers[id-1].join();
    }


}