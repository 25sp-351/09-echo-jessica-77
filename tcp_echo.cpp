#include "tcp_echo.h"
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// constrctor 
EchoServer::EchoServer(int port, bool verbose) 
    : port_(port), verbose_(verbose) {}

void EchoServer::start() {
    server_sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock_ < 0) {
        std::cerr << "Socket creation failed\n";
        return;
    }

    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port_);

    if (bind(server_sock_, (sockaddr*)&addr, sizeof(addr))) {
        std::cerr << "Bind failed\n";
        return;
    }

    if (listen(server_sock_, 5)) {
        std::cerr << "Listen failed\n";
        return;
    }

    running_ = true;
    std::cout << "Server started on port " << port_ << "\n";

    while (running_) {
        int client = accept(server_sock_, nullptr, nullptr);
        if (client < 0) continue;
        
        if (verbose_) std::cout << "\nNew connection\n";
        handle_client(client);
    }
}

void EchoServer::handle_client(int client_sock) {
    char buffer[1024];
    while (true) {
        int bytes = read(client_sock, buffer, sizeof(buffer));
        if (bytes <= 0) break;
        write(client_sock, buffer, bytes);
        if (verbose_) std::cout << "Echoed: " << std::string(buffer, bytes);
    }
    close(client_sock);
}

void EchoServer::stop() {
    running_ = false;
    close(server_sock_);
}