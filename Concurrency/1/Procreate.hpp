#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "Error.hpp"

class Procreate {
    pid_t childPid;
public:
    Procreate(const char* args[]) {
        switch(childPid = fork()) {
            case -1: {
                Error e;
                e.className = "Procreate";
                e.funcName = "Constructor";
                e.problem = "Cannot fork";

                throw e;
            }

            case 0:
                execv(args[0], const_cast<char* const *>(args));
                exit(127);
        }
    }

    ~Procreate() {
        waitpid(childPid, 0, 0);
    }
};