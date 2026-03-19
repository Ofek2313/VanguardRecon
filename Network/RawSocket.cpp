#include "RawSocket.h"
#include <stdexcept>

namespace VanguardRecon
{
    RawSocket::RawSocket()
    {
        m_sockfd = -1;
    }
    
    RawSocket::~RawSocket()
    {
        if(m_sockfd >= 0)
            close(m_sockfd);
    }

    bool RawSocket::OpenSocket(int protocol)
    {
        m_sockfd = socket(AF_INET,SOCK_RAW,protocol);
        return m_sockfd >= 0;
    }

    ssize_t RawSocket::SendTo(const void* data,size_t length,const std::string& destIp)
    {
        struct sockaddr_in dest;
        dest.sin_family = AF_INET;
        inet_pton(AF_INET,destIp.c_str(),&dest.sin_addr);

        socklen_t destLen = sizeof(dest);
        ssize_t bytesSent = sendto(m_sockfd,data,length,0,(struct sockaddr*)&dest,sizeof(dest));
        if(bytesSent < 0)
            throw std::runtime_error("Send To Failed");
        return bytesSent;
    }

    ssize_t RawSocket::ReceiveFrom(void* buffer,size_t length)
    {
        struct sockaddr_in src {};
        socklen_t srcLen = sizeof(src);
        ssize_t bytesRecv = recvfrom(m_sockfd,buffer,length,0,(struct sockaddr*)&src,&srcLen);
        if(bytesRecv < 0)
            throw std::runtime_error("Receive To Failed");
        return bytesRecv;
        
        
    }
}