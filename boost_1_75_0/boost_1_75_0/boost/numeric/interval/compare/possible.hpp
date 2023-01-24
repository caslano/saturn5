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
Bcb7VMvHjlBZncdO4GeL25DXzT6Hp6otVFNaKOVsYQQ4zOSJoIAVRs4FSUfNTi70sbtAWXsg1ccWZBDnw7QuPuV97NqV9zH+CRRSpKEb1o+0pGdJ26TguSV5ucE0V7mT8//HaNsuckl5d3iu2asWEfuyyVoVsC9pSRfQ1nqUW+Aa7kh5NwTXTiN7dTJFEyYps3pEfG4Mxa7CFaJVSnmDrWAkVLJKn6XCbanDMPX/4BEqHrTsVrxdqG7bHi/zw/ykPIrR54Rh0ic9adF7JsrOvbbS5Rbi0oXqf34DCfAYHSj+jvyXnQ8t6qGx7iruwUKfFR4u8U09ovuscGPyriBXQ73KCJvXWd1BDQ1aid59oIbmRgaiV0dXQ4stZA6AGnoJZ0nBJB/TIt1kzOq01wd6qHfnz+g3umqaFB7q5qcJuAbqUyhVtNBCr1/AtdA6byaM3gJTJBn/pcyydcGLoirnV4uFykkekKZ/U/yN3yUydT2/iB8inXd+9Is1+hesuimELh+PK+zBUMRsHvntkUVMVSKxvOhkLJqHjUUbmqI31GQhT11ZdNy/BWqAcU8PHgtPlluqzDwcgVWtzNm8s9U3tdWNDmagdD/G/S7INajde6yFU3smuh7BeCZq59KwUO17FKndT9TuB2r3g2ESNEUucmhssuxGRy489LFgrk748JgOOfWizz/8VdNoM6AJFDoTKfyq5ycMSdrjm7oP
*/