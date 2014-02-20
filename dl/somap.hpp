/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/

#ifndef _SOMAP_HPP
#define _SOMAP_HPP

#include "dl_include.hpp"
#include <utility.hpp>

namespace vsd { namespace dl {


using namespace vsd::dl::utility;


struct SoData
{
   SoData(const std::string& soname_, int& chksum) : soname(soname_) , checksum(chksum){}
   std::string soname;
   int checksum;
   /*
    * Through local DBUS
    */
   std::vector<::pid_t> localvsD_DBUS;

   /*
    * IPv4 Address , bin format
    * Port , big-endian format
    */
   std::vector<std::pair<::in_addr_t, ::in_port_t>> remotevsD_IPv4;

   /*
    * IPv6 Address , bin format
    * Port , big-endian format
    */
   std::vector<std::pair<uint8_t, ::in_port_t>> remotevsD_IPv6;
};


struct SONAME{};
struct CHKSUM{};


using boost::multi_index_container;
using namespace boost::multi_index;

/*
 * Contain information about SO library
 * Include Library File Name, CheckSum, TODO Deployied vsD processes(include local and
 *    remote hosts
 */
class SoMap{
private:
   using Key = std::string;
   using Content = int;
   using ContainerType = multi_index_container<
      SoData,
      indexed_by<
         ordered_unique<tag<SONAME>, member<SoData, std::string, &SoData::soname>>,
         ordered_unique<tag<CHKSUM>, member<SoData, int, &SoData::checksum>>>>;

public:
   auto Add(const std::string& soname) ->bool;
   auto Get(const std::string& soname) ->int;
   auto Get(const int& chksum) -> boost::optional<std::string>;

private:
   std::mutex somapMutex_;
   ContainerType somap_;
};


auto SoMap::Add(const std::string& soname) ->bool
{
   // TODO remote this and make CheckSum to check soname in rpath
   auto chksum = CheckSum( (std::string("./modules/") + soname.c_str()).c_str() );
// auto chksum = CheckSum(soname.c_str() );

   if (chksum == -1)
   {
      return false;
   }
   else
   {
      std::lock_guard<std::mutex> lock(somapMutex_);
      auto Result = somap_.emplace(soname, chksum);

      if (Result.second == true)
         return true;
      else
         return false;
   }
}


/*
 * No need return type specified for c++1y
 */
auto SoMap::Get(const std::string& soname) -> int
{
   using SoMap_Index_Type = ContainerType::index<SONAME>::type;

   SoMap_Index_Type::iterator it = somap_.get<SONAME>().find(soname);

   if ( it != somap_.get<SONAME>().end())
   {
      return (*it).checksum;
   }
   else
      return -1;

}


auto SoMap::Get(const int& chksum) -> boost::optional<std::string>
{
   using SoMap_Index_Type = ContainerType::index<CHKSUM>::type;

   SoMap_Index_Type::iterator it = somap_.get<CHKSUM>().find(chksum);

   if ( it != somap_.get<CHKSUM>().end())
      return boost::make_optional((*it).soname);
   else
      return boost::optional<std::string>();
}


}} //vsd::dl

#endif // for #ifndef _SOMAP_HPP
