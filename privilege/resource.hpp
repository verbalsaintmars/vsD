/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/

#ifndef _RESOURCE_HPP
#define _RESOURCE_HPP
#include "privilege_include.hpp"

namespace vsd{ namespace resource{


class PrivilegeUtil final
{
public:
   static mode_t ClearUmask() noexcept(true)
   {
      return ::umask(0);
   }

   static void Chdir(const char *a_path) noexcept(true)
   {
      if (::chdir(a_path) == -1)
      {
         throw std::system_error(
               std::error_code(
                  errno,
                  std::system_category()),
               std::string(
                  "[system_error] chdir failed to chdir")
               );
      }
   }

   static void Chroot(const char *a_path) noexcept(true)
   {
      //Privilege system call
      if(::chroot(a_path) == -1)
      {
         throw std::system_error(
               std::error_code(
                  errno,
                  std::system_category()),
               std::string(
                  "[system_error] chroot failed to chroot")
               );
      }
   }

   static void CloseFD() noexcept(true)
   {
      int maxfd;

      if ((maxfd = ::sysconf(_SC_OPEN_MAX)) == -1)
      {
         maxfd = 8192;
      }

      int fd = 0;

      for (; fd < maxfd; ++fd)
      {
         //if (fd == 1) continue; // debugging purpose
         ::close(fd);
      }
   }
};


class PrivilegeUid final
{
public:
   void dropPrivilege()
   {
      orig_uid_ = ::geteuid();

      if (::seteuid(::getuid()) == -1)
      {
         throw std::system_error(
               std::error_code(
                  errno,
                  std::system_category()),
               std::string(
                  "[system_error] seteuid failed to set euid")
               );
      }
   }

   void recoverPrivilege()
   {
      if (::seteuid(orig_uid_) == -1)
      {
         throw std::system_error(
               std::error_code(
                  errno,
                  std::system_category()),
               std::string(
                  "[system_error] seteuid failed to set euid")
               );
      }
   }

   void dropPrivilegePermanently()
   {
      if (::setreuid(::getuid(), ::getuid()) == -1)
      {
         throw std::system_error(
               std::error_code(
                  errno,
                  std::system_category()),
               std::string(
                  "[system_error] setreuid failed to set euid")
               );
      }
   }

private:
   uid_t orig_uid_;
};


}} // vsd::resource

#endif // for #ifndef _RESOURCE_HPP
