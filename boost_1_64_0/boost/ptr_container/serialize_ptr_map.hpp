// Copyright Sebastian Ramacher, 2007.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_PTR_MAP_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_PTR_MAP_HPP

#include <boost/ptr_container/detail/serialize_ptr_map_adapter.hpp>
#include <boost/ptr_container/ptr_map.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class Key, class T, class Compare, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_map<Key, T, Compare, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

template<class Archive, class Key, class T, class Compare, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_multimap<Key, T, Compare, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_map.hpp
97jWzZpucPLk6M7+4m4DDeecKEHcM8+6iiQYGt1R5QT9B/4NmATu+UajgU5mdyCDAXGlYPQ1NQu8n/6fY+IDyFji52vXqG9sfzSi2/dEdzeJejRERhr+AooTl+GHBAtaHHOBS15Y9Wk1VRNT0bDXZGRlE0IbPIMm7+1g+8Pl/zxfRDh4UESgDiFTWG9zHmmzRgXl/qqeW3m5UurRWP28Q9stMwMEP4EXtpF4wSJUU8X+3jWtLticrch0HOr76or4eFsI0Q85EA7Jdk7CIsM6QzCRnxS3yU6q4paJQ81OenNEN+xrr1xKpOf8Y9GrrmoHNV6jYrgcp2kf8YVG0GBO/7HB9UEBal4PaxUGf8BR4tIMlUjzUyU7gET17ROK6SDSBTXZItzbL0euD75i1q4YVVLGKvtOMEpMDh6WVx6HA2U/xs1HGgn2fdOqlGPJTGnhIVg3GhcAcPqLx2hIh3eD3CP+8t4XEm5fuNdoCEDYF+WFa1cobprrnPO4zg2/PZQRQQzXcoSH35H9DS0LAqI8B6OgAXudoPCv6ewQ1a8rtEKbOx5TPONBal/Cfw==
*/