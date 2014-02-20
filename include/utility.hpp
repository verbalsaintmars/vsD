/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/

#ifndef _UTILITY_HPP
#define _UTILITY_HPP

//#include <cstdint>
#include <fstream>
#include <ios>
#include <iterator>
#include <vector>

#include <boost/crc.hpp>

#include <dlfcn.h>

#include <arpa/inet.h>
//#include <netinet/in.h>

#undef htons


//defines
#define VSDASSERT(cond, msg) \
   do{   \
   } while(0)


#define UNUSED(x) ((void)x)



namespace vsd { namespace dl { namespace utility {

/*
 * Not utf enabled
 * Dynamic check rpath for soname
 * http://stackoverflow.com/questions/2836330/is-there-a-way-to-inspect-the-current-rpath-on-linux
 */
static int CheckSum(const char* soname)
{
   auto handle = ::dlopen(soname, RTLD_LAZY | RTLD_LOCAL);
   if (handle == nullptr)
   {
      // not a proper so file
      return -1;
   }
   ::dlclose(handle);

   std::ifstream file(soname, std::ios_base::binary);

   if (file.fail())
   {
      return -1;
   }

   std::istream_iterator<unsigned char> begin(file), end;

   std::vector<unsigned char> content{begin, end};

   boost::crc_32_type result;
   result.process_bytes(content.data(), content.size());
   return result.checksum();
}


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

}}} // vsd::dl::utility
#endif // for #ifndef _UTILITY_HPP
