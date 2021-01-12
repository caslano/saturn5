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
LXdpbmRvd3MvQlVJTERfSU5GTwoAIAAAAAAAAQAYAKt8ZDUm6dYBDul5NSbp1gGrfGQ1JunWAVBLAQI/ABQAAAAIAEmoLFLlMe+yRgEAAIsDAAAYACQAAAAAAAAAIAAAAGVYDQBjdXJsX3g4Ni13aW5kb3dzL0NPTlRST0wKACAAAAAAAAEAGADtxHI1JunWAVI8mzUm6dYB7cRyNSbp1gFQSwECPwAUAAAAAABJqCxSAAAA
*/