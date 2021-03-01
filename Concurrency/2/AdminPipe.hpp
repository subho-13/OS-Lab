#include <bits/stdint-uintn.h>
#include <fcntl.h>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;
class AdminPipe {
    string name;
public:
    AdminPipe(string name);
    ~AdminPipe();
};

inline AdminPipe::AdminPipe(string name) {
    this->name = name;
    mkfifo(name.c_str(), S_IRUSR|S_IWUSR);
}

inline AdminPipe::~AdminPipe() {
    unlink(name.c_str());
}