#ifndef BOOST_METAPARSE_V1_CPP98_NTH_OF_HPP
#define BOOST_METAPARSE_V1_CPP98_NTH_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/nth_of_c.hpp>
#include <boost/metaparse/limit_sequence_size.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        class K,
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct nth_of :
        nth_of_c<
          K::type::value,
          BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE, P)
        >
      {};
    }
  }
}

#endif


/* nth_of.hpp
2zAUfb/g/3BpCIUyTVYWxmqEoXRdU7o1ofX6MvagyNcf1JGCpaT43092vja2pzGYEPq4HJ1zrq4kPTmvlaMUZG0KG6YX6l5tm7sUZlm2GAa8vcmgbOxyWZsSGCtU3YDkJ6Tku8MgW1o3XQjkyqsdAxdvBU7jKc7v4aPylGC2oTcYX+KD3eIkFjGKaTK9TOIYb79kcG2NJ+PZZzKlrxJ8D582xnSsIpUn2JELHYAZa1nQ3ekMcuInvUkg+2u9EDGkfW1Ngrqxjv7sIIwHB2JvQVekX/6fjb285PsqwAhGeN3UPa+rcwKph02AOGq31KZQeb8OBw5blEatKD1WHRUOdaccW2VKwtfaV8iKAOQ7JEptVytl8hRYgec9X8L5eDZ/yu4WybgnWswfM/5NvJt8iENj+4X4fo7MYmNLPhLBwpEmLPcuB//P1NZFh31+qApPLfqKsH+3WCmHSyKDZ66y/gzkdsAGinVrvdW2SaFPgh+08VCZCGbW+QR/8xnB13AX7KoMBsK1b9qGj59vHp/u5g8RXGlN6xC+4BcRRL9Qi39LLfkpA8mPafHTd/0BUEsDBAoAAAAIAC1nSlLJc2blDgEAAJwBAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTMyOVVU
*/