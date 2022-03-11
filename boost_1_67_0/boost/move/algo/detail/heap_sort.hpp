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
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
*/