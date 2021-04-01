#ifndef BOOST_METAPARSE_V1_CPP98_SEQUENCE_HPP
#define BOOST_METAPARSE_V1_CPP98_SEQUENCE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/impl/sequence.hpp>

#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct sequence;

      #ifdef BOOST_METAPARSE_SEQUENCE_N
      #  error BOOST_METAPARSE_SEQUENCE_N already defined
      #endif
      #define BOOST_METAPARSE_SEQUENCE_N(z, n, unused) \
        template <BOOST_PP_ENUM_PARAMS(n, class P)> \
        struct sequence< \
          BOOST_PP_ENUM_PARAMS(n, P) \
          BOOST_PP_COMMA_IF(n) \
          BOOST_PP_ENUM( \
            BOOST_PP_SUB(BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE, n), \
            boost::mpl::na BOOST_PP_TUPLE_EAT(3), \
            ~ \
          ) \
        > : impl::BOOST_PP_CAT(sequence, n)<BOOST_PP_ENUM_PARAMS(n, P)> \
        {};
      
      BOOST_PP_REPEAT_FROM_TO(
        1,
        BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
        BOOST_METAPARSE_SEQUENCE_N,
        ~
      )
      
      #undef BOOST_METAPARSE_SEQUENCE_N
    }
  }
}

#endif


/* sequence.hpp
a/lw3xXRZ8B0QTIUz5XU/cNvAuzz6uogD+mnQRAiXoSmwyZGNZHQcwNFq5CMCbWffV1B5Q9MVcACF6L5BijyoQhT3Cl9umr77ySkaj5Y7d1cBagQC7M6MVMMermmL+zku2+vM058iPHNt/HlN/IRXjNTMHJqZU17gMOkSs4IkZ60NhcK694xgWkNqJZ7MDL22q3VTOIikHAytKmXX36j1nSTCTvJK3FlBmmMJojnE6tOq4+3WOB64dMrCxIGqo8wXJfLgRS3UPpLEjhmbx2lsxuzAfiu7WAh/EqZmpYSK3xDbt4T3mf8QB0o2Vcq0IU96qpZOiLsezfhjRo0z5vWQFUOYr6sAxqGf8JjPlRMuQ1A8zEUXD1MxruUkU7KpN3kZEAftyukUL6xdjpATkAKefh01D9/Wi0sYXM/9NTEF/Id70xxComodGm6BDgb9Vg9ft85J3UXKkEhrhanUqMaOHqts3id7NPTKlJQRP97w0DzAqQzTGlhYHik9DuQc22oPt+KbI3OaANF7lDb2wVwJOMqqO1NcBz1+f76m+2B7C0HdqKeLJDnchFOPQ==
*/