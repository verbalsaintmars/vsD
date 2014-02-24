/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/

#ifndef _GIVEBIRTH_HPP
#define _GIVEBIRTH_HPP
#include "fork_include.hpp"

namespace vsd{
namespace fork{

/**
 * This class will
 * 1. Setup proper signal using signal module
 * 2. TODO Setup thread clean handler
 */
class GiveBirth final
{
public:
   GiveBirth() : forkId_(::fork())
   {
   }

   pid_t GetPid()
   {
      if (forkId_ == -1)
      {
         throw std::system_error(
               std::error_code(
                  errno,
                  std::system_category()),
               std::string(
                  "[system_error] fork failed to fork")
               );
      }

      return forkId_;
   }

private:
   pid_t forkId_;
};


}} // vsd::fork
#endif // for #ifndef _GIVEBIRTH_HPP
