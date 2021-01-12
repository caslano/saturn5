#ifndef BOOST_METAPARSE_V1_CPP11_ONE_CHAR_EXCEPT_C_HPP
#define BOOST_METAPARSE_V1_CPP11_ONE_CHAR_EXCEPT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/unexpected_character.hpp>
#include <boost/metaparse/v1/cpp11/impl/is_none_c.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char... Cs>
      struct one_char_except_c :
        accept_when<
          one_char,
          impl::is_none_c<Cs...>,
          error::unexpected_character
        >
      {};
    }
  }
}

#endif


/* one_char_except_c.hpp
z2/4A3ezkB+Zwp/YhjsU/O5jed7FCnySO/FV7syV3IXrWYlf8jfcS3or8xBWYXvuSuulPc7oWZZtF9armcgzwkd7t/ZXNuTebMTGbMoDeQA7sRm7sjl7siWz2YZnsj3P56G8lB15GTvxKh7O63kkn2QXPseufJnd+CqP5tvszk95DHeS1p6szGO5B3uzJo9nfZ7I/Xky23AAD+NgnswhHMpUnslhnMbhvJFpnM8M3sFRfJGn
*/