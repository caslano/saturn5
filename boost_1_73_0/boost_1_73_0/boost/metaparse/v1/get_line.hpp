#ifndef BOOST_METAPARSE_V1_GET_LINE_HPP
#define BOOST_METAPARSE_V1_GET_LINE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_line.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_line_impl;

      template <class T>
      struct get_line : get_line_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_line.hpp
dOwT6XNQXo/sE+11n9T/D2kX+TV7hBm7X6bLfjmfuV+EmbJfhJm5X4SZv1+EtXK/yJOm/cr7D48wehXZ
*/