//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2016-2016. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_IS_SORTED_HPP
#define BOOST_CONTAINER_DETAIL_IS_SORTED_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace container {
namespace dtl {

template <class ForwardIterator, class Pred>
bool is_sorted (ForwardIterator first, ForwardIterator last, Pred pred)
{
   if(first != last){
      ForwardIterator next = first;
      while (++next != last){
         if(pred(*next, *first))
            return false;
         ++first;
      }
   }
   return true;
}

template <class ForwardIterator, class Pred>
bool is_sorted_and_unique (ForwardIterator first, ForwardIterator last, Pred pred)
{
   if(first != last){
      ForwardIterator next = first;
      while (++next != last){
         if(!pred(*first, *next))
            return false;
         ++first;
      }
   }
   return true;
}

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_IS_SORTED_HPP

/* is_sorted.hpp
3N/z7D3qhEajou/LnpUu+/yH7//PziooLHkC4F++///TWL6/jQhVz3g5rhog29AffRjDPlCorvN0pfwUVXZKal6e56JkTq56kau8W4s4nkDrXqmBKl0jI8L5GQDyLfU+c3W9w/lapMTFp8pS9zvdkZLFexsMfX9HJxWnk1rjf41ak5D9mgxCg5K4vhMUFqbTSjq5FjJOpSvvde3j5Yjrfy8gZehrH578Y1U7lHp3uNo2ua4m
*/