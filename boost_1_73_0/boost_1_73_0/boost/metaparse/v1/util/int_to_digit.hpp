#ifndef BOOST_METAPARSE_V1_UTIL_INT_TO_DIGIT_HPP
#define BOOST_METAPARSE_V1_UTIL_INT_TO_DIGIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/int_to_digit_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class N = boost::mpl::na>
        struct int_to_digit : int_to_digit_c<N::type::value> {};

        template <>
        struct int_to_digit<boost::mpl::na>
        {
          typedef int_to_digit type;

          template <class N = boost::mpl::na>
          struct apply : int_to_digit<N> {};
        };
      }
    }
  }
}

#endif


/* int_to_digit.hpp
9vWX2g6fmFn+wX1/2/uWL833DmPn98X25/c3jnzoylUDbzz37bQhR595GRY0td/wzCMffv5WcfGytzw9gZ8/fYCxbmpfcNH4gheH3vvCsUUbb3n31kNuxl6jdufGlY7Pflhr/ceq+x8cuHrMr6CtH7av2D1oxo0Z9u+rxg7a8r9j9+5kbBa1b7xzwS+K7nipbe/Q79ccKRxZBpaF2v+57dZ+w36y+IWLfuhTMma9Zx9jj/P2CufwrsLld7yaN2s=
*/