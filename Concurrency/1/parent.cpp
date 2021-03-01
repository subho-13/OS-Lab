#include "AdminSem.hpp"
#include "Procreate.hpp"
#include <cstdio>

void handle(int sig) {
    printf("Waiting for child processes to end ... \n");
}

int main() {
    signal(SIGINT, handle);

    AdminSem semx("procx", 1);
    AdminSem semy("procy", 0);

    const char * child1 [2] = {"./childx", NULL};
    const char * child2 [2] = {"./childy", NULL};
    Procreate procreate1(child1);
    Procreate procreate2(child2);
}