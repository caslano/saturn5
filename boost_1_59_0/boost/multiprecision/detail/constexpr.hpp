///////////////////////////////////////////////////////////////
//  Copyright 2019 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_CONSTEXPR_HPP
#define BOOST_MP_CONSTEXPR_HPP

#include <cstring>
#include <boost/multiprecision/detail/standalone_config.hpp>

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
   //
   // There are 3 branches here, only one of which is selected at compile time:
   //
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   if (BOOST_MP_IS_CONST_EVALUATED(*first))
   {
      // constexpr safe code, never generates runtime code:
      while (first != last)
      {
         *result = *first;
         ++first;
         ++result;
      }
      return result;
   }
   else
#endif
   {
#ifndef BOOST_NO_CXX17_IF_CONSTEXPR
      if constexpr (std::is_pointer<InputIterator>::value && std::is_pointer<OutputIterator>::value && std::is_trivially_copyable<typename std::remove_reference<decltype(*first)>::type>::value)
      {
         // The normal runtime branch:
         std::memcpy(result, first, (last - first) * sizeof(*first));
         return result + (last - first);
      }
      else
#endif
      {
         // Alternate runtime branch:
         while (first != last)
         {
            *result = *first;
            ++first;
            ++result;
         }
         return result;
      }
   }
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
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
*/