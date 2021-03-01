#include "UsrSem.hpp"
#include <cstdio>
#include <signal.h>

void handle(int sig) {
    exit(1);
}

int main() {
    signal(SIGINT, handle);
    
    UsrSem semx("procx");
    UsrSem semy("procy");

    int i = 0;
    while(true) {
        semy.wait();
        printf("Childy -> %d \n", i);
        i++;
        semx.signal();
    }
}