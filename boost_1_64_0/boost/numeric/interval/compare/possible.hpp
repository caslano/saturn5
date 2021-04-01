/* Boost interval/compare/possible.hpp template implementation file
 *
 * Copyright 2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_COMPARE_POSSIBLE_HPP
#define BOOST_NUMERIC_INTERVAL_COMPARE_POSSIBLE_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {
namespace compare {
namespace possible {

template<class T, class Policies1, class Policies2> inline
bool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() < y.upper();
}

template<class T, class Policies> inline
bool operator<(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() < y;
}

template<class T, class Policies1, class Policies2> inline
bool operator<=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() <= y.upper();
}

template<class T, class Policies> inline
bool operator<=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() <= y;
}

template<class T, class Policies1, class Policies2> inline
bool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() > y.lower();
}

template<class T, class Policies> inline
bool operator>(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() > y;
}

template<class T, class Policies1, class Policies2> inline
bool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() >= y.lower();
}

template<class T, class Policies> inline
bool operator>=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() >= y;
}

template<class T, class Policies1, class Policies2> inline
bool operator==(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() <= y.upper() && x.upper() >= y.lower();
}

template<class T, class Policies> inline
bool operator==(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() <= y && x.upper() >= y;
}

template<class T, class Policies1, class Policies2> inline
bool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() != y.upper() || x.upper() != y.lower();
}

template<class T, class Policies> inline
bool operator!=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() != y || x.upper() != y;
}

} // namespace possible
} // namespace compare
} // namespace interval_lib
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_INTERVAL_COMPARE_POSSIBLE_HPP

/* possible.hpp
/OxlDb7omQWO9T4reKVwzA/RTaUtDiB3eQ1BIA+plisz495dorbwI4WOjiiHLjQCLZDnTlK+3iF8Vt28b+c3xRDfdPTKtKKMoWQZmjIIIDUFUgvjgHEXLLGWGCAPJVTpqybo8KRNt+tqzMQZwibZefVr5JTBy5KL5qCkc9HPAiS+TVn+l5PdXtkmyn5R3IvBH8n8Y5b/h+5VZgvwXGXRYSSbCiwr1cW7JDVUrIpo5HQg9apKPK0Zv1U5FQbkKAHFMArllQsDP7nZAA4KjlQivBu/Ip/za6ChTQSy0Kg2hRnUB/r3hT4hBlHt+EiZhYyg14maNIar0i5YqTfKAP8fovDls4deitZF7E06GluO4C9+970O9PKglr3vg4JGU31Vyfo9FrKFhpzV8Gfh7JtC3FayZzD0JGP/pxVs2kdu/LGPPFkk2EEkrwjhQ7Nd5Gf8PhRLptnDCsWVJIIUF5ZgqkMdr8jnLq5qtzLS6qTg6jSK1Iklgn3ubJydAjYXW1lJXwPxlNybsG9O6E32GAQKm7pz/IKzf82lihu25Gpcg3C+PSDT4K7oNLZQsg==
*/