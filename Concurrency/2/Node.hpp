#include "UserPipe.hpp"
#include "AdminPipe.hpp"
#include <bits/stdint-uintn.h>
#include <cstdint>
#include <string>
#include <iostream>

class Node {
    AdminPipe cPipe;
    UserPipe  pipe;
public:
    Node(string name, string station);
    void display();
};

inline Node::Node(string name, string station) :
cPipe(name), pipe(name) {
    UserPipe regPipe(station);
    vector<uint8_t> tmp;

    for(char c: name) {
        tmp.push_back(c);
    }

    tmp.push_back('\0');

    regPipe.send(tmp);
}

inline void Node::display() {
    vector<uint8_t> tmp(8);
    int counter = 0;
    while(true) {
        pipe.receive(tmp);

        counter = 0;
        for(int i = 0; i < 7; i++) {
            counter |= (tmp[i] << (i*8));
        }

        cout << "-> " << counter << "\n";
    }
}