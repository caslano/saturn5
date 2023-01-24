#ifndef BOOST_METAPARSE_V1_CPP98_ONE_CHAR_EXCEPT_HPP
#define BOOST_METAPARSE_V1_CPP98_ONE_CHAR_EXCEPT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/unexpected_character.hpp>
#include <boost/metaparse/v1/cpp98/impl/is_none.hpp>
#include <boost/metaparse/v1/cpp98/impl/one_char_except_not_used.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/limit_one_char_except_size.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/mul.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE,
          class C,
          impl::one_char_except_not_used
        )
      >
      struct one_char_except;

      #ifdef MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE
      #  error MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE already defined
      #endif
      #define MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE(z, n, unused) \
        template <BOOST_PP_ENUM_PARAMS(n, class T)> \
        struct one_char_except< \
          BOOST_PP_ENUM_PARAMS(n, T) \
          BOOST_PP_COMMA_IF( \
            BOOST_PP_MUL( \
              n, \
              BOOST_PP_SUB( \
                BOOST_PP_DEC(BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE), \
                n \
              ) \
            ) \
          ) \
          BOOST_PP_ENUM( \
            BOOST_PP_SUB( \
              BOOST_PP_DEC(BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE), \
              n \
            ), \
            impl::one_char_except_not_used BOOST_PP_TUPLE_EAT(3), \
            ~ \
          ) \
        > :\
          accept_when< \
            one_char, \
            impl::BOOST_PP_CAT(is_none, n)<BOOST_PP_ENUM_PARAMS(n, T)>, \
            error::unexpected_character \
          > \
        {};

      BOOST_PP_REPEAT(
        BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE,
        MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE,
        ~
      )

      #undef MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE
    }
  }
}

#endif


/* one_char_except.hpp
57fC1Gogdi8AG/9k4h8LZZVlyYhniT7PSku55wXRb19NSa7hIJUSELMr9pJ6ezlyZrHPs9rpH/3zP1mK7iKbf7xF9BfMIh+texB6fIb8459sR6wkYEmH9hqTO1bKS4bGRmDao4ulqalATYthJ73TNIR8vgRNtkTPJ+HSbJ6JZ8Jz4mJedVVCL3K5gH19mtVxVcz7T+p0VOeHvaZ3X08VTFgK7pUXwfU86LNpJXh1AaZu2XEaK3rlNgvjmmEGowSRk1LkOz6hJ3Ob58ahSZeXUuwbIbImowByW5rNl5fWXpNKx6IvL729JhohxJy8vrxMhh9WCslL4rBjCjZfnqm9xkJ3nL68YbQ+Sm5cRPqrVB2mtMMqJQTskwOxvgQmZdaxRaDxc1jPt7FIGkrOcHuwZqg6V6cWYGGRLhyQMjicA3Aqz2qEzkijCGGKhsYswqLPtbLcdY5Ot/mtFpvPXl7sc60W/SPb3tVT6bUirccfvRh7fGTFu9jjnlQpHntcxP0kVF9kXBINjHHU+dK4NPixSePSMY5DGjcMfpzwS8Xa8rH/BorS5BRqd1tqKFeMS8UYbI0VEokVtitmC85rmPPdw8g662JKY+xWyZo9QM11zcn662ye61qv1labm81qq00LjU2hyJT70lZjEmNG0bpBqtDIt2LRpCYKQ/m8hSTeOkxXTtIPZJ30CuVA3wvyDsUHULAXUAs97dXylIto
*/