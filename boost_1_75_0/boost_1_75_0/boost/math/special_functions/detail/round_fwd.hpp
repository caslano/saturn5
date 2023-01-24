// Copyright John Maddock 2008.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_ROUND_FWD_HPP
#define BOOST_MATH_SPECIAL_ROUND_FWD_HPP

#include <boost/config.hpp>
#include <boost/math/tools/promotion.hpp>

#ifdef _MSC_VER
#pragma once
#endif

namespace boost
{
   namespace math
   { 

   template <class T, class Policy>
   typename tools::promote_args<T>::type trunc(const T& v, const Policy& pol);
   template <class T>
   typename tools::promote_args<T>::type trunc(const T& v);
   template <class T, class Policy>
   int itrunc(const T& v, const Policy& pol);
   template <class T>
   int itrunc(const T& v);
   template <class T, class Policy>
   long ltrunc(const T& v, const Policy& pol);
   template <class T>
   long ltrunc(const T& v);
#ifdef BOOST_HAS_LONG_LONG
   template <class T, class Policy>
   boost::long_long_type lltrunc(const T& v, const Policy& pol);
   template <class T>
   boost::long_long_type lltrunc(const T& v);
#endif
   template <class T, class Policy>
   typename tools::promote_args<T>::type round(const T& v, const Policy& pol);
   template <class T>
   typename tools::promote_args<T>::type round(const T& v);
   template <class T, class Policy>
   int iround(const T& v, const Policy& pol);
   template <class T>
   int iround(const T& v);
   template <class T, class Policy>
   long lround(const T& v, const Policy& pol);
   template <class T>
   long lround(const T& v);
#ifdef BOOST_HAS_LONG_LONG
   template <class T, class Policy>
   boost::long_long_type llround(const T& v, const Policy& pol);
   template <class T>
   boost::long_long_type llround(const T& v);
#endif
   template <class T, class Policy>
   T modf(const T& v, T* ipart, const Policy& pol);
   template <class T>
   T modf(const T& v, T* ipart);
   template <class T, class Policy>
   T modf(const T& v, int* ipart, const Policy& pol);
   template <class T>
   T modf(const T& v, int* ipart);
   template <class T, class Policy>
   T modf(const T& v, long* ipart, const Policy& pol);
   template <class T>
   T modf(const T& v, long* ipart);
#ifdef BOOST_HAS_LONG_LONG
   template <class T, class Policy>
   T modf(const T& v, boost::long_long_type* ipart, const Policy& pol);
   template <class T>
   T modf(const T& v, boost::long_long_type* ipart);
#endif

   }
}

#undef BOOST_MATH_STD_USING
#define BOOST_MATH_STD_USING BOOST_MATH_STD_USING_CORE\
   using boost::math::round;\
   using boost::math::iround;\
   using boost::math::lround;\
   using boost::math::trunc;\
   using boost::math::itrunc;\
   using boost::math::ltrunc;\
   using boost::math::modf;


#endif // BOOST_MATH_SPECIAL_ROUND_FWD_HPP


/* round_fwd.hpp
WwLnAQSHAkzcoXTn2ELuTkUamGuRa8O1C1Gcjv5FKQQSz7jwD3GMk5Mgn+68ZR9bNQ49L4a9+FbWetfeiED9dth6h/kJSPDTut/7daEc2694C72+bQylNsPhHtDw3cNHP8ylTHcHTCA7nm8Kvl1ZHT1SY+KB9Q1h06td42gZ/zZpkGVPqfMlYQL/xKHhkSItWaFnwHvMD1VZ644PuyIHYh+819wACdSDT6WTwP5bOZ+CY53yA8H5h97GG5EPvJo8eMp+MRrFehag7C+cAkqTGu61elYZ5evgCPtya9cxl5y4fNvxKyXNYHBRbYVa4txtn4yuMX6QD4alNjasH6H28twX+PIigsBhO7bAkQcogSvS0IxT1kpH8Kkr7PdH6tDBeqLWvSyBUv0wD+Qr1R3Q7G2bQwvrMv2U4O7ob+J7tid87zuxA7h4adKctxo7iQ+5Zxnt0/5z0y9NboKS5+uzUuAX33fpEBbEfu31Z45YQ5+t9G88OnP88pe11wttUNVA9fYduumdbPNa9SGlP0WFXGbqKxiMyiqKLqrP2sXb0DDlnLHGk6Y9jeGM4E4/Xp/SYVHLtTzdIynhulEIWrymoEn0C5zJsgrMMmax2bEfaFfZPq+QjBn5pNp9lH9B/ljPelWvJBozf57lojhvHsIMgq9bfG6x7roWKYe6SzxaP9n13hqM5KyqLoF++RiDbrtFU1uT5NV+eCNKjzVa
*/