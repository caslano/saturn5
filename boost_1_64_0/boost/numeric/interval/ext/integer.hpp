/* Boost interval/ext/integer.hpp template implementation file
 *
 * Copyright 2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_EXT_INTEGER_HPP
#define BOOST_NUMERIC_INTERVAL_EXT_INTEGER_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>

namespace boost {
namespace numeric {

template<class T, class Policies> inline
interval<T, Policies> operator+ (const interval<T, Policies>& x, int y)
{
  return x + static_cast<T>(y);
}

template<class T, class Policies> inline
interval<T, Policies> operator+ (int x, const interval<T, Policies>& y)
{
  return static_cast<T>(x) + y;
}

template<class T, class Policies> inline
interval<T, Policies> operator- (const interval<T, Policies>& x, int y)
{
  return x - static_cast<T>(y);
}

template<class T, class Policies> inline
interval<T, Policies> operator- (int x, const interval<T, Policies>& y)
{
  return static_cast<T>(x) - y;
}

template<class T, class Policies> inline
interval<T, Policies> operator* (const interval<T, Policies>& x, int y)
{
  return x * static_cast<T>(y);
}

template<class T, class Policies> inline
interval<T, Policies> operator* (int x, const interval<T, Policies>& y)
{
  return static_cast<T>(x) * y;
}

template<class T, class Policies> inline
interval<T, Policies> operator/ (const interval<T, Policies>& x, int y)
{
  return x / static_cast<T>(y);
}

template<class T, class Policies> inline
interval<T, Policies> operator/ (int x, const interval<T, Policies>& y)
{
  return static_cast<T>(x) / y;
}

} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_EXT_INTEGER_HPP

/* integer.hpp
rc/d5DO4Nn7dQK9nvwI+gIF2nWwihrioTJxH5kuD3XL0Xhn4d0/b+bpexflcIuFlmlQ5kA0eFGgIm+U5/pxAU6fvvA83nS1JYAALQwVtXu6McjpRuJ0neKnTraNEGwhbSb5vkA0cK74hJXN3X+ZRgBqr/RFP2eFG5ULIz3ojynl3pd9MO8CS6Nlwmgf6RuE0C4ndNcuXID935oArwIl03ZocbZrdv5XRDMfExsEQ/jguiZdlG179bo93mw29cq1npomZ40C+XOz1W90Npnk71sv+yAslI++o/v0ZuwDqPtRmkHAY1VDFMHsPTn2cLaFIdjMZ7xVowYh0wo9ZIJdCvqSbcIITMEmizrXHZ7HNkn9eYx+sU/QUED021Un4OcAq1jGFsDc87m5NbSUIK9ntovy/DPPfE4sNT3fmbdbVjE+k4aAwcswtPS8tXw3J4XBt/uVNpyIdUPv3MKMDEGGyyETheakCMja+Qz05V83PiPwmoNSBs5M1hGKDrCca3YeVtVE0qT27OXqUuX90KNHpo6Kb3gP4LrDnijpKDdnFhXu2hG/H9A0sbL1iug==
*/