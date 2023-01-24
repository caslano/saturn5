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
3yf23s8DUP1vwGNBilM8k4SkzIy3K/kBG+0vodTWicu56bddH9w9ZC/qGdKFW1nxQ26nCThTcTPT8UPCTAnjWEEdVIgHqlg5TkKLNuIPhW3QL7VKi3qvttob1+O+uD8eKAjOCE8NJY0w9Cf8Qnv0Y6wk5aRkCFXh3ZG90crY2oJTsbnhGfCakX4toZWGZ+NE+HX4NRmoDb+LGnFIMVQtbES0mBZu1IhRK+G9Cb+zXkzlhYel9ej2uXf53/jekNUDe3SPabtcIZ7BgBLGYdwwNKoD+JrEKDQKypq0KtHDyxGadxNk5McxKgAqUIoWYmqLSHyM8pAXaJz5rTk93F52AQDLeqw4YnQFyVPcuEJYCpvJYlLeyEIalAWOP32uutNe/mnyTReGIruhyGHLL3Ik0hu4HcEpjcV/7bHR549JudMYFeG4UIQGrJhllj+x9jS3tyR8fx5kxGW4CjVhZnsSBFljNMga+hDbk5qneZ9MAeCupwnPM4SnMkUn2+lD4BZi/1ssLZNXK6uo1a8PVStBZlg6eK/Z87StLc9ARl7J2jIVtQgZ9qa37e9/QN6/nb1fyt8vGo7GJn6AxrpmZaRNwb1kJhP7TwBu3Gv6qPKTa7ZJd2rzMNoEOAvEQrxZjONbBHFwPVr22uoxDzJ8W6xDYXo4yPbFCOyL18G+aDj2xW54/X1SdhcAh/ea9NduAsXMEisC+9E+oL9b3VIC
*/