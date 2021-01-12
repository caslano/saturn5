#ifndef BOOST_METAPARSE_V1_CPP11_ONE_CHAR_EXCEPT_HPP
#define BOOST_METAPARSE_V1_CPP11_ONE_CHAR_EXCEPT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/unexpected_character.hpp>
#include <boost/metaparse/v1/cpp11/impl/is_none_c.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/accept_when.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Cs>
      struct one_char_except :
        accept_when<
          one_char,
          impl::is_none_c<Cs::type::value...>,
          error::unexpected_character
        >
      {};
    }
  }
}

#endif


/* one_char_except.hpp
rMLZ3J13syof5B58jNX4BPfkC6zO11iDbzGFH7AWv2JtVpbWOqzGetybe7Mx6/MI/pbd2YAnsBEz2YTZ3JcTuB8nsSkL+z8Lz+P4qkju/6yl6aqzHVvxUHZgB3ZjRw7iYRzGThzJw5nJIziOR3IyuzCfXXkVu/FaHsXr2J0P8Rg+wR58mifyGfblBi4XsedtPC/8rqoploZ0fxLa3/qMR3A90/k5c7mBZ/AL/olfcQW/5mp+
*/