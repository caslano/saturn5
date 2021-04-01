#ifndef BOOST_METAPARSE_V1_ITERATE_C_HPP
#define BOOST_METAPARSE_V1_ITERATE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/iterate_impl.hpp>

#include <boost/mpl/deque.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, int N>
      struct iterate_c : impl::iterate_impl<N, P, boost::mpl::deque<> > {};
    }
  }
}

#endif


/* iterate_c.hpp
GtpMfMWEqbwrmMBz9DAqvzqZBP38leEg71Of7Vg65gnSWkw+tlhS/LNfNOofleENVhaSwqjSzYm4Aw2CN2c36Lam6r7QzcXS2RZeVGjvcL86WHeSTGC+gomoYtQL1Mpv9oWWpcc/fAc4c7FXyIINlXC9T71kFUbz6AuFvupVQJZ/LoEAsHvKSNd0B91F2fVEYf4PFSY0dyIlVvy7PvcIXyQWEPFGfLPf7YWosoXON/dlxNHArrIH6Y3QDUEgF0mzZ/EpLK0YMpGT61ssMYxITx3sBU6g/r16iYdSrRoIwQGPh+VkeHyVBdEjMXmSpFjoU9ZlbaLfp0cR1fG9Rktqe6JgF6uX06sc4kMNjpUxQp/AoJWBa0rJHErWben6Kpj49MH5ptEBpRXWSjPbkMGUZX0viEllqNeeQ2MiYQBiKmRGqOZ/lsdRGA7tjrpfORE2daHXHUhr20V2dnLrZwjzZh6z+fZy2HUsycZVVWYyrwD1kxmlPy7It3pqh7KARrKnNWJLNVVsNqMTYVBk+eNXZW26kcTLHxjW4hY8QQf73oTAHeK7ymODLkcIGA==
*/