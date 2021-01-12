//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALLOCATOR_PINNED_ALLOCATOR_HPP
#define BOOST_COMPUTE_ALLOCATOR_PINNED_ALLOCATOR_HPP

#include <boost/compute/allocator/buffer_allocator.hpp>

namespace boost {
namespace compute {

template<class T>
class pinned_allocator : public buffer_allocator<T>
{
public:
    explicit pinned_allocator(const context &context)
        : buffer_allocator<T>(context)
    {
        buffer_allocator<T>::set_mem_flags(
            buffer::read_write | buffer::alloc_host_ptr
        );
    }

    pinned_allocator(const pinned_allocator<T> &other)
        : buffer_allocator<T>(other)
    {
    }

    pinned_allocator<T>& operator=(const pinned_allocator<T> &other)
    {
        if(this != &other){
            buffer_allocator<T>::operator=(other);
        }

        return *this;
    }

    ~pinned_allocator()
    {
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALLOCATOR_PINNED_ALLOCATOR_HPP

/* pinned_allocator.hpp
OgmmAdKFOAwnxhcgFzuJZp2rD+Qu9JHhD5g+yBL6N4/A15H3/Il2bJ4ice2G7aamDT2u0Hft+g52zX/vOYU31B/x1reVxDVk/ytfSxPvtPQ241zq8eaoN9HE+T42bbX+Wix2Nvri3Fk8pDnifrlunJlnHvfu03kMbbvK5haWlBXlls0J1n/vuW2O6KNPIGyv4NyK3KKy4IeuyFOd39ggcZxjEtBUMzGjjRCzFZ6GaPJ8s4U+
*/