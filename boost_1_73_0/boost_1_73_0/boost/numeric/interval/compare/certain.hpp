/* Boost interval/compare/certain.hpp template implementation file
 *
 * Copyright 2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_COMPARE_CERTAIN_HPP
#define BOOST_NUMERIC_INTERVAL_COMPARE_CERTAIN_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {
namespace compare {
namespace certain {

template<class T, class Policies1, class Policies2> inline
bool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() < y.lower();
}

template<class T, class Policies> inline
bool operator<(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() < y;
}

template<class T, class Policies1, class Policies2> inline
bool operator<=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() <= y.lower();
}

template<class T, class Policies> inline
bool operator<=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() <= y;
}

template<class T, class Policies1, class Policies2> inline
bool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() > y.upper();
}

template<class T, class Policies> inline
bool operator>(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() > y;
}

template<class T, class Policies1, class Policies2> inline
bool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() >= y.upper();
}

template<class T, class Policies> inline
bool operator>=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() >= y;
}

template<class T, class Policies1, class Policies2> inline
bool operator==(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() == y.lower() && x.lower() == y.upper();
}

template<class T, class Policies> inline
bool operator==(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() == y && x.lower() == y;
}

template<class T, class Policies1, class Policies2> inline
bool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() < y.lower() || x.lower() > y.upper();
}

template<class T, class Policies> inline
bool operator!=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() < y || x.lower() > y;
}

} // namespace certain
} // namespace compare
} // namespace interval_lib
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_INTERVAL_COMPARE_CERTAIN_HPP

/* certain.hpp
vQB3KKCMmRGwInxA1RBHjIeEiHMLcVUYpyTzoiZCSQH0YrBF4/k149gfH3fVGEOMD+uT8902VwIi207zTef21nasiaPN3dvbsWX5Zsa4N63Bd/ak9k5wSO98J71fuzdn10qMvmkZqh8V1g+Fq0pNWFRHxmzxvpg6msvoiVnA424mDXL1ESFXy4Z8VDJkxi7AXB7aaqlw47ZNZb466GoJNs5EnMF9OdQ4Y2rDxpDCZNh8gNi/UozL++7ZrxdX73sng9Pzy5trFce1+UFshEHyveFNIegiuAwmuHDkoVEgTesMj5cRdX7BFtYC8tCC8LrzqlWkaRgtfL5qZUcrBTyzb6nxqNXqaHs7nc5+6w5gRICkuuZILQbosSA1V4GTH8+tCudPReOHl7X2fvuus9Pe3VsmzkT6tWDwETGlDn3mkspQG1XIPy2TEmMkDwgGckxftTqddkvvtF+Px50xfa139lqvhzXqTVtLQE/jE+jD/VFZxt1p/9RowX87nb293SIAgwo5zezLxLHv4+HbZym9rrardeAPouRai7ljKBlvH23je629W8U3+F6b/BTtkR3x5xvwpdwBj7bhnRyRKnxsV4+CygE6eDvpvbk46S2H6wiR7O5X4U+FCeiD92COEdUldFCVkSEr9iXCrJU1
*/