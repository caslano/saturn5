#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_CONCAT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_CONCAT_HPP

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
        template <class A, class B>
        struct concat;

        template <char... As, char... Bs>
        struct concat<string<As...>, string<Bs...>> : string<As..., Bs...> {};
      }
    }
  }
}

#endif


/* concat.hpp
9SSPpJqIkn9k931PE3VNT/JIqqm41uo757EVmK09ySOpZgHeYte9bl8cUR/3JI+kmiPlj9ma/nKKrdsk9iKPpFqIutG5WcQhokb0Io+kWoprbe+/fRZRV/Yij6SCogwv61y3jKinepFHUq0CvD0cfPTUQKK+60UeSaUgFfR8j9z2ZTlRSb3JI6nW4lrlSw+nEjW2N3kk1UaURuYQu1rrUwt6k0dSbZHy+6+jfz6ylKjHe5NHUu3E8+qe9FUtoj4=
*/