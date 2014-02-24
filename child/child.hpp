/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/

#ifndef _CHILD_HPP
#define _CHILD_HPP
#include <signal_daemon.hpp>
#include <daemon.hpp>

#include "child_include.hpp"
#include "child_gflags.hpp"

/*
 * TODO
 * 2. daemon
 * 3. setup signal
 * 3. Fork
 * 3. drop privilege before call into .so
 *
 * 4. *prepare dbus , being a callee , also a caller to loadso
 *
 * 5. vsD uuid, soname, sohash, version, status{standalone,report,heartbeat}
 *       , runlease, cmd accept{forceclose,etc}
 * 6. loadso
 * 7. prepare dbus , callback to vsD(with uuid session),
 *    request cmd{openup new .so, etc.}
 */

namespace vsd{ namespace child{


}} // vsd::child

#endif // for #ifndef _CHILD_HPP
