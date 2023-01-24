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
Xfaw3YtRIW+Qt00K4teq/F5O3qAwfjldrf+gDuD1dfZ2CeQG4Y/8LIsVZyaobXAaT7t+ELvgXRnlstaw5ICibXI6X8DKOi9cv4C0vAUadbUr9A9QfubIVfxUcDQ7ujjWM+9btFDyjCk5gp2cA2wMl7k6U8zSrxl9ktLc4JxR3yv+mkNNjIrn1LHV7RG51ecU1tn92tSvj5aFPHZ5Mu1cVtBCpHlZW2FP7IenRjugaXCFOA6lXZvNmSkKG3tG+LxARpjQezu6CGK2FTRDz3Lms8m2H7XrwjockJHZ0da5sTEKmOykWJSNe6/PWhXrQ0TBMzK6YQqE34ur3owq9YZwKeXFYp73QzRbH9/J0JeA9aIjBZDkwlyh2exTriV0VA55QytgIZBP5KxBjRDXsnTyiBthK6c9mC5aiW9i3d2InFYTS+lqVBOuWtf+HNVBipxuKKpwKrWR+oCvRD40Wzh3JBzqPlzc/MqVHEwAxBO/WMWlYHUQ6sGaeFjQRwtUNv1e8jqJ//NrPB+XXOdfAstDC2BviW7Mg6JGK2AIw3zftWjIEU0q9exBEWi8A3f/AMz9+Km2QfZYGtMm09JTN61cCckx1o1wm4w9YfZsOcJsftP4v2evY5bD+p4Drk/URoAqFfAw70NAzxjphMTSMb74EUTXDyCEkL9VH4DabNuE6ZFv/QsUrYqMlxwTlnmUHfcG5ajRBuwLoAdcPGux
*/