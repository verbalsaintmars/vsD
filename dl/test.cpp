#include <dl_interface.hpp>
#include <iostream>
#include "somap.hpp"
#include "loadso.hpp"
/*
 * TODO [done] cmake file
 * TODO [done] calculuate chksum of .so file as key to register
 * TODO [done] create a internal map to map chksum : .so file
 * TODO dynamic rpath inspect for soname chksum
 *
 * TODO DBUS Setup for each process
 * TODO integrate with daemon / signal
 * TODO doxygen style
 * TODO make daemon / signal use std instead of boost
 */

/*
 * This is a demo of how to use dl
 */
int main()
{
   /*
    * Giving a module name.
    * rpath is set for this test program. It will load modules under ./modules directory
    */
   const char *soname = "libfoo.so";

   /*
    * CreateSoMap will create a map of module checksum and module name
    */
   vsd::dl::CreateSoMap somap;
   if (somap.Add(soname) == false)
      return 1;

   /*
    * LoadSo in charge of loading mudule, delete module, base on module's chksum as index
    */
   vsd::dl::LoadSo loadso;
   auto ChkSumResult = somap.Get(soname);

   if (ChkSumResult == -1)
   {
      return -1;
   }

   auto Result = somap.Get(ChkSumResult);

   if (Result)
   {
      loadso.RegisterType(ChkSumResult, *Result);
   }

   vsd::dl::DLObject* dlo = loadso.GetModule<GetModuleFunc_Type>(ChkSumResult);
   dlo->ForFun();

   loadso.UnregisterType(ChkSumResult);

   std::cout << dlo->GetUUID() << std::endl;

   loadso.DeleteModule(ChkSumResult, dlo);

   dlo = loadso.GetModule<GetModuleFunc_Type>(ChkSumResult);

   if(dlo == nullptr)
   {
      std::cout << "opps" << std::endl;
   }
   return 0;
}
