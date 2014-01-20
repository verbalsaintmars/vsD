/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/

#ifndef _LIB_HPP
#define _LIB_HPP
/*
 * TODO Generic dl loader
 *
 */

#include "dl_interface.hpp"
#include <fstream>

class Fun : public vsd::dl::DLObject
{
public:
   void ForFun() override
   {
      std::cout << "Fun's ForFun!" << std::endl;
   }
   ~Fun() = default;
};


vsd::dl::DLObject * CreateObject()
{
   static int i = 0;
   static Fun * fun = new Fun;
   std::ofstream tmpfile;
   tmpfile.open("/tmp/haha.txt", std::ios::out | std::ios::app);
   tmpfile << "called number : " << i++ << "\n";
   tmpfile.close();
   return fun;
}


RetDLObjectFunc_Type GetCreatorFunc()
{
   return &CreateObject;
}
#endif // for #ifndef _LIB_HPP
