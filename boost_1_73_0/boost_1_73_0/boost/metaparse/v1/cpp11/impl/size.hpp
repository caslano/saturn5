#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_SIZE_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_SIZE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

#include <boost/mpl/int.hpp>

#include <type_traits>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct size;

        template <char... Cs>
        struct size<string<Cs...>> : boost::mpl::int_<sizeof...(Cs)> {};
      }
    }
  }
}

#endif


/* size.hpp
DWIo69aMVW7Zlz332CHI2m8tYijrNkWOqN2rboqRZaxFDGV9i/hr1y9vkH52brgWMZR1O9H1rn1vkzrspWsRQ1l3EF2/u/fAl5D16FrEUNadRNchL94kTQ6/W4sYytqlyDF/8c9ellhHTCCGsnYrct045/l3SfP8zARiKOuujFV28+c/8oB0c3vOBGIo69uK3FO8f3vjVWR9dwIxlHW3ItfDTSdO3ynl1wRiKOuejFV2vf3euFKazD+0DjGU9R0=
*/