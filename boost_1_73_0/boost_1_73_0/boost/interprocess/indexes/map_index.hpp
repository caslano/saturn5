//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MAP_INDEX_HPP
#define BOOST_INTERPROCESS_MAP_INDEX_HPP

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
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/allocators/private_adaptive_pool.hpp>
#include <boost/intrusive/detail/minimal_pair_header.hpp>         //std::pair
#include <boost/intrusive/detail/minimal_less_equal_header.hpp>   //std::less

//!\file
//!Describes index adaptor of boost::map container, to use it
//!as name/shared memory index

namespace boost {
namespace interprocess {
namespace ipcdetail{

//!Helper class to define typedefs from IndexTraits
template <class MapConfig>
struct map_index_aux
{
   typedef typename MapConfig::key_type            key_type;
   typedef typename MapConfig::mapped_type         mapped_type;
   typedef std::less<key_type>                     key_less;
   typedef std::pair<const key_type, mapped_type>  value_type;

   typedef private_adaptive_pool
            <value_type,
               typename MapConfig::
         segment_manager_base>                     allocator_type;

   typedef boost::interprocess::map
      <key_type,  mapped_type,
       key_less, allocator_type>                   index_t;
};

}  //namespace ipcdetail {

//!Index type based in boost::interprocess::map. Just derives from boost::interprocess::map
//!and defines the interface needed by managed memory segments
template <class MapConfig>
class map_index
   //Derive class from map specialization
   : public ipcdetail::map_index_aux<MapConfig>::index_t
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   typedef ipcdetail::map_index_aux<MapConfig>  index_aux;
   typedef typename index_aux::index_t       base_type;
   typedef typename MapConfig::
      segment_manager_base          segment_manager_base;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructor. Takes a pointer to the
   //!segment manager. Can throw
   map_index(segment_manager_base *segment_mngr)
      : base_type(typename index_aux::key_less(),
                  segment_mngr){}

   //!This reserves memory to optimize the insertion of n
   //!elements in the index
   void reserve(typename segment_manager_base::size_type)
      {  /*Does nothing, map has not reserve or rehash*/  }

   //!This tries to free previously allocate
   //!unused memory.
   void shrink_to_fit()
   {  base_type::get_stored_allocator().deallocate_free_blocks(); }
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

//!Trait class to detect if an index is a node
//!index. This allows more efficient operations
//!when deallocating named objects.
template<class MapConfig>
struct is_node_index
   <boost::interprocess::map_index<MapConfig> >
{
   static const bool value = true;
};
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}}   //namespace boost { namespace interprocess {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_MAP_INDEX_HPP

/* map_index.hpp
YXN0ZXIvcHJvamVjdHMvV2luZG93cy9WQzEwL3NyYy9VVAUAAbZIJGBQSwMECgAAAAgALWdKUjBBnfMnAAAAMwAAADAACQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDMTAvc3JjLy5naXRpZ25vcmVVVAUAAbZIJGDT19LLS07i0tfSyy9IzStOSQMxYVRpPogqLU4tAtFlyRUFRflZXABQSwMECgAAAAgALWdKUj1pE2QBBQAAM0cAAC4ACQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDMTAvc3JjL2N1cmwuc2xuVVQFAAG2SCRgxZxNb9pAEIbPQeI/WPTSSjGyXUjJoQe+0kSiaVRL7ZkEE7lycWQgiZTmv9coEIK9Ox+74/jUYGbnfXbesVkvpt/jmyxdpvOV8yterqeJE67Wszh1wjRZr+J04ZzFSXTsnKXZ32keE2XLzUHfb3tes/GhMCjw/PzoVZb+iW5WH1tPvcHwdDge9NzeoNN3fX/kub2R77ue1/eGp37+bid4bn1yvjqtm3WWtI5f/m3f3zze5Uk2r5+6QdAb51ncfuCfuJ0gOHP73fGJ282PdsfBaPTFHz23mo3xYrYVbja+Jen1NGk2jl7+CPODOfXH3ZyG
*/