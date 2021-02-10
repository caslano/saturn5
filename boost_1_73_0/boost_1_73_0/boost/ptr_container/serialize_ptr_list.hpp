// Copyright Sebastian Ramacher, 2007.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_PTR_LIST_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_PTR_LIST_HPP

#include <boost/ptr_container/detail/serialize_reversible_cont.hpp>
#include <boost/ptr_container/ptr_list.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class T, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_list<T, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_list.hpp
dXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjU1OS5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUrLtjHN1BQAAuAwAACIACQAAAAAAAQAAAAAAlllDAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliNTYwLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSKdIQHLEDAAADCAAAIgAJAAAAAAABAAAAAABUX0MAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWI1NjIuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJIhGS5DwQAAPEIAAAiAAkAAAAAAAEAAAAAAE5jQwBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjU2NC5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUgTtOuJOAwAAfwcAACIACQAAAAAAAQAAAAAApmdDAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliNTY2LmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS/BEWjZYDAACRCAAAIgAJAAAAAAABAAAAAAA9a0MAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWI1NjcuY1VUBQABtkgkYFBLAQIA
*/