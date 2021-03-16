#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_PUSH_FRONT_C_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_PUSH_FRONT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, char C>
        struct push_front_c;

        template <
          BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, int C),
          char Ch
        >
        struct push_front_c<
          string<BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, C)>,
          Ch
        > :
          string<
            Ch,
            BOOST_PP_ENUM_PARAMS(
              BOOST_PP_DEC(BOOST_METAPARSE_LIMIT_STRING_SIZE),
              C
            )
          >
        {};
      }
    }
  }
}

#endif


/* push_front_c.hpp
OD64cFDrU0pS5AwZ14ZLMF2ck6Y/eJh/KGHAnLeFCL0szRoRFbiG9TlAR2XOSqLzHvtDAHxHs93DeFIUeBFHm0LkBhl1kXEtRWTCcU9MYXtSAC+cnsVdUjqz3DIh+UpIz9JHFr0yM05TIXyeEpAO5OE7pCw4DWp5+RbUqzrhtrHfF96FMu2w/7kWtTFjg7ZtC0YcTYlY4YRhZwJYoOSyqQbWSY84cQ8qRZkquQzlng7rXnI2CZ1EVtgqB+fu2zc=
*/