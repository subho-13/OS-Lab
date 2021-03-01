#include "AdminPipe.hpp"
#include "UserPipe.hpp"
#include "Mutex.hpp"
#include <bits/stdint-uintn.h>
#include <cstdint>

class Station {
    AdminPipe cRegPipe;
    UserPipe regPipe;

    vector<UserPipe*> clientPipes;
    string fetchClient();
    Mutex mutex;
public:
    Station(string name);
    void addNodes();
    void broadcast();
};

inline Station::Station(string name):
cRegPipe(name), regPipe(name) {}

inline string Station::fetchClient() {
    vector<uint8_t> tmp(1);
    string clientName;

    while(true) {
        regPipe.receive(tmp);
        clientName.push_back(tmp[0]);
        if(tmp[0] == '\0') {
            break;
        }
    }

    return clientName;
}

inline void Station::addNodes() {
    string tmp;

    while(true) {
        tmp = fetchClient();

        mutex.lock();
        clientPipes.push_back(new UserPipe(tmp));
        mutex.unlock();
    }
}

inline void Station::broadcast() {
    vector<uint8_t> tmp(8);
    uint64_t counter = 0;

    while(true) {
        counter++;

        for(int i = 0; i < 8; i++) {
            tmp[i] = counter >> (i*8);
        }

        mutex.lock();

        for(int i = 0; i < clientPipes.size(); i++) {
            clientPipes[i]->send(tmp);
        }   

        mutex.unlock();

        cout << counter << " ->\n";
        sleep(2);
    }
}