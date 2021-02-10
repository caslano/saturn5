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

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_PTR_UNORDERED_SET_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_PTR_UNORDERED_SET_HPP

#include <boost/ptr_container/detail/serialize_reversible_cont.hpp>
#include <boost/ptr_container/ptr_unordered_set.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class T, class Hash, class Pred, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_unordered_set<T, Hash, Pred, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

template<class Archive, class T, class Hash, class Pred, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_unordered_multiset<T, Hash, Pred, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_unordered_set.hpp
L3Rlc3RzL2xpYnRlc3QvbGliNTkxLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pScMhOGi4FAABNDAAAIgAJAAAAAAABAAAAAADN0UMAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWI1OTcuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLnGwRiPwMAAHgIAAAiAAkAAAAAAAEAAAAAAETXQwBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjU5OC5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUmsJe+qfBAAA5woAACIACQAAAAAAAQAAAAAAzNpDAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliNTk5LmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pStIuvl5oIAADxHgAAIgAJAAAAAAABAAAAAAC030MAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWI2NDMuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJJYXJHoQgAAGYaAAAiAAkAAAAAAAEAAAAAAJfoQwBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjY1MC5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdK
*/