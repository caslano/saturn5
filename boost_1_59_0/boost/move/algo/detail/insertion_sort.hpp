//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_DETAIL_INSERT_SORT_HPP
#define BOOST_MOVE_DETAIL_INSERT_SORT_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/utility_core.hpp>
#include <boost/move/algo/move.hpp>
#include <boost/move/detail/iterator_traits.hpp>
#include <boost/move/adl_move_swap.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/move/detail/placement_new.hpp>
#include <boost/move/detail/destruct_n.hpp>
#include <boost/move/algo/detail/basic_op.hpp>
#include <boost/move/detail/placement_new.hpp>
#include <boost/move/detail/iterator_to_raw_pointer.hpp>

#if defined(BOOST_CLANG) || (defined(BOOST_GCC) && (BOOST_GCC >= 40600))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif

namespace boost {  namespace movelib{

// @cond

template <class Compare, class ForwardIterator, class BirdirectionalIterator, class Op>
void insertion_sort_op(ForwardIterator first1, ForwardIterator last1, BirdirectionalIterator first2, Compare comp, Op op)
{
   if (first1 != last1){
      BirdirectionalIterator last2 = first2;
      op(first1, last2);
      for (++last2; ++first1 != last1; ++last2){
         BirdirectionalIterator j2 = last2;
         BirdirectionalIterator i2 = j2;
         if (comp(*first1, *--i2)){
            op(i2, j2);
            for (--j2; i2 != first2 && comp(*first1, *--i2); --j2) {
               op(i2, j2);
            }
         }
         op(first1, j2);
      }
   }
}

template <class Compare, class ForwardIterator, class BirdirectionalIterator>
void insertion_sort_swap(ForwardIterator first1, ForwardIterator last1, BirdirectionalIterator first2, Compare comp)
{
   insertion_sort_op(first1, last1, first2, comp, swap_op());
}


template <class Compare, class ForwardIterator, class BirdirectionalIterator>
void insertion_sort_copy(ForwardIterator first1, ForwardIterator last1, BirdirectionalIterator first2, Compare comp)
{
   insertion_sort_op(first1, last1, first2, comp, move_op());
}

// @endcond

template <class Compare, class BirdirectionalIterator>
void insertion_sort(BirdirectionalIterator first, BirdirectionalIterator last, Compare comp)
{
   typedef typename boost::movelib::iterator_traits<BirdirectionalIterator>::value_type value_type;
   if (first != last){
      BirdirectionalIterator i = first;
      for (++i; i != last; ++i){
         BirdirectionalIterator j = i;
         if (comp(*i,  *--j)) {
            value_type tmp(::boost::move(*i));
            *i = ::boost::move(*j);
            for (BirdirectionalIterator k = j; k != first && comp(tmp,  *--k); --j) {
               *j = ::boost::move(*k);
            }
            *j = ::boost::move(tmp);
         }
      }
   }
}

template <class Compare, class BirdirectionalIterator, class BirdirectionalRawIterator>
void insertion_sort_uninitialized_copy
   (BirdirectionalIterator first1, BirdirectionalIterator const last1
   , BirdirectionalRawIterator const first2
   , Compare comp)
{
   typedef typename iterator_traits<BirdirectionalIterator>::value_type value_type;
   if (first1 != last1){
      BirdirectionalRawIterator last2 = first2;
      ::new((iterator_to_raw_pointer)(last2), boost_move_new_t()) value_type(::boost::move(*first1));
      destruct_n<value_type, BirdirectionalRawIterator> d(first2);
      d.incr();
      for (++last2; ++first1 != last1; ++last2){
         BirdirectionalRawIterator j2 = last2;
         BirdirectionalRawIterator k2 = j2;
         if (comp(*first1, *--k2)){
            ::new((iterator_to_raw_pointer)(j2), boost_move_new_t()) value_type(::boost::move(*k2));
            d.incr();
            for (--j2; k2 != first2 && comp(*first1, *--k2); --j2)
               *j2 = ::boost::move(*k2);
            *j2 = ::boost::move(*first1);
         }
         else{
            ::new((iterator_to_raw_pointer)(j2), boost_move_new_t()) value_type(::boost::move(*first1));
            d.incr();
         }
      }
      d.release();
   }
}

}} //namespace boost {  namespace movelib{

#if defined(BOOST_CLANG) || (defined(BOOST_GCC) && (BOOST_GCC >= 40600))
#pragma GCC diagnostic pop
#endif

#endif //#ifndef BOOST_MOVE_DETAIL_INSERT_SORT_HPP

/* insertion_sort.hpp
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
*/