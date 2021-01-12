//  boost/detail/lightweight_main.hpp  -------------------------------------------------//

//  Copyright Beman Dawes 2010

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <iostream>
#include <exception>

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                exception reporting main() that calls cpp_main()                      //
//                                                                                      //
//--------------------------------------------------------------------------------------//

int cpp_main(int argc, char* argv[]);

int main(int argc, char* argv[])
{
  try
  {
    return cpp_main(argc, argv);
  }

  catch (const std::exception& ex)
  {
    std::cout
    << "\nERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR\n"
    << "\n****************************** std::exception *****************************\n"
    << ex.what()
    << "\n***************************************************************************\n"
    << std::endl;
  }
  return 1;
}

/* lightweight_main.hpp
wwwJNdX0tJT7nWjaa7hlUoaPBppT/gNobWdQvx/nLXeqs94RP/beId27Hb93vk1r3fzyWs04Y+z9s8RfbuAYs1/Tq3mHC90HYMOK193z4nVHyrOZmmP1LcX4uXUW+rt192cewvE2KsjLon9iBftd2nQPR6JpKzsZ3Gt/qPX2dM2nQRLPHeE/kledOSzieOR0ZDayiNxaj9yJ7EDeCOSag9RK9CGYNkg/5DRkdvBFJz+hzhwI
*/