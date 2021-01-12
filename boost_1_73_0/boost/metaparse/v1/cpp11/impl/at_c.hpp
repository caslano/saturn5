#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_AT_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_AT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

#include <boost/mpl/char.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, int N>
        struct at_c;

        template <char C, char... Cs, int N>
        struct at_c<string<C, Cs...>, N> : at_c<string<Cs...>, N - 1> {};

        template <char C, char... Cs>
        struct at_c<string<C, Cs...>, 0> : boost::mpl::char_<C> {};
      }
    }
  }
}

#endif


/* at_c.hpp
d22vemTxc/rOScPfHZHURlXS8JKk4YeO2HobVg9Z/vRaYZ8NedoiefuG8VOMb1W1cPyQ0Gh38j1DNI/5RftdTrqWmMdE4zMS55GXnZca9svu0fR+ZPmbe6PCfW1uGB+bdEg0r8K/tSv2t/j3GvjbjOJ/i1pzygt3AbFlLizaV4vPd1bid+NfiX2nb2L6Q+YUjO8czSue/ti9y+SQ/31T4m03rw51WXNE7HcdrxMporJIEz6x
*/