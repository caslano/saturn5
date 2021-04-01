//  boost/detail/lightweight_test_reporter.hpp  ----------------------------------------//

//  Copyright Beman Dawes 2014

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                         Configuration reporting cpp_main()                           //
//                                                                                      //
//  Displays configuration information, then returns test_main(argc, argv), which       //
//  must be supplied by the user.                                                       //
//                                                                                      //
//  Note: cpp_main(argc, argv) is called from a try block in main(), which is           //
//  supplied by <boost/detail/lightweight_main.hpp> as is a catch block that reports    //
//  std::exception what().                                                              //
//                                                                                      //
//--------------------------------------------------------------------------------------//

#include <boost/config.hpp>
#include <boost/version.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/detail/lightweight_main.hpp>
#include <iostream>

int test_main(int argc, char* argv[]);

int cpp_main(int argc, char* argv[])
{
  std::cout << BOOST_COMPILER
#ifdef __GNUC__
            << ", __GXX_EXPERIMENTAL_CXX0X__ "
# ifdef __GXX_EXPERIMENTAL_CXX0X__
              "defined"
# else
              "not defined"
# endif
#endif
            << "\n"
            << BOOST_STDLIB << "\n"
            << BOOST_PLATFORM << "\n"
            << "Boost version " << BOOST_VERSION / 100000 << '.'
            << BOOST_VERSION / 100 % 1000 << '.' << BOOST_VERSION % 100 << "\n";

  std::cout << "Command line: ";
  for (int a = 0; a < argc; ++a)
  {
    std::cout << argv[a];
    if (a != argc - 1)
      std::cout << ' ';
  }
  std::cout << std::endl;

  return test_main(argc, argv);
}
/* lightweight_test_report.hpp
zAEUKKCBEndujdRO277ChkvnqPxpFcqzIycKDfTC+efIVHbG1uSrQUVlyhSjdeBl5RYajKu4Yjr6cCk2gx4gVMkG96SMG/6ZeqFKi0c/b7hSXZVNnt4+gdWx2T4HiR8MXPCytB/tmpgVJPsWgdwJII08raB39J2DNf5mfE/LaSbcwljY6TlIh84IKp7XDuzruoKespY00fLcIBNcw9EVWxMOQaQHyLopsXv5rksAQh6TTLKWKcoEqnZYrEW1+BzuklqfflL1bpatZlxQJnSDUq6/wJCs1VdRJiCQpObbuPY4G9TYn60VHP7PJ4Rw0Y9V4flQBCSPCmjRlu62mgRTYDAFAYlQu+k/v/Oakhe+fCtXRcU4RvHl/ZalR4UzuYZlWLjFtbttI0uv9xZs/bTGsLou+xiUGJKh8D6vd/lrnICHCmBxz0rMz94m0ZFtXxLApp7LM+b6Up2DvK5TQYnBKOLFMYnVDiwNXOVD+aMkqqx5XSy/TyPazOAOA6kHrxDgHbtk2A4UV9jXKbFmAvXfqhlq0FVGihaBQdG23lCzKzDABqqcV2ReHSessw==
*/