#ifndef BOOST_METAPARSE_V1_GET_PREV_CHAR_HPP
#define BOOST_METAPARSE_V1_GET_PREV_CHAR_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_prev_char.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_prev_char_impl;

      template <class T>
      struct get_prev_char : get_prev_char_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_prev_char.hpp
DritMp/m5/sERc/rIRu1b0P8FPdjEBwoYon3pMtNtQFZeBud4AhTeyi38IoSlC0Hct6kGlGTv8u19Dh6P1JunCB2n4ktQ6YEp8NTh1Q61hk2jVC7gRMRFAXvgG+ErNH+vZfRejYHs9zLpGuj9Kfhnp1aQ34/NKAgNzXDzdaDHIxgqkt5TjvH2vJcqWvaiVYwohU9+U3u2RN6+cEw13MMazFUQ/yy1wm1PQdhqwKZZi5Zn1SuhveFdx9o03jcd7Y=
*/