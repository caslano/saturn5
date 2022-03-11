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
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
*/