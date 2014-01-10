#ifndef _DAEMON_HPP
#define _DAEMON_HPP
#include "daemon_include.hpp"
#include "typehelper.hpp"

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

      /*
       * It's in different process here...
       */
      if (forkId_ == 0)
      {
         if (forkCnt_ == 2)
         {

            if (!(vsd::type_helper::underlying(dflag) &
                     vsd::type_helper::underlying(DAEMON_FLAG::NO_UMASK)))
            {
               ::umask(0);
            }

            if (!(vsd::type_helper::underlying(dflag) &
                     vsd::type_helper::underlying(DAEMON_FLAG::NO_CHDIR)))
            {
               ::chdir("/");
            }

            if (!(vsd::type_helper::underlying(dflag) &
                     vsd::type_helper::underlying(DAEMON_FLAG::NO_CLOSE_FILES)))
            {

               if ((maxfd_ = ::sysconf(_SC_OPEN_MAX)) == -1)
               {
                  maxfd_ = vsd::type_helper::underlying(DAEMON_FLAG::MAX_CLOSE);
               }

               int fd = 0;

               for (; fd < maxfd_; ++fd)
               {
                  //if (fd == 1) continue; // debugging purpose
                  ::close(fd);
               }
            }

            if (!(vsd::type_helper::underlying(dflag) &
                     vsd::type_helper::underlying(DAEMON_FLAG::NO_REOPEN_STD_FDS)))
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
         }
         else
         {
            ::setsid();
            Daemon{dflag};
         }
      }
      else
      {
         _exit(0);
      }
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
   static void * operator new(size_t) = delete;
   static void operator delete(void*) = delete;
private:
   static std::atomic_int forkCnt_;
   static int maxfd_;
private:
   pid_t forkId_;
};

std::atomic_int Daemon::forkCnt_{0};
int Daemon::maxfd_{};

}} // vsd::daemon

#endif // for #ifndef _DAEMON_HPP
