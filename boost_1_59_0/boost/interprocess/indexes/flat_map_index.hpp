//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_FLAT_MAP_INDEX_HPP
#define BOOST_INTERPROCESS_FLAT_MAP_INDEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

// interprocess
#include <boost/interprocess/containers/flat_map.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
// intrusive/detail
#include <boost/intrusive/detail/minimal_pair_header.hpp>         //std::pair
#include <boost/intrusive/detail/minimal_less_equal_header.hpp>   //std::less


//!\file
//!Describes index adaptor of boost::map container, to use it
//!as name/shared memory index

//[flat_map_index
namespace boost { namespace interprocess {

#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!Helper class to define typedefs from IndexTraits
template <class MapConfig>
struct flat_map_index_aux
{
   typedef typename MapConfig::key_type            key_type;
   typedef typename MapConfig::mapped_type         mapped_type;
   typedef typename MapConfig::
      segment_manager_base                   segment_manager_base;
   typedef std::less<key_type>                     key_less;
   typedef std::pair<key_type, mapped_type>        value_type;
   typedef allocator<value_type
                    ,segment_manager_base>   allocator_type;
   typedef flat_map<key_type,  mapped_type,
                    key_less, allocator_type>      index_t;
};

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!Index type based in flat_map. Just derives from flat_map and
//!defines the interface needed by managed memory segments.
template <class MapConfig>
class flat_map_index
   //Derive class from flat_map specialization
   : public flat_map_index_aux<MapConfig>::index_t
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   typedef flat_map_index_aux<MapConfig>  index_aux;
   typedef typename index_aux::index_t    base_type;
   typedef typename index_aux::
      segment_manager_base          segment_manager_base;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructor. Takes a pointer to the segment manager. Can throw
   flat_map_index(segment_manager_base *segment_mngr)
      : base_type(typename index_aux::key_less(),
                  typename index_aux::allocator_type(segment_mngr))
   {}

   //!This reserves memory to optimize the insertion of n elements in the index
   void reserve(typename segment_manager_base::size_type n)
   {  base_type::reserve(n);  }

   //!This frees all unnecessary memory
   void shrink_to_fit()
   {  base_type::shrink_to_fit();   }
};

}}   //namespace boost { namespace interprocess
//]
#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_FLAT_MAP_INDEX_HPP

/* flat_map_index.hpp
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
*/