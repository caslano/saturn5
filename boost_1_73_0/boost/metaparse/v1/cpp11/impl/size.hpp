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
DfkoJ8v3JfF0FP6yHOKAn5A+zoZzF2FOOYXpqb+d6alR1A9N2LbZacX6nbgmdp8WW2LJ+R/Pa9farf9O3VjCc4B1SX1zFOz458uDqtZ7QNWEsrfRcRuV0TXNVLHS8IwwXe3o+WAoIyjVo3MKZhyVwQ33Rakhz5N/k1StGbXdaBlkLO/z90jK+9hVM5bp23zWGR2Lk6on9V+YNJxWMPxfso1myPcq8uoj466sVqyehekK7/WH
*/