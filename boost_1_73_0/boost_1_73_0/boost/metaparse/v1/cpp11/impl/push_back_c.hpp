#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_BACK_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_BACK_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, char C>
        struct push_back_c;

        template <char... Cs, char C>
        struct push_back_c<string<Cs...>, C> : string<Cs..., C> {};
      }
    }
  }
}

#endif


/* push_back_c.hpp
HmIoa2fGKrveU9deuAxZ7/URQ1nnkOf61tZdUhw6PmIo60sZa3mBmzv1YWm2Od5HDGWdSyy/86wnpd3hKh8xlHVexiqnSv5V/WVkPeMjhrLOJ7rG/uvqE5GlBIihrAuIDVe+81qpYq8KEENZF2ascjJ/cH7ZkchqBIihrC9nrHKqXPH6MukG5twAMZT1FUXOr9c0X3oX5v4AMZT1VUXuDqf/aXorst4IEENZFyly9H5Y995E1kdDxFDWxRmrvIE=
*/