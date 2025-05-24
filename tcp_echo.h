#ifndef TCP_ECHO_H
#define TCP_ECHO_H

#include <string>

class EchoServer {
public:
    EchoServer(int port = 2345, bool verbose = false);
    void start();
    void stop();

private:
    void handle_client(int client_sock);
    
    int port_;
    bool verbose_;
    int server_sock_ = -1;
    bool running_ = false;
};

#endif // TCP_ECHO_Hq