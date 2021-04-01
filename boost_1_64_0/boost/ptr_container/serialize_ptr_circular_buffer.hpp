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

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_PTR_CIRCULAR_BUFFER_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_PTR_CIRCULAR_BUFFER_HPP

#include <boost/ptr_container/detail/serialize_reversible_cont.hpp>
#include <boost/ptr_container/ptr_circular_buffer.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class T, class CloneAllocator, class Allocator>
void load(Archive& ar, ptr_circular_buffer<T, CloneAllocator, Allocator>& c, unsigned int version)
{
    typedef ptr_circular_buffer<T, CloneAllocator, Allocator> container_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::size_type size_type;
    
    size_type n;
    ar >> boost::serialization::make_nvp( ptr_container_detail::count(), n );
    c.reserve(n);
    
    ptr_container_detail::load_helper(ar, c, n);
}

template<class Archive, class T, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_circular_buffer<T, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_circular_buffer.hpp
tTx5kv9MXxEKTf1aoQYbFcuO2c8Kr4tPRHpajSUJ4uaClWDSQWmAk/jxOA3wnuc8Ug6XDn0565pipJls4vHz9p210lfvOF1nL6oeenPfIAqZa7ynx/LWkALw9cdd6psFbtXRt1wyNf5zd3FqWA0MKWgJQx3FVAxWPSD4W8GIda9+nGmX3RD866ZfuNoz3fWo3+tT/NTYs6uL2KvmAL1gMbUWTqiLqmsM454Tjc60XbRtPcV87WmJfQ6p9W5zZsuePv0fMt4TAlwTYu02PRx9AxXw2HpxF//zk+cR22ZZM4Pn8Q7bCWLtvPXpNzYGiaQTCrjCBiPEctB5jSeJAtHCollobIEY/IhJAQGihJoZ7X/jkL0mx6536v/HY5B/ZqQCK4hWvuOOu3GCasce2g/wN1c6ZNB+4rRhYdr/TbqafS12+edh3TWfbY/SssRgL2mZ3mSf1IL2lXHuxUYfHR4KLr0eSmYuvJ0H7hP0QeewzeBcajyEr8hazdon6ALZ0SgXVn9nzA1ESVJT7yW9Ze3JQGV4ej5SWW0yi5TN4EbKY+nXE8cHA8XBu/q/og==
*/