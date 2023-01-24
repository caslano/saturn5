#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_POP_FRONT_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_POP_FRONT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct pop_front;

        #ifdef BOOST_METAPARSE_POP_FRONT
        #  error BOOST_METAPARSE_POP_FRONT already defined
        #endif
        #define BOOST_METAPARSE_POP_FRONT(z, n, unused) \
          BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) BOOST_PP_CAT(C, n)

        template < \
          BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, int C) \
        >
        struct
          pop_front<
            string<BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, C)>
          > :
          string<
            BOOST_PP_REPEAT_FROM_TO(
              1,
              BOOST_METAPARSE_LIMIT_STRING_SIZE,
              BOOST_METAPARSE_POP_FRONT,
              ~
            ),
            BOOST_NO_CHAR
          >
        {};

        #undef BOOST_METAPARSE_POP_FRONT
      }
    }
  }
}

#endif


/* pop_front.hpp
k8m258EsBlY3r4zwJJAB0//udA7+2ukrwHK0GJvW+qru7AAN5pnCgwAFUY0E7eJuQDuClYn/O2gnPtCx6ozi4M0I0hrKCov1KnY4scKpVAOj1asYhBVYdSqCoE+fFf6lj5ybmPfPjITYbTkPaMd/wAi51zl4r9M3LcUpacQMCOqJS9oDoKcw0F1SrVeJFla8Hd0F+ufPDv3Sc0P/YXEX6K3nAX35+4zWijj4tOhbnO6UghhgcfHgmUPqdGKJEBUFp7TduzjJKKzYZwhFA6sBISbS2TGZe25MfprRBZOc88Dky/eCXKPCjSki2BEbibhQieu5GgYwdwASMcKK1G6ReObsSCw8NxKpXZEYfR5IdP6TMdOPzsEHgeipCD7CTNWjtTOXtJ90j2nQMV9riLik7wCXWGHFLVS4Jcb0/1uPTL7r/9Qjwzgy7c7BvyH4CHAgXj1y4QKUXYd5ICV7ioaCQ9oHWJiEFS/ru8Xi8bNjMacrFnHimmBGd4bMY9O7IDPyPJC5/R8hAwVQwDpOLlAbOhkSBSaGhSs9FI0eworvdGFoYCkCwOLRIBbWnBFhWNxzXlhU39kFi6st5Vm47OPDADK0c7rB4sV3g4ME6+Fs6wp9QSoDP3C5A4c6IFOTBZP3rkBUVrtTwqiudlH9OcN+tuHGsNmoF83C7xWhNxBmbNAnkZqik/aJYygJC1hZh5M4L6Nq4Rs3QUmRUEkp
*/