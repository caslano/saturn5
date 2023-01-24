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
iHBCOAgEuECkVEka2jeX7HVy/Tut0x6o0yZGtkFutfyqmLw8Gep3C9Svcoi8XAXF3cSWcgoAc/d50I8hTWXMU34W7ayeVotAn8lidvFpg3injwkn6LynCbXKFxkly2LkhmHsbbWIfd8sRsHsx16UTgmtjDDSEgM0M3CrQDfPUsLwsNMxeM2yS5g0FL1JCAk8k0WzmznIF4bmlrPccpbbynJb8cIs2lyxkn1rXQ5GDY0d+9JUchVsvSfPCgPAP5TIG5TFQCXXepN6gW+q/0igJNhlbA9NDm+PVEd3xuoL9sRrC58qKsNFRU24oKglbsSMiBEygvHiZOJgySeJ8mR16eqynvLJFZsra6ueqK6r2TO5vnZPXX1qX311nTHZqDYqjfLC0tr6JlwEKVnf1jCjcQpumFqaTPb5V3h11aeEgAbrQhI3oDohIBvAIGh+LRgytLAW1Qq0Qq2oJqGVaEmt1FemVWhVWo1Wq6W0Uq2+pkFr1Ip8nPa2A+2lNHQM0NAg8/Ew+d9nuE/ocgDWPmPuhSyuYqeU60aNQjPaLrDyUBbojr38AXv5Q5Ckm0iRuahJ4OtpHMzXyJD1NPAMX09fAuDdb/L4nXwnZCaeZNL1qlsxKsOGsF2aABEs7tMG4nOddO11WrPfhncKZNTTg4sPWYNL99vW4EpShq3BLroGfcK15IcD+7n8cAiA/v1Efhjqf2FZ76f8p0jEuwIh
*/