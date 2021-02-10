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
SBfO+2MPME8e4m1Ltb8zHpVYd93fzrbh1UZssahucE9yFzb+SYvZsixeKXSZXDUDsNiXAkfhB/Hmq+Ls+nbYZVp0gbcLb+2A1vwFyJHmI5YLAT/XgV2bN/19Txx86YWwzOOsMgc5CNlr9AeW1Q7FO2e1u4xc6eyRQd8Xc+vLuYVL3FYtJhIT6GL+l3NEp/1mxHFHuKMTzyKwrprkKp/EZT+qNue8mgPmN/nGYsxYn3n0K3Wqe4e1oXExuTdXH5WYX8U4BUFhDcaUmj5kkI39KDc2HbnArDjmpBHVdzkLxEY5b+FJezdJtxOtS6XbPz79py1z48loOuqO0GN0Ujv8PJ5DS2Sf9X7v3IwHvc8N5fvlHBGE9qSNv920Tle87zmGCzgRksYIOEP6x3U3M6wNAtgv8svuQ8ZdU9NPFuhBlVw1hB1DgIT57EBr//9smxAeTnZTNUY9LJ/P1rzyJ98Y0De8o8FikrhuBX/zDf0Nkhp2JrLLl/t4+vlnm3GPf/HRUJ3Az7pA6sb1WpVyiKsW/UPf3WW1pm09YdoMi+xTvY6Fq4YTtWu4GtYmok/C/bnOxYJHVw48TGFCcLu5QlWq8xtZLMImZ0txxd8BLu4doocAPfeD3hFQPL3XKxB4uXJlvwX5gZA+gNKWpwmm
*/