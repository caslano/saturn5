#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_SIZE_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_SIZE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>

#include <boost/mpl/int.hpp>

#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct size;

        #ifdef BOOST_METAPARSE_STRING_CASE
        #  error BOOST_METAPARSE_STRING_CASE
        #endif
        #define BOOST_METAPARSE_STRING_CASE(z, n, unused) \
          template <BOOST_PP_ENUM_PARAMS(n, int C)> \
          struct \
            size< \
              string< \
                BOOST_PP_ENUM_PARAMS(n, C) BOOST_PP_COMMA_IF(n) \
                BOOST_PP_ENUM( \
                  BOOST_PP_SUB(BOOST_METAPARSE_LIMIT_STRING_SIZE, n), \
                  BOOST_NO_CHAR BOOST_PP_TUPLE_EAT(3), \
                  ~ \
                ) \
              > \
            > : \
            boost::mpl::int_<n> \
          {};
  
        BOOST_PP_REPEAT(
          BOOST_METAPARSE_LIMIT_STRING_SIZE,
          BOOST_METAPARSE_STRING_CASE,
          ~
        )
  
        #undef BOOST_METAPARSE_STRING_CASE
      }
    }
  }
}

#endif


/* size.hpp
SCRgzVTbbuIwEH23lH8YpeKlImtC2UqNQqSqVG213YIg7T6u0mQgVoMd2Q4sf79jB0ql/YF9Ac/F5xyfGUgtGlsWBjOWCrlW9PWBh73SlcnYY54v/Ac83Ocs5edKyvtmdsFSjW1zoFRV2AKkKmssP6bhAU3YI/D4Wwzj0QjmPwI2KywmkHc4hNENvKgdVeIRxJNkcpNQz8PPPGAr1DvUCThtkfEBXxcfGLA7JS1KGz2j3Ng6gWufklhaoWQCZaPMl6780KJD+WN5bbdNwAIWj68m30m+E+uecRRP77iAu0a4W0ZUyNLSBxmlbS0MaKTYgJIUIlT43m1gjYXtNIJVUDSN2kNn3NmghUpo0qT0wSfogO4egUVzUJ1tOwtCDumCkBuPePe6fP6d36/y2dMSdoUWxXtDKo4U5LinJMHnTNo7k7Ha2pYqpzCVxRazz7nBXtja8UbCH4keTgbNhGmVEc684WcxmhFYj0EU1LfL2Fd508Hi14w3auM5+3paqu22kBWo1oFNQ6mi/p1DOglZNl2FYS814XzwOF/lT4tk4EQu5sucx1eTa6cwmhPqEczN5zQGP6A31GJ9AL9oxdqi9ta5LYG6MPCOKCE0tbIhS3e+lyBarawqVZMxZ0ZPdFrLgD0qYxP4R0/AXsnO
*/