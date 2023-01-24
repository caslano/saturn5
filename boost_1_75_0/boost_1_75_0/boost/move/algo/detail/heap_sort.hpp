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
U/JuKSbGUIesQa9pWEMa7UveLhWNaLfadXY3P1M7D4D4S9IuK2ZbRSuLrUaDFko3CPQTMYnZ05j7B/M/s/zbLDusil/yM9NbAGj8JbEBth3nKxvQdhBgF6EQPTe4hj3Zql9yP651APyS1nGwPeJypsRK+U6iL6hZ4mRplWgQ00QJFiOJhTIhG13XMR5d1xJD1yW+ha6Dvd0/4OvX+7y9Zr8P/JLb8H0JwN/tIfSIfGeAWbjQw/TUpsyKPZepRLMfdL+GEVBXoQItdIs+KSwXq1Vai3e+7tWiakwplnQ0R4upVZKB1kIX+LwFmqayel4H9QxDPfOhnoEh9dwIVTtM6rkVgFN7zD0nZTPjZXYAXZRWVlBKxZ5d1HuqueAWjAuFS2JSmi8ulmcrSaFPPK5tV2eJMaGB2EmTlS1pslfRqK2MZPnh2+IohZ7kfpHjAah8MtO4sDr16XvRfhiWJnGu1CLOAYrFxpyemd+Agq5wxjPzTkApE3uH+wEYgBSi+Ptt+soz7IifW85tNa2NyFEGH5JJ7F+mURId0FkWsel2eMIzY7ym+9BBmJlTYStJyBXKbnmG2qRFvBE97Iv4I4FIcCIOhP1x3fDGtbgak0tgudWHThktwXgg7jf0OPxepK4ii1DQUUAtMM1IyVlVyPRXgHUI9JLEwKL6r6e4n8FCAFY8ZdrLc0d9aQLGM4S7Yfdiet+FSHfNHaL37YFi
*/