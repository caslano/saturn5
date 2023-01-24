#ifndef BOOST_METAPARSE_V1_UTIL_DIGIT_TO_INT_C_HPP
#define BOOST_METAPARSE_V1_UTIL_DIGIT_TO_INT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/digit_expected.hpp>

#include <boost/mpl/int.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <char C>
        struct digit_to_int_c : error::digit_expected {};

        template <> struct digit_to_int_c<'0'> : boost::mpl::int_<0> {};
        template <> struct digit_to_int_c<'1'> : boost::mpl::int_<1> {};
        template <> struct digit_to_int_c<'2'> : boost::mpl::int_<2> {};
        template <> struct digit_to_int_c<'3'> : boost::mpl::int_<3> {};
        template <> struct digit_to_int_c<'4'> : boost::mpl::int_<4> {};
        template <> struct digit_to_int_c<'5'> : boost::mpl::int_<5> {};
        template <> struct digit_to_int_c<'6'> : boost::mpl::int_<6> {};
        template <> struct digit_to_int_c<'7'> : boost::mpl::int_<7> {};
        template <> struct digit_to_int_c<'8'> : boost::mpl::int_<8> {};
        template <> struct digit_to_int_c<'9'> : boost::mpl::int_<9> {};
      }
    }
  }
}

#endif


/* digit_to_int_c.hpp
ka3wNJ9zj4dZf4USo1M2APZBuMDgf4sz0jblw5SIXruN32TU1ern8f2VAZ2Rr9HBEI+tq3DQ9UAy6CvRpN7Cq4uw8ovxhFhwb2XWDnZ0Khx2By5Dw68Ev1xwUBwDC74u4xcMEIA1Hl3FbkBcgnzWTPPeCr6BLJ0fbbyeyKZsjj8suYvfRUuV7k+ulNOAWLBdtWcqJhx9VHgFVXHc3hOogoefRS82AYFQitlDDh4bLcvzdZe2ZzN9N0UPh4Dl5eqNre56YIbRkXQUFXHMkuW2B7wcVsTjTg+fjaY2DDY3EfsvVCJTJRdEhz1Sh5PuogWwj/JBCpPx4rZSTk9kqz5ZZ9ANUGq9JBQxfr8spbF8TBqVIhVuZsSVsJX8ebdAjPQxXG28HPpmY8ihwK72NkdhhDRv7WYB69Q9qSMblMud9Wshawgv/XBN1eXGpNbt4cuJIVstF+6k6BC1orpXgo9TeNnPOBpAj7EfBLTtiroQtusg0FddPxiv2KSGro1htHpJSeKbZ1qKj/CxPEZn/JPOsW9shhxy3ohmxBcAfy5HJk+fOUonoQaMPhSkKL/TC3ccby/hOcp1+jz9xMlQYFzRGv9nSgtySNDYcWvkG3UsmP0Nnd1AKZFc9otOCz7a1Ru98xPXB1J7xzzprflqYw6JLptgDjfSDaY6cl5s6M+1CreTIhtJ5XgdWVUrivhopF5m6vU5+vFl2cNXshOV
*/