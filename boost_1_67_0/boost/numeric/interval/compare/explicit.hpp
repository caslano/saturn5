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