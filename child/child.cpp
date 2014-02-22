#include "child.hpp"


// -variable=value for non-boolean flags, and --variable/--novariable for boolean flags
int main(int argc, char *argv[])
{
   {
      vsDGFlag{}; // register GFlags
   }
   google::ParseCommandLineFlags(&argc, &argv, true);
}

