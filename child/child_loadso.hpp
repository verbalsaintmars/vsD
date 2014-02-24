/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/
#ifndef _CHILD_LOADSO_HPP
#define _CHILD_LOADSO_HPP
#include <givebirth.hpp>
#include <resource.hpp>

namespace vsd{ namespace child{ namespace loadso{

using namespace vsd::resource;

enum class RESTRICTION : int
{
   RELAX,
   RESTRICTED
};


/**
 * TODO
 * run loop
 * prepare dbus setup as client to child daemon (as server)
 * loadso and runso
 * report to child daemon
 */
class Forked
{

};


class LoadSoRun final : public Forked
{

};


class LoadExeRun final : public Forked
{
};

/**
 * Thread stack
 * Will fork and loadso
 */
void LoadSo(RESTRICTION a_res)
{
   using namespace vsd::fork;
   GiveBirth gbirth;
   if (gbirth.GetPid() == 0)
   {
      if (a_res == RESTRICTION::RESTRICTED)
      {
         PrivilegeUtil::ClearUmask();
         PrivilegeUtil::CloseFD();
         PrivilegeUid().dropPrivilegePermanently();
      }
   }
}

}}} // vsd::child::loadso

#endif // for #ifndef _CHILD_LOADSO_HPP
