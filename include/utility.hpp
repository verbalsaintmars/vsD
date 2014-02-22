/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/

#ifndef _UTILITY_HPP
#define _UTILITY_HPP

//#include <cstdint>
#include <ios>
#include <iterator>
#include <vector>

/*
 * POSIX
 */
#include <arpa/inet.h>
//#include <netinet/in.h>

#undef htons


//defines
#define VSDASSERT(cond, msg) \
   do{   \
   } while(0)


#define UNUSED(x) ((void)x)

// http://stackoverflow.com/a/3418029
// #ifdef UNUSED
// #elif defined(__GNUC__)
// # define UNUSED(x) UNUSED_ ## x __attribute__((unused))
// #elif defined(__LCLINT__)
// # define UNUSED(x) /*@unused@*/ x
// #else
// # define UNUSED(x) x
// #endif

#define SAVEERRNO \
   int __orig_errno = errno;

#define GETERRNO \
   errno = __orig_errno;

namespace vsd{ namespace utility{ namespace network{


static uint16_t GetPort(uint16_t port)
{
   return ::htons(port);
}


static int GetIpv4(const char *strptr, void *addrptr)
{
   return ::inet_pton(AF_INET, strptr, addrptr);
}


static int GetIpv6(const char *strptr, void *addrptr)
{
   return ::inet_pton(AF_INET6, strptr, addrptr);
}


static void GetIpv4Str(const void * addrptr, char *strptr)
{
   ::inet_ntop(AF_INET, addrptr, strptr, INET_ADDRSTRLEN);
}


static void GetIpv6Str(const void * addrptr, char *strptr)
{
   ::inet_ntop(AF_INET6, addrptr, strptr, INET_ADDRSTRLEN);
}

}}} // vsd::utility::network
#endif // for #ifndef _UTILITY_HPP
