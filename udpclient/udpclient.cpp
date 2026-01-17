#include "udpclient.h"

#include <iostream>

UdpClient::UdpClient(const std::string &ip, const int port)
{
    if ((_descClient = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        std::cerr << "сокет" << std::endl;
        return;
    }

    struct in_addr addrServer;
    if (inet_aton(ip.c_str(), &addrServer) == 0)
    {
        std::cerr << "inet_aton" << std::endl;
        return;
    }
    _addrServer.sin_family = AF_INET;
    _addrServer.sin_port = htons(port);
    _addrServer.sin_addr.s_addr = addrServer.s_addr;

    _isOpen = true;
}

UdpClient::~UdpClient()
{
    if (_isOpen)
    {
        close(_descClient);
    }
}

ssize_t UdpClient::send(const std::string &data)
{
    if (!_isOpen)
    {
        return -1;
    }

    return sendto(_descClient, data.c_str(), data.size(), 0, reinterpret_cast<sockaddr*>(&_addrServer), sizeof(_addrServer));
}