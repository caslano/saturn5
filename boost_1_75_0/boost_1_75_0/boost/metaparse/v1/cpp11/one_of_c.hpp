#ifndef BOOST_METAPARSE_V1_CPP11_ONE_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP11_ONE_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/error/none_of_the_expected_cases_found.hpp>
#include <boost/metaparse/v1/cpp11/impl/any_of_c.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char... Cs>
      struct one_of_c :
        accept_when<
          one_char,
          impl::any_of_c<Cs...>,
          error::none_of_the_expected_cases_found
        >
      {};
    }
  }
}

#endif


/* one_of_c.hpp
Jy6CvVWOqrNTgKvO3+9X52SnlUc6Rkt1uym9Y2OKtMpGF2pbMAHSrz7lV3g+NAmujQr38kY2psRGw/czwr0Dtp99ysKO2GD4mXfHcBnrlFmsOTB+6W/r56UbbcEB2uiv08NU5splC5F5OtYfDlPdNZoO2FDis9+VR9xn+5SfwxfiRfhxRjgDesIfPuX2jhg3s3Ye2cJEM1+EejbjXW1jya73LC7S62qFp95E9TjcBkGysdfbFkuqJXYeTVibUu7ecEefNV6MLP/b+rmZ0HNFKAP+zgk74cEUS8z+Nh4P3Eff1WXwve977hZpCfpGSrX/RIVp22Sp9u/0xSnVbja+PMBfQnMXt+3Q8dnFeKET7jyHr67qG+m8SVpyjJr5jJ71c5abSFuK0Ux/qVbCGNC2dKm2F32xSrUvI9/2toNas0p16MU+WZ1woXfdVHQHImWaDbbFxR3IiaW90wtp2EzdNXUOcPned1L4fmz64rZ5MJnQyTy80H9wrE345zMcZN01sP9jb8RbCr2huybcirpU4qPdHVKwA2P78jEO2a3zgHzSDN2r6P669tACv/uYXwoe8SrHYpU8vhpz4LC0XvcxrxQ8Frss0nZz6KxImz3kRV+UUfhnAP4cGum0hQbx87GzuQUPfl+7+FtcQrxy5PNhDZG9WZGGLCBoMzrMxn227/L3YxAbIMCMWwBpbHvjWCLVWSme9SXi/Kkyy+uC
*/