#pragma once
#include <string>
#include <cstdint>

namespace VanguardRecon
{

  struct ICMPheader
  {
    uint8_t type;
    uint8_t code;
    uint16_t checkSum;
    uint16_t id;
    uint16_t sequence;

  };
  
  class UserDiscovery
  {
    public:
      bool PingHost(const std::string& ip);
      UserDiscovery();
    private:
      uint16_t CalculateCheckSum(const void* data, size_t len);
      ICMPheader CraftEchoPacket();
  };
}
