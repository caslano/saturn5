#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_FRONT_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_FRONT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, char C>
        struct push_front_c;

        template <char... Cs, char C>
        struct push_front_c<string<Cs...>, C> : string<C, Cs...> {};
      }
    }
  }
}

#endif


/* push_front_c.hpp
OXa1Lu1EkyFiKOsfFbmyHX3mZ89F1hdDxFDWJRnrgAL3Be0m6d5mV4gYyrpUkfPrrEMuWIOs50PEUNZlGWv/AnfwXTulm4p3c8RQ1uUZq9wQ99346lpkMY4YyroiY+1X4H4RX3kGsrZyxFDWPylyFf3y+259D7Iu4oihrCsVOXrNP95fugf4MUcMZV2lyN3hoIm/kqL39yLEUNbVilw33vbhUw9A1jERYijrmoz1/gK38zPfkDrR5ggxlPXPihw=
*/