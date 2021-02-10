//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_UNORDERED_PTR_MAP_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_UNORDERED_PTR_MAP_HPP

#include <boost/ptr_container/detail/serialize_ptr_map_adapter.hpp>
#include <boost/ptr_container/ptr_unordered_map.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class Key, class T, class Hash, class Pred, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_unordered_map<Key, T, Hash, Pred, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

template<class Archive, class Key, class T, class Hash, class Pred, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_unordered_multimap<Key, T, Hash, Pred, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_unordered_map.hpp
CAAtZ0pSiuW6VyEMAACNJAAAIgAJAAAAAAABAAAAAABgq0MAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWI1ODIuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJEsOh+NQQAACYKAAAiAAkAAAAAAAEAAAAAAMq3QwBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjU4My5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUixD7WURBwAAAhgAACIACQAAAAAAAQAAAAAASLxDAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliNTg2LmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSf79vQK4DAACkCAAAIgAJAAAAAAABAAAAAACiw0MAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWI1ODkuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlItlk+ZzwMAAMgIAAAiAAkAAAAAAAEAAAAAAJnHQwBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjU5MC5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUssDMfXTBQAABw4AACIACQAAAAAAAQAAAAAAsctDAGN1cmwtbWFzdGVy
*/