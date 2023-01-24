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
Gi07DMSH8n4A1ZnvLN/njP+Oep2n4e+k+Zfly41+1gDoOLWoWocsTGczEAKdpgUCak0Uhrz+5mscDUHnE898OEf5dS5JZ/lELXfNcE4BtFsBg0GD0XHCLM6I8z0DHXd14rvPfW04sMBD2kWqQIXT58iNRzvscz/Yx7fy55KGTwSERwRsVKBWZMq4AmczxWSmzIlBiaKVCtLUBE35q/0M0nrvZm0XLmDI0ShhCzq7isiX5IG/yqCkTvjVVvSKQn2opFXwTsxdzEsSDrT29P/UhG+kiVkFmKUJg15xvHxdfEwQBDke1cD1+lbnIY8ELKLRSsLRuvWsBf5L3A3D39p5nRiIt67fDQ9zcWnE06n5INg12jIwWzgFTV4/zNh+8ikaT1yhfyFksNNmcKlNoxchoxCdKkggJEMndgfdWUY2TUx8j1KWSAiCUNJuhXTaIcPjlJiU2lN8cm7u97OSZ+6Fnaju7nVNuu9mZF4VKEkfXr0llcRMXISNCswUaSpJYmW4f6JJU0WWCbI8ZNo6X62LtED4wi3oewmw+ye4tEUzWvvb+JSkX10iNtrKF4XdwS1vpuSJoPr6C9LcFFSW+yur/ztbgNYzwkCRZfXiv4PpdLpoK7CVIcAOiuXAVd1X4w3g6UWARcEL6+Q9Sb3nlRfA16d8ru/CWIs6jTX7KIapiDiWIUdTTdaANATi20we6vMX/+7H6XUlnXZIO7Sb
*/