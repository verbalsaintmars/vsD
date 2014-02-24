#include "child.hpp"


// -variable=value for non-boolean flags, and --variable/--novariable for boolean flags
int main(int argc, char *argv[])
{
   {
      vsDGFlag{}; // register GFlags
   }
   google::ParseCommandLineFlags(&argc, &argv, true);

   using namespace vsd::signal::daemon;
   using namespace vsd::daemon;

   DaemonSigSet daemonSigSet;
   daemonSigSet.prepareSignal();

   // Start daemon with rootdir = .
   Daemon vdaemon{DAEMON_FLAG::NONE, "."};

   daemonSigSet.restoreSignal();

   vdaemon.run();
}

