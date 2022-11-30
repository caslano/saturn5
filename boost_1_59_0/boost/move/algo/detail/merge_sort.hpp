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

#if defined(BOOST_CLANG) || (defined(BOOST_GCC) && (BOOST_GCC >= 40600))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif

namespace boost {
namespace movelib {

// @cond

static const unsigned MergeSortInsertionSortThreshold = 16;

template <class RandIt, class Compare>
void inplace_stable_sort(RandIt first, RandIt last, Compare comp)
{
   typedef typename iter_size<RandIt>::type  size_type;
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
   typedef typename iter_size<RandIt>::type         size_type;
   
   size_type const count = size_type(last - first);
   if(count <= MergeSortInsertionSortThreshold){
      insertion_sort_copy(first, last, dest, comp);
   }
   else{
      size_type const half = size_type(count/2u);
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
   typedef typename iter_size<RandIt>::type       size_type;
   typedef typename iterator_traits<RandIt>::value_type value_type;

   size_type const count = size_type(last - first);
   if(count <= MergeSortInsertionSortThreshold){
      insertion_sort_uninitialized_copy(first, last, uninitialized, comp);
   }
   else{
      size_type const half = count/2;
      merge_sort_uninitialized_copy(first + half, last, uninitialized + half, comp);
      destruct_n<value_type, RandItRaw> d(uninitialized+half);
      d.incr(size_type(count-half));
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
   typedef typename iter_size<RandIt>::type       size_type;
   typedef typename iterator_traits<RandIt>::value_type      value_type;

   size_type const count = size_type(last - first);
   if(count <= MergeSortInsertionSortThreshold){
      insertion_sort(first, last, comp);
   }
   else{
      size_type const half = size_type(count/2u);
      size_type const rest = size_type(count -  half);
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
   typedef typename iter_size<RandIt>::type       size_type;

   size_type const count = size_type(last - first);
   if(count <= MergeSortInsertionSortThreshold){
      insertion_sort(first, last, comp);
   }
   else{
      size_type const half = size_type(count/2);
      size_type const rest = size_type(count -  half);
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
   typedef typename iter_size<RandIt>::type  size_type;
   if (size_type(last - first) <= size_type(MergeSortInsertionSortThreshold)) {
      insertion_sort(first, last, comp);
   }
   else {
      const size_type len = size_type(last - first) / 2u;
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

#if defined(BOOST_CLANG) || (defined(BOOST_GCC) && (BOOST_GCC >= 40600))
#pragma GCC diagnostic pop
#endif

#include <boost/move/detail/config_end.hpp>

#endif //#ifndef BOOST_MOVE_DETAIL_MERGE_SORT_HPP

/* merge_sort.hpp
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
*/