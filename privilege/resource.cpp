/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/

#ifndef _RESOURCE_CPP
#define _RESOURCE_CPP
#include "resource.hpp"
namespace vsd { namespace resource{


uid_t orig_euid;


void dropPrivilege() noexcept
{
   orig_euid = geteuid();
   if (seteuid(getuid()) == -1)
   {
   }

}


void recoverPrivilege() noexcept
{
   if (seteuid(orig_euid) == -1)
   {
   }
}


}} // vsd::resource

#endif // for #ifndef _RESOURCE_CPP
