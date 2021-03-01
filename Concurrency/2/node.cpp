#include "Node.hpp"
#include "thread"
#include <signal.h>

Node *node;

void handler(int signal) {
    node->~Node();
    exit(1);
}

int main(int argc, char **argv) {
    node = new Node(argv[1], "pstation");
    signal(SIGINT, handler);
    node->display();
}