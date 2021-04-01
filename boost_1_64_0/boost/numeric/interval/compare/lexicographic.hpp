/* Boost interval/compare/lexicographic.hpp template implementation file
 *
 * Copyright 2002-2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_COMPARE_LEXICOGRAPHIC_HPP
#define BOOST_NUMERIC_INTERVAL_COMPARE_LEXICOGRAPHIC_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {
namespace compare {
namespace lexicographic {

template<class T, class Policies1, class Policies2> inline
bool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  const T& xl = x.lower();
  const T& yl = y.lower();
  return xl < yl || (xl == yl && x.upper() < y.upper());
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
  const T& xl = x.lower();
  const T& yl = y.lower();
  return xl < yl || (xl == yl && x.upper() <= y.upper());
}

template<class T, class Policies> inline
bool operator<=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  const T& xl = x.lower();
  return xl < y || (xl == y && x.upper() <= y);
}

template<class T, class Policies1, class Policies2> inline
bool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  const T& xl = x.lower();
  const T& yl = y.lower();
  return xl > yl || (xl == yl && x.upper() > y.upper());
}

template<class T, class Policies> inline
bool operator>(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  const T& xl = x.lower();
  return xl > y || (xl == y && x.upper() > y);
}

template<class T, class Policies1, class Policies2> inline
bool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  const T& xl = x.lower();
  const T& yl = y.lower();
  return xl > yl || (xl == yl && x.upper() >= y.upper());
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
  return x.lower() == y.lower() && x.upper() == y.upper();
}

template<class T, class Policies> inline
bool operator==(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() == y && x.upper() == y;
}

template<class T, class Policies1, class Policies2> inline
bool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() != y.lower() || x.upper() != y.upper();
}

template<class T, class Policies> inline
bool operator!=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() != y || x.upper() != y;
}

} // namespace lexicographic
} // namespace compare
} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_COMPARE_LEXICOGRAPHIC_HPP

/* lexicographic.hpp
UxwKoFgKRpcbTM9V7Ol7iqJ/03OUS3NXGRElX/0DZxRYVqSASzQdoxRnSlRbTDu7eJYHBusHtWoMcWLt9QUAgk1r8iL1zmy4OG7Wh0Xkwvl4FKgbcGfoaG7NUG/42YfitZ5MVmW2/l/KnBo7ymAf3+HAIgZGmI4T6EXREwFfoUKEkIvF/6uG2Wujy9xLwe5A9PTS2Xs3fNKEGsKVtafyQyRID4uE3je4/5aHB8hMsebQIiAWAzIgVCCZkRj+rGCZG1JESEnQ6fts0OXlBrUvO/6a6nal8h7sZfGPFVePvwwqR3eJEobkzW9V9v1kusiMG3bX2u41BJOmFm/ae/98e3kohD+TUBq+sp7huos3Zgp6p1iIPVd4dzy/D4yg8ecH2KMLNemsQi8e5JkRfCcYFAHg6eGWwrVbMFye25/xDju3woG8ByHmHXlvwPrPTngzkn8U5ifS3wv9d7kNPGTGX7kphWLMmN4XYpzlMWa5Yc70G0UZRyarQlXJBPTJDib0gdsHFtaYCgSiUh5Ro203cUjRsZUxZBJF05tgMsTODMwAYz3TrFfz4xDhEg==
*/