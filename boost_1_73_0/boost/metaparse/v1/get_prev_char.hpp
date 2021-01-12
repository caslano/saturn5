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
xXa8Zm7B7XZF0vDyYHhPy7tMbHkPGjawwPqujfe4vqf492nlcqeRZhuJ1uvYsgruT/15e4/Q1uu1yQDDNcNyBveDK0Nue+eNN94468SpcucE44X7jipqFe5FtXViGdSeu+dlMDZoxA75y4DCOFvmRssg97PsX1kGjeYVbPMaScNV5/3+ZfCw/w1MH/hPL4OKiWUQbB95u8dsU8hfFru0b2YJYXj0A7+8LFKMkyFyl8WcB/Zu
*/