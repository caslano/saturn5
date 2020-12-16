#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_UPDATE_C_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_UPDATE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, int N, int C>
        struct update_c;

        #ifdef BOOST_METAPARSE_ARGN
        #  error BOOST_METAPARSE_ARGN already defined
        #endif
        #define BOOST_METAPARSE_ARGN(z, n, unused) , BOOST_PP_CAT(C, n)

        #ifdef BOOST_METAPARSE_UPDATE
        #  error BOOST_METAPARSE_UPDATE already defined
        #endif
        #define BOOST_METAPARSE_UPDATE(z, n, unused) \
          template < \
            BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, int C), \
            int Ch \
          > \
          struct update_c< \
            string<BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, C)>,\
            n, \
            Ch \
          > : \
            string< \
              BOOST_PP_ENUM_PARAMS(n, C) BOOST_PP_COMMA_IF(n) \
              Ch \
              BOOST_PP_REPEAT_FROM_TO( \
                BOOST_PP_INC(n), \
                BOOST_PP_DEC(BOOST_METAPARSE_LIMIT_STRING_SIZE), \
                BOOST_METAPARSE_ARGN, \
                ~ \
              ) \
            > \
          {};

        BOOST_PP_REPEAT(
          BOOST_METAPARSE_LIMIT_STRING_SIZE,
          BOOST_METAPARSE_UPDATE,
          ~
        )

        #undef BOOST_METAPARSE_UPDATE
        #undef BOOST_METAPARSE_ARGN
      }
    }
  }
}

#endif


/* update_c.hpp
LfN2k+e4kgBOz7TcSnfuJKsjxgaKzxpU9hBTlkp+I/lxkt8fqE5be2/3vWydymQtX/SqB2CdeqmcH5ssFI+DfVw08/hKgZDbj9YzmzrOSmBT27e14+HjWrHQXsPekasXCYN4aGuK05aTWuN+d8fq9hAcsp0HDuBFjj0o7e7fnz2/t29zBn8j0cSOQ7sYlVKN9ouSvv3Z7sPYtHq7sjaNrIAd6O3C/9ni/u7eg/cZXAYWJY8JkwWkD/Q63kTPB3GSHhxE4DK84fX2jmzH4DJu/rgNJrKYScsAm8bO39zWfqywZdPZm9rad9XNr534uaitvVwZq4xUhDD6D/cnco3+ze7t6ezLmhS6+/AHSvdCgt290Z/wkg7Ak9kF91ck4Z4DSFmF+z2ADvX1mkgmg5T8ua+7rX0/CD+w1NaetxOhUDw6SLye1zU4UKmM1Qf39ePPji0bOjZtyGw1kM6Bvft2dplpmcjCzM8UFHhGL+u61+CBWmUEAadtO5G3ut62BuJbO3h+qQxjs962p4TTQV/PwM4L+rv3DG7ZsG1DR1x7cHJ8WbMUOjYltcDEpg0dWzdt27xh0+Ak4vRnTmTL5rMNETvW0JV3hG5FzDe06TXQrO/Bz3vx8z78vBh64/34959u65/pM5FAJu6o0wNYZhcENsu7aU+4Fv+K76KhO6EFsyPjJpHgliF5T/aaGGaOuB7sGoJBOVM1cU/NOhwooY5/mwNnHd9svhyru/MNbI+PBHvuDcZend3acjvofonKbqSyy0XZJ6hsUJR9kspWtnLZp6jsswLv01T2GFOWag/CMVbtx6dU/+zn0Y6tkcUcwNElSosG/5ELP3ubAdN+HdZrLtae+FNtG1BU+fsy2kGNWvxhpDUErL/h67RPP8X4N9LJCNNE4+FLwVj/EG1k5re2fNu0EfZ/2xbTfcL9MeFOtrq4P1kV48JDR7g/IdxLDV0q+ymVbW1N3Z+hvNqfbwX9+Q3aeMaC1pYHmJidJs8acI7AR6C9PfBd1T6+aXayHuk9t3EciSs4qzTfXmFIy3H0g9TnJNDCLZfmn76ZaTV5/gEthc6PAxmf1A5LfZE9m3ybyk5D2TdRttyUNTu2hXwm+kUvlbjt/lw9f89FO6aK/ZKP19FilONy0z4ZBz9xNWdehmEd2sZwG+1Wji72igWZu4lwaCl2NK1f436Y52GCfvxG7cd8tLWvuytjn4Xh8gVU7ue/mE3lcf4LI/MVKPvpGfa+4btNy3yr+SFO/bH+o8rrmqjtrZbVW7l8HZUTq0n5PancsNrsm4QxXzQVPL7+qq7DdrSDOuFrNXT22WTks9TK5/tN87HF/DSQT8siTT5bov5uCeSzjcp9+Wy35SnlY/nS5XOnRZp8zkY7qNNQPvcD/IFntracDNwf0jreQWWnm7ImeRsz9o79rcjspEXa2bob7cCRWpPf0t6CgTJp2Wu5vJNPZCdwrYNzcqKE51nKho7wFeNBRqRdbe579JjX6P5Z9S+dtkiLD3hAu+snxbZkSdB3I+sa49nIWoG9TMdlBBqfvYD/8UyrZ3/U5FgcKQwPTozVEYNRU+6w56rz5EC7l/8SDsSMuS2YDme0OEU4/AYacOK2YWk5vugBWR/u3zhhEHD0+geyZqSa8imhz+anwT3tGYv8/et8tPO45a0tK4zt0uQ+a9oYxa9Qpm2LNH/sg9DGbiRWyvZM0XzmOftgwEzOIqkrHpLg28kc4x6m8nhOFPD/V4L37YD9lPozbPZelJ0iykZR1raitWW2KWty/8ehQtEta9U5UwP9CkhkUSl+eRTzplI1OMEbKHkc/suTVcJDXxwcjBv585mQUZjx2qs7bUFrWDTKbsJ7/Kk=
*/