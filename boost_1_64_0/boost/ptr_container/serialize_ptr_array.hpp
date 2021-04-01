// Copyright Sebastian Ramacher, 2007.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_PTR_ARRAY_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_PTR_ARRAY_HPP

#include <boost/ptr_container/detail/serialize_reversible_cont.hpp>
#include <boost/ptr_container/ptr_array.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class T, std::size_t N, class CloneAllocator>
void save(Archive& ar, const ptr_array<T, N, CloneAllocator>& c, unsigned int /*version*/)
{
    ptr_container_detail::save_helper(ar, c);
}

template<class Archive, class T, std::size_t N, class CloneAllocator>
void load(Archive& ar, ptr_array<T, N, CloneAllocator>& c, unsigned int /*version*/)
{
    typedef ptr_array<T, N, CloneAllocator> container_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::size_type size_type;
    
    for(size_type i = 0u; i != N; ++i)
    {
        T* p;
        ar >> boost::serialization::make_nvp( ptr_container_detail::item(), p );
        c.replace(i, p);
    }
}

template<class Archive, class T, std::size_t N, class CloneAllocator>
void serialize(Archive& ar, ptr_array<T, N, CloneAllocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_array.hpp
6UUjyxiRN3wtQPszMqLbmCgsNT6lB4VDmHmVwTSQfmFdut4Z3FsbNO45UJroIZM6gxkHPFlq9+UUx6jV2DcR5D/fMH/cJxUrBW33D1iStwnzK6KBcLVXxDR4Ijva3LhKkNLPAFaZ8ylms+VAtkhsKK/hK7BcdcGSYRyV4J8VjSOny20dCjDYzSaeRB8axBjjcdEyhY1nxMGBdEIlnhfMoHu4UDjFpawJUpOZsD7+zCP06c5miVQqH3F6nABgbJbS/RKO3TQD815mTLoIe9l3Jyyw+ZbqYjfFZz3XkNuqbzbiJ53UQKJfwgrXuivRdtWCMu/HmZTgkcCatnsLe7zqK/akZnbqklvdM6siHwlD5A4c2SbcK39kweQSLhdqJn/uFoN1Z0CYEExiRvZm/JjjuHwz/lPxC8Dx2XC2agQVdMll1uw19hRjTokbpzphIy2TnnCTdk+yBp45KMcJ1ibKn8dvfhRRrgQYohAYMfy+DqJQarhWDprEjPBP2K/AiEudBl3AnlVDCi6WXpXHGrQr32quzHj5UUra+8XLeICRlA15WvX+aR1/z4T54g==
*/