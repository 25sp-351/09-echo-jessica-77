#include "tcp_echo.h"
#include <iostream>
#include <csignal>

EchoServer* server = nullptr;

void signal_handler(int) {
    if (server) server->stop();
}

int main(int argc, char* argv[]) {
    int port = 2345;
    bool verbose = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-p" && i+1 < argc) port = std::stoi(argv[++i]);
        else if (arg == "-v") verbose = true;
    }

    EchoServer es(port, verbose);
    server = &es;
    
    std::signal(SIGINT, signal_handler);

    es.start();
    return 0;
}