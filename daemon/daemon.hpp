/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/
#include "daemon_include.hpp"
#ifndef _DAEMON_HPP
#define _DAEMON_HPP
#include "typehelper.hpp"

// TODO first fork OK, but second fork failed and throw? init will collect it!

namespace vsd { namespace daemon {

enum class DAEMON_FLAG : int
{
   NONE = 0x00,
   NO_CHDIR = 0x01,
   NO_CLOSE_FILES = 0x02,
   NO_REOPEN_STD_FDS = 0x04,
   NO_UMASK = 0x0A,
   MAX_CLOSE = 0x2000
};

using namespace vsd::type_helper;

class Daemon final
{
public:
   Daemon(DAEMON_FLAG dflag) : forkId_(::fork())
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
               ::chdir("/");
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
   static void * operator new(size_t) = delete;
   static void operator delete(void*) = delete;

private:
   static std::atomic_int forkCnt_;
   static int maxfd_;
   enum : int {FORKNUM = 2};

private:
   pid_t forkId_;
};

std::atomic_int Daemon::forkCnt_{0};
int Daemon::maxfd_{};

}} // vsd::daemon
#endif // for #ifndef _DAEMON_HPP
