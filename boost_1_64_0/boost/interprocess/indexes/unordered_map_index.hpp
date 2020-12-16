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
DLh9Mvjw+wjsHsHvU8AzMHfdijTgOwV4GujKQJxBQ0HZoByYlwIT8lFG4L5O2OXDHLQRv7eCyoWd+A3eo6BToP34bsyHGSjmNsRB+AfcDz9O4/demC8V5sAtwLNA1xTkwQKkD7QUtAl0BPy7gcmwO4nfacBD+G4CnQUdgNsMmMUshJxAlfi9BNgI2gk6AftGmG0Dnd0HfpgdA+2fAgSdAaXdjrI2NQQNNOKI31GiAQPuAiXAbD9wFDAJPENBGaB8UBPMC2DeANoO2gcqhfkx4CbgNtA+0CHQKZhFbkb9wu8UYGQBEOHk4Hd//K4DbgZl43claI/4Bh4VvNPAAxoF2gmzTGDCFxE2MA14CGb5wAbQRPh5At/b8NsL+0bQFtAefO8EHgPmgMdYhPzA7wMwK8d38h2ID8wygTOBS0FHYFeH70b83g5qwvcj+F4L/l2gg6CToKifIG6gJaC1oJ2gg6AToMjH4S9oJqgUtBG0C3QQdAIUtR95CpoJKgc1graD9oOOgU6Dop4ADygbVAraBNoNOgg6DjoDivopwgHNBHlB20EHQSdAnieRT6B8UANoJ+gg6BQo6gDyDFQK2gLaDToIOg46DYr6GcIGXfy7+Hfx7+Lfxb+Lfxf/Lv6JP3qTxzDlPRvjl1R7cWtmdX1NSZn8WVuZWlwP5fLUS4ddOixtWerq2hFpl4617BrSx6TWluPkb2lqDe5jwwXlPo6Smmu9ddVLxEM0q0cuWT2ysK6ydtmw6mKx9j5evLqZLPYBu0E36PEiw8I5FSU11bXVy+qSU3IHJYtHLVdVXIf3oZKn4YBxRWVZDdZgPdGn4rD/kBdmYDSUnVc4PWtK/oLcrMKKurJVhXV1/Dbmn8EjFpZDDQRcuKysqK6+pqywrriS9umzo8uiDet+oW2m4Xg31xWPtYJPo8W5Db9A6FwXnQX4areAZzjZnTrTtawdb0DDX8c9kB4autnfET0Dvp3O+FVQ+tt4hzcO+fOxuEMuX+QhPUIKh/Y7l+o4zM4SSJcpAnlyxBEmnTa30ro8iLT6p+2Qi/WSQOGMboST9jGFUzFidaFfWPLMzM3d2r7bSbo3kVaWlX85MNTd16OJ7zqjUHtWRvnT1bqrpKwB5w3wvqfi81h86r5D3fs944hntbEYOaDOVK2w7s9cTPZ5KOPdbfc8ybLJ9xoTz1Lcyxdh3fk2ncw6UBxlGUZaEc2KUnUWZwHxzIJs+tKbug0h8n60crrP1/SYYeKVmQ4ztHf5Mn8m+CvofZm4Fm/LqHflVsB+JeiSIO5p850lgTzV3VHqLImsC3a58VkSvq9FycJ29j49TNUTQi67zbLs1q60XRdm3VB0zvcTndCE1yVeSs0ZnrojpVN8q2fe8Xfud6TAb+0dKcfDnXGNAW+UPq7qjhSqR63Fl/3guhIaxBn9KOPcz+h/VXNHCsIMeD/RoQhnuuPi4as23XQbQ1Bplu5Nrq+t3sUA3nO/iwHxcNzFgPC094Xsi3SmNVq0qfq08n0wwZXJNCP4+2DSjHO/D6ZTfNv3wfhkWyo2cnT3gxnneT/YedQ/dceSPa45HYnZcXdUjnF+d0fltEMuOechl2DujvL17ck8ePiCKXXAVwHjxRhC9u2rR1ScW99O7jmtPyT+kjptWu283H9XIVdV/9/hE2G/D3VznfOsq3LPbQH3rcsM6125N8m+0AzUX9/xCdnjXE6i9R5AMpkl4j2A27CvXu4YK8SJ/oN4Us3vG2H2sQKPJdLJ/h6c41ms7i4X/SGlzpBhAYcT34eIwVjooiVaY4ZLqC+M8XdbVUpNiRoz1JDbr4g21Xb/dj/KBxGQysdBxBtjrjN66cchHO+VxHcE51Y=
*/