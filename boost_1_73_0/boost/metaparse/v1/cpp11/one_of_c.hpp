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
MFbk+lteQX0b83MyXnOG6abYZ50Q1oqKZ9nvxfKzzVfsd8GWy+53XSd9B5iXf28sWHc34H0Nd2Q+Uzb5txgqzhe9vpFOsVAsF89/Z5rv4+X++/telpguFojnxVpRwQ19fdFR9BdTxDzxmFgpNomqv7F9RFcxSHSUpkncWrtsiW2yPfYrtMuWddzmbbNVua943YFGhvP8uyMT6xDkG7e1egSbmsfrEnQ/MF6foE+z4m22Zd23
*/