#ifndef BOOST_METAPARSE_V1_UTIL_IS_DIGIT_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_DIGIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/in_range_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class C = boost::mpl::na>
        struct is_digit : in_range_c<char, '0', '9'>::apply<C> {};

        template <>
        struct is_digit<boost::mpl::na>
        {
          typedef is_digit type;

          template <class C = boost::mpl::na>
          struct apply : is_digit<C> {};
        };
      }
    }
  }
}

#endif


/* is_digit.hpp
K+/JemI3wmbpi/XXnJwPoCvLWx+zYmvMiT3RHftjfhwk8XewAC5GD1yBhXA1euImLIqfYnE8jSXwEpbEH9EbH2NpzEbhyqAb/g0rYnmshxWwFVbEtlgJX8Mq2B6rYkf0QRPWwEFYC+OwNo7HujgF6+FCrI/LsQFuwlfxQ2yIh7ERHsfGeAmb4BVsirewOT7CFpiFumyJ+bAVemFrrIBtsTm+hn7YAd/Gzjgfu+K72B1XYQ88
*/