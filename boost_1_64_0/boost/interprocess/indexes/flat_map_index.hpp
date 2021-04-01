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
p1f5fyzV3WWsPFkDhgp+gPbteWSyTurgM1syqYcqx/hr9vl4Gwwzt3JcMRfgGgcZjqb9u5L/HQOxQ70thZS8lLrc9W/D5BvtaxDzHh3ktKQeoy4mxCw1LWgxLjnjayObadebJnR3H31x6b5p5SShGWj9lVKdUXkwgz1wDUFR+B0AGMhJbc+vcUtr3GucqLodFIGDHVdmxI+Poy0528/spg9DTawgYrteiJT1pRrQomOFdIqUb+XbUmV/s8Ib/8nxhD/Q5wSNMjR0k7Oh0tJX8zmVnhmdnHZ00lg4wUAVl1UnBLMkMgtkEGhl/raqX66AG/8QBwZOr7XMPhBjb4R+FyWgfKoLqc4FpeR/lQraqSzr3gPX9QCm06aFjR2Pa9xXuXSucSxQgh2DkVaiZDBf/SaWISHNc5r3AK+Roo2d/z5d0fxE3/CVsBn3fjeyHJjOcWylJ1luLiCZ7aFnA1nNeUgCQ3bWbyt3BU08URptM+6OdMwdvEJTeFb3Bqw51GpZdb/zBUG5YbqbTQwNIHvuupJliUoV64LpvyUDow1cfpAWwX3czvagLuZEXw==
*/