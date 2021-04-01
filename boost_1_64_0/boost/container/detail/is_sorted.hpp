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
jIT2BZUtPjo9Me1xCplg2BQO6Kjc90IAsM4Nz+KzfkB1ZXnHtkZO5YCbCMg+3wz8iKiOKZcEu2ANspSNaRSn5+qndFCOyopTfJ8a/2wlEn9IizwP+lEqxDbz9gyZvgaOykyS6LpMop1aZOMV5MLllaL0wZKV9WiwVXgu22w/oQfMQu5RUylZ24fg5xwks8Pcceyyg1A4vAeLwsH2Ekg9s0exLdfqKPZPPGw9n2GHaUeu6QB0O25xI65SRJzQudu0/leRXdkmLTCE9myRrfao2Aub+ti4qlCr12dRq2WDejIG+3RkjtUDc8Sustlr2zGOiXtRhStH7wnrYkB65MaT0rNFtcuSo9mBZU8C33wwGDDpRnasamcSx2UV1D7EJOCOZDEhSsjxUcWsjYWHUPf7+hcKOJmlBwUssc+lP4tmrg9FTxsnm+xOodGJQUJnCZCjt8dhDSIENEtp8n3PYfd2uP7DBRT8g/bbUY/DJCJdEnbIAduEZeoQscHub5ojszwVZ5JpcRKwI4USLEh2WcXeZ2QZnNvZG96BBd4epNrgyGnQFuql7XNpPGkA2g==
*/