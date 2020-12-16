//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_COMPLEX_DETAILS_INCLUDED
#define BOOST_MATH_COMPLEX_DETAILS_INCLUDED
//
// This header contains all the support code that is common to the
// inverse trig complex functions, it also contains all the includes
// that we need to implement all these functions.
//
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/config/no_tr1/complex.hpp>
#include <boost/limits.hpp>
#include <math.h> // isnan where available
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/math/special_functions/sign.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/special_functions/sign.hpp>
#include <boost/math/constants/constants.hpp>

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std{ using ::sqrt; }
#endif

namespace boost{ namespace math{ namespace detail{

template <class T>
inline T mult_minus_one(const T& t)
{
   return (boost::math::isnan)(t) ? t : (boost::math::changesign)(t);
}

template <class T>
inline std::complex<T> mult_i(const std::complex<T>& t)
{
   return std::complex<T>(mult_minus_one(t.imag()), t.real());
}

template <class T>
inline std::complex<T> mult_minus_i(const std::complex<T>& t)
{
   return std::complex<T>(t.imag(), mult_minus_one(t.real()));
}

template <class T>
inline T safe_max(T t)
{
   return std::sqrt((std::numeric_limits<T>::max)()) / t;
}
inline long double safe_max(long double t)
{
   // long double sqrt often returns infinity due to
   // insufficient internal precision:
   return std::sqrt((std::numeric_limits<double>::max)()) / t;
}
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
// workaround for type deduction bug:
inline float safe_max(float t)
{
   return std::sqrt((std::numeric_limits<float>::max)()) / t;
}
inline double safe_max(double t)
{
   return std::sqrt((std::numeric_limits<double>::max)()) / t;
}
#endif
template <class T>
inline T safe_min(T t)
{
   return std::sqrt((std::numeric_limits<T>::min)()) * t;
}
inline long double safe_min(long double t)
{
   // long double sqrt often returns zero due to
   // insufficient internal precision:
   return std::sqrt((std::numeric_limits<double>::min)()) * t;
}
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
// type deduction workaround:
inline double safe_min(double t)
{
   return std::sqrt((std::numeric_limits<double>::min)()) * t;
}
inline float safe_min(float t)
{
   return std::sqrt((std::numeric_limits<float>::min)()) * t;
}
#endif

} } } // namespaces

#endif // BOOST_MATH_COMPLEX_DETAILS_INCLUDED


/* details.hpp
4/lysIzO7+BkvJnxZGlhFrEwEzQ7LARk5W1cKuzgE4a3jpSVKZZHonXFOtss9BdmY6G17NUU4T7qGaC7D5WfptYGmk0S1rZpbUE74x8jKlMIy/xaUZ73K6ZbxM7p9lL2fHtNt73EvwXW7nahLvSsjxzLVlAm1k9MThxjW8+2Nf6st5FRXp3N/G+sD4+t9V1XZ5Gqum9P0s2VId0HdLpvboVfie4/keg+YEH3AYnu2TyLyeysV7pGzWPXQOg+GeUoJ0nVva3ath1Te3gdobB+Ir2HhEV638Kkrd2KrheQrb2B5rvMBn2DdDkmh+r62KZ5aIObqP6T3ZebP3Aq4x8r0jXCEtgXyW8GcDZ7vrlQ9+TXMI8L2PNNRP05/JrfewO80vo1iz0v1urDRew6gdWvjiSEsdFgHicnKqhbe6nZbNgWTmP+Nw4Lj+WzyfknyAfV/i2wqVIbJygPKZLy0E22cy+Vh9OY/Qrth648zKs/TtruLad8Ec5F4XUtn2/A82r7WUBibR7m1+z5ZNQ18bygHgtloEdcBrR5m6+y5/srk7h+cXtm21uflYOFyO+MZGvl4BkqB7rwWDlg8zmpnb3KxHtY5H0VoOewvo/p07Bc7KnOX6Q5B7hgLoX2SnAVD5ULzFysa5h7dHNDUx29tJk799tVbL4tdhVbmytori3cZLDs0yS8HApoO1A/8qwtVEZW/tvajzXu84slfb4FWYnXsK84qzi0r7iMXcdHnJdoRTfqvDTfJuHzFL8Ptgs63Rze3NTSGNSOyf0y4F/wvSfWB/HiHn3bsHBxVDenk0dGoHzQN0pYHUgcq5t3Q98UfZwO5kVZBxCGrp0D6/wmkR7Aa34/oNBww/eu/5g9T+De65Fsej4e+A57bhuWPlk7Q/KEv4ubOwNavNeH8R4m4jOLjefOiPcesb7XRwGbQ3ThZhUnHNU085mXjz7lpz1a420jNzdHPAfK+l4iVvc8Ec+lMt7bRLzHi/HeMuI5XEZ7zozsHiZqwW6hvUrqaK+SgDYmhPtEm4JeI/7lNNfmIeoeHwamAAeAY4GPAtOBjwMnAp8C5gCfBuYRXz7wRWAR8CXgVODLQBfwNWAT8HXgEcA3gPOAAaAX+CFwAV13Aj8HXgr8GngV8BvgfcBvgQ9SfA8DPwI+xp1FvVIdUwAuIznTQL3q9xfJOQU4HlgKTANOJXnKgbsAK0iOaUAncDpwGnAGcB9gJXBf4F7AZuDewKNoLlgrcB9gO13PB84EngfcH3gJ8ABgN80lu4X4lgLLgLfTNZ1XQN/L+H4XnFcwj+YYzQduAzwOuB3weEp/B3BP4Ak01+lESv/J3Jy3AIVfLDhrdi6FfwQwG3gkcFtgCzAXeBRwV2ArzRVro3A71O8QYAOFm8z8DbpLKdzLKN2XA3cCLgbuBrySys9VwL2A3cBZwGuANcBrgYcBrwPWAa8Azqbr74ELtXdg3KD4xzC56ZuA4j+D4j+T9HY2cHfgOcD9gAspvouABwHPA84Bnk/luBN4DPBCYAfxnQBcADyNrr8HOtT3PeBYwdnHm3NnAqcA7Xz+k78cQf4fSv7qaI5ZPXACcDbN8WukfGsiOT0kZ9NQuuhdBPoRpOtGCv8mahdu58/IJn9pgr1mcsjfDkB2n9K1M3CJybOIzZ43bHavGSv7zOjPGHbvmLDO9poxc75wSVZCxDOGXVkJI7LfTC9kle0507ci8r4zZs4bTnnQ+v4zdK4E5iNGv/eMZ3ebcjJoMWg5qA80AEqebFMKQG5Qx+TY3LOYi7mYizmzbtTs/1h9OBL2/23VNf4IKV4pnVWdVzerYt/9K6rLKupKqw/SVvpPJL4Ons8dwsLmErRycwk=
*/