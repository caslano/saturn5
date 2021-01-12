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
RC8xVvTUDuPELP9eIXaKqt+pi8gQE8VcsUJsF5W/1w6ilxgpbhMLxUqxXZT9wX5MdBdFXlcfdlSH/uI2/54vlot1YqdI2WUdELNqeg+zxcTcYbFMbBRL/K30j8ovNgd9KXcKnr27WuypD+T+tX67H+RxtQo+b3eu4WXM75P539M3cvu8vp1FPX9n0E+yPp5/+5m8U2v/4nN59QddsO/k7Yb30H9y0Ff03vejXK9OYV93ha/C
*/