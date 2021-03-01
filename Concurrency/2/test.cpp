#include "AdminPipe.hpp"
#include "UserPipe.hpp"
#include <bits/stdint-uintn.h>
#include <fcntl.h>
#include <iostream>

using namespace std;

int main() {
    AdminPipe adminPipe("testme");
    UserPipe pipe1("testme");
    UserPipe pipe2("testme");

    vector<uint8_t> tmp(1);
    tmp[0] = 'a';

    for(int i = 0; i < 10; i++) {
        cout << tmp[0] << "\n";
        pipe1.send(tmp);
        pipe2.receive(tmp);
        cout << tmp[0] << "\n";
        tmp[0]++;
    }
}