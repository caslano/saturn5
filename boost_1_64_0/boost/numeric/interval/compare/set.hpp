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
2/pxnMUAOTtrjK9mps9u6Dir5puPvA9ynp8Vl6E45zuILvsy9rYAg7cV2YHz3SxlmhNu/1WlRb2J0w39kBaBgy8oJCueLfTb6DgijzNev2fSRc4s52zd8JIfsap8EaOpAfGFO9cERaIia/J/HGkTQwV8Dk6u0/WlSedQ/gxhtsBmk+ZtCNIGNyNJv2GiB96FiAIzMkRvmAxIcZZO3jUzfRpDhsYRyMWFZVx93FTxAgQ0O4aw43PD0fJ+DhhvJgLjWL/g70iH7n1pxVnd4k1cshWjywnDSlnu4v9eQZCV1NNEmsdkjdSWmD1FsjpSrzFvIXWprKbdxG1bhLXwfJkizaG9nRs8Kkj0CL9EaBiboLYaHI7j/TUuNvQTOY0F9bll8BVKyHYNFzQIU+QOV8EvU8hx8PfplYV1WY9jk/ZYEcWBCG2HQXOhN5HiE7IR/IcExPl85/pofq7EiWBrhS0bYDubM7y8ocQyyCc3ecwB/IQnJRB0ya2tEI1W2SZmKYldvbJE+mj8PklgrP/OzzXjBJbkSXSND/zobW+9MlOmFbJRqT8Qtv790fQL+Q==
*/