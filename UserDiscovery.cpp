#include "UserDiscovery.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>

namespace VanguardRecon
{
  UserDiscovery::UserDiscovery()
  {
    PingHost("127.0.0.1");
  }

  uint16_t UserDiscovery::CalculateCheckSum(const void* data, size_t len)
  {
    const uint16_t* ptr = (const uint16_t*)data;
    uint32_t sum = 0;
    while(len > 1)
    {
      sum += *ptr;
      ptr++;
      len-=2;
    }
    if(len==1)
      sum+= *(uint8_t*)ptr;

    while((sum >> 16) > 0)
      sum = (sum & 0xFFFF) + (sum>>16);

    return (uint16_t)~sum;
  }
  ICMPheader UserDiscovery::CraftEchoPacket()
  {
    ICMPheader header;
    header.type = 0x8;
    header.code = 0x0;
    header.checkSum = 0x0;
    header.sequence = htons(1);
    header.id = htons(123);

    header.checkSum = UserDiscovery::CalculateCheckSum(&header,sizeof(header));
    
    return header;
  }
  bool UserDiscovery::PingHost(const std::string& ip)
  {
    char buffer[1024];
    int sock = socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
    ICMPheader data = CraftEchoPacket();
    struct sockaddr_in client;
    client.sin_family = AF_INET;
    inet_pton(AF_INET,ip.c_str(),&client.sin_addr);

    socklen_t destLen = sizeof(client);
    sendto(sock,&data,sizeof(data),0,(struct sockaddr*)&client,sizeof(client));
    
    recvfrom(sock,&buffer,sizeof(buffer),0,(struct sockaddr*)&client,&destLen);

    ICMPheader* replay = (ICMPheader*)(buffer+20);

    if(replay->type == 0)
    {
      close(sock);
      std::cout<<"OK"<<"\n";
      return true;
    }
    close(sock);
    return false;

  }
}
