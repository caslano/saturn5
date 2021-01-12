#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_BACK_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_BACK_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, char C>
        struct push_back_c;

        template <char... Cs, char C>
        struct push_back_c<string<Cs...>, C> : string<Cs..., C> {};
      }
    }
  }
}

#endif


/* push_back_c.hpp
ztnec1u0HivCerQXlcUB4tmCme8cXw9p8Rp/fHpsRX7BsRutR3J6E9OWeB2bUmXz6+8Lvt9552Ln3SHeZOemjkwv9b6dUyFq+zqerrbmqy8Gh3I8zwqmC/MOZWjjbWAnpnNdWGhdUV7UFq9Uk85d4unMyx5SYO72lI1MzL/E5S0I/QC8HbbZK2JPXxyasLx0v3JGyOjS9Puyte0lD5Rfci1IaFs/yoN4v2Hb3qYHJfQHkNxH
*/