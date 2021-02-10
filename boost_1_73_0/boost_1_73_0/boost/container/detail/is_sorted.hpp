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
Eg3/aqk0diTPzcRhD1DiGCumdEtEE4xBIIdbRlebmw7Tedy8Lo0lDlhNbvRUYkcm0yiJRtE4tjx9X+CJ/4d3ORn7llsVllHryXc6YBVTA2wmKwb6cA/+tmDTNdODj/i+NZdUoaCNaaeWaJKkuOC1gc7aFgu0A4AXUSGaZRddGyCSdvTT6AJOTrR9B/rYdZPmFu1/tfmL4WriP4UAUDeozmJgJ9idD/Cze1DYDnzv/M3qfkO8/PmKrCVknJKqrWF/uFOK/niT2DfLLZipt/fFC8be52AcJDPLM73GJr5zj9xD8x3FeDUN4Ys3vvKtKVV4B0t4IMy667a7NrRaZFvXolFaVlqwneFVeBFG12EamdHTTpVQnQDs2PfBG8cRXjmfp4/LCTbqxgH7UVcfPjxR6TQxVrb1D1BLAwQKAAAACAAtZ0pSHetTKl8EAADPCQAAPQAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxJTkZPX1NUQVJUVFJBTlNGRVJfVElNRV9ULjNVVAUAAbZIJGCtVW1vm0gQ/s6vGHHKyY4oTlqp12uT6qhjX1AcsAxpzpIltIYl7N2apewSx7r0v9/sguO4OSX5UCJnYZiZZ16eGdyFDYc/7bJc7Q5evBLzS/DC
*/