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
Wl1tkLbZUJpvQ9Ca1jcr9U+4RPymbntLIK0v9UCbshIfY+gbWablnV7qmvyun9emHSll4lEjJW6Rdm2aYJV4mPxd7StvIfNpmM3W5my5oLU5B0i66IiQQFNMTFS0LEc/aV+NIAO1DvtIWtJFxyBltGtTHiLzvcuE1vgUQ3yDxAOkzfmQ4e8XDPGHWtyu/+MA6ct/M6EwYSUhgG1lD9ssvzXlU9dsIhnusyc7iZSJdPtWdT2o
*/