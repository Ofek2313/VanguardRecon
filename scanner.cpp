
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "HostDiscovery.h"
#include <thread>
#include <mutex>
#include "scanner.h"

namespace VanguardRecon
{

  Scanner::Scanner(const ScanConfig& scanConfig)
  :scanConfig(scanConfig) {}

 Scanner::~Scanner()
 {

 }
      
 void Scanner::OutputScanResults(std::vector<scanResult> scanResults)
 {
  for(scanResult result : scanResults)
  {
    if(result.openStatus)
      std::cout<< result.port <<"# " << result.banner << "\n";
  }
 }
 void Scanner::ScanPort(const std::string& ip, int port, std::vector<scanResult>* scanResults)
 {
    int sock = socket(AF_INET,SOCK_STREAM,0);
    
     struct sockaddr_in client;
     client.sin_family = AF_INET;
     client.sin_port = htons(port);
     inet_pton(AF_INET,ip.c_str(),&client.sin_addr);
     
   struct timeval timeout;
   timeout.tv_sec = 2;
   timeout.tv_usec = 0;
   setsockopt(sock,SOL_SOCKET,SO_SNDTIMEO,&timeout,sizeof(timeout));

     int result = connect(sock,(struct sockaddr*)&client,sizeof(client));

     
     struct scanResult scanresult;
     scanresult.port = port;

     if(result == 0)
     {
       scanresult.openStatus = true;
       scanresult.banner = grabBanner(sock);
       
     }
     else
     {
       scanresult.openStatus = false;
     }
     close(sock);
     std::lock_guard<std::mutex> sockLock(portMutex);
     (*scanResults).push_back(scanresult);
     
 }

 std::vector<scanResult> Scanner::ScanPorts(const std::string& ip)
 {
   std::vector<scanResult> scanresults;
   std::vector<std::thread> threads;

   for (size_t i = scanConfig.startPort; i <= scanConfig.endPort; i++) {
      threads.emplace_back(std::thread(&Scanner::ScanPort,this,ip,i,&scanresults));
    
   }
   for(std::thread& thread : threads)
   {
    thread.join();
   }

   return scanresults;
 }
 std::string Scanner::grabBanner(int sock)
 {

   struct timeval timeout;
   timeout.tv_sec = 2;
   timeout.tv_usec = 0;
   setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));

   char buffer[1024];
   std::string banner;

   ssize_t bytes = recv(sock,buffer,sizeof(buffer),0);
   if(bytes > 0)
      banner.append(buffer,bytes);

   return banner;
 }

 void Scanner::ScanLocalNetwork()
 {
    HostDiscovery userDiscovery;
    bool result = userDiscovery.PingHost(scanConfig.ip);
    std::cout<<result;
    if(result)
        OutputScanResults(ScanPorts(scanConfig.ip));

 }
}

  
    

