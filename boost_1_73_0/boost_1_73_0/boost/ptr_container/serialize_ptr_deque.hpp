// Copyright Sebastian Ramacher, 2007.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_PTR_DEQUE_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_PTR_DEQUE_HPP

#include <boost/ptr_container/detail/serialize_reversible_cont.hpp>
#include <boost/ptr_container/ptr_deque.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class T, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_deque<T, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_deque.hpp
UEsBAgAACgAAAAgALWdKUmqVxE8OCAAAtxoAACIACQAAAAAAAQAAAAAAZhlDAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliNTU0LmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSTZRTpSkHAACTEQAAIgAJAAAAAAABAAAAAAC9IUMAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWI1NTUuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLf+vSzNAUAAK4LAAAiAAkAAAAAAAEAAAAAAC8pQwBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjU1Ni5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUvHCuX0LJAAANkMBACIACQAAAAAAAQAAAAAArC5DAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliNTU3LmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSpjvQDR8DAAB3BgAAIgAJAAAAAAABAAAAAAAAU0MAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWI1NTguY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKufKUO5QIAAKcGAAAiAAkAAAAAAAEAAAAAAGhWQwBj
*/