//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2017-2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_DETAIL_HEAP_SORT_HPP
#define BOOST_MOVE_DETAIL_HEAP_SORT_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>
#include <boost/move/detail/workaround.hpp>
#include <boost/move/detail/iterator_traits.hpp>
#include <boost/move/algo/detail/is_sorted.hpp>
#include <boost/move/utility_core.hpp>

namespace boost {  namespace movelib{

template <class RandomAccessIterator, class Compare>
class heap_sort_helper
{
   typedef typename boost::movelib::iterator_traits<RandomAccessIterator>::size_type  size_type;
   typedef typename boost::movelib::iterator_traits<RandomAccessIterator>::value_type value_type;

   static void adjust_heap(RandomAccessIterator first, size_type hole_index, size_type const len, value_type &value, Compare comp)
   {
      size_type const top_index = hole_index;
      size_type second_child = 2 * (hole_index + 1);

      while (second_child < len) {
         if (comp(*(first + second_child), *(first + (second_child - 1))))
            second_child--;
         *(first + hole_index) = boost::move(*(first + second_child));
         hole_index = second_child;
         second_child = 2 * (second_child + 1);
      }
      if (second_child == len) {
         *(first + hole_index) = boost::move(*(first + (second_child - 1)));
         hole_index = second_child - 1;
      }

      {  //push_heap-like ending
         size_type parent = (hole_index - 1) / 2;
         while (hole_index > top_index && comp(*(first + parent), value)) {
            *(first + hole_index) = boost::move(*(first + parent));
            hole_index = parent;
            parent = (hole_index - 1) / 2;
         }    
         *(first + hole_index) = boost::move(value);
      }
   }

   static void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
   {
      size_type const len = size_type(last - first);
      if (len > 1) {
         size_type parent = len/2u - 1u;

         do {
            value_type v(boost::move(*(first + parent)));
            adjust_heap(first, parent, len, v, comp);
         }while (parent--);
      }
   }

   static void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
   {
      size_type len = size_type(last - first);
      while (len > 1) {
         //move biggest to the safe zone
         --last;
         value_type v(boost::move(*last));
         *last = boost::move(*first);
         adjust_heap(first, size_type(0), --len, v, comp);
      }
   }

   public:
   static void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
   {
      make_heap(first, last, comp);
      sort_heap(first, last, comp);
      BOOST_ASSERT(boost::movelib::is_sorted(first, last, comp));
   }
};

template <class RandomAccessIterator, class Compare>
BOOST_MOVE_FORCEINLINE void heap_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
   heap_sort_helper<RandomAccessIterator, Compare>::sort(first, last, comp);
}

}} //namespace boost {  namespace movelib{

#include <boost/move/detail/config_end.hpp>

#endif //#ifndef BOOST_MOVE_DETAIL_HEAP_SORT_HPP

/* heap_sort.hpp
T+CD+kfy/Z/qN45hsTgLjB3oOuKSjfV53YcVejBjoDr0KFvDbg8FmByVCojdMkOp8NIaz4ZpnYxNEp5zghNGa1pVRipzValwJZvQQDGlCVabJcnzTSka9m0vag+m5hNsIZmSnQXjg13a2WiXXBt2leVtVmQ63hZtdFFdyTRUyX6gpfuHLuzAnaFvFL161KKxXDV9o+jV59E7B3LGohwX5Dh650CeqE6Duqg3eiOeI10LOuwldByGDmOpViMscWScSubuRP6uRuTv0tqhxQPXsU3cHtczIK2aUn/QdYQx4iWMQDOnXao2S3KYpbD7XjI/7eTSFw+MI0OTYSRxCb5KB/yN2NQzwu0Vxx0KX87PWSZ+T0eeOMjlPVzdz3M3bsMooOnCrt63aGZ4HsNLzvcK30RafPtEov5ytF7lE6DQ90Sbw1cyZHgcN7e2lzS3gB+yQm+4aW6ShyO18O0LjVUECsry9+n56uRy1q0k72NO8VQ7mua7YpXJmcDRmG0GQ4xzb8kCAk7FLY4wF/JMsRcMUwfUFoQlKcnmo1ZwUqFx0lk6WQU5rGj3iA+7JuTZsNdnvq4MeRDenA3aKElLsF3+FvN9ZSBYdQWRmaqJ9B+HPa9jSrAZ+ZaNBgJmFv31FonCV2NHHbS/AebnsF8hy/DLyTTcutX08xbdz5k9uZ8sPXXw+X7mv0d+8V37cfOTU3Ob4SdLiJdWiwxUnsUCx0pUUCLYZCNLnyM5OhI4Du7LP+WDu5QC+pOHDb1Wbo2KH83VsbzR9Eka1kuw0InxMvbSMq56zZyobNESU0aimPnY6I6ZFb9VVlIQOcZ+vq4/ff16P1mPDqT6A6+qvnz0iav+q0TQxbujlo98P5uYBrzP7PeV7snUfnzlXWZN6B+8JtB25Q/T6iTzIesQQ/7SvZnGArc9A4U6rjw1rS7srdDauGKnRW+0szOcY5izqo2mlm7+VzggYP7GMv3rn+y/vFX+VHpcjDija6sIlSSEiaekE2fYz6jqnsrC88PojzlG9+HIc1EUUCoip7YHz9VhrqnP5zjMXVStfTNU7XlvPFVjSrVbU6rdcofcXVa0WVrTdtOoTCUgK3FRnKFxFGfUonEu2gRK5UDOWDTABTkujoqduCiZWhbtKiviTCARRcUIQRHMcQIh+4tHEbINdAa3TIHC1gRDgS6kU+z+rkISZvJzNnXObqdJwpZEClTDFGjrogvDcxheZL6gQCwk6cSVBSXWP6jPZYAC9UFTx6imLneaerytbuo8bmoHdqCuk4iYoT4ubsHmBW8TUkbTHFY86njMY6KqGQzaZ29mRQUj0k5FAo0NoBPkwpMbR4GGhRcJQio0Qm7qIr1c7PQy0/QSKX4ZC7U0XqFJ5ivTpBqmQTFFk8x30KRzQZNG8AzWME2qaYQm/baX3iBMk3ZqmlSjaFLMoUk8h9L5W3Tn3wgJTfqpfsWirMlt/k+TDL1p39ecV4be+D2GehxKlOYEIA6z0cZ2UZpKoRcm6JZem+4wJgHwRH5NO2qZdtQ2RTt+81ES7Ygx7Yhp2lHbGO2Yk0w7apNox5xGaceoj+JpR4y3UkzRjti3STsc/V9vvu9ysvocleH4yunwiFHsAl9vifZPb9jGEaRYG0nAP6RSLO0bTPlqGIF3DtXXXcyFjoOG8PQiWDr9a6Ufq+Vr4RNf4asPRLJPuK+18FUtAb5X7ti3deTN881wYO6Dj/RS+vz1Ppc+Pz3Skf6PRAZSDC1IqiIjo4VGn9vur9wxcnCUDkdPNazTjTH1as2IA/xqlLljXtdPKbrPGMqvaFD9rdVmUPfJoJ4PfrNBwZ4Y9/sCbuuK7oaDc9tfvhZ3H7ZtWkZ0o5BZwYs=
*/