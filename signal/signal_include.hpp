/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/

#ifndef _SIGNAL_INCLUDE_HPP
#define _SIGNAL_INCLUDE_HPP


/*
 * C++
 */
#include <iostream>

#include <map>
#include <utility>

#include <cassert>
#include <cerrno>
#include <csignal>
#include <cstdlib>

#include <system_error>


/*
 * Boost
 */
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/optional.hpp>
#include <boost/type_traits.hpp>


/*
 * POSIX
 */
//#include <signal.h>
#include <sys/resource.h>


#endif // for #ifndef _SIGNAL_INCLUDE_HPP
