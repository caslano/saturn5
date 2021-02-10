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
dkApFHbAKnjxAW6FR9xCESYLXNgh24XNbjVeJbBsKmZth7ZsbSdAg0mMoIbTCMBW+jNoeQ9WsHAAuZLNmuUlwAuSXPLtCfyMZAP87Sv8p44Lwp/AL3HeZPu7aGwJzxMnBxxHTg4YNlO76XJDELArRGL4No0wm1tc4wAHVE4pqAMbpoJgG4DdEZpwjUclkKg0MypdyQd+zj00YW22lSQBAtMkF5fWn2DELu7nZRY+KTV1aDk7tJ4EKrhwAVhFjhzjdgu7qjFmB3dVBLOBr2qAWmE3Q3BbfFKI1xWeFIBX5OsAvkKgD9Nwo1mYkAi11GpqTogUhi4zxoRNwbG13P8EnAo1DGgFrmjALBRvQK7iHtNi61yKKBOW4Y5/APaYetqiEU3Wt7Adp33vgi6Qzkmw1zPYvVB+rA0vEUFuP/t2tp+BEJj9DJSQ7Od2SiBCkMZUb12IDBBHYHJNRFCOpQ+YJYgD3Pz2gQFAbOSHMraE3bjTDJidDaUTO6a6z3ZMr54x8owts8HYM46AZCs5QjFbygDCCS0BftFiDjbm9Bx3ddzs6rg637satnfNvNbY1Mp4dAU8m4AzhJ+2ZGORLxO7yis6GeDFsOgIvmJYdEyaVfkcAwoLoceXZYcJqpmeWKtC4SKkNDXr8DZBGIXC
*/