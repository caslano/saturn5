//  (C) Copyright Herve Bronnimann 2004.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
 Revision history:
   1 July 2004
      Split the code into two headers to lessen dependence on
      Boost.tuple. (Herve)
   26 June 2004
      Added the code for the boost minmax library. (Herve)
*/

#ifndef BOOST_ALGORITHM_MINMAX_HPP
#define BOOST_ALGORITHM_MINMAX_HPP

/* PROPOSED STANDARD EXTENSIONS:
 *
 * minmax(a, b)
 * Effect: (b<a) ? std::make_pair(b,a) : std::make_pair(a,b);
 *
 * minmax(a, b, comp)
 * Effect: comp(b,a) ? std::make_pair(b,a) : std::make_pair(a,b);
 *
 */

#include <boost/config.hpp>
#include <boost/tuple/tuple.hpp> // for using pairs with boost::cref
#include <boost/ref.hpp>

namespace boost {

  template <typename T>
  tuple< T const&, T const& >
  minmax(T const& a, T const& b) {
    return (b<a) ? make_tuple(cref(b),cref(a)) : make_tuple(cref(a),cref(b));
  }

  template <typename T, class BinaryPredicate>
  tuple< T const&, T const& >
  minmax(T const& a, T const& b, BinaryPredicate comp) {
    return comp(b,a) ? make_tuple(cref(b),cref(a)) : make_tuple(cref(a),cref(b));
  }

} // namespace boost

#endif // BOOST_ALGORITHM_MINMAX_HPP

/* minmax.hpp
jE5CfqfGr+N3/soA3L8I9MUZPV5XbglPZsIzJU/E843rCYD3cp91KPSz9cGwkkuYlmjw8DUQeGECh5lG7Szzu9BVJkVI/sbK3r8goaA6GuS8lL2dEuVotvlXPHLn6VUABJcfhCAe48HpOOId/Wna3uxhoXSwvb9ixo8BTDuzHDrC6/uedllCGTfy7TYKJ1QvZepjHrLAb0600FPAU0uCaEza+Z+oSrCvw0yEEeSWFQXbgzbUHokv9UYEilx8GBzBEdvKqXvrdWEZf8MufDzOqWIhcRou+ZtBuzplfpQyllhU0BPBYam86kuw4o4TYrdzGvuASkAdIKWaRnVJ0lfekbh+2eAIyksO7NbDNIMmZseGoSLE0zN8PE414Pg1sdJoKXZtjxtOCAqIBBLNQ8w5diszli1VbL7cX0e42CZ2dz/daIScxGWkSOS0dJ6s4UGW3j9N793ve+Dy549oNSHW3ZPlzN5J0nVXEk4H3Oc99tp4rHfqcm+0UTx0YbvgsDCSl6c0ioMVGsct402ilPbyk56N0pVIuJMa9xeKTqhHkylVUi/bSkXGyBgH0w==
*/