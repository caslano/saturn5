#ifndef BOOST_METAPARSE_V1_CPP14_ONE_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP14_ONE_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/error/none_of_the_expected_cases_found.hpp>
#include <boost/metaparse/v1/cpp14/impl/any_of_c.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char... Cs>
      struct one_of_c :
        accept_when<
          one_char,
          impl::any_of_c<Cs...>,
          error::none_of_the_expected_cases_found
        >
      {};
    }
  }
}

#endif


/* one_of_c.hpp
a5fHcPEhIi+8I23sDv9pc4rdi69kTp17I/cISGgukDErhTHo7Pny6pT6bvtaUy3/i9KH4ySdKvXjyi83EDKmjY9mFqdEfObCLmB17t4kfB/e3iJyRabbh76h+8vJzcjxDkUb2VqK/9TpwtzJuERe5FhQNnEaCRpBacPWEhRSHME5JUn5Rje3m/TgVzvPJQgjyd5t96PjUDAfspRmBYrIgmN2U62a/PNm/W+7gSRpCVs0icGZ79iugd90DMtmnqZdvPxKHmax21bgcOtxQTaIYzpXjMpeUmQO/NSr36nZxwEmgcqd2jQaPMuvXFd2u6zyH4ZkNkaKIe+JqrWCBzaNLWR8D54+C3wCZv5rLJECWVFGzx86dbcKlV4zguXfcFqd28EwsQZFgoCn7qy/ofUxqHVie3SUF6CnGpFpw2YiJ4PiR8gR1hJLze/u26P+buVcxKdi+Yk/OfJW5SFkSKX7GL8VWJQlF8l/xROPCLntQ7xniObEIfYhk3euVEzROdXmpOn2JMEHBQTzCr3TTevqXtfapVYM9dOPL+7YN/co5tZUhRmHK6hgwc28OQ==
*/