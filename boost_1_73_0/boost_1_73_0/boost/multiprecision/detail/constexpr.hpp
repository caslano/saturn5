///////////////////////////////////////////////////////////////
//  Copyright 2019 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_CONSTEXPR_HPP
#define BOOST_MP_CONSTEXPR_HPP

#include <boost/config.hpp>

namespace boost {

namespace multiprecision {

namespace std_constexpr {

template <class T>
inline BOOST_CXX14_CONSTEXPR void swap(T& a, T& b)
{
   T t(a);
   a = b;
   b = t;
}

template <class InputIterator, class OutputIterator>
inline BOOST_CXX14_CONSTEXPR OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
{
   while (first != last)
   {
      *result = *first;
      ++first;
      ++result;
   }
   return result;
}

template <class I>
inline BOOST_CXX14_CONSTEXPR bool equal(const I* first, const I* last, const I* other)
{
   while (first != last)
   {
      if (*first != *other)
         return false;
      ++first;
      ++other;
   }
   return true;
}

}

}

} // namespace boost::multiprecision::std_constexpr

#endif

/* constexpr.hpp
kY6tyMF2S872+NVWJG0EWYqkbRNbkZ2OKgJfbUXeHr2Skwh+tRVJm1JmkTsUn38sf2bk70SXHB007MkkKfo2Kb0ZVLZ+7GHEnx/4NYrv84Yqoy0Mh3DYuwO1sUn+Zh4hILN6ffSiOCpnE7bJ7SDpDN/Cz0u2Aw3jMjKdsoG72pOgy3pdnrSUu10c49QBH4nPy/xI9GORbFj1J5rXeCYk3dg9LOy2jncyRSjLpflIRmrt8niFoldl65uLoYhhb0vgONNRn2pk6OFh5DnQFRcUMsFG+CnomFowse4opvD44AdX8/HAjaJcVOxo3CQu5hzukJhQY2pTEj07aXT0hEjsjymmXrCgUcY2ZGMVgx4m56AGNF97gyvHixWmVUA0GyCSlS3sXW1oSZOo1f4LvVyikzOHesmmZ400vEiPsEWzLCg3VD2dTUalm6nwKPZ0BvP0A54cXKVrsmc8dykhIG5vCtOmTLWAEnv4hSdwxTmxh+U2ZSWxK1Pmuzd+EI5pOxeDADBGKTn2zc8ia2B4zU2u/5WxYqp+LJEKkhEhIvQTUGjvtjfYa5cfy251VBZVkZleoKfJKU+tLy4DEFCwdZXMie8oa5Vlbi6ZBJyycot8f5izAMAJOCqzqz4Z8D4kLCceYYzPe1Xh1GQY3GGP
*/