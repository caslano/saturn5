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
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
*/