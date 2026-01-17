/**
 * @file udpclient.h
 * @author your name (you@domain.com)
 * @brief Слиент udp
 * @version 0.1
 * @date 2026-01-17
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

class UdpClient
{
public:
    explicit UdpClient(const std::string& ip, const int port);
    ~UdpClient();

    ssize_t send(const std::string& data);

private: 
    struct sockaddr_in _addrServer;
    int _descClient = 0;
    bool _isOpen = false;
};