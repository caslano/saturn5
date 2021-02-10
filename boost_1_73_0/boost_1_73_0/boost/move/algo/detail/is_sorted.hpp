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
mWEgVZLz5O7cb7j2p+R9HC9pMAwgHI3g6m+PzJjhE4hrfgqjM/io7tETjCB4NXl1NsGYvy5jj7SoE7CVD7Tb0IzdcY9ctICDD1zemnwCr51J8sQIJSeQFEofRcVNyW2WL4bmZlc8O2ZCl0qL9iF7Gsl2/Nze7LHeQpKzSnNzntVSNm9BlTbyXJuKyVvM75HLK7yQKHtmS1hHDXJzUQiL0DKWuA0GtIeYksyUGL3fRRbRNQFmH05dIfAgTA4XgxkIaXOcQq2FvIWBgsxGw0AAOrVJVW0wVZshStRux2S6r9SXaoD+sjanuBIyKeqU+w5+QunJ+6t1vFhOThB4ebWKaclMTg9NRahC3dJUPchCsbS1OdQBAnZIiIkMGtfsKSl5VcDJenUxW6xoIW5s46hUyLzQqI6ycBkPCHazJxtTHiXC/B1lSOVnXomsAacrlhlegcm5EwXkTMMN5xJ8nSvjk+jexdqqKmVUooop+bSer4BJJZudqrVHln+s14AM/M6/sF1Z8CEeBa3XM9TF9QwsCR6ZL9efPRL/u5zDAoW4+G9+ULvnJuVo+8+nBYoV6z9Aksh5wcnJ/57Fn2Ae3PH3PIRHPLSC7VgIw9EAumvrvlu82jWAd/Cj8QnaD/o27vfIT+HZ/7Ttw3f+J+g5
*/