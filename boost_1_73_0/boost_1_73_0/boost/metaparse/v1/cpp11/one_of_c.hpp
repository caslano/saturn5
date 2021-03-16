#ifndef BOOST_METAPARSE_V1_CPP11_ONE_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP11_ONE_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/error/none_of_the_expected_cases_found.hpp>
#include <boost/metaparse/v1/cpp11/impl/any_of_c.hpp>

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
PRgkj6SeQco7bM4d03EVUQeD5JHUs4Y/rxc7Dv+aqNqtyCOpzYa/KSWXd/gXUYNbkUdSWwyv8xFj3mcz+stakUdSzxmeYUWdIYNYabQij6SeN/x51Xl2ZClR77Qij6ReQMpfc/hhQgM2+gqkkEdSLxr+vK79YjJ7K1ulkEdSWw1/XjNjB3UgKjOFPJLaZvi1Ii6uFSJqeQp5JLXd8Hc5a3H3HKI2p5BHUjuQivd8tU52+Zioj1LII6mXDO8dbu4=
*/