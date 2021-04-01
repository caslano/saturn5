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
ZGf1A1YzDbAhFU4BZfzhorkXPiLLZ+eApF22GFf9n+HqZxzQXC7EfFAh/tB26aTkaZpbi1Q4EUXsQ7BFW+EQZ7Z1BZypV1idhdFLm/CP3BEVyza2lT2AhlXBIwDGV9I6ysMKy4NoHJfvikDvtZkh+ISfx76sIrfJZ07MQwiMjSQjx5+6ykhOaZFvIhAZiDgIJ3rx8u+m75Wc4p4U+S8s7yi3+oDXC/Ju2ja6h+RDmUVEyLVo+5b97e2EXaweA0fwYaoTsNfAQTDc4jwIR9AH/PZLqWj44T47/jfa0vT9EaNwSvz3pObppawi/iA4Mb6IVWFz/8Mewvkun0Ys21ZmVIOHDochxBuFa/O1W2e7vrKzHKfedq5sGg8qb5i/EQHD5nwd3GphG8h5gAhtFbG5alVzp0cbY9fHm2F1xPqsDCo7IHdjDcfQivucQm05h24Th8y0RlhHxq40Gdol1a/VPSQr9nRuR4TFn3BhuBwjMowazyIt7Ju/hPdwJhuT7nrpvvdXmUcozBr6R+/VI8dACiJKemgOibX9THftxE3uMaaLnUuMlztd5bg59w==
*/