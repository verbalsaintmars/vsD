#ifndef _SIGNAL_HPP
#define _SIGNAL_HPP
#include "signal_include.hpp"
#include "typehelper.hpp"

/*
 * TODO: Arch design
 * TODO: disposition write
 *
 * SIGABRT / SIGIOT(linux)
 * SIGCHLD
 * SIGCONT processes in the same session can be sent this signal by any processes in the
 *    same session(ignore privilege)
 * SIGHUP re-read config
 * SIGINFO c-T, obtain status info from foreground
 * SIGINT interrupt character / c-C
 * SIGIO
 * SIGKILL
 * SIGPIPE
 * SIGPROF kernel generates this
 *    signal upon the expiration of a profiling timer set by a
 *    call to setitimer()
 * SIGQUIT
 * SIGSTOP always stop a process
 * SIGTERM
 * SIGTSTP job-control stop signal
 * SIGTTIN terminal driver sends this signal to a background proccess group when it
 *    attemps to read() from the terminal.
 * SIGTTOU
 * SIGUSR1
 * SIGUSR2
 * SIGVTALRM the kernel generates this signal upon expiration of a virtual timer set by a
 *    call to setitimer()
 *
 */

namespace vsd { namespace signal { namespace type{

using sigHandle_t = void(*)(int);

}}} // vsd::signal::type


namespace vsd { namespace signal {

template<typename HT>
class SetSigHandler final
{
public:
   SetSigHandler() = default;

   struct sigaction operator()(int sig, HT handler, sigset_t mask, int flags)&&
   {
      struct sigaction sa;
      struct sigaction saold;
      sa.sa_handler = handler;
      sa.sa_mask = mask;
      sa.sa_flags = flags;

      if (sigaction(sig, &sa, &saold) == -1)
      {
         throw std::system_error(
               std::error_code(
                  errno,
                  std::system_category()),
               std::string("[system_error] Set signal disposition error.")
               );
      }

      return saold;
   }
   /*
    * SA_NOCLDSTOP
    * SA_NOCLDWAIT
    * SA_NODEFER
    * SA_ONSTACK
    * SA_RESETHAND
    * SA_RESTART
    * SA_SIGINFO
    */
private:
   static void* operator new(std::size_t) = delete;
   static void operator delete(void*) = delete;
};


template<typename DISPOSITION>
boost::optional<struct sigaction> setSigHandler(
      int sig, DISPOSITION dis, sigset_t mask, int flags)
{
   using namespace vsd::type_helper;

   static_assert(
         boost::mpl::eval_if<
            boost::is_same<
               arg_num_t<remove_pointer_t<DISPOSITION>>, boost::mpl::int_<1>>,
            boost::mpl::eval_if<
               boost::is_same<
                  result_type_t<remove_pointer_t<DISPOSITION>>, void>,
                  boost::mpl::true_,
                  boost::mpl::false_>,
            boost::mpl::false_>::type::value,
         "[static_assert] Signal disposition function should have signature as void(int)");

   try
   {
      return boost::optional<struct sigaction>
         (SetSigHandler<DISPOSITION>()(sig, dis, mask, flags));
   }
   catch(std::system_error& se)
   {
      return boost::optional<struct sigaction>();
   }

}

}} // vsd::signal

#endif // for #ifndef _SIGNAL_HPP
