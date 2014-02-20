/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/

#ifndef _LOADSO_HPP
#define _LOADSO_HPP
#include <dl_interface.hpp>
#include <typehelper.hpp>

#include "dl_include.hpp"


namespace vsd { namespace dl {


using namespace vsd::type_helper;


class LoadSo final
{
private:
   using Handler_Type = void *;
   using Key = int; //chksum
   using Content = Handler_Type;

public:
   /**
    * id : [in] Key to register
    */
   auto RegisterType(const int& id, std::string soname) ->bool;

   /**
    * id : [in] Key for grabbing the handler
    * Symbol : [in] Symbol to load from .so
    */
   template<typename RetFuncType, typename... Args>
   DLObject * GetModule(
         const int&,
         Args...,
         const char* = "GetModule");

   void DeleteModule(
         const int&,
         DLObject *,
         const char* = "DeleteModule");

   auto UnregisterType(const int& id) ->bool;

private:
   auto dlopen(const int& id, const char*)->bool;
   auto dlclose(void *)->bool;

private:
   // TODO use implemented hopscotch later
   std::unordered_map<Key, Content> moduleMap_;
};


auto LoadSo::RegisterType(
      const int& id,
      std::string soname) ->bool
{
   return dlopen(id, soname.c_str());
}


template<
   typename RetFuncType,
   typename... Args>
DLObject * LoadSo::GetModule(
      const int& id,
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

      return (*rft)()(args...);
   }
}


void LoadSo::DeleteModule(
      const int& id,
      DLObject * module,
      const char* Symbol)
{
   auto Result = moduleMap_.find(id);

   if (Result == moduleMap_.end())
   {
      return;
   }
   else
   {

      DeleteModuleFunc_Type rft;

      *reinterpret_cast<void **>(&rft) = ::dlsym((*Result).second, Symbol);

      (*rft)(module);
   }
}


auto LoadSo::UnregisterType(
      const int& id) -> bool
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


auto LoadSo::dlopen(
   const int& id,
   const char* soname) ->bool
{
   Handler_Type ht = ::dlopen(soname, RTLD_LAZY | RTLD_LOCAL | RTLD_DEEPBIND);

   if (ht == nullptr)
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


auto LoadSo::dlclose(void *handle) -> bool
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

#endif // for #ifndef _LOADSO_HPP
