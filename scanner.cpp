#include "scanner.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace VanguardRecon{

  Scanner::Scanner(const ScanConfig& scanConfig)
  :scanConfig(scanConfig) {}

 Scanner::~Scanner()
 {

 }
 std::vector<scanResult> Scanner::ScanPorts(const std::string& ip)
 {
   std::vector<scanResult> scanresults;
   for (size_t i = scanConfig.startPort; i <= scanConfig.endPort; i++) {

     int sock = socket(AF_INET,SOCK_STREAM,0);
      
    
   struct timeval timeout;
   timeout.tv_sec = 2;
   timeout.tv_usec = 0;
   setsockopt(sock,SOL_SOCKET,SO_SNDTIMEO,&timeout,sizeof(timeout));


     struct sockaddr_in client;
     client.sin_family = AF_INET;
     client.sin_port = htons(i);
     inet_pton(AF_INET,ip.c_str(),&client.sin_addr);
     
     int result = connect(sock,(struct sockaddr*)&client,sizeof(client));

     struct scanResult scanresult;
     scanresult.port = i;

     if(result == 0)
     {
       scanresult.openStatus = true;
       scanresult.banner = grabBanner(sock);
     }
     else
     {
       scanresult.openStatus = false;
     }
     scanresults.push_back(scanresult);
     close(sock);
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
   std::string IP;
   subnetIP = "10.0.0.";
   for(int i{0}; i < 256; i++)
   {
     IP = subnetIP+(std::to_string(i));
     std::vector<scanResult> scanresults = ScanPorts(IP);
     for(auto result : scanresults) {
       if(result.openStatus)
         std::cout << result.port;
     }
     

   }
 }
}

  
    

