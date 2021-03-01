#include "UsrSem.hpp"
#include <cstdio>
#include <unistd.h>
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
        semx.wait();
        printf("Childx -> %d \n", i);
        i++;
        semy.signal();
    }
}