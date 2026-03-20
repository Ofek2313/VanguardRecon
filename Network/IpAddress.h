#pragma once
#include <string>
#include <cstdint>
#include <arpa/inet.h>

namespace VanguardRecon
{
    class IpAddress
    {
        public:
            explicit IpAddress(const std::string& ip);
            bool operator==(const IpAddress& other) const;
            std::string ToString(uint32_t ip);
            sockaddr_in ToSockAddr() const;
        private:
            uint32_t m_ipAddress;
    };
}