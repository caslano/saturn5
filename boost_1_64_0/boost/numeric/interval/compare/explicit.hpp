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
M5j8zV+zk+fymwDMVtiBoyuHM8+Udhr8D9Dz/AIrLyyvwgczjg9WUvalgTlz4jLMV9ixNWMPck99qN1uk9lM9rMcrLIw66DSX/gtCFZJWPqh04z7DlirPxb8x/pH3TzOupSr3a7Ee3fu7+Ewc2E7Ep8P59hhGmFnJrcI4NkNZiHMIyloOesuTM7n8IsjSvH8orRbvOAJ5zMJZieszbK9fN8JmK6wxgezrnBtKr9pMKY633cPZiksYfH3RjzzwcyEPYvVdWOMHuF+Kywy91wXnqFhcs4Cy56z4v4OMxDWcMpY5oSv8ps6J5dzr6oGk3ndd8+8djwvwYyE1bt6hbWuJaz0X2uPZ6ah1STGAVZSWJUViZ9Y62AOwla9clnLeqbYEHPdPZwzmLewjBH2HJ/rYz2dYsKGZtydzDHA7IQ53+i7m2c+mL8w058LZjBfYCWEfZpXIpE5AbMVVsQlrwjjDisurP2Si7znGD3Bf2Zd2D/f717l+oPJdp9sog5zL4Y5CTuYlHaWezHMUL6vzYMf3I+eFNbIf4OaflvDepb5pDC2bfG8/HrDW+Y1zFLYsaiV/M17MBNh1Q31dHhGUX5zWo8S0/hNAGYtbPf9Z1zvmjzEXVhWufOOzF2YobTEf75zzmCmwr7cveTEugszF5YWHvEPcxdmJWxcfC3mZw/Firk2YQ6OhNkKu1VzRTHetRXzD041ZX1R+nJLZ888rgdYWWGlrr48w5yHmQlbsWUW467zVHs+l6TNYd11hMn43R1eJYd78VNlXvz3p3IvflrYlzZ47tFvwbjHwtyF7a/eIp1/t1DsZdLa3cwzWMBfC8dzk3v8ZI5P9CUMz/sx/+XjTuBruvI4gD9ZX5KX5CV52SOyySKLRIKolCAl9i21BrHHvjQIgtBQu6ggJYilpChqqKWWVGMZlNRSsSuprWjUFgTzk7nv//45M++0M3M/zXfOveec///8z7k3Y450ofHdxdiZqZJ0tB60MHdmw/aNeUI5AXNj5jyhMe3vbWD2zFrW0Z6iWiA8zyl0Ja3b0TAHZmtfFlIOZsHUzB5cnLaUcgKmY1a9yL0O5QTMidnjrf3r0TkZ5sysoPPX8bT+hHs+1bTeT2tMaLcmoib1RXuv6tgttbrl9Ds+GI+D/5lx5XS2gdkwCzwxOJVqq9Cua+rVEbS/w3yY9Q85Hkw1C6Zl9i6nXR7NmWDDBprH0HsjzIHPdc3rrWgdCbar7d/O9A1CsB9GbqZ2twQLWvPHbZpPwZ4udqN26vtVLT8+9yvaj2B8rk8v8XtG+Qnj+TkpblQI5SfMk9m5JpOL6L0DFqxYJ1xHpaYfpHcumCWzLo+X3aU5g1kwcywfSu8BW2E2zOae+oHm7ABMy6yVU5MpdMYU7JO8zgX0jg6zYja+U1MvWu9Cu6VD6s+ls/eDquby8P4bqmcwPr4MJ8N8+sA0zG5Or9ec5hpmzmz0jiXULhbmyMfQtHoh7Q+wGop1xDVXddqM9gCYPbOBG3I30rcgmJaZrX/eF3RmhwUyW/Xtb3tpPmFqZoMGvHpO6x1myezGqjHZtN/COii/K2+Hf/7uQXEOrbF3hv8tRxtca37u2JdqD6wWs9KdW8fS82C2zC6uW3CdfncGs2e2rvvlCqrX7w21pzWuAS73ztJ6gIUyO9f6+lKaa1iIYq0qv82m3KbaCgtg1t9tdRS9d8DcmEWdd/2M1jvMg5n1ux1XaAwwe2bnzlx9QWP4gDXN7FLWUHqeDubIbETrzRTbMJg5s3/vPnSe6ieMPy+822GqZ4kwV2bdnwyYQ+cQGB/Dynr3Q2leYDpmd39aPpdqAcyT2a45WTdoTcOcmU29G0r1rOSDIQ4tcV0=
*/