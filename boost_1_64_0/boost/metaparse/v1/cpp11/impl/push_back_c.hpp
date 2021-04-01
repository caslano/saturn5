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
WBh1twgp7eHvjrwLSD1dXD+JsbC6P+Q+8o/FRvreJG8oXcILug8ZIDzC1WLno0uJ5wCAHKdJfPqeFo/eO1SMj1QLhu7hV51w1p4dEoZ1ymU9QExB5bKVpB7SsZVaIulRfiXssYj99qHFeAbiybHvxQrw5eSbUSxiqEWTCCRCstJZdCaXVCgW2WtqWmfjNmrepdnSBD80PgLohSzMBDRHM44luecUmU5H2LDWeiLlN6P3f8fZuebullv2Y6rAR/iKjkdrDIpse6DtxpxtLTYR2ep0tdG9ml7q4k5+GnDmFwdEI5lMwIkNP17lWtXA2DVN+XIx0e71PjUxy0PyoJmwjYnLhP8T5kGiVbD9ZeSEiaM9UNmasNKosuzHHky24zns2l6mumuDNeA1zZEWEWSs4+QGh8QyjCLTdEAzMhQqRTfsNWDPQyFfHEYUcFv+coTAe8SzmXdNLJ2RiLjPIGJClCzIf4bHyRkmr3qcE6GBFhlrcmDOdi7PqvqRIvSmOztQAHnqXM2rUy7/ZbVPwJxU20ttxnd7GJQ8vAb7dQxYd/Lc9QRIWFMV885g5A==
*/