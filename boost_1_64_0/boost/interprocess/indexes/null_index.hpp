//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_NULL_INDEX_HPP
#define BOOST_INTERPROCESS_NULL_INDEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/offset_ptr.hpp>

//!\file
//!Describes a null index adaptor, so that if we don't want to construct
//!named objects, we can use this null index type to save resources.

namespace boost {
namespace interprocess {

//!Null index type
//!used to save compilation time when
//!named indexes are not needed.
template <class MapConfig>
class null_index
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   typedef typename MapConfig::
      segment_manager_base    segment_manager_base;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   typedef int * iterator;
   typedef const int * const_iterator;

   //!begin() is equal
   //!to end()
   const_iterator begin() const
   {  return const_iterator(0);  }

   //!begin() is equal
   //!to end()
   iterator begin()
   {  return iterator(0);  }

   //!begin() is equal
   //!to end()
   const_iterator end() const
   {  return const_iterator(0);  }

   //!begin() is equal
   //!to end()
   iterator end()
   {  return iterator(0);  }

   //!Empty constructor
   null_index(segment_manager_base *){}
};

}}   //namespace boost { namespace interprocess {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_NULL_INDEX_HPP

/* null_index.hpp
t2ryoZj73WWGjO8qnldUGDI/VgCnUR7KdrYSmEN8yv+oxMD+e9n/OvZ/Dft/DfvfwP5fy/5fJ/0Hn5r3NrL/mzXz3pPcTr3L/ep7PL48DRwH/BOwHPgXYJVob0NluXkfuJ75bhLtNXATf/P6C5/nwthGs/4y1SXLTxawE3A6MApYDKRz3MDuwFm8DjMXOBBYBEwlPpn+bOAIth/N9hPYfiJwPnAKMA84HbgQmAMs4PWYxcBSdreC3a0ELgHeALwaeCPb30r2Mn3NoCZOXwmX3x6gE5y+EI6/h9eHJvO6TzT73w3YABwCXMP2Ip/ief0nEbgd2NMl27dewAeY/2Hm/xGwL/BxYH/g02x/iO1/DxzskvXhUuBbwJEu2e6PBoYg3mOB0cB0YCpwkovbfWAmcCIwm75lurfQ+R5ON8u1C2gjp7tC+AusYrlWszzXALsBvcBk4BeAg4G1wDHAOuB44GqWUwPn27XAhcDrgEvYn0JgPbCYvmW8lvJZFypTHK8OoHyOVxnPI8p5PlDB4/SV3L5U8ryyCjgZWM3j9lXATPrm9RwT9YnDGcVy7wtK4n5/nSHHYTcCe1C+yHp1E3AM9QcynFsMWS438TrDrbwudxtwKfMVU52V9e+LwArgHcAq4J1AL8lDjhe+bMh2HGWH6uM9wC/T3EyuG37dkO3lg8CfAb8BPAx8GPgycDfwNeA3gf/k8D8BfgcoEvtdYCTwe0C3Ke07Ae8DxgF3AIcBdwJHkL3Mr2RQVLJa/2rgJeoYlss3LT5QkHxpfnxLW/D19uPLCJIvJ0i+pUHyeYPka2wlvQ/58W0Jkm9nkHx7/PgiTTvfV/34DgTJdyRIvqYg+ZoVH8q3nS9PrQuzrhvaMs36Qw3X91rgMGAdcDh/j6Jv1W7ksD+zNO3Gn3h+9SEwCfhP4BDgR0AR7qe8bhAaItsLF49Xw4BZwIgQNQ/fw+EM0MzDX+F5+OtAYfZmpHLXxO7iNesjT3M6DwLjgM8A5fiK9XOoDXKOr+ZwuuYDewFzTRluPjAFeBVwEDCP8k2aj2DzkcAFwBnAhaZst67g9YzFwCrmqwYWAGuBi4DXsP2NZK/mi3s4nsM188XNIXJ88iXgQOAXgWnAu4FjgNt4PHwf8AvAB4C3AR8CirR+E7gD+G3gY8DvAN8Efhf4NvB7wHdFHIB/Bn4f+D5wL/BT4KM8j3wMGAn8MdBtyvjEAp8C9gYeBA4APgMcDHwamErfMp0HDNYZAJ5iecSKcDidC3kecFUI718AE4A3AhOBhcB0/h4HLAZOApbwuL8CWA1cweP9VTzOrwLeAKzheVI98FvAtcA9wOuBL9K3bP83AE9wOCeB64Hv8ffRMJQ7TJwyQOWgbaDDoLOgNEykloC2gvY2ApFh6XNCjALQVtAj4jc8OwQ8Dp5mYQaeSphtAe0DRc0NoYnYQZgnAUVkEkBeMTkDTcTvdPAUgLYLM+A20FKY75sLgtkx4CHgGaBnXoixCXa7QIdBx2E+FGZnN8AOCZqJ38nAZpjHTIRbhJsCzAR55wFhtwWYj+8G/C4F7sN3E2g7vveCjoLOgNI3gg/UPwfuQJvAWw7cCLNtwj1+7wc+gu+TQM9lMIfZHlDMTUgvvicCl4KO5OA3vpuBDfjeCsrG9xJQwvwQow64G2abgYeAu4FpMN8PzAGehFmDQHxvBZ4R7m5G2Ph9EBQzCfkAWgqzicBTj4Efv7eAluJ7N/Ak+A4BI3NFQYP7W5A3+J0BSsfvyH2IM6gAv/fAvlTw4fc20AF8N4H243czcBT4kicj3/HdAL7toMzJ4AMuBbrykCbgUGAmeNM3IR2gpfi9GeaN4ht2XtA2/N4C3Cu+YX8=
*/