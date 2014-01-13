/* ******************************
 * Copyleft 2014 Verbalsaint
 * ******************************/
#include "signal.hpp"
#include "disposition.hpp"
/*
 * test
 */
int main()
{
   sigset_t sets;
   sigemptyset(&sets);
   if(vsd::signal::setSigHandler(
         SIGINT,
         &vsd::signal::disposition::SIGINT_test_handler,
         sets,
         0))
      std::cout << "ha" << std::endl;
   for(;;){}
}
