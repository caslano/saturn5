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
auQozB2+Ae9sI6evUDGgXKiYUg4WsvHwADbJpdqkAwCTjRKUjtnDxHKqbJyHm3TY3kz+3UyevBa++mFv/KpVWFVXXLbXM9Ze2u4ZbZe2WCt7sF1aJ5vVdtZ5FKW7Fu6HFoCPWCOYQfNH/vx9IDLrsEEB0Wm9FkWo+fkWxOg73C1g5pSbQiB4YLZ/pIU0PBSA0DAuRmDWrmh7uYc5V2dzpeXpW/gAiw4tCbFQDJmJp2n54t1pKQWqz3BNsEb0bQmqz/Ba0EsU83j4ms/+Q8lo+XYck6MB94WYjtPv2i3j3jeYKKftFqmUvGQAlewHSq6bglMvOhrDU+6CUr4bILTvln89qWAc20hqp+cxlLWuH6xrsDqx3W+FCbTgF8U8AZOWeRfv1nly8AI9e4GHsi/sdvguAj36WkT7pZsZ2myH3C0g6+dmcpQxP7RrN4zLfWzOdUGrG/aFTrjF+9UJF4Dhk23BbpR+m1+MmG0LfpErXiT1HVocD++1zsdM0rOaOskTNPtuJTyXdArluSrAPEmaqqPEqeTtwARJmNi1Whw0rRlax0pSqbcZdHL9Uyw+d8Ft8KlmFOsCxpONgp6gunWB8fBGAyk7rgZQhrN2Iy+ao9t0WjU+MLjgCWgbU5S4GgLR0FIDc1J4ZzToVKOMWqdrzbpgcb7dOjKf2vBPE/6RwW5q0VH/uppQf8cNAS3coeKSyTIEWNoAlqvIvtlF
*/