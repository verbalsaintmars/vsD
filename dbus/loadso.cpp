#include "loadso.hpp"

namespace vsd{ namespace dbus{ namespace so{

// name mapping to dbus assigned id, i.e xml's node
const char *LOADSO_SERVER_NAME = "vsd.dbus.loadsoul";
// path to object, i.e xml's node
const char *LOADSO_SERVER_PATH = "/vsd/dbus/loadsoul";


LoadSoServer::LoadSoServer(DBus::Connection &connection)
  : DBus::ObjectAdaptor(connection, LOADSO_SERVER_PATH)
{
}


bool LoadSoServer::Session(const uint64_t& a_sessionId)
{
}


bool LoadSoServer::Soname(const std::string& a_soname)
{
}


bool LoadSoServer::SonameHash(const int32_t& a_hash)
{
}


bool LoadSoServer::Version(const std::string& a_version)
{
}


void termDbus(int sig)
{
  dispatcher.leave();
}


void Start()
{
   vsd::signal::setSigHandler(
         SIGINT,
         &termDbus,
         vsd::signal::Sigset(vsd::signal::SIGACTION::EMPTY),
         0);

   DBus::BusDispatcher dispatcher;
   DBus::default_dispatcher = &dispatcher;

   DBus::Connection conn = DBus::Connection::SessionBus();
   conn.request_name(ECHO_SERVER_NAME);
   EchoServer server(conn);
   dispatcher.enter();
}

//  signal(SIGTERM, niam);
//  signal(SIGINT, niam);

}}} // vsd::dbus::so

/*
TODO
child fork loadso
1. loadso setup dbus and register
2. child setup dbus and connect to child
3. child send session soname sonamehash version to loadso
4. loadso load so , test hash and version. if ok, then run, else
5. send info back to child and die
6. use dbus to make sure child runs first(or start up and start service)

*/
int main()
{

}
