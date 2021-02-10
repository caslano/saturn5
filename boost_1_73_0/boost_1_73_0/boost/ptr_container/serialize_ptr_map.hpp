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
AAoAAAAIAC1nSlIl7AWfiwUAAGASAAAiAAkAAAAAAAEAAAAAABxvQwBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjU2OC5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUqM0D+gIBQAAEQ4AACIACQAAAAAAAQAAAAAA8HRDAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliNTY5LmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS92YEtDcEAADcDAAAIgAJAAAAAAABAAAAAABBekMAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWI1NzAuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIJdAHUDgcAAIkWAAAiAAkAAAAAAAEAAAAAAMF+QwBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjU3MS5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUlTFgKd5BQAAhBIAACIACQAAAAAAAQAAAAAAGIZDAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliNTcyLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSnGDpw+UEAABPCwAAIgAJAAAAAAABAAAAAADai0MAY3VybC1t
*/