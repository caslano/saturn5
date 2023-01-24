/* Boost interval/compare/set.hpp template implementation file
 *
 * Copyright 2002-2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_COMPARE_SET_HPP
#define BOOST_NUMERIC_INTERVAL_COMPARE_SET_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>
#include <boost/numeric/interval/utility.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {
namespace compare {
namespace set {

template<class T, class Policies1, class Policies2> inline
bool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return proper_subset(x, y);
}

template<class T, class Policies> inline
bool operator<(const interval<T, Policies>& , const T& )
{
  throw comparison_error();
}

template<class T, class Policies1, class Policies2> inline
bool operator<=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return subset(x, y);
}

template<class T, class Policies> inline
bool operator<=(const interval<T, Policies>& , const T& )
{
  throw comparison_error();
}

template<class T, class Policies1, class Policies2> inline
bool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return proper_subset(y, x);
}

template<class T, class Policies> inline
bool operator>(const interval<T, Policies>& , const T& )
{
  throw comparison_error();
}

template<class T, class Policies1, class Policies2> inline
bool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return subset(y, x);
}

template<class T, class Policies> inline
bool operator>=(const interval<T, Policies>& , const T& )
{
  throw comparison_error();
}

template<class T, class Policies1, class Policies2> inline
bool operator==(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return equal(y, x);
}

template<class T, class Policies> inline
bool operator==(const interval<T, Policies>& , const T& )
{
  throw comparison_error();
}

template<class T, class Policies1, class Policies2> inline
bool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return !equal(y, x);
}

template<class T, class Policies> inline
bool operator!=(const interval<T, Policies>& , const T& )
{
  throw comparison_error();
}

} // namespace set
} // namespace compare
} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_COMPARE_SET_HPP

/* set.hpp
1seyzRTBtsPDNnt3qj6Lp3CY7ZOneyBabGvo+O2Lbgs8Ejqet+jKQHaoKZdntemL/5yH//Q2Tnd0w3+SkLRHlBzKjXhDTfmBllCT9fTv9S05dF3kklDTHR1faYNXXEvAEik5NEECMA6YKw8kULG5nMoltY3fS9ZUSdvs1Sr9zm22pRLF71AROk+hmEee4biCYl5xHtfNoUWFKynfUxjw0uC8eARkyQ2xk6hVwwzmwsqpJn+CeMKbNLcjjTupSdBcusLqWQFzFxkA1noecseVdCbSJreCDtGHzNI9CzAFbmJWkwLazXrUPDDbdxp33H31DXns5qbFeuxu1S2lOy/AjO10eXP0ctQF0fpu63NTQZx8nqiHs781Plo2CZ6UXD+EZ+gKjlE1OnAx90aZ9eJM35gVC85Kr2BPAjd7Ac9LvpefP2Db1Gr+YZqIB1/HfyY4KNQae0GBmfYN15AK8ffiLQgW9xXyfPH3Z5Xg0SlSRZOSdCA9M9xolfPzIS6gxc20W9wmUgyg4kLKjbS4DoW56io6qUWo9uIMfpr/OZh/PAeDEZoiJXwxz5qMWoJsnCuewU8VYDpIVAiwog0vEvdKkBj820bFyxTNPj5oFmkLOBw8d8R06JvnRuC7ipp9YJD7D/10WjD1az4Aa800AIgqHUKI0Xt6FBl6z3THPq8yUvWGb4VZ2wx/9oJKA38akMzCt9Y6GuFfvFoP/631
*/