#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_POP_FRONT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_POP_FRONT_HPP

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
        template <class S>
        struct pop_front;

        template <char C, char... Cs>
        struct pop_front<string<C, Cs...>> : string<Cs...> {};
      }
    }
  }
}

#endif


/* pop_front.hpp
7iCGsk4n/nph5X9KNuw4iKGsz5ETzl1wy2vI+oqDGMr6O6Lr6neoy5H1uIMYyvq8IlcA17pAit6lLmIo6wuKXAF2rP6ldJdylIsYyjqDPNfdzxnSRj/jIoayziSWP+XwHdIOe7mLGMr6+4y1ssAddOjdH0TWEy5iKOssRY6o5dNrPoKs/T3EUNY/EGss+cHE7cgyPcRQ1tmKnJX8ZvknMU7yEENZXyQnXHbOxdLd8k0eYihrhyLn1+Zn16xA1os=
*/