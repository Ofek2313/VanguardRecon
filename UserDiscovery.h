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
  struct ARPheader
  {
    uint16_t hardware;
    uint16_t protocol;
    uint8_t hardwareLength;
    uint8_t protocolLength;
    uint16_t operation;
    uint8_t senderHardwareAddress[6];
    uint8_t senderProtocolAddress[4];
    uint8_t targetHardwareAddress[6];
    uint8_t targetProtocolAddress[4];

  };
  class UserDiscovery
  {
    public:
      bool PingHost(const std::string& ip);
      UserDiscovery();
    private:
      uint16_t CalculateCheckSum(const void* data, size_t len);
      ICMPheader CraftEchoPacket();
      // ARPheader CraftArpPacket();
  };
}
