#ifndef BOOST_MOVE_DETAIL_IS_SORTED_HPP
#define BOOST_MOVE_DETAIL_IS_SORTED_HPP
///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2017-2018. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace movelib {

template<class ForwardIt, class Pred>
bool is_sorted(ForwardIt const first, ForwardIt last, Pred pred)
{
   if (first != last) {
      ForwardIt next = first, cur(first);
      while (++next != last) {
         if (pred(*next, *cur))
            return false;
         cur = next;
      }
   }
   return true;
}

template<class ForwardIt, class Pred>
bool is_sorted_and_unique(ForwardIt first, ForwardIt last, Pred pred)
{
   if (first != last) {
      ForwardIt next = first;
      while (++next != last) {
         if (!pred(*first, *next))
            return false;
         first = next;
      }
   }
   return true;
}

}  //namespace movelib {
}  //namespace boost {

#endif   //BOOST_MOVE_DETAIL_IS_SORTED_HPP

/* is_sorted.hpp
ow059F91fwQrlodKrH3Njie7qqybf5jh7nkhxFuL+HU01J6nyQoaZ3C7huNhMG58+p+B+HPcPsATSOd9swwq22fd8zYHo5Ew6VlvEg76hNfasXlckPg8qJpDGD49W+je5g+6EOxdAcubXlrAUZ1OIdXSEVM3At8tmGV5q6xNAVYRxw5sjz9s2mJeGGofvgULZ0soU6iNIfVKsue5oCMEsbr+1J1CDruJ42WsPEfkpWD58hIDlr/3WglqQ+rxtfWr6e3v9lt6gjOm/NormE2swPhAhMhDaopxfRIGUutRnHb+76ZtxzUE4YvRWmpmVW7EsK0Q1pLfagTs2YV+myN8gufJMO97fSUPu3PO+r4oBjOT3Y/+5Avkpxul9Ass3nm4nfgwBJk2Fm6BMjwWgAUOHnDSsEH5Yo33x0XtFMlAJh4Z5SC3Q0+MjYmL6NaSmvM1nC8d5fszopTmcHSdjVe4yX3b6/LvZLGp4tyMqtOl4y7m3U1RoNGHXxqqcquOzAWNzwLWapsnUKpLNv2gF8nIBO+poU4eTQJm44BJOyXxfE2p+FTTJCJr8cl+Hg==
*/