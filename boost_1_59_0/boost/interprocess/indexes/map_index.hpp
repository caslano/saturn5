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
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
*/