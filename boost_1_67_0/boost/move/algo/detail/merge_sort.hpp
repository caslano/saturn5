//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_DETAIL_MERGE_SORT_HPP
#define BOOST_MOVE_DETAIL_MERGE_SORT_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>
#include <boost/move/detail/workaround.hpp>

#include <boost/move/utility_core.hpp>
#include <boost/move/algo/move.hpp>
#include <boost/move/algo/detail/merge.hpp>
#include <boost/move/detail/iterator_traits.hpp>
#include <boost/move/adl_move_swap.hpp>
#include <boost/move/detail/destruct_n.hpp>
#include <boost/move/algo/detail/insertion_sort.hpp>
#include <cassert>

namespace boost {
namespace movelib {

// @cond

static const unsigned MergeSortInsertionSortThreshold = 16;

template <class RandIt, class Compare>
void inplace_stable_sort(RandIt first, RandIt last, Compare comp)
{
   typedef typename iterator_traits<RandIt>::size_type  size_type;
   if (size_type(last - first) <= size_type(MergeSortInsertionSortThreshold)) {
      insertion_sort(first, last, comp);
      return;
   }
   RandIt middle = first + (last - first) / 2;
   inplace_stable_sort(first, middle, comp);
   inplace_stable_sort(middle, last, comp);
   merge_bufferless_ONlogN_recursive
      (first, middle, last, size_type(middle - first), size_type(last - middle), comp);
}

// @endcond

template<class RandIt, class RandIt2, class Compare>
void merge_sort_copy( RandIt first, RandIt last
                   , RandIt2 dest, Compare comp)
{
   typedef typename iterator_traits<RandIt>::size_type  size_type;

   size_type const count = size_type(last - first);
   if(count <= MergeSortInsertionSortThreshold){
      insertion_sort_copy(first, last, dest, comp);
   }
   else{
      size_type const half = count/2;
      merge_sort_copy(first + half, last        , dest+half   , comp);
      merge_sort_copy(first       , first + half, first + half, comp);
      merge_with_right_placed
         ( first + half, first + half + half
         , dest, dest+half, dest + count
         , comp);
   }
}

template<class RandIt, class RandItRaw, class Compare>
void merge_sort_uninitialized_copy( RandIt first, RandIt last
                                 , RandItRaw uninitialized
                                 , Compare comp)
{
   typedef typename iterator_traits<RandIt>::size_type  size_type;
   typedef typename iterator_traits<RandIt>::value_type value_type;

   size_type const count = size_type(last - first);
   if(count <= MergeSortInsertionSortThreshold){
      insertion_sort_uninitialized_copy(first, last, uninitialized, comp);
   }
   else{
      size_type const half = count/2;
      merge_sort_uninitialized_copy(first + half, last, uninitialized + half, comp);
      destruct_n<value_type, RandItRaw> d(uninitialized+half);
      d.incr(count-half);
      merge_sort_copy(first, first + half, first + half, comp);
      uninitialized_merge_with_right_placed
         ( first + half, first + half + half
         , uninitialized, uninitialized+half, uninitialized+count
         , comp);
      d.release();
   }
}

template<class RandIt, class RandItRaw, class Compare>
void merge_sort( RandIt first, RandIt last, Compare comp
               , RandItRaw uninitialized)
{
   typedef typename iterator_traits<RandIt>::size_type  size_type;
   typedef typename iterator_traits<RandIt>::value_type value_type;

   size_type const count = size_type(last - first);
   if(count <= MergeSortInsertionSortThreshold){
      insertion_sort(first, last, comp);
   }
   else{
      size_type const half = count/2;
      size_type const rest = count -  half;
      RandIt const half_it = first + half;
      RandIt const rest_it = first + rest;

      merge_sort_uninitialized_copy(half_it, last, uninitialized, comp);
      destruct_n<value_type, RandItRaw> d(uninitialized);
      d.incr(rest);
      merge_sort_copy(first, half_it, rest_it, comp);
      merge_with_right_placed
         ( uninitialized, uninitialized + rest
         , first, rest_it, last, antistable<Compare>(comp));
   }
}

///@cond

template<class RandIt, class RandItRaw, class Compare>
void merge_sort_with_constructed_buffer( RandIt first, RandIt last, Compare comp, RandItRaw buffer)
{
   typedef typename iterator_traits<RandIt>::size_type  size_type;

   size_type const count = size_type(last - first);
   if(count <= MergeSortInsertionSortThreshold){
      insertion_sort(first, last, comp);
   }
   else{
      size_type const half = count/2;
      size_type const rest = count -  half;
      RandIt const half_it = first + half;
      RandIt const rest_it = first + rest;

      merge_sort_copy(half_it, last, buffer, comp);
      merge_sort_copy(first, half_it, rest_it, comp);
      merge_with_right_placed
         (buffer, buffer + rest
         , first, rest_it, last, antistable<Compare>(comp));
   }
}

template<typename RandIt, typename Pointer,
         typename Distance, typename Compare>
void stable_sort_ONlogN_recursive(RandIt first, RandIt last, Pointer buffer, Distance buffer_size, Compare comp)
{
   typedef typename iterator_traits<RandIt>::size_type  size_type;
   if (size_type(last - first) <= size_type(MergeSortInsertionSortThreshold)) {
      insertion_sort(first, last, comp);
   }
   else {
      const size_type len = (last - first) / 2;
      const RandIt middle = first + len;
      if (len > ((buffer_size+1)/2)){
         stable_sort_ONlogN_recursive(first, middle, buffer, buffer_size, comp);
         stable_sort_ONlogN_recursive(middle, last, buffer, buffer_size, comp);
      }
      else{
         merge_sort_with_constructed_buffer(first, middle, comp, buffer);
         merge_sort_with_constructed_buffer(middle, last, comp, buffer);
      }
      merge_adaptive_ONlogN_recursive(first, middle, last,
         size_type(middle - first),
         size_type(last - middle),
         buffer, buffer_size,
         comp);
   }
}

template<typename BidirectionalIterator, typename Compare, typename RandRawIt>
void stable_sort_adaptive_ONlogN2(BidirectionalIterator first,
		                           BidirectionalIterator last,
		                           Compare comp,
                                 RandRawIt uninitialized,
                                 std::size_t uninitialized_len)
{
   typedef typename iterator_traits<BidirectionalIterator>::value_type  value_type;

   ::boost::movelib::adaptive_xbuf<value_type, RandRawIt> xbuf(uninitialized, uninitialized_len);
   xbuf.initialize_until(uninitialized_len, *first);
   stable_sort_ONlogN_recursive(first, last, uninitialized, uninitialized_len, comp);
}

///@endcond

}} //namespace boost {  namespace movelib{

#include <boost/move/detail/config_end.hpp>

#endif //#ifndef BOOST_MOVE_DETAIL_MERGE_SORT_HPP

/* merge_sort.hpp
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
*/