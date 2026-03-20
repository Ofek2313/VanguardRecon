#include "IpAddress.h"
#include <stdexcept>

namespace VanguardRecon
{
    IpAddress::IpAddress(const std::string& ip)
    {
        in_addr addr{};
        inet_pton(AF_INET,ip.c_str(),&addr);
        m_ipAddress = addr.s_addr;
    }
    std::string IpAddress::ToString(uint32_t ip)
    {
        in_addr addr{};
        addr.s_addr = ip;
        char buffer[16];
        if(inet_ntop(AF_INET,&addr,buffer,sizeof(buffer)) == nullptr)
            throw std::runtime_error("Failed To Convert");

        return std::string(buffer);
    }
    bool IpAddress::operator==(const IpAddress& other) const
    {
        return other.m_ipAddress == this->m_ipAddress;
    }
    sockaddr_in IpAddress::ToSockAddr() const
    {
         struct sockaddr_in sockaddr;
        sockaddr.sin_family = AF_INET;
        sockaddr.sin_addr.s_addr = m_ipAddress;
        return sockaddr;
    }
}