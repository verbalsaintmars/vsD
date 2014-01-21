/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/

#ifndef _DL_INCLUDE_HPP
#define _DL_INCLUDE_HPP

/*
 * C++
 */
#include <cstdint>

#include <iostream>

#include <mutex>

#include <string>

#include <vector>

// #include <map>
#include <unordered_map>


/*
 * Boost
 */
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <boost/optional.hpp>
//#include <boost/variant.hpp>



/*
 * POSIX
 */
#include <arpa/inet.h>
#include <netinet/in.h>

#include <dlfcn.h>



#endif // for #ifndef _DL_INCLUDE_HPP
