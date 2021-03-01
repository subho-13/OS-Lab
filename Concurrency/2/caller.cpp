#include "UserPipe.hpp"
#include <bits/stdint-uintn.h>
#include <cstdio>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    UserPipe pipe("9775701877");
    fstream file("story.txt", ios::in);
    
    string tmp;
    vector<uint8_t> transferUnit;


    while(!file.eof()) {
        file >> tmp;
        cout << tmp;
        for(char c: tmp) {
            transferUnit.push_back(c);
        }

        pipe.send(transferUnit);
        transferUnit.clear();
    }

    transferUnit.push_back(EOF);
    pipe.send(transferUnit);
}