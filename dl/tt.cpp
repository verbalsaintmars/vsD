/*
 * C++
 */
#include <functional>

#include <iostream>

// #include <map>
#include <type_traits>

#include <unordered_map>
#include <utility>

#include <cerrno>
#include <system_error>

#include <string>


/*
 * Boost
 */
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/optional.hpp>
#include <boost/type_traits.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <boost/variant.hpp>


/*
 * POSIX
 */
#include <dlfcn.h>

#include <typeinfo>

#include <boost/utility.hpp>

template< class T >
using remove_pointer_t = typename boost::remove_pointer<T>::type;

using RetDLObjectFunc_Type = int *(*)();

//using Creator_Type = RetDLObjectFunc_Type(*)();
using Creator_Type = int;



struct Test
{
private:
~Test(){}
};

struct T2 : Test
{
};

void func()
{

}

int main()
{
   T2 t2;
}
