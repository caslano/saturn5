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
A02hWMbB2uMzshdon2+0+WHKY4IraTqq8M6DUlr6EPWubo6OtxwzaGhHKxBZHxzRU2wrVcmHC493nRYeEoHryfXB1pOiImi4Dpt+nZQRK/qlNJV0H+5Rq2z1krDBnrdNjcpiiBZZbu+8+kY+6N/Vu3hOCfhjburkxh3C57OFfLm/x7BZsBKYlMt3Yy7VdrdMNwYfqax2elIALh+sFAtNHxn7c3t9Bcu3nqjXPDAKilCUlU39AQuBTyyVmZ1uFW4=
*/