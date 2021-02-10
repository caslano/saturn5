// Copyright Sebastian Ramacher, 2007.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_PTR_SET_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_PTR_SET_HPP

#include <boost/ptr_container/detail/serialize_reversible_cont.hpp>
#include <boost/ptr_container/ptr_set.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class T, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_set<T, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

template<class Archive, class T, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_multiset<T, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_set.hpp
YXN0ZXIvdGVzdHMvbGlidGVzdC9saWI1NzMuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJOvW2zPgMAACYIAAAiAAkAAAAAAAEAAAAAAAiRQwBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjU3NC5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUq8v8JJWBAAAxQoAACIACQAAAAAAAQAAAAAAj5RDAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliNTc1LmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pShPfv/j8FAAD1DgAAIgAJAAAAAAABAAAAAAAumUMAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWI1NzYuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKevtdzKwUAAFsMAAAiAAkAAAAAAAEAAAAAALaeQwBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjU3OC5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUoT/MsvtBgAAohEAACIACQAAAAAAAQAAAAAAKqRDAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliNTc5LmNVVAUAAbZIJGBQSwECAAAKAAAA
*/