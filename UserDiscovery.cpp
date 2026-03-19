#include "UserDiscovery.h"
#include "Network/RawSocket.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>

namespace VanguardRecon
{
  UserDiscovery::UserDiscovery()
  {
    
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
    VanguardRecon::RawSocket RawSocket;
    RawSocket.OpenSocket(IPPROTO_ICMP);

  
    ICMPheader data = CraftEchoPacket();
    RawSocket.SendTo(&data,sizeof(data),ip);

    RawSocket.ReceiveFrom(&buffer,sizeof(buffer));
    
   
    int headerLength = (buffer[0] & 0x0F) * 4;

    ICMPheader* replay = (ICMPheader*)(buffer+headerLength);

    if(replay->type == 0 && ntohs(replay->id) == 123)
      return true;

    return false;
    

  }

  // ARPheader UserDiscovery::CraftArpPacket()
  // {
  //   ARPheader arpHeader;
  //   arpHeader.hardware = 1;
  //   arpHeader.protocol = 0x800;
  //   arpHeader.hardwareLength = 6;
  //   arpHeader.protocolLength = 4;
  //   arpHeader.operation = 1;
  // }
}
