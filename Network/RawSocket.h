#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstdint>
#include <unistd.h>
#include <string>
#include "IpAddress.h"

namespace VanguardRecon
{


    class RawSocket
    {
        public:
            RawSocket();
            ~RawSocket();

            bool OpenSocket(int protocol);
            ssize_t SendTo(const void* data,size_t length,const IpAddress& destIp);
            ssize_t ReceiveFrom(void* buffer,size_t length);
            
        private:
            int m_sockfd;

    };
}