#include "Semaphore.hpp"

#include <vector>

using namespace std;

struct Item {
    int id;
    int producerId;
    int payload;
};

class Buffer {
    vector<Item> items;
    
    Semaphore full;
    Semaphore empty;

    Semaphore mutexIn;
    Semaphore mutexOut;

    int nextIn;
    int nextOut;
    int size;
public:
    Buffer(int size);
    void add(Item i);
    Item get();
};

inline Buffer::Buffer(int size):
items(size) ,
full(size) ,
empty(0),
mutexIn(1),
mutexOut(1),
nextIn(0),
nextOut(0) { this-> size = size; }

inline void Buffer::add(Item i) {
    full.wait();

    int index;

    mutexIn.wait();

    index = nextIn;
    nextIn = (nextIn + 1)%size;

    mutexIn.signal();

    items[index] = i;

    empty.signal();
}

inline Item Buffer::get() {
    empty.wait();

    int index;
    Item tmp;

    mutexOut.wait();
    index = nextOut;
    nextOut = (nextOut + 1)%size;
    mutexOut.signal();

    tmp = items[index];

    full.signal();

    return tmp;
}
