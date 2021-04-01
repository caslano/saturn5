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
RE/tdPOZVu82C/Uzc3ah74O7yRdeAKgQa5j4R4lruCS61Tu1jS//n7NP9j6/5rmRNEXvZqd9P5iN/PUP1HT5szymX+bkQqgKi/cPCWQY/sIVxj2qdy8Td4sC5EfD+HotwVdioeMvST6yAdzojaYqLgA1YoN8S7+kGAYvlAMGK6Nrne8+i+mA38ztMvgI82IZMhZ+HOTi87RCt1EkUt7tUWN6lSISMeaLlBgTkwxWq1SHGdWz1qSYHTctU+LBW3OXYk7n5dctmemV35nqKJbZlpaYMfPTJJ+U+vgVrfxltkyTnpQIsdjL+cf9nrgeaW8XRDZWEGk7IHaZLMlq+EFvmk2J6sMfsfeduEg5Zt1cUTMmY2oQgEoihq2bh1jkFv8ezOZrG0gFResA4JGWtN3J7fFfJ0yrDgm5970hwyyYNEC4vFHmb38cELFL89ESso7D1VDI3WBO4VerzCe2oNnjZqkGtDnq6utWQqPbBUIvHAP4sqH5a1mvZzLnZZd7FnTT+yXJPwB8ppeY825OCTlnvYJryfk1VEASnAprC4bI2+Wt82HVTka2/QzmwA==
*/