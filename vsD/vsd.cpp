/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/
#include "vsD_include.hpp"
/*
 * TODO
 * session id generator
 */

inline void prepareSignal(sigset_t& filled_Sig, sigset_t& orig_Sig)
{
   ::sigfillset(&filled_Sig);
   ::sigprocmask(SIG_BLOCK, &filled_Sig, &orig_Sig);
}


inline void restoreSignal(sigset_t& orig_Sig)
{
   ::sigprocmask(SIG_SETMASK, &orig_Sig, nullptr);
}

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

   sigset_t filled_Sig, orig_Sig;
   prepareSignal(filled_Sig, orig_Sig);

   // Start daemon with rootdir = .
   Daemon vdaemon{DAEMON_FLAG::NONE, "."};

   restoreSignal(orig_Sig);

   vdaemon.run();
}
