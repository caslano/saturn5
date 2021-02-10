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
WXwEYMU0vGq2xeHPXazTIJnMwzgNo5kTY1bAoFFCWkIDEgBkW9evCRNCMhotDVl+GQjFNhyvPAgtbEVdw5oTyoluDqGHqtwqXSAP/2qF7gHXUs14uSrDXXpJMsUMD44PV2WMM3f2rs6zeB5e+WlAVZyF02DQe9Q0DzquSX6DWUvOC0qhi+48NLlWjKQ511aUIidTBGu3MsgEMfughkK9F8BxaEewBrGIljhl5A1yUSrbLxo0/Mp50xW265BWSCpgJbUSp2NJSMvH6XHiDe0/8xfT1JktptNOEM+jNJpE08TxsaHpNCH6YHqNVlblqjYf4DxN48SFs+47vPTpiKP4GI/kEoW4YfPee/CHfxlPA8eTpdMjo4PwL49wI6SwB4gFUR6Q8BD+duA5rEjwACc8XBjt9iG/ZchR7uVqMy6V8tZCjtDhN73g1CfBPEVPOTJcWq/hm5caIhTQjibzUqNHFBiZlvYlG9LUyMfHHcG7UulN3459z3nNmWyb3dU/jleKrtH+lR9O/c/hNEyXTrca+yHDFonyVaqtJMbsFzBshLYh9Jx4Rz9672iXO0/680Ttvfe2n+08SBfzGVz500XgzLnFpd5HCLLoAkTZYYdL+u9VuMPFYnYxi65nWdTxnZQQwS5RbjBcpFl0ll0G
*/