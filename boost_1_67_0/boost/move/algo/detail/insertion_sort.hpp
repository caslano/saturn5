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

#endif //#ifndef BOOST_MOVE_DETAIL_INSERT_SORT_HPP

/* insertion_sort.hpp
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
*/