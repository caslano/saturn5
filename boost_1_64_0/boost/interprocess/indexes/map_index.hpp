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
nAh8F3gZ8CQwE/gOcBaZc3pNvv+b2grp/zCRXm4fT4NPpP8jYBrwLHAU8GNgBvATYBYwFAN0LzDclPUjGdgI7Ae8A9gfeDdwEPAh4BDgI8BI4B6gG/g00AP8BTAaeBjYFXgEGGPK+hILfAMYB3wb2AP4d6ALaJqop8Bw4AhgF+BIYDfgKGBv4BhgH+AAYCpwIHA4sBNwFLALcAwwHjgB2B14GTAdmAkcB5wOHA+cB5wAzANOBK4EZgHXAacD7wTOAN4FnAW8BzgZ+E3gFOB+4FSRXrKX8ij33VMNnM/y7kj1Vv7BDyp/95my3u0AJgN3mlI+94v483c6fUv5PwC8HPggMAe4i8Nr9N19DPwChyf8rePwKkNl+VoF7ACsAgr7NcAugg9I42TgIGADcDTw2lAZj+uAc5m/ALgaWAG8BuglcxWPZo5HrSYeizgeizkeV3I8yjkeRRyPYo5HGcdjGcdjOTCH+RcDS4ArgaXAGjaXb1fzHbTcJh1r8Xb1DeAT2AiMBK7neNwI7AzcABxI36pdPsD+fU3TLt8Mvt7A24D9gJuBVwHvBK4GbmF/0qy7RFEn2J9QUH9fO2DKeL0JjAa+Zar2Yw+7m6hpP64xZb6uAcZTvZfxvx6Yyt/D+XsscB1wAvAGU7WXBt/Rt81wtpcbwOcBbgQK81vY/03s/91cbm8DZgBvN2X7tNmUcvoisBh4B3A184kwtwK/BLyL2xX4w/nE90Oy3ApCbPlE/R2N+4BhwCJDuTvC7i6h9svubm2kdHc9cACwEcj5iwRLdw9o8ncb5NcDuAO4ALgLuAT4EHAp8GFgLXA3cK3wA9gIfITlfkQQ+38pt8/xoIPs//fY/z3AXsC9wKHAR4EjgS8CpwEf4/q3j8P9CbAU+ARwOfBx4Ar+vh/4FPC7IpxQ2S4/A3wG+Avgc8BfAY8CnwWKOD0H/LOIK/A0hxuK+D4P7AY8CkwyhbmqZzlRXC419ewlru/HgdHAV4GDgW8DhwDfAE6gb+nfbuseMbRx7F9X0Hb27xCX82eBbuBhrievAQXfc8CewN9w+TzC7ehvgeOBR4HZIl3AEuDvgdeIeAGvZ3/WiXC5v3sJuA34MvA+4CvAB4hPxrfJ4HuhgNUs1+4iHI7v2yHIP+DJECnXd0Nk+t8LkXL9EzAd+GfgPOBfgYuAfwmR8moGHmJz4effgH8ChnJ+uYDvAz8IkXL6EBgBPAvsZEr7zsBP8J0C/BQ4CmjAfA7QBJaY0r9y5l8JfAd8VfTN41qT7+8RZYvT2R80lMcXkeDrCIwBXgaMBWYB40Q4wHjgFcAErjfdudz24HY7CdgA7AXcCuwbKtuDfqEy3/sDvwEcCPwWMAX4E+Bg4K+BQ4C/E/EBvgEcDjwJTAOe4u+/0LfMrwnAPqbkHw6cBBwNnAzMAE4BzgdOBxYAZwOLgJcD64HZwLXAOcANwPnAHWz/Q+AM4I+BC4A8zuW7Q9CGaMa5g0NkuzQEOFWkAzgDmAqcLeIPvBw4DHgffat2OyOOy5+m3U4PkeOMccBI4HigsJ8A7ArMBsYApwBTgFO5fE4DjmbzccBZwAnAy4E57G4+MBO4gr5lfPaAjnB8buX4dAPtAlEXw+nsDJwC7MLpjOJ09ud0RgMXALsCC4QfwMXAWODVwHhgMTABWAHsDqwEJgJrgT2Aq4FJwOuAycA1wD7ADcB+wE0yPG7/+Xw2cKWm/X82RLY7v+N6/DxwGPAocATwBeB04Mucnt9zvuCb56987pjqknP+upv71x9wP/pD7qf3AqcCHwU+wvZPAfcBXwD+GPg68CfAE8D9wDNkL8fPTwDdwCeBUcADwK6m9G8k8EfAMWSu8mFndx4=
*/