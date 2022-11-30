//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_UNORDERED_MAP_INDEX_HPP
#define BOOST_INTERPROCESS_UNORDERED_MAP_INDEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/intrusive/detail/minimal_pair_header.hpp>
#include <boost/unordered_map.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/allocators/private_adaptive_pool.hpp>

#include <boost/intrusive/detail/minimal_pair_header.hpp>         //std::pair
#include <boost/intrusive/detail/minimal_less_equal_header.hpp>   //std::less

//!\file
//!Describes index adaptor of boost::unordered_map container, to use it
//!as name/shared memory index

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

//!Helper class to define typedefs from
//!IndexTraits
template <class MapConfig>
struct unordered_map_index_aux
{
   typedef typename MapConfig::key_type            key_type;
   typedef typename MapConfig::mapped_type         mapped_type;
   typedef std::equal_to<key_type>                 key_equal;
   typedef std::pair<const key_type, mapped_type>  value_type;
   typedef private_adaptive_pool
            <value_type,
               typename MapConfig::
                  segment_manager_base>      allocator_type;
    struct hasher
    {
        typedef key_type argument_type;
        typedef std::size_t result_type;

        std::size_t operator()(const key_type &val) const
        {
            typedef typename key_type::char_type    char_type;
            const char_type *beg = ipcdetail::to_raw_pointer(val.mp_str),
                            *end = beg + val.m_len;
            return boost::hash_range(beg, end);
        }
    };
   typedef unordered_map<key_type,  mapped_type, hasher,
                         key_equal, allocator_type>      index_t;
};

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!Index type based in unordered_map. Just derives from unordered_map and
//!defines the interface needed by managed memory segments
template <class MapConfig>
class unordered_map_index
   //Derive class from unordered_map specialization
   : public unordered_map_index_aux<MapConfig>::index_t
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   typedef unordered_map_index_aux<MapConfig>   index_aux;
   typedef typename index_aux::index_t          base_type;
   typedef typename
      MapConfig::segment_manager_base     segment_manager_base;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructor. Takes a pointer to the
   //!segment manager. Can throw
   unordered_map_index(segment_manager_base *segment_mngr)
      : base_type(0,
                  typename index_aux::hasher(),
                  typename index_aux::key_equal(),
                  segment_mngr){}

   //!This reserves memory to optimize the insertion of n
   //!elements in the index
   void reserve(typename segment_manager_base::size_type n)
   {  base_type::rehash(n);  }

   //!This tries to free previously allocate
   //!unused memory.
   void shrink_to_fit()
   {  base_type::rehash(base_type::size()); }
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

//!Trait class to detect if an index is a node
//!index. This allows more efficient operations
//!when deallocating named objects.
template<class MapConfig>
struct is_node_index
   <boost::interprocess::unordered_map_index<MapConfig> >
{
   static const bool value = true;
};
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}}   //namespace boost { namespace interprocess {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_UNORDERED_MAP_INDEX_HPP

/* unordered_map_index.hpp
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
*/