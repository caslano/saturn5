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
nVRrb9owFP1uif9wRdVvC06gtAVlaGgwjWktjKTt9tHElyZqEkeOw+Pf7ybh0U2MdbMsxY9zfM517rVrMDeByHHA3ChdKvq84HattMwH7JM/Y7Oh98i+Tjyfufy44/IafMEuwEO9Qm3lkUTmasziLa3DU4gpSBWlz1Cy38Ea4RkNmBBB4lIUsYE4yg2owmSFgVBoaQVKooQorVClMzqITEBeSTBXCiOCEIMXSAj5vmlwY5oDZpQRMbRtJvV6o62yA8At9G6hbodB2bpOG6aBgXYbnE7fvobW//J+I7bPEO/EtgSA0+sR8R6/+8zS1q4TxgF7D3fgdet04UsRg3O9487Hw9HdmMWlcNXPkeEGRhiQnYrcgwVdrTWAItechuTeeu3+9CH7sMtVOuSG/t6qjnsv/7e42z2y37evKB3WaayEbIUmid+ufq9W0LEr9S6gCf6oftI3MZ2rfqcDWbH4VbP71ojpvijjD8lXpv8uz6sC+BhHmJpdAQTVhCB1zg7Y0mSE38/ATUWCVWmBjHRdAqkK1pK2eL0HbqCSRKSyIvc5v/w89fzJrH9JrNl07nNe0rgJo5xnwoTcsR2bwz+BLYvgVoImVHJnwOUHXRru4qgifEQdLbdQ3gCIpUF9KFCq2xwWSLXezENlmsxd
*/