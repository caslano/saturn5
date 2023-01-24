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
Oy/YY3GhHnwthkjpqkxlrjPp1+qELGUIrEw/x6w6yavOal7lYJZyLdb8UR990yptTOSZRl0bc1bzJE/tXLRbDsyAEV0FP9HewF3oAk050Tgxxr84PxqSPvZ4zxO4IF/m1Bto7juQAgL/4ul6mRS6MZxvcGTHMj1WAG704xss2JYdCt24kG8c4hv7QzecfINF3rI9oRu/v0I3OOZh2bbQjc/5BgcaLFsZuvEe32DWXaYvzvBDxVqH1qbDCkUStamFxqUC/VKBcSlPv5SnL12HJaYl3xpf1Cpt8a3xmjv2JTIoED7vCKVUjtV9PXjt+v4D/131TkwTYiHFYDl6LzImxDy68pXMjjt5FJgGchID0/AH13PLX7ZLevSK7qCux7IccJU+CVpdYG5JgGqJhqS+kp1XZ4E7Pi8zOKPAy6WoomjzgOE1Po+ynaNleusHdtJ3yKMStUVsLvwoyW1vIAbBKUtNZGPDwQU2Mdk4sr5y0mSWKweXMo8v4VlZsWy8iJgQp+F1VVbJ69+Nxf44RMerdBepF1lsqwNewdhYpT1eYL6mgHlJpF7bTSmqcIryaDeQM3pI3LfR3FNf4qAbvIRZBh/CAsHK76gLkMAPPsWE1gr4ZKFT8qZWFnWh6nG9/2nny3PgMk5AE2lKfCGGtJa+cVnAzJ7keZ19yczOn3qVj9Vbn6jDzh+tNbHzdx2QnechO/NLs4CrswJXZRFX
*/