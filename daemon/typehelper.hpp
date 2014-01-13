/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/
#ifndef _TYPEHELPER_HPP
#define _TYPEHELPER_HPP

#include "daemon_include.hpp"

namespace vsd { namespace type_helper {

template<typename T> using Underlying = typename std::underlying_type<T>::type;

template<typename T> constexpr Underlying<T>
underlying(T t) { return Underlying<T>(t); }

}} // vsd::type_helper

#endif // for #ifndef _TYPEHELPER_HPP
