#pragma once
#include <string>
#include <vector>
#include <thread>
#include <mutex>

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
     void OutputScanResults(std::vector<scanResult> scanResults);
      Scanner(const ScanConfig& scanConfig);
      ~Scanner();

    private:
      std::mutex portMutex;
      void ScanPort(const std::string& ip, int port, std::vector<scanResult>* scanResults);
      std::string grabBanner(int sock);
      ScanConfig scanConfig;
      std::string subnetIP;
     


  };


}
