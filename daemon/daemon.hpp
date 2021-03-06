/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/
#ifndef _DAEMON_HPP
#define _DAEMON_HPP
#include <typehelper.hpp>
#include "daemon_include.hpp"

template<>
void generalSignalHandler<SIGUSR1>(int sig)
{
   SAVEERRNO

   assert(sig == SIGUSR1);

   UNUSED(sig);

   GETERRNO
}


namespace vsd { namespace daemon {

enum class DAEMON_FLAG : int
{
   NONE = 0x00000000,
   NO_CHDIR = 0x00000001,
   NO_CLOSE_FILES = 0x00000002,
   NO_REOPEN_STD_FDS = 0x00000004,
   NO_UMASK = 0x0000000A,
   MAX_CLOSE = 0x00002000
};

using namespace vsd::type_helper;

class Daemon final
{
public:
   Daemon(DAEMON_FLAG dflag, std::string rootdir = "/") :
      forkId_{::fork()} , rootdir_{rootdir}
   {
      if (forkId_ == -1)
      {
         throw std::system_error(
               std::error_code(
                  errno,
                  std::system_category()),
               std::string("[system_error] fork error.")
               );
      }

      ++forkCnt_;

      fork(dflag);
   }


   /*
    * get _this_ pid
    */
   pid_t getPid()
   {
      return forkId_;
   }


   pid_t getGrpPid()
   {
      return ::getpgrp();
   }


   pid_t getSessionPid()
   {
      return getsid(getPid());
   }

   void run();

private:
   void fork(DAEMON_FLAG dflag)
   {
      /*
       * child process
       */
      if (forkId_ == 0)
      {
         /*
          * second fork.
          * First fork :
          *     Not to be process leader. We need to make a new session
          * Second fork :
          *     Get rid of being the session leader.
          *     Process can not reacquire a controlling terminal
          */
         if (forkCnt_ == FORKNUM)
         {
            /*
             * clear umask
             */
            if (!(underlying(dflag) & underlying(DAEMON_FLAG::NO_UMASK)))
            {
               ::umask(0);
            }

            /*
             * set process's current working directory to /
             * to prevent system shutdown unmount directory other than root dir
             */
            if (!(underlying(dflag) & underlying(DAEMON_FLAG::NO_CHDIR)))
            {
               ::chdir(rootdir_.c_str());
            }

            /*
             * close all process's fd
             */
            if (!(underlying(dflag) & underlying(DAEMON_FLAG::NO_CLOSE_FILES)))
            {
               closeFD();
            }

            /*
             * redirect STDIN_FILENO STDOUT_FILENO STDERR_FILENO to /dev/null
             */
            if (!(underlying(dflag) & underlying(DAEMON_FLAG::NO_REOPEN_STD_FDS)))
            {
               redirectFD();
            }
         }
         else
         {
            /*
             * First fork child. Set to session leader.
             */
            ::setsid();
            Daemon{dflag};
         }
      }
      else
      {
         _exit(0);
      }
   }


   void closeFD() noexcept(true)
   {
      if ((maxfd_ = ::sysconf(_SC_OPEN_MAX)) == -1)
      {
         maxfd_ = underlying(DAEMON_FLAG::MAX_CLOSE);
      }

      int fd = 0;

      for (; fd < maxfd_; ++fd)
      {
         //if (fd == 1) continue; // debugging purpose
         ::close(fd);
      }
   }


   void redirectFD()
   {
      ::close(STDIN_FILENO);

      int fd = open("/dev/null", O_RDWR);

      if (fd != STDIN_FILENO)
         throw std::system_error(
               std::error_code(
                  errno,
                  std::system_category()),
               std::string(
                  "[system_error] Open /dev/null to STDIN_FILENO error.")
               );

      if (::dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO)
         throw std::system_error(
               std::error_code(
                  errno,
                  std::system_category()),
               std::string(
                  "[system_error] dup2 STDIN_FILENO => STDOUT_FILENO error.")
               );

      if (::dup2(STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO)
         throw std::system_error(
               std::error_code(
                  errno,
                  std::system_category()),
               std::string(
                  "[system_error] dup2 STDIN_FILENO => STDERR_FILENO error.")
               );
   }

private:
   inline void prepareSignal();

private:
   static void * operator new(size_t) = delete;
   static void operator delete(void*) = delete;

private:
   static std::atomic_int forkCnt_;
   static int maxfd_;
   enum : int {FORKNUM = 2};

private:
   pid_t forkId_;
   std::string rootdir_;
};


std::atomic_int Daemon::forkCnt_{0};
int Daemon::maxfd_{};


void Daemon::prepareSignal()
{
   using namespace vsd::signal;
   // ignore child signal. Use dbus to communicate to child process
   ::signal(SIGCHLD, SIG_IGN);

   if(setSigHandler(
         SIGUSR1,
         &generalSignalHandler<SIGUSR1>,
         Sigset(SIGACTION::EMPTY),
         0))
   {
      //TODO[LOG]
   }

}

void Daemon::run()
{
   prepareSignal();
   while(true)
   {
      pause();
   }
}


}} // vsd::daemon
#endif // for #ifndef _DAEMON_HPP
