// Copyright Sebastian Ramacher, 2007.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_PTR_VECTOR_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_PTR_VECTOR_HPP

#include <boost/ptr_container/detail/serialize_reversible_cont.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class T, class CloneAllocator, class Allocator>
void load(Archive& ar, ptr_vector<T, CloneAllocator, Allocator>& c, unsigned int /*version*/)
{
    typedef ptr_vector<T, CloneAllocator, Allocator> container_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::size_type size_type;
    
    size_type n;
    ar >> boost::serialization::make_nvp( ptr_container_detail::count(), n );
    c.reserve(n);
    
    ptr_container_detail::load_helper(ar, c, n);
}

template<class Archive, class T, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_vector<T, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_vector.hpp
O4wzJi6XUv9vTBy5kCImLvjqFb8D2iVjWXVUO6W0S5usRy5Jg4gjxiBEE0pEz/Kh+hN5aTQJQRpNvq8qMlP/J80W8Yd2jMAQmGHbzM/zNJeP9SkRTphUCwxjhGDEvz+8vksMRQvxlurc6xIDZxI1SjOlX0DQRVP6gxIG5BN4pYL1oW3M8UE3YUFmG631yisDobipL4KwlOJ2dUn+/GPQ1tTGqyNXhsDWqK9OLg7DVea16tQxqAG3i1o359hE+PD7siAs5cPrhpwZ20tOXc6rtzjU/+oJsxBpS650fxJDqca2InRMU+pU4yapYUNqoE40voF0IonxFlfkD5eHHr3fE3Vkugg9+qotm7K+w0xBdRPCJY05zzQU/PoBcdW71AmKfdzOW3vnjc916MvHC4xG10Xty3e6ux9bBZM76TIIktjdsBG88sQSVhAXj4bA1Gf1a1B8GQsVFY/ZaOQakRUw3i3eti2dBRk3jUaT6lsXmTT6v7U+u+igIDou8Wlnrv7xCd52LhM9qT7hbSdNW/y3HawDvP0L4VpQV6LOvkkSEnhDo60Yw8uRB1ie9r9HnUoPDY9cgp50qGBW7rEi1r8+xctRrb8aO4Z9ot/RXmAEPTAqmoEQJugxdzOgJJ/S10ChI6EiU3w15Ho7dESjbRAuceAoUXByWRpUZ1fcIDCBOjMrt6kwgDXhvHkayJki9A6cP8u6tUAi6IcjXBNS
*/