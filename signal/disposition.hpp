/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/

#ifndef _DISPOSITION_HPP
#define _DISPOSITION_HPP
#include "signal_include.hpp"
#include <utility.hpp>

namespace vsd { namespace signal { namespace disposition {


template<int SIGNAL>
void generalSignalHandler(int sig);

/*
 * Used for coredump
 */
template<>
void generalSignalHandler<SIGABRT>(int sig)
{
   assert(sig == SIGABRT);

   UNUSED(sig);

   /*
    * TODO :
    * 1. Check capability
    * 2. Check resource
    * 3. TODO[LOG]
    */
   std::abort();
}

/*
 * Alias type for pointer to specific function type
 */
template<int SIGNAL>
using DISPOSITION = decltype(generalSignalHandler<SIGNAL>)*;


/*
 * Used in child process
 * [in] sig : set sig to default then raise again causing child to stop/die
 */
void child_term_handler(int sig)
{
   ::signal(sig, SIG_DFL);
   ::raise(sig);
}


/*
 * Trigger process to read config/resetup process
 * [in] sig : must be SIGHUP
 */
void SIGHUP_daemon_handler(int sig)
{
   /* re-read config or else for daemon process */
   assert(sig == SIGHUP);

   UNUSED(sig);
}


void SIGINT_test_handler(int sig)
{
   assert(sig == SIGINT);
   /* test installed handler for [c-c] */
   using namespace std;
   cout << "in SIGINT handler : " << sig << endl;
}

}}} // vsd::signal::disposition

#endif // for #ifndef _DISPOSITION_HPP
