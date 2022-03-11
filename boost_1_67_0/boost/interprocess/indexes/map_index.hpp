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