/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/
#ifndef _DL_HPP
#define _DL_HPP
#include "dl_include.hpp"
#include "dl_interface.hpp"
#include <typehelper.hpp>


namespace vsd { namespace dl {

using namespace vsd::type_helper;


template<typename Identifier_Type>
class LoadSo
{
private:
   using Handler_Type = void *;
   using ModuleMap_Type = std::unordered_map<Identifier_Type, Handler_Type>;

public:
   /**
    * id : [in] Key to register
    */
   bool RegisterType(const Identifier_Type& id);

   /**
    * id : [in] Key for grabbing the handler
    * Symbol : [in] Symbol to load from .so
    */
   template<typename RetFuncType, typename... Args>
   DLObject * CreateObject(
         const Identifier_Type&,
         Args...,
         const char* = "GetCreatorFunc");

   bool UnregisterType(const Identifier_Type& id);

private:
   bool dlopen(const Identifier_Type&);
   bool dlclose(void *);

private:
   // TODO use implemented hotchscotch later
   ModuleMap_Type moduleMap_;
};


template<typename Identifier_Type>
bool LoadSo<Identifier_Type>::RegisterType(
      const Identifier_Type& id)
{
   return dlopen(id);
}


template<typename Identifier_Type>
template<
   typename RetFuncType,
   typename... Args
>
DLObject * LoadSo<Identifier_Type>::CreateObject(
      const Identifier_Type& id,
      Args... args,
      const char* Symbol)
{
   auto Result = moduleMap_.find(id);

   if (Result == moduleMap_.end())
   {
      return nullptr;
   }
   else
   {
      static_assert(
         boost::mpl::eval_if<
            std::is_pointer<RetFuncType>,
            std::is_function<remove_pointer_t<RetFuncType>>,
            boost::mpl::false_>::type::value,
         "[static_assert] RetFuncType should be a pointer to funtion type");

      RetFuncType rft;

      *reinterpret_cast<void **>(&rft) = ::dlsym((*Result).second, Symbol);

      auto CreatorFunc = (*rft)();

      return CreatorFunc(args...);
   }
}


template<typename Identifier_Type>
bool LoadSo<Identifier_Type>::UnregisterType(
      const Identifier_Type& id)
{
   auto Result = moduleMap_.find(id);

   if (Result == moduleMap_.end())
   {
      return false;
   }
   else
   {
      if (dlclose(Result->second))
      {
         /*
          * Will throw if compare object throw
          */
         try
         {
            if (moduleMap_.erase(id) == 1)
            {
               return true;
            }
            else
            {
               return false;
            }
         }
         catch(...)
         {
            return false;
         }
      }
      else return false;
   }
}


template<typename Identifier_Type>
bool LoadSo<Identifier_Type>::dlopen(
   const Identifier_Type& id)
{
   /*
    * Chk for null return
    * Chk IdentifierType can cast to const char*
    */
   static_assert(boost::is_convertible<Identifier_Type,const char*>::value,
         "[static_assert] IdentifierType should able to cast to const char*");

   Handler_Type ht = ::dlopen(id, RTLD_LAZY | RTLD_LOCAL | RTLD_DEEPBIND);

   if ( ht == nullptr)
   {
      // Debug
      std::cout << ::dlerror() << std::endl;
      return false;
   }
   else
   {
      return moduleMap_.insert(std::make_pair(id, ht)).second;
   }
}


template<typename Identifier_Type>
bool LoadSo<Identifier_Type>::dlclose(void *handle)
{
   int erret = ::dlclose(handle);

   if (erret == 0)
   {
      return true;
   }
   else
   {
      //debug
      std::cout << "[debug] " << ::dlerror() << std::endl;
      return false;
   }
}


}} // vsd::dl

#endif // for #ifndef _DL_HPP
