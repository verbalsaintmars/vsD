#ifndef _DISPOSITION_HPP
#define _DISPOSITION_HPP
#include "signal_include.hpp"

namespace vsd { namespace signal { namespace disposition {


void child_term_handler_template(int sig)
{
   /* perform cleanup */
   ::signal(sig, SIG_DFL);
   raise(sig);

}


void SIGABRT_handler(int)
{
   /* must terminate, no return */
}


void SIGHUP_daemon_handler(int sig)
{
   /* re-read config or else for daemon process */
}


void SIGINT_test_handler(int sig)
{
   /* test installed handler for [c-c] */
   using namespace std;
   cout << "in SIGINT handler : " << sig << endl;
}

}}} // vsd::signal::disposition

#endif // for #ifndef _DISPOSITION_HPP
