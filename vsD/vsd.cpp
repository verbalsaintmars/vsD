/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/
#include "vsD_include.hpp"

int main()
{
   /*
    * TODO
    * fork process to load .so
    * child process with dbus enable
    * daemon has dbus enable
    * daemon listen to dbus and load .so
    */
   using namespace vsd::daemon;


   // Start daemon with rootdir = .
   Daemon vdaemon{DAEMON_FLAG::NONE, "."};


   vdaemon.run();
}
