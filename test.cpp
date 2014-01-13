#include <iostream>

using namespace std;

int main()
{
   cout << "Test Cmake" << endl;
}
/*
#include "daemon/daemon.hpp"

int main()
{
   using namespace std;
   try
   {
      vsd::daemon::Daemon d{vsd::daemon::DAEMON_FLAG::NONE};
      cout << "session : " << d.getSessionPid() << endl;
      cout << "Grppid: " << d.getGrpPid() << endl;
      cout << "pid: " << d.getPid() << endl;
   }
   catch(system_error& se)
   {
      //TODO : Write Err Log
      //TODO : Do other tasks, report to mothership
      std::cout << se.what() << std::endl;
   }
   for(;;){}

}
*/
