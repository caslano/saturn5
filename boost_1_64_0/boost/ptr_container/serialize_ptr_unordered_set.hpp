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
CJlhh+kaAjSBDFW1RUuy14Htx9ivHfowY8lP62S+x6s2JRbip+67zoupHqsS9fJuLEJjzUrGQinimbrGelNdZmyKiad0eWWu1H1jabr2qyqywuZsfz0eoPXQc0jIjrX1KP+l4zZheZCvcwM07x54oHqPwd6eNo1yZp8sv04imxRqp7xQCVpdRAZoCHcuE87Dd+DiqtfFkB24dZF/Gvd/aQco3nnXDEjR796cj2w/MCgO2jHe52qJhochNZyR2b/4I7XBBXn8i3ffhBD+lawLT193u3W+twyV+tdVoDWqLYCTU9ztIRxZPGfLcpfF276YRKXTeQh20Z1wyoUACh15m3+JihXDkiwrcL/zSD52iILHCOawewFNsibzvh0AemnSF2bFt1FmGc+fGM+fyIOYVdULhD8ctvLwcV5r3ffKTLLEDkL44Q5B8N6rTawoPXEAE8waMSf8NKmXOLra3YT621G5YYEb4TweVctqyN+RzDbeZrAghee+XmYqDgZK/2Ohf3rjD/9VYPBQe33m8jeacuViFmrk+HTXjUPHai6DXog7wxaRt1RmVYMwvw==
*/