#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "scanner.h"
#include "HostDiscovery.h"

int main(int argc, char* argv[])
{

  VanguardRecon::ScanConfig scanConfig{1,1000,argv[1]};
  VanguardRecon::Scanner scanner(scanConfig);
  // std::vector<VanguardRecon::scanResult> results = scanner.ScanPorts(argv[1]);
  // for(auto var : results) {
  //   if(var.openStatus)
  //      std::cout<< "#" <<var.port<< ": " << var.openStatus << var.banner << "\n";
  // }
  VanguardRecon::HostDiscovery UserDisocvery;
  scanner.ScanLocalNetwork();
  
 
  
  

  
    

}
