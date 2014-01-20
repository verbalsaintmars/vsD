#include "dl_interface.hpp"
#include "dl.hpp"
#include <iostream>
/*
 * TODO cmake file
 * TODO calculuate chksum of .so file as key to register
 * TODO create a internal map to map chksum : .so file
 * TODO integrate with daemon / signal
 * TODO doxygen style
 * TODO make daemon / signal use std instead of boost
 */



int main()
{
  vsd::dl::LoadSo<const char*> ls;
  ls.RegisterType("./libfoo.so");
  vsd::dl::DLObject* dlo = ls.CreateObject<Creator_Type>("./libfoo.so");
  dlo->ForFun();
  ls.UnregisterType("./libfoo.so");
  std::cout << dlo->GetUUID() << std::endl;

  delete dlo;
  dlo = ls.CreateObject<Creator_Type>("./libfoo.so");
  if(dlo == nullptr)
  {
      std::cout << "opps" << std::endl;
  }
  return 0;
}
