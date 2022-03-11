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