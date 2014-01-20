/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/

#ifndef _TYPEHELPER_HPP
#define _TYPEHELPER_HPP
#include "general.hpp"

namespace vsd { namespace type_helper {

template<typename T>
using arg_num_t = boost::mpl::int_<boost::function_traits<T>::arity>;

template<typename T>
using result_type_t = typename boost::function_traits<T>::result_type;

template< class T >
using remove_pointer_t = typename std::remove_pointer<T>::type;

template< class T >
using result_of_t = typename std::result_of<T>::type;

/*
 * Enum class type grab
 */
template<typename T> using Underlying = typename std::underlying_type<T>::type;

template<typename T> constexpr Underlying<T>
underlying(T t) { return Underlying<T>(t); }

}} // vsd::type_helper

#endif // for #ifndef _TYPEHELPER_HPP
