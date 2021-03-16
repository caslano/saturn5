#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_AT_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_AT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

#include <boost/mpl/char.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, int N>
        struct at_c;

        template <char C, char... Cs, int N>
        struct at_c<string<C, Cs...>, N> : at_c<string<Cs...>, N - 1> {};

        template <char C, char... Cs>
        struct at_c<string<C, Cs...>, 0> : boost::mpl::char_<C> {};
      }
    }
  }
}

#endif


/* at_c.hpp
6iDlDcHN+6tiuhP1cyp5JFUXqVaeb+3rd+UT1b47eSRVDyl/LPrCqZ/mEZXVnTySihdlGLl470GibutOHkklIOXPiWrFdP6eqD3dySOpRKT8vnL34lNs5PBXd/JIqr4ow1bZk65ipdGDPJJKEmW4J2FjT6Iu7kEeSTUQZdiy95OsPbytB3kk1TDA63xa69fYitm+HuSRVCNRht8uXvIRK40e5JFUcoC/y+cevr+CqNSe5JFUY6T8NaIjof7sKec=
*/