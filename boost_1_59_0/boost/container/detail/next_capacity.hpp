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

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

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
         new_cap = SizeType(cur_cap * Numerator / Denominator);
      }
      else if(Denominator == 1 || (SizeType(new_cap = cur_cap) / Denominator) > overflow_limit){
         new_cap = (SizeType)-1;
      }
      else{
         new_cap = SizeType(new_cap*Numerator);
      }
      return max_value<SizeType>
               ( SizeType(Minimum)
               , max_value<SizeType>
                  ( SizeType(cur_cap+add_min_cap)
                  , min_value<SizeType>(max_cap, new_cap))
               );
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

template<class SizeType>
BOOST_CONTAINER_FORCEINLINE void clamp_by_stored_size_type(SizeType &, SizeType)
{}

template<class SizeType, class SomeStoredSizeType>
BOOST_CONTAINER_FORCEINLINE void clamp_by_stored_size_type(SizeType &s, SomeStoredSizeType)
{
   if (s >= SomeStoredSizeType(-1) ) 
      s = SomeStoredSizeType(-1);
}

}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_DETAIL_NEXT_CAPACITY_HPP

/* next_capacity.hpp
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
*/