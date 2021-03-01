#include "UserPipe.hpp"
#include "AdminPipe.hpp"

#include <bits/stdint-uintn.h>
#include <cstdio>
#include <fcntl.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    AdminPipe createPipe("9775701877");
    UserPipe pipe("9775701877");
    
    vector<uint8_t> transferUnit(1);


    while(true) {
        pipe.receive(transferUnit);
        if ((char)transferUnit[0] == EOF) {
            break;
        }

        cout << transferUnit[0];
    }

    transferUnit.push_back(EOF);
    pipe.send(transferUnit);
}