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
XsYHaII3PMIafYs/hwF8RTy/Dp6neqeOT8fPfEriTuwi2RsGwTwCVOOUBiRIixzO95gXwju/e9kfkS4AiYf9gTCEfsKSdQDkI3DhVUYBuawKA7kc+w7PW9AYZsaws0HLDCXEqO/iz0BGdegw6SLFoIuAKQKkqtyVG01Rx1nUg3/i9Sq7gil/SAFTntuRimSV882BJPV7Mk+xMl3MGtmq2V9UOK5djXJ8PPlSX9Ge1woNjnkSfQOx68fQBeG/oAzrB4+c33GXoQuSIniALxwsodiUSqINF4oJT0/KXMq58wcMC7YAPTzrUwbzFeK11ERXCKYN9k7VpMVadIkcXnTmJXLynJglEqcsUOpFWiJrlnKsPWKJxOidV8ctEzftweI6cbN6P6sWy6TkCVwm8gWNcuYeNJy/QDSTJJj/c2Wt2p034OrgMR+m8Niuek3xuqZ/aQdds1uE5hfUaRhKBkMpdM3Y+V2W3Uk90mjdKDwH96t3qgrT6lb8Zrel1u2stS37ADp3Oz+zLUNWw7yJbmfd/CsWt6H7zvbkSrhnqQuPxLsLDrGdyHZBbgqCWCiHh1uZheHRrpnO4YkLHmAjE3NqnSMTF031seFWUOFgFXsttbAgB6JLuadmNy/FKpLn4ubcA+g5vFx2/jEzy4erdbf6K8hT1gs/VRL/BMT27LBqmFNeLQBu1zga1X3HKMoheHHk3TNXx3P+Mesczf4X
*/