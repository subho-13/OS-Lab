#include "Station.hpp"
#include "thread"
#include <signal.h>

Station *station;

void handler(int signal) {
    station->~Station();
    exit(1);
}

int main() {
    station = new Station("pstation");
    signal(SIGINT, handler);
    thread t1(&Station::addNodes, station);
    t1.detach();
    station->broadcast();
}