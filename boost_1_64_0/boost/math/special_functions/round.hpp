//  Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_ROUND_HPP
#define BOOST_MATH_ROUND_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/config.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

namespace boost{ namespace math{

namespace detail{

template <class T, class Policy>
inline typename tools::promote_args<T>::type round(const T& v, const Policy& pol, const boost::false_type&)
{
   BOOST_MATH_STD_USING
      typedef typename tools::promote_args<T>::type result_type;
   if(!(boost::math::isfinite)(v))
      return policies::raise_rounding_error("boost::math::round<%1%>(%1%)", 0, static_cast<result_type>(v), static_cast<result_type>(v), pol);
   //
   // The logic here is rather convoluted, but avoids a number of traps,
   // see discussion here https://github.com/boostorg/math/pull/8
   //
   if (-0.5 < v && v < 0.5)
   {
      // special case to avoid rounding error on the direct
      // predecessor of +0.5 resp. the direct successor of -0.5 in
      // IEEE floating point types
      return static_cast<result_type>(0);
   }
   else if (v > 0)
   {
      // subtract v from ceil(v) first in order to avoid rounding
      // errors on largest representable integer numbers
      result_type c(ceil(v));
      return 0.5 < c - v ? c - 1 : c;
   }
   else
   {
      // see former branch
      result_type f(floor(v));
      return 0.5 < v - f ? f + 1 : f;
   }
}
template <class T, class Policy>
inline typename tools::promote_args<T>::type round(const T& v, const Policy&, const boost::true_type&)
{
   return v;
}

} // namespace detail

template <class T, class Policy>
inline typename tools::promote_args<T>::type round(const T& v, const Policy& pol)
{
   return detail::round(v, pol, boost::integral_constant<bool, detail::is_integer_for_rounding<T>::value>());
}
template <class T>
inline typename tools::promote_args<T>::type round(const T& v)
{
   return round(v, policies::policy<>());
}
//
// The following functions will not compile unless T has an
// implicit conversion to the integer types.  For user-defined
// number types this will likely not be the case.  In that case
// these functions should either be specialized for the UDT in
// question, or else overloads should be placed in the same 
// namespace as the UDT: these will then be found via argument
// dependent lookup.  See our concept archetypes for examples.
//
template <class T, class Policy>
inline int iround(const T& v, const Policy& pol)
{
   BOOST_MATH_STD_USING
   T r = boost::math::round(v, pol);
   if((r > (std::numeric_limits<int>::max)()) || (r < (std::numeric_limits<int>::min)()))
      return static_cast<int>(policies::raise_rounding_error("boost::math::iround<%1%>(%1%)", 0, v, 0, pol));
   return static_cast<int>(r);
}
template <class T>
inline int iround(const T& v)
{
   return iround(v, policies::policy<>());
}

template <class T, class Policy>
inline long lround(const T& v, const Policy& pol)
{
   BOOST_MATH_STD_USING
   T r = boost::math::round(v, pol);
   if((r > (std::numeric_limits<long>::max)()) || (r < (std::numeric_limits<long>::min)()))
      return static_cast<long int>(policies::raise_rounding_error("boost::math::lround<%1%>(%1%)", 0, v, 0L, pol));
   return static_cast<long int>(r);
}
template <class T>
inline long lround(const T& v)
{
   return lround(v, policies::policy<>());
}

#ifdef BOOST_HAS_LONG_LONG

template <class T, class Policy>
inline boost::long_long_type llround(const T& v, const Policy& pol)
{
   BOOST_MATH_STD_USING
   T r = boost::math::round(v, pol);
   if((r > (std::numeric_limits<boost::long_long_type>::max)()) || (r < (std::numeric_limits<boost::long_long_type>::min)()))
      return static_cast<boost::long_long_type>(policies::raise_rounding_error("boost::math::llround<%1%>(%1%)", 0, v, static_cast<boost::long_long_type>(0), pol));
   return static_cast<boost::long_long_type>(r);
}
template <class T>
inline boost::long_long_type llround(const T& v)
{
   return llround(v, policies::policy<>());
}

#endif

}} // namespaces

#endif // BOOST_MATH_ROUND_HPP

/* round.hpp
55buzF09vqPxpenrAR11TavdjNGdxXR8RMwzp/1kfjoO9qUpUTGXz9xdviQpUqPH2TnX3rPkzoav87adQ/kSXq/l3KdKnh6RZ8nXNrheDz8R5yzbA3JUKbjX473uqW+UaHLCkuh67fsu0+D53SfH68CFzQHGvl75P9ond1GLO5w/cA0ql/KaYNu3zdkubbcuff5A+KLO9T/Lznqor88tBsXT2Pdx/V7O68v9XRsPVQsyVOizYPNhcidNmeCBecY+RdpMiD7c+0uSlDj5+/n8fe/5AvsXke+9Pfa/JOsUPM57PNV29L7mBL09/eWs9fr5Ah025LVD6IEes5lQn4uYg5cSQw0q4neNWV28EQEx99h/oNwde8bzh9yLqc8qpx+uF9fVnn4kb+Z9yi3P4V4V3N57IVY57/mfcw6fi73Xd+zZ5MRrkpZnhQEBuV6fA45Jy+dskmraYEh6X73oMyMvpyqNB4lBSn5Fhmw8RO3Y55A+bfU7OI/vFdxcn49sGwyZ09Wfk8t5P6lOZ8StqcexWrWZEH6A64QDSnRZEJPLNtMHqqs8zhBn57S2VLWdP7fvP4RO27OtEVDfa3Do2GNmhB9szNglS4UuU4JizcQKPvS/6/w7p3OC8CPVpXBea57+u4Z/k7NJkqdGnxmb7qOaYOX/Vt34J75m2+ORx6WI96NEPicHMXc4oMGAOWceJTdS1Nfr9AfOmRO5iPfS7JKmRJMBcyLe50av5f0xe9z89O//1vcKuDEJCjQ5IaiNAjUGLNnQ3jZJilS8l+1dx3tm2yw3lvtmxpjd2OeJ65zD3NTe7c7pfifn9DPh87nnhX7brjzuPV1fnuFnVp/T9nrNep0Tgp7bYpsD8tQ5ifps417fS+/BIzfUxqfOFzi6kc89hP1P77ljYs9QfzLUGLLirEPTnBJHT1MjbV/jmbZPU3eGzIg83ecE7sUhVbpMiT7D4/eeL3D99d80NBiwIHaor+yTp06fOXX/zyWireu7f26MOBmO6TIlL+7oRj6PcMbrbJzMs80t0s+SNwviHk8J5tSaYyIen2GV87rhmJufbt9xvkDHvlZO3Yg9xzizR/Pt5ws0n/XfNfXZU88RnxZjCj5DBZ+rZuzSfJH5y4C415IUpdefL1DcVHsavm47bsiC5vP+u+bvxDblcYHr+/pelKh6HLU9JJTXDmfTYUro+a7Ngn0ckKdCmwlBeWyyTYIsx5z1fOeQoECdISs2X+A5UhzTYsiKzfU6/DQlWowJF3ixeHLKUSFc1A5nkyD/KvVfryWPnvecgTzhkNdb4pc/Z6DDzhX8vIezX/rfdZAp2/qjzhdoZM7nPZA6rNfZz9fr649pMWRO7GXGjjOvlCcVuoxZsSWHszmgzZAFe87JUKLNmNDL5UqcDMe0mRBar8e/F2mOaTMh9ArnESfDMR0mhOUwf4nXBds8uyV9pKk/ZXkMbPv63SzJjSWRV2uLXQ7IU6PDCQuirzFvOCrpy71cM1TfFgq0md3BtUOFeC8UOIvZF0OBxW3OF9i87fkCu+Soc0L4bK8/ZKjQJ3C78wWuQYIyI1Zs+r8OO2Sp0mPBWadtkSX1OvOG/tu9Fh6bExzJtcGAOf3XmqvHxowkDWpvMB5l/Vyvt+9y8iY1fLO+Xs/rBMfXFZ+z2WAn5PXSNmlbpM6e4/Lm1Mz+qm2PKYf2j7w+pr0mBl5vjoodfa+22KfocZO58Wi8Va7/t5b+DLskKdJgRKBq3DnmhBUx/T4gT3W9Xv4sdkjRXq+V3yLJES3m9N4TCiQpsU2MxrdDPheqT0XdWLH1FvmQoUyHOTH5bpPkiK2q2Gy/3WPtnq2NTX3fJU2ROj2mRIzBjdknx4A=
*/