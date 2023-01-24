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
9B/hDr7Acl7BffOQ1H8WzqHgNtxE+o9xlQruDYk7sMDSf2MVOUi4GYzLV3BrJO5hC3e3ghtEuIsZl6bgZkncFAt3g4K7jHAnNrCcf0PR7xLXz8L1VHAfvUH8v4HaPE3SRuZHjcfJZP9y2W8oZSdK+r3zLft3jDIfTLgpjFuh4I48KPvfwoUV3EyqUwbXyS2fcUtUnVxUdgKXnaeUrUn6gVbZlyhlJxFu7/OEcyu4Q7JOsRbu5GglTrSV5N/zLGsl7cHiKPlfQPKfy/5mqxJXlPTPFFvyXyl7IeEGMu5VBReQuDkWbpqC60C4WMaVKzi/xF1h4f6q4FoTbtdzhBut4DwSFwlY8c9RSn9OQty9jPMouP+uFbhaC/emgnuQcOMY9+sWG/ehxK2ycBUK7hLC9WLcdgX3vMRdb+FyFVxfwjU8S7g1Cq5c4npYOJeC2zYRca8wbqqCGy9x382TuM+vs3GbCbeIcf0VXH+Je9HC/UPBjSTcUMbFKbh2ErfAws1WcDmEa8u4DzcrsuwBgRts4S5TcC9tpvVv/yQerpO0neYxD4NNC0n1cfMoiLAT7xvnwr0RP/nvFGPY8QA9MAil1H8xF0GQ+CbS7ZtLmG14v53vqawqvv8K75/n+9/xfh3fp8Jr1q/h+2y8r+T7+/C+lO+/xfsivq/H+6l8/yPe5/P9Mbz38/1/8N7L9yfxvr94Lt6n8b0D2Lz+XL6P
*/