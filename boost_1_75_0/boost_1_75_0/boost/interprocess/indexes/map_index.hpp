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
tFfGwBDfdPBG1h9HEl9S4qdriLY+JlOHbPFDPSNFu9pszOL5A4blekAcmtIRYorS2zN/LnecI6WZ9tiLuflgyGhc6+5nXXi7cmGUhrtmVwBJPg5aLzHIVCV/s/In4IQw9r3qJBefj/cGRy9htlpngYR969O0O0i+VEHdXRZ3Hkg+lqeaVAaPIq+BfEQzlXWMkk0qgn8lf6xKzp3SKp6mZ/UpGHCXZdEuyM4lsNDnRR0bKI8r/HMzG07OxBeW08hpScSVBFCueoXur9NL0qQcDafM4Jc7YjONZb7wwVIlev0KGk5Ii+YR50oAgogXi9l6gtstwRf1Q1vvAx5jmh6kr6DZen5PrjwOUak2hcbX6p196DYkFHY1iXuxvAJ80Po2JbAFkX+dnl0pn1Ksr5KY0q/H4YS7bvJ5v8CSSevZbvOjTL4yHOwD2oUG7SIeQ2ZkN9KabMvmIuzU6is0iuEqIG3MTpraBaphHyqaxzFRgoE1kPr9oI8Rsal+/o3Wo6GETjZGJkA2jy51EZFkZceTY7Ur7pK1ScJJ5Eb1e4HOInmRehU2cNKXeB6usJZjXliD/zqmfQBhdvu1825nZ+oXv8jkRIT90liA8Ccaa3UaCVBbI86mTsdbv+VeKskM41fD8UfoY9gWbGfVE/DZ+v5WXybuLuEaUk88mQLOD4tfrbO9/cKMbd6c+zHAt6Bkxs5e4OfgXNtiLpM31TMD
*/