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
Z53kk0xQ3sfHzLLfz0eYJcu5h3RFcC+WwX1YHQ9ibTyEDfBT7IVHMBS/xIl4DKfhcVyOX+P7eBL34Sk8gGfwGzyHN/A8/ogX09ejvFuPxQjG9biFdC64DQvgdkzDuYRUme6QrEd3QqJM9wrpCmNuLIN5sALmxYbojs0wP76GHujCzApiVfTEruiFPbEo9sXSWJP8yqAvlsM+WB7HYwUpXxuC8p46TpXlykZQ+6cbyvmlK8Zj
*/