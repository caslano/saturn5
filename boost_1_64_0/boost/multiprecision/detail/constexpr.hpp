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
RLqbYqFPQU+re+EDvKNYaryoMpAswv3sC3BoWdu71jBMhRaoJ+rh/s4tsa1WKajRJcMDrz27pbAVoCCmz9JspsojGqXPSvxjVJ5+l8CLgFuSdXRdCDNpIAIarn2J9lEs3HUqTHyew7Of53/9XWTa3ubqGwQS+BTwTGXNVaSVWXRelrsKLrcw1j82wo35pmRsgFiC2mR2lWn2x6PjJsdp5YccZcd47VDbkZldsz3UYSZmxWV2lXNQ7IS0IGJNQv+9rpmDiUZyP8Vu2QXSb4zr3eHCXoOnQWwv1NDAHycXxa/XjSXrgdw+1RiClUInSeBw1EW2mJ24Gmaa7T2SK34yuOl10cg3jZsK0cfR4CBPxnbBdS/hSoQG90rVoxrIw6qOEuq5SI52e1FzcHPnl9P2wdrOyIxfbPNGEXEv0UmFR8fRjU24NUy/YToBiyVgyNt/0GKOp6MzhA+VdswPXDgKmlys/8I8jziY9gi0nmioxVwyD+cj9YjzDSYrypRWtONGgLOy+cb8aAfDYsvf6nFPSB75+QjXoF3smiEzmM3LwzrVdB4TDHBCuxwwIA==
*/