// Copyright John Maddock 2008.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_ROUND_FWD_HPP
#define BOOST_MATH_SPECIAL_ROUND_FWD_HPP

#include <boost/math/tools/config.hpp>
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
   template <class T, class Policy>
   long long lltrunc(const T& v, const Policy& pol);
   template <class T>
   long long lltrunc(const T& v);
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
   template <class T, class Policy>
   long long llround(const T& v, const Policy& pol);
   template <class T>
   long long llround(const T& v);
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
   template <class T, class Policy>
   T modf(const T& v, long long* ipart, const Policy& pol);
   template <class T>
   T modf(const T& v, long long* ipart);
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
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
*/