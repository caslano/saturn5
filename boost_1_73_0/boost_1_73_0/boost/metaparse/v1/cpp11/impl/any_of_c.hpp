#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_ANY_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_ANY_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/or_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <char... Cs>
        struct any_of_c
        {
          typedef any_of_c type;

          template <class Chr>
          struct apply : or_c<(Chr::type::value == Cs)...> {};
        };
      }
    }
  }
}

#endif


/* any_of_c.hpp
yUjWYt/WlTySCgR42/th3dZs/XB3V/JIKiLAyzB23ZlMov7oSh5JRSKV6PkaxK17m6iUbuSRVBRS/vzrzorebEY/pht5JBUd4GX46e9HLyWqsht5JFUDKX+lomB3zRlEbexGHknVRMofs01+L4m12J92I4+kYsTzGnTvn/8lKjGVPJKKDYg26mCH+4kalkoeSdUSGaZvPbacqLmp5JFUbaRiPN/eX95jLcC9qeSRVBxS3vDR/FJ2wXSink8lj6Q=
*/