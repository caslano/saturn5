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
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
*/