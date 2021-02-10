#ifndef BOOST_METAPARSE_V1_GET_LINE_HPP
#define BOOST_METAPARSE_V1_GET_LINE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_line.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_line_impl;

      template <class T>
      struct get_line : get_line_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_line.hpp
ZEB1nEnMdsxub2Lw9d8+i4BNKUcB/2EGbFK73FTqtY9TwBdpVQLperZN/pavj79m7eP6x1XAflKz4WRDhAKSutrywcPNcnU3nwX9vZW0fcpPAxZQJ0eSiB/w+PGf+AdQSwMECgAAAAgALWdKUtNBWSjoAQAAHwMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjUxVVQFAAG2SCRgZVNNb5tAEL2vxH8YpfIlKl0TJYcgbNVNozhqalybpm4u0QYGsw3sInYhJr++A/ijUi+wH2/evPcGAovGxsLglAVSpZper9i+6SoxUzaPomX/gLLSu5Zl1pbPw3IRPi9X4eY3C/gJH/CBgn2ANVYNVq6RCbKgwjJv6ToRVgys3PvkwcV4DOE39lVY9CGq8SOMr2GhG7rwxuBd+pfXPkHuvkdsoPOhU+uafsNT8YrsRiuLyroPqLY28+HyeBK1JXYFO8szW+SMpVqTwkFDwPeaSOpNLjv8IDXuNwQYmkx7zwQ/bAMlCspqFsdoDAhQWrldIhITyLSx8CZtBrWRags2Q4h18SKVsFIr0CmcEgRUDTSiAqESOKR5OKSGQx+SQWaa6T/RT7qlz3lSF0Xrj/q6ZbiK+HEmk9E8XEf3y172UB6QjoI6DURU
*/