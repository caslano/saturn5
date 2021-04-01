//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_NEXT_CAPACITY_HPP
#define BOOST_CONTAINER_DETAIL_NEXT_CAPACITY_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

// container
#include <boost/container/throw_exception.hpp>
// container/detail
#include <boost/container/detail/min_max.hpp>

#include <boost/static_assert.hpp>

namespace boost {
namespace container {
namespace dtl {

template<unsigned Minimum, unsigned Numerator, unsigned Denominator>
struct grow_factor_ratio
{
   BOOST_STATIC_ASSERT(Numerator > Denominator);
   BOOST_STATIC_ASSERT(Numerator   < 100);
   BOOST_STATIC_ASSERT(Denominator < 100);
   BOOST_STATIC_ASSERT(Denominator == 1 || (0 != Numerator % Denominator));

   template<class SizeType>
   SizeType operator()(const SizeType cur_cap, const SizeType add_min_cap, const SizeType max_cap) const
   {
      const SizeType overflow_limit  = ((SizeType)-1) / Numerator;

      SizeType new_cap = 0;

      if(cur_cap <= overflow_limit){
         new_cap = cur_cap * Numerator / Denominator;
      }
      else if(Denominator == 1 || (SizeType(new_cap = cur_cap) / Denominator) > overflow_limit){
         new_cap = (SizeType)-1;
      }
      else{
         new_cap *= Numerator;
      }
      return max_value(SizeType(Minimum), max_value(cur_cap+add_min_cap, min_value(max_cap, new_cap)));
   }
};

}  //namespace dtl {

struct growth_factor_50
   : dtl::grow_factor_ratio<0, 3, 2>
{};

struct growth_factor_60
   : dtl::grow_factor_ratio<0, 8, 5>
{};

struct growth_factor_100
   : dtl::grow_factor_ratio<0, 2, 1>
{};

}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_NEXT_CAPACITY_HPP

/* next_capacity.hpp
tvPhXJUhke6QFCnPmrVpd7Vik+eRXHokL7hCDBGmTONa8vMCKwAks3NcB8wJbozyWUTI1C9pfhBNeWUVPvuOy8/UAjxUCAZ++O/Mm4wp37V9PKGKg9zOSIvm89A3BXWrvVakNKYl/2VGTH9Esi0Xdl84hHuuOyW586MpRsmd26I6YEr0IkYF9wAm/PHTRndBvBdoHZCXirs1FMdGKsoJQb8juyGKCiFoS3srw25rNI9lrKR3AVpCSZlWfVIfKAriJFMCrfOZCyWfOnj8yrgMR09W/9axNXOjizKkdSWVHGI0yd/Ceikbma1MHRwy8CrY/Cay2gW/fWkVMup7PUHK6lfwSxXNSC1YGH5s6GI9ZTwbM9oGr75YmYoY9eeCXphSJ+WzSxJYIJDAz0y0b9U5BgtF2orYZ/S8bpQWZOWlCkYt/2X5ZNQ0UCIjVuDG8nPMO4VD/iB2GHK9WMraG+aDcy6hAh3KWwrC4XA6DEcic7U0V+pJeb1JKtb/n5SDfib9IejD9VvkHD/tR9L0wuwaXv7jeykYwMm8d13MUYlUZhEDTGxanuMFCMCbJw==
*/