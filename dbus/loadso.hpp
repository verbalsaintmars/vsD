/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/

#ifndef _LOADSO_HPP
#define _LOADSO_HPP
#include "loadso-dbus-server-glue.hpp"
#include <signal.hpp>

namespace vsd{ namespace dbus{ namespace so{

class LoadSoServer :
   public loadsoul_adaptor,
   public DBus::IntrospectableAdaptor,
   public DBus::ObjectAdaptor
{
public:
   LoadSoServer(DBus::Connection&);
   virtual bool Session(const uint64_t& a_sessionId);
   virtual bool Soname(const std::string& a_soname);
   virtual bool SonameHash(const int32_t& a_hash);
   virtual bool Version(const std::string& a_version);

};


}}} // vsd::dbus::so

#endif // for #ifndef _LOADSO_HPP
