//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_MAP_HPP
#define BOOST_CONTAINER_PMR_MAP_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/map.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class Key
         ,class T
         ,class Compare  = std::less<Key>
         ,class Options = void >
using map = boost::container::map<Key, T, Compare, polymorphic_allocator<std::pair<const Key, T> >, Options>;

template <class Key
         ,class T
         ,class Compare  = std::less<Key>
         ,class Options = void >
using multimap = boost::container::multimap<Key, T, Compare, polymorphic_allocator<std::pair<const Key, T> >, Options>;

#endif

//! A portable metafunction to obtain a map
//! that uses a polymorphic allocator
template <class Key
         ,class T
         ,class Compare  = std::less<Key>
         ,class Options = void >
struct map_of
{
   typedef boost::container::map<Key, T, Compare, polymorphic_allocator<std::pair<const Key, T> >, Options> type;
};

//! A portable metafunction to obtain a multimap
//! that uses a polymorphic allocator
template <class Key
         ,class T
         ,class Compare  = std::less<Key>
         ,class Options = void >
struct multimap_of
{
   typedef boost::container::multimap<Key, T, Compare, polymorphic_allocator<std::pair<const Key, T> >, Options> type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_MAP_HPP

/* map.hpp
G/5cvYnkMy0L7duVt8VQPzyXBW8xsm/7l8rWGmUCFOj2MD46PBJoUxQ+uFE6033L98HjSueTdQWFjVUhIz43iRv1BEWjBs1Ubzpp/gMFswdsD0OvUrWCCGxZvTHJaLciLGBL40R/3yBT+onBm14EY34hwk1k1XgyPjvRNSyaeYBm46cLMOG/ho1kec6AcZgC9oLSzPfixbJtsNeiYPgu0AIk/EAwhuVB/A5c46flg3Bakm7kmUwEK2579UBMbsv62ci7JiUIePYQ/IlD2QQxXKssgUXzQDOCOndBY/+3klAvorEGUBujohW/PyqAv+BPaEznoH08QqZ5xjzOhZjG2KxgZ/+0TpTpeFqmuQzLvtEPzshHF96zeBSdNsDJoMkx0jLarXU0VY5kCFilYoxeQymsn13dzwXehqWx0z29Ncp4g1CJKey2PT2OEmJtCXaJnnPzEdQbBEPE4qw8obYjER1QBqJ58r8y/HnpH1TMFmn6uGK0SmjUYid6ZDPBCh5dxy+VPI/coMeldJhhUb9xHix19AgVc3cm1zONlBuVnRa6Pi4xSDKZkJteOA==
*/