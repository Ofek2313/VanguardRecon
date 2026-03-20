#include "HostDiscovery.h"

#include "Network/IpAddress.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>

namespace VanguardRecon
{
  HostDiscovery::HostDiscovery()
  {
    m_socket.OpenSocket(IPPROTO_ICMP);
  }
  
  uint16_t HostDiscovery::CalculateCheckSum(const void* data, size_t len)
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
  ICMPheader HostDiscovery::CraftEchoPacket()
  {
    ICMPheader header;
    header.type = 0x8;
    header.code = 0x0;
    header.checkSum = 0x0;
    header.sequence = htons(1);
    header.id = htons(123);

    header.checkSum = HostDiscovery::CalculateCheckSum(&header,sizeof(header));
    
    return header;
  }
  bool HostDiscovery::PingHost(const std::string& ip)
  {
    char buffer[1024];
    IpAddress Ip(ip);
    VanguardRecon::RawSocket RawSocket;

    

  
    ICMPheader data = CraftEchoPacket();
    m_socket.SendTo(&data,sizeof(data),Ip);

    m_socket.ReceiveFrom(&buffer,sizeof(buffer));
    
   
    int headerLength = (buffer[0] & 0x0F) * 4;
    uint8_t TTL = buffer[8];
    ICMPheader* replay = (ICMPheader*)(buffer+headerLength);

    if(replay->type == 0 && ntohs(replay->id) == 123)
    {
        std::cout<<(int)TTL;
        return true;
        
    }
      

    return false;
    

  }
  std::vector<IpAddress> HostDiscovery::AliveHostDiscovery()
  {
    std::vector<IpAddress> IpAddresses;
    for (size_t i = 1; i < 254; i++)
    {
      if(PingHost("10.0.0." + std::to_string(i)))
      {
        IpAddresses.push_back(IpAddress("10.0.0." + std::to_string(i)));
        std::cout<<"10.0.0." + std::to_string(i) << '\n';

      }

    }
    return IpAddresses;
  }

  // ARPheader HostDiscovery::CraftArpPacket()
  // {
  //   ARPheader arpHeader;
  //   arpHeader.hardware = 1;
  //   arpHeader.protocol = 0x800;
  //   arpHeader.hardwareLength = 6;
  //   arpHeader.protocolLength = 4;
  //   arpHeader.operation = 1;
  // }
}
