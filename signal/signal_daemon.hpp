/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/

#ifndef _SIGNAL_DAEMON_HPP
#define _SIGNAL_DAEMON_HPP
#include "signal_include.hpp"

namespace vsd{ namespace signal{ namespace daemon{

class DaemonSigSet final
{
public:
   DaemonSigSet()
   {
      ::sigfillset(&filled_Sig_);
   }
public:
   void prepareSignal()&
   {
      ::sigprocmask(SIG_BLOCK, &filled_Sig_, &orig_Sig_);
   }


   void restoreSignal()&
   {
      ::sigprocmask(SIG_SETMASK, &orig_Sig_, nullptr);
   }

private:
   sigset_t filled_Sig_;
   sigset_t orig_Sig_;
};






}}} // vsd::signal::daemon

#endif // for #ifndef _SIGNAL_DAEMON_HPP
