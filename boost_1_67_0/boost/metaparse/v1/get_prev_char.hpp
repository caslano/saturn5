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
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
*/