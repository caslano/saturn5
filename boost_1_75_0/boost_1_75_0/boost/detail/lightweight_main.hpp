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
vrjWUoOJd7v2jbdKSJTujXlGozGZi77wGD7mbeygghzpbaFcL80Ff2ir2RmHtKgBbMpxW7+37m28PdumMws5mJRPOPOJ7A/3I7tInwrTHvNMJEj3OSgq/kkeRDB8ogdgPHrihWJg3kLyF/Ua5n7pxaV6Wyg7V7vCPi5hr5c36nPb5CJfwJ1rGhlUlwrJTt2GKThADnESWvajYJp4KTUQTaKaPsCR9fQjvk9beK46KIGmghP0x7hcy00XLcBFpMQF5ebNHOeFQdyR3aY/F2gdpv2Y5XZEnme8FWzoMhRSwe1m089rZ/I53DFQdVnmLxcoFRsUZ9iPAir97yegJgv0kXKyYqOD7HRMdOm5ssVN7e8nwKwz6ZFp2PkD4J7Uxzd7F/lOZ+vPAFYsqdMfhJvDuKUKLl3inrRwD0rc5nQYTObfIQMIuyBhCP73JsK/5Om13hSHAwobiIVhATctQ8b2Xg9Itx4elAHp2RnVGfv10KBNb3uwiMxaHBDnb03VKqqLe0Zcbrhzbqor26nBYyuqncPrKnYubL0jfhWQOxra1Mb/ssOjZeKADsfHze4Gzx70O6qiUPzHO7CktVux7r3dUCwW/8GTqVqwd1f8FYqPw2qF4yveOg/p28OvHfGxRBjc7p5U/1pFCsqPx3ar8gN1r5AfeAvyY8luRX5cAj6Wec4iJz7rtidFs82qsOYsUotI/7/B+mmHYj9K4sEV
*/