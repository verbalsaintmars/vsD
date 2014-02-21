/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/

#ifndef _DISPOSITION_HPP
#define _DISPOSITION_HPP
#include "signal_include.hpp"

namespace vsd { namespace signal { namespace disposition {

/*
 * Used in child process
 * [in] sig : set sig to default then raise again causing child to stop/die
 */
void child_term_handler(int sig)
{
   SAVEERRNO

   ::signal(sig, SIG_DFL);
   ::raise(sig);

   GETERRNO
}


/*
 * Trigger process to read config/resetup process
 * [in] sig : must be SIGHUP
 */
void SIGHUP_daemon_handler(int sig)
{
   SAVEERRNO

   /* re-read config or else for daemon process */
   assert(sig == SIGHUP);

   UNUSED(sig);

   GETERRNO
}


void SIGINT_test_handler(int sig)
{
   SAVEERRNO

   assert(sig == SIGINT);
   /* test installed handler for [c-c] */
   using namespace std;
   cout << "in SIGINT handler : " << sig << endl;

   GETERRNO
}

}}} // vsd::signal::disposition

#endif // for #ifndef _DISPOSITION_HPP
