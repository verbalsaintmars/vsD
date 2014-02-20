/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/

#ifndef _RESOURCE_HPP
#define _RESOURCE_HPP
#include "privilege_include.hpp"

namespace vsd { namespace resource{

/*
 * 1. set coredump size
 * 2. chroot
 * 3. set set-user-id privilege
 *
 *
 */

void dropPrivilege() noexcept;
void recoverPrivilege() noexcept;


}} // vsd::resource


#endif // for #ifndef _RESOURCE_HPP
