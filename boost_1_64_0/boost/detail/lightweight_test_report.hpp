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
UGmsXRsQTUrf5hDPgaUxzd7yxiilt7oXfy1iv+riryL76qJG5cOBPcRrvxjAx58ofiIhanypWeU9aOWq9KVRovZBR06dsOLdhn4fHIl4dzLhI586TRCvmZba4JmRaP4yiaBsbfbOHoKXVZ5MaNdnaG93Qc7sw9VBF46XYWNCOyhaJi+MDMOzqjW+RDYerqzyNIK7+ZI0vvm/BiphsXnUdedX9rdsy/0/SXEVQcz0FyWvFKmwOQEENK7LNloB1fhc+vW7G2uUepyR2VyvikbfmBYbyYrxtNg6Xq2Exn9zYzP+7rri7w7GP1HBP5GnJSn4J9URf0N8ZefJ4i8TO1uqYvc2wq4aWMErHpYhzBl6kFQfeY2L6G5tdozUhUKgMswRavFEba3pjf7RXl2UK6kPZ4t+xJEjLk4j9kNteg83eH72p6w+IgshNsMsD2W1uljwsYMlh/9Eee305O8/NlTWG3+s8phWRGAoD5SFWBVBP+EXOFwzxDTWNz23aTRi2yZGTXy5nvrrougwV8Ng/8wGOpI+fiWTSwtEuow0KJ013XC6ovHEdudAu1LqD4vrguSfRLl/eUmGGZ1mfPM8DoEDN1EU9VN437x9ouxkAZ4d4GgqQ/rvs8kLyWloe6T4IS7iR8p0+JmHnb69npEr4yV+VQuJsY4PSuNegaMuSAH+bom6pJrk81a2UcK68LsXd2A420ezf0/hRxOJgandRtCuNV0ao7thXKABb2fffW3+qMj6Cn8fjFf4G1mmr8LjnRgh5qD3dVxRJHjYsrsOi4fl6hobyDy0gwkJyasyeof2JjRoiFn5T9RH7LHRfBrIdsdUtBp8q7pGDbYjYqyirzxDjJ8qx7F/ssr3Ue0vvOTj3hDqCnZxi6cN9Af6oDRU5KGQ83kxp/Z+/xQb/djncYpJ5uYE8iZCYbc+9ssiTbF2RCieQKus8r8SSsMApbK4YvZH28lEAShiF4ADbUiAKXMACd6mGi6ogatpZJs/67JZlX9i/4T318zrTbNYxSlM7Ek9nf72fM9KlH5Za/ql2MyPZ0/X3cT852EN+t6G1/Y59UvdK3l9rNgv0EdpEjzDenqdhfUY77cNtJZA+cCiiOAU41fK/p76vqR03dXA6O97Drto2HU4Qp4zAS0tmSXCntiNXa+F02rQ+SfGfB458Wl1HfyJbgmq/+UP1XV4rxaB9CAgOaZ3oZe8Xl1rhBk1/lt95Ty26MPwzmM76pvx/+eXdep/UP2oN+tSv3dQ/VWOOpwHjztN58Ht71bX7fzrNLd/qSPc869Toffcj3i71v5fTu7/BQebkP5fKrxV74Q3fr9FB73/8lV1+PR7PtpEv5WpddMf3EIA5AulcCpU7o+P14Rz/iTRLl0H5SNQUVVvCHdmIZ2nE5ovn2Brzn5YCrgmdb9c+maO1aPWxbNSuFXCs5K4h3yYRfK1G/epHc1Bvn6GsnYpWU5tLWZtpaxHs8TOs4glB8oI+pHfa1iR56hIMRQRESvHYeVyypnIK/u0nOZH63QZE8ZHWS+PRPHzdC61m/UXITE0O2A4T/u74DECF1Z5WL6CKsX+RRwyHmh2Kodl+aCPk0SlLnRWY/foJaB4cYqfWz1p7KeX/+bR0MIIVRUS/jgj/OEXnAZ8rv9zKPMxG++A/S2yymcSoT7LFkqWaU35aQyk/Tqs1x6HWR5N4LEWE1SNURjvnf8caQ5SmlzE0cvVvnyj2mBndpX2DbszbFeTYLP1hZttukNaRhrquGwZUaQINNTx6A7xfXUNmQKuoFJfDYBSEcZSc1kp8FRD3ybFgHSQTfVU+6nRqXqqWfdfw/5HiPvBL+rJ+0EQig1RyULYQJHJj2oGhddkR+A=
*/