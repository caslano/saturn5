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
wumTRYcM2JuVPG5cWAKuOie35lMDu6yGT8DUAeKSf9y6i4PDykPLJKaePzEoMRvrnfQ2I+fTp4bG+uLiurKsHn5B8blLb92n/Lc62R+SmWOme+KnpLfpGZmfPtUX+9CWT5gwoa6Oj19cXOrWfcqbuxcusGNe7I1z1z99KvLet37hpAkTxmP2SXV1fF267eQic4uAioqQkACv586H5hvd0Nm6cOJ4HDAnJ5Q18NWPjh8/fTOkorq6IiTgucvh+cYxYuOpMGk6CbNnz55R0ov/jJZ2/OfqalZFSLCf647NVgYCnMrxYMyevRyHmfls/gFI1TaJ6+hoayb8LsvsNk2kuCdMIqwKJCz3aek1Se0umH1o6WgOxvw7txvTOewTZisc5ASlFQAdLOLTyi25Zb0KmDwN+uDp6ejx/NEjvZ95/DRFRUUlHI4oKbf0uQtSrz3xf1ZZ+dDl0XauNhMmLFfG4QgOvkcwP27w6FFDe8Jou2dp+TvlpKfy2Ccc9OWGAt8jjXV4jo4ezccvPPrTqslrF6ydyGGfMWHGkQJeKDxS35jch3/oqE+yk+Xk1nLZZ8yYWVBYUMgNvu9bsD46OjqtvIALNOydumHXgm7+2YXlFG95YXl5AY+/G8aJ+ZkpU3ftm8Zjn7GivDtUFZa3ZH/B35oydf8+Uj1RZuYvSlU9obywJTu3L39HylSVdd3ss3ybKNYmEqoKW3OzvuDP
*/