//  (C) Copyright Jeremy Siek 1999.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_INT_ITERATOR_H
#define BOOST_INT_ITERATOR_H

#if !defined BOOST_MSVC
#include <boost/operators.hpp>
#endif
#include <iostream>
#include <iterator>
#include <cstddef>
//using namespace std;

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
namespace boost {
namespace iterators {
#endif

// this should use random_access_iterator_helper but I've had
// VC++ portablility problems with that. -JGS
template <class IntT>
class int_iterator
{
  typedef int_iterator self;
public:
  typedef std::random_access_iterator_tag iterator_category;
  typedef IntT value_type;
  typedef IntT& reference;
  typedef IntT* pointer;
  typedef std::ptrdiff_t difference_type;

  inline int_iterator() : _i(0) { }
  inline int_iterator(IntT i) : _i(i) { }
  inline int_iterator(const self& x) : _i(x._i) { }
  inline self& operator=(const self& x) { _i = x._i; return *this; }
  inline IntT operator*() { return _i; }
  inline IntT operator[](IntT n) { return _i + n; }
  inline self& operator++() { ++_i; return *this; }
  inline self operator++(int) { self t = *this; ++_i; return t; }
  inline self& operator+=(IntT n) { _i += n; return *this; }
  inline self operator+(IntT n) { self t = *this; t += n; return t; }
  inline self& operator--() { --_i; return *this; }
  inline self operator--(int) { self t = *this; --_i; return t; }
  inline self& operator-=(IntT n) { _i -= n; return *this; }
  inline IntT operator-(const self& x) const { return _i - x._i; }
  inline bool operator==(const self& x) const { return _i == x._i; }
  // vc++ had a problem finding != in random_access_iterator_helper
  // need to look into this... for now implementing everything here -JGS
  inline bool operator!=(const self& x) const { return _i != x._i; }
  inline bool operator<(const self& x) const { return _i < x._i; }
  inline bool operator<=(const self& x) const { return _i <= x._i; }
  inline bool operator>(const self& x) const { return _i > x._i; }
  inline bool operator>=(const self& x) const { return _i >= x._i; }
protected:
  IntT _i;
};

template <class IntT>
inline int_iterator<IntT>
operator+(IntT n, int_iterator<IntT> t) { t += n; return t; }

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
} /* namespace iterators */

using iterators::int_iterator;

} /* namespace boost */
#endif

#ifdef BOOST_NO_OPERATORS_IN_NAMESPACE
namespace boost {
using ::int_iterator;
namespace iterators {
using ::int_iterator;
}}
#endif


#endif /* BOOST_INT_ITERATOR_H */

/* int_iterator.hpp
DQ/iac968O56HuI5nyY4vy1Xq6LHk6rsderlMUKIKutkygrwgwDsDavmXEYzaK3Gwj8+72VAm9ZxvMGv9U4GOR5nm6abF53Mp9XP25gnK3zW55hafgoU9eBb5ziIjAP14+Pb74KXTYL8GQ4M+Bx17T1HJn5pZe1JyRSAgw5bhwPaY5PsRO1C/fxGJsxgkfjSNjjXp+2NvQ9v5o9EWGWotW38NCVV5tcEG0pa/YVrD3iWRFq4dYo1a23qEyX9qFf5UGXjM1Mj1mibE0anf426b5U3M/75MnpJyeiy9sPnQ2bjzKdMwFuNFEuhJOB3+k1V+ywCH78/AgDqdj9J2mlkCXtdjXePOywi8d09q64kqgWlI/7c0KtZEzoV/dV9S4qtY/Ej1ZPoRmErq3mKKxHnp7fUlX7h4samf/kXJEa7xrJNcunkWLE/ZaXy4qaorCw0GvfKC1WWEOOifGI50909g4+fxe9WrMXyz0sF73Z79qOR+cYxsvH6hmxZ+iZ27QkJWzIVNzfjgzHZ7zKVRJwICItnmIQ8QstPJRoq+C3U9/5E2VnF1AFkYRinWClaHAoUl8XdHcrF3d3d9UJxdyhe3N2KQ3G9uEtxd5d778rD7j5sdrPJzMskk5NM5kzmz5n5P5VAq091HH1NdzPj0/Dn0wGOBoH56t4CbYRxzD4+qv8INsLGzvujRnlma6syCtmP52JXn7GagZjcc87E
*/