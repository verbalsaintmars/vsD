/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/

#ifndef _DL_INTERFACE_HPP
#define _DL_INTERFACE_HPP
/*
 * This is the interface for bridging from dl module and modules
 */

#include "dl_include.hpp"

namespace vsd { namespace dl {

using Var_UUID_Type = boost::variant<std::string, boost::uuids::uuid>;


enum class UUIDTYPE : int
{
   STRING,
   RAW
};


class DLObject
{
public:
   static void* operator new(std::size_t count)
   {
      return ::operator new(count);
   }


   static void* operator new(std::size_t count, const std::nothrow_t& nt)
   {
      return ::operator new(count, nt);
   }


   static void operator delete(void* ptr)
   {
      ::operator delete(ptr);
   }


   static void operator delete(void* ptr , const std::nothrow_t& nt)
   {
      ::operator delete(ptr, nt);
   }

public:
   const Var_UUID_Type GetUUID(UUIDTYPE=UUIDTYPE::STRING);

public:
   virtual ~DLObject() = default;

public:
   virtual void ForFun();

protected:
   DLObject();

private:
   const boost::uuids::uuid uuid_;
};


void DLObject::ForFun()
{
   std::cout << "DLObject ForFun" << std::endl;
}


DLObject::DLObject() : uuid_(boost::uuids::random_generator()())
{
}


const Var_UUID_Type DLObject::GetUUID(UUIDTYPE type)
{
   if (type == UUIDTYPE::STRING)
      return boost::uuids::to_string(uuid_);
   else
      return uuid_;
}


}} // vsd::dl

/*
 * Could have parameters
 */
using RetDLObjectFunc_Type = vsd::dl::DLObject *(*)();
using Creator_Type = RetDLObjectFunc_Type(*)();


// Will return function to create the DL object
extern "C" {
   RetDLObjectFunc_Type GetCreatorFunc();
}


#endif // for #ifndef _DL_INTERFACE_HPP
