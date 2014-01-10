#ifndef _TYPEHELPER_HPP
#define _TYPEHELPER_HPP
#include "signal_include.hpp"

namespace vsd { namespace type_helper {

   template<typename T>
   using arg_num_t = boost::mpl::int_<boost::function_traits<T>::arity>;

   template<typename T>
   using result_type_t = typename boost::function_traits<T>::result_type;

   template< class T >
   using remove_pointer_t = typename boost::remove_pointer<T>::type;
}} // vsd::type_helper

#endif // for #ifndef _TYPEHELPER_HPP
