/* Boost interval/compare/explicit.hpp template implementation file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_COMPARE_EXPLICIT_HPP
#define BOOST_NUMERIC_INTERVAL_COMPARE_EXPLICIT_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {

/*
 * Certainly... operations
 */

template<class T, class Policies1, class Policies2> inline
bool cerlt(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() < y.lower();
}

template<class T, class Policies> inline
bool cerlt(const interval<T, Policies>& x, const T& y)
{
  return x.upper() < y;
}

template<class T, class Policies> inline
bool cerlt(const T& x, const interval<T, Policies>& y)
{
  return x < y.lower();
}

template<class T, class Policies1, class Policies2> inline
bool cerle(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() <= y.lower();
}

template<class T, class Policies> inline
bool cerle(const interval<T, Policies>& x, const T& y)
{
  return x.upper() <= y;
}

template<class T, class Policies> inline
bool cerle(const T& x, const interval<T, Policies>& y)
{
  return x <= y.lower();
}

template<class T, class Policies1, class Policies2> inline
bool cergt(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.lower() > y.upper();
}

template<class T, class Policies> inline
bool cergt(const interval<T, Policies>& x, const T& y)
{
  return x.lower() > y;
}

template<class T, class Policies> inline
bool cergt(const T& x, const interval<T, Policies>& y)
{
  return x > y.upper();
}

template<class T, class Policies1, class Policies2> inline
bool cerge(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.lower() >= y.upper();
}

template<class T, class Policies> inline
bool cerge(const interval<T, Policies>& x, const T& y)
{
  return x.lower() >= y;
}

template<class T, class Policies> inline
bool cerge(const T& x, const interval<T, Policies>& y)
{
  return x >= y.upper();
}

template<class T, class Policies1, class Policies2> inline
bool cereq(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.lower() == y.upper() && y.lower() == x.upper();
}

template<class T, class Policies> inline
bool cereq(const interval<T, Policies>& x, const T& y)
{
  return x.lower() == y && x.upper() == y;
}

template<class T, class Policies> inline
bool cereq(const T& x, const interval<T, Policies>& y)
{
  return x == y.lower() && x == y.upper();
}

template<class T, class Policies1, class Policies2> inline
bool cerne(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() < y.lower() || y.upper() < x.lower();
}

template<class T, class Policies> inline
bool cerne(const interval<T, Policies>& x, const T& y)
{
  return x.upper() < y || y < x.lower();
}

template<class T, class Policies> inline
bool cerne(const T& x, const interval<T, Policies>& y)
{
  return x < y.lower() || y.upper() < x;
}

/*
 * Possibly... comparisons
 */

template<class T, class Policies1, class Policies2> inline
bool poslt(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.lower() < y.upper();
}

template<class T, class Policies> inline
bool poslt(const interval<T, Policies>& x, const T& y)
{
  return x.lower() < y;
}

template<class T, class Policies> inline
bool poslt(const T& x, const interval<T, Policies>& y)
{
  return x < y.upper();
}

template<class T, class Policies1, class Policies2> inline
bool posle(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.lower() <= y.upper();
}

template<class T, class Policies> inline
bool posle(const interval<T, Policies>& x, const T& y)
{
  return x.lower() <= y;
}

template<class T, class Policies> inline
bool posle(const T& x, const interval<T, Policies>& y)
{
  return x <= y.upper();
}

template<class T, class Policies1, class Policies2> inline
bool posgt(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() > y.lower();
}

template<class T, class Policies> inline
bool posgt(const interval<T, Policies>& x, const T& y)
{
  return x.upper() > y;
}

template<class T, class Policies> inline
bool posgt(const T& x, const interval<T, Policies> & y)
{
  return x > y.lower();
}

template<class T, class Policies1, class Policies2> inline
bool posge(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() >= y.lower();
}

template<class T, class Policies> inline
bool posge(const interval<T, Policies>& x, const T& y)
{
  return x.upper() >= y;
}

template<class T, class Policies> inline
bool posge(const T& x, const interval<T, Policies>& y)
{
  return x >= y.lower();
}

template<class T, class Policies1, class Policies2> inline
bool poseq(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() >= y.lower() && y.upper() >= x.lower();
}

template<class T, class Policies> inline
bool poseq(const interval<T, Policies>& x, const T& y)
{
  return x.upper() >= y && y >= x.lower();
}

template<class T, class Policies> inline
bool poseq(const T& x, const interval<T, Policies>& y)
{
  return x >= y.lower() && y.upper() >= x;
}

template<class T, class Policies1, class Policies2> inline
bool posne(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() != y.lower() || y.upper() != x.lower();
}

template<class T, class Policies> inline
bool posne(const interval<T, Policies>& x, const T& y)
{
  return x.upper() != y || y != x.lower();
}

template<class T, class Policies> inline
bool posne(const T& x, const interval<T, Policies>& y)
{
  return x != y.lower() || y.upper() != x;
}

} // namespace interval_lib
} // namespace numeric
} //namespace boost

#endif // BOOST_NUMERIC_INTERVAL_COMPARE_EXPLICIT_HPP

/* explicit.hpp
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
*/