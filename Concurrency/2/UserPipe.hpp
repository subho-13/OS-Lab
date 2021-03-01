#include <bits/stdint-uintn.h>
#include <fcntl.h>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

class UserPipe {
    int fd;
public:
    UserPipe(string name);
    void send(const vector<uint8_t>& bytes);
    void receive(vector<uint8_t>& bytes);
    ~UserPipe();
};

inline UserPipe::UserPipe(string name) {
    fd = open(name.c_str(), O_RDWR);
    if(fd == -1) {
        throw "error";
    }
}

inline void UserPipe::send(const vector<uint8_t> &bytes) {
    if (write(fd, (void *)bytes.data(), bytes.size()) != bytes.size()) {
        throw "error";
    }
}

inline void UserPipe::receive(vector<uint8_t> &bytes) {
    read(fd, (void *)bytes.data(), bytes.size());
}

inline UserPipe::~UserPipe() {
    close(fd);
}