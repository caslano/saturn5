//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_FLAT_MAP_HPP
#define BOOST_CONTAINER_PMR_FLAT_MAP_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/flat_map.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class Key
         ,class T
         ,class Compare  = std::less<Key > >
using flat_map = boost::container::flat_map<Key, T, Compare, polymorphic_allocator<std::pair<Key, T> > >;

template <class Key
         ,class T
         ,class Compare  = std::less<Key> >
using flat_multimap = boost::container::flat_multimap<Key, T, Compare, polymorphic_allocator<std::pair<Key, T> > >;

#endif

//! A portable metafunction to obtain a flat_map
//! that uses a polymorphic allocator
template <class Key
         ,class T
         ,class Compare  = std::less<Key> >
struct flat_map_of
{
   typedef boost::container::flat_map<Key, T, Compare, polymorphic_allocator<std::pair<Key, T> > > type;
};

//! A portable metafunction to obtain a flat_multimap
//! that uses a polymorphic allocator
template <class Key
         ,class T
         ,class Compare  = std::less<Key> >
struct flat_multimap_of
{
   typedef boost::container::flat_multimap<Key, T, Compare, polymorphic_allocator<std::pair<Key, T> > > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_FLAT_MAP_HPP

/* flat_map.hpp
GuLOe5OPE0sTPnfJ/1VvynB4cECz0XCVWG5nPtZ0OmY0bqJ1iJQQBBIpBQK3nXMhaWmhERgu2GqG9HshnbZgMlVkaQY6NQgpQpARaGlX3vncV3hI6okuOXLX+farer5nUs9dgu79K1gmfH4tPKnBb0+aQy1UYJcHC7tHoGJqDw01E9+8v6lKgxLz7rMasX2uyaqWQrnbtW69Sr0lLcQbpjrD4Vydfn1VVUIXBMCdC5jHANhlwCpLicQUKSRZVj7xx80rKSXD4XDRMuCMFUuBYdGWYP6vBrVIvlkC54Ws7xrSlxJqri0SLar26Ogod8NU9bXpNGY6a4BF7EBKc2SYqEg7GtAij/6LIkG3E9FphxyNEmK3TBgFOjEsQwjQgRXFA0MMnDGwqJRioY6HSSUpwJdofEyqXruyulLWSQJ+XIC7Brd7kNaaTJkNQsx5AcYekCSazHoCpNZWcDDteiShaH6RKuDEds8uUA1xWAjadLeq9pW0ItdOTX11KoaqSfPzlzwB9rzEVAE6oRWVvWB1RMDFAIThnDA/WnQYiA9eHIA3Cb0ByXu6JpzZAl/zsiet46z55nCHemOgD6Ph0FBl72trQErBeJJyPDYnAQkpczuAIyimKwqUsR+4GRcEJjR40G9wNIyZTBRZQnkSOw7sCEOWGAIgQqNsC+cjczp+UN59ozTD7V+dSy/n9HWeBAeFv39eupAgzApHrQVZ
*/