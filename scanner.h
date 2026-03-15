#pragma once
#include <string>
#include <vector>

namespace VanguardRecon
{

  struct scanResult
  {
    int port;
    bool openStatus;
    std::string banner;
  };

  struct ScanConfig
  {
    int startPort;
    int endPort;
    std::string ip;
  };

  class Scanner
  {
    public:
      void ScanLocalNetwork();
      std::vector<scanResult> ScanPorts(const std::string& ip);
      scanResult ScanPort(int port); 
      Scanner(const ScanConfig& scanConfig);
      ~Scanner();

    private:
      std::string grabBanner(int sock);
      ScanConfig scanConfig;
      std::string subnetIP;
  };


}
