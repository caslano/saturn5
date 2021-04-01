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
lOtZka89Uy+qDS1l0uodkK+8yUgTeVQC55P1mxM5l79GhtCzaJHXNH8HmIYREZoXptuFpCsiwY6l3MtiMTJV0x4Tv1TR9yAovE9GAZ7ap0OWJvvekq9R40KGHhn7TSo28WPuey2z7jjT0QE4kEmde/O2ggWwcuPRAND7i1Fq55z5bX2vY1+9+IecsseL+pCMsk1bH8Ft9U7qhu08sCSC2ys+BLidU0cTLfWsrahR/TihM/53Vp+hq+R0tQqKG6D4bVcHKJZn068L2DHItMrEA7Zdndg5gq8GWlYAzW6Xcc36AfJz2bLsTX0K+XXggsW8SdWqktBJQtW7T37J9F0EGqwiTbKfnS8CSRe5CSlMdcc5squNAdimjw0WbbK4yOMiHpTlu4iyspv8WeMNt4T/Tga6/tAt8v+1T17hb0BedFVzyWr5leStMjKIaiGlpu8ZFLv8OWOuXPop3Fp4w7zh/g3YsiOMeOjRswoOihOQODjTz5TJCmUlvltPT1OYkY6Az4P1MOEIW2LLLYbEW0l4Qwcj9zOjMJCYqgYfl5xF0Spy7FUpjxPper7CGA==
*/