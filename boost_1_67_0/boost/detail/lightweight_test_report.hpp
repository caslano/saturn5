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