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
jgXRdKU0nxomlg9rX3Tlv+DzaYbEcaVXukCT6zkw2cblRuF/6nr8Wp346scuMt9dxtkcbZkEgn/t3R6fr2TMobLio+8RXI04TJv+2gs9npmvOGcPaLlS/39gjBs1KHwuCpKdJ47085r7UqO6aOQ7BlT+SCPHfyxfivAH+0QOvp5Xve/HZj4tvQUZaVzUJs4vfR6I93Xt5O4b8J2bano5uSwP08vJZfl3Ief0cnJVzunl5CK9
*/