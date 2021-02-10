#ifndef BOOST_METAPARSE_V1_GET_COL_HPP
#define BOOST_METAPARSE_V1_GET_COL_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_col.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_col_impl;

      template <class T>
      struct get_col : get_col_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_col.hpp
pfGJAlF3N/dYu9Y2sce+tqvYI+QVI3g/ll+/+B9QSwMECgAAAAgALWdKUnmbcQboAQAAHwMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjUwVVQFAAG2SCRgZZNfb5swFMXfLfEdrjrlpRpzUrUPtWi0rKuaal2SJazL+jK5cAleg42woaGffhecJpX2gv9wfO7vHkPk0LpEWhyzSOnM0PCM7YupUjtm0zhe9A8oK7NrWe5c+cdPtfFjxI/yiHsH9gFWWDVYhValyKIKy21Lr1PppDflo08jOBsOYf6NfZUOBcQ1foThJcxMQy9GQxidi/NLQZLb7zHzdgI62ND2C57JZ2TXRjvULrxHvXG5gPPDTtyW2B3YOZ67YstYZgwReoaI75kI9XqrOr1HTfoFCXyRcd8yyd+WkZYFRTVJErQWJGijwy4IhSnkxjp4US6H2iq9AZcjJKZ4Ulo6ZTSYDI4BAuoGGlmB1CmE4T5OMGUnpYK+DmFQM834XfJX3VRwntZF0YrBYjlf/17MlzHvKb06orIFGftzJK6JX1hMKnSfB9P5Kr5biEF3Ef3J0dnF8B3DXkA7hdyFThUIF2R+8KTpPiVK7wErlbXQxQoyc1j1bXf3BLm08ISo4cTmxp2wqOm1
*/