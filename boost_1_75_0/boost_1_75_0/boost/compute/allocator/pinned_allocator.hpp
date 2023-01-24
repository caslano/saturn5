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
w1feSr+MmSIxuZhU526Lcyt58+ahyjQFEROt0omCwA99hMvyYK4y8O+EiydkCMmTk4WLb8vB3IBwL8I9TAa3Fcuzkcruujx3A/TKD3oXaPpQT2iY9KMY+L4Pj4qaFy5E4Wll1PrzAHozwuu9LQMg5SEI/okLLZ5RMdUyi+0HqfSJyC9bFHnOfdkRZkwxrpukHXWnoBRDvw0YdNLCWMxmZJUeTJTuSrZKC1Os0u1DRKFRDDTibLyB4vNrtz64TQ7fwoQwPiV82wi3qeFb4PHxGeFbEKzjs8K3bXCbE76Vbdkdkl5q99jW0B6jY31ZWZlwWbUO/93mjcUEOjppe6ApwaLUW0Gx2WsJNF16Yo81u8mSth9f9IFLqTFte/ZuaZfVsC3QlDTRkJgi7ZtgsBs3WKWvbPBs24Ds3TZD0Jr2pbQr0BRjlfZnb7Nm77MYmmzSVlvaJzZpJ1Zry66zGgIW6TOo32OrSmtRAbDAe6UegMBmpZ280e2WtJ3Zu0Vv0hq/QQdN2wyJJt6qrcpmaLYZDlmkFovUCO0DWDaYYHbb0jotqBqeAjBssCzcpjWBsOywGroQEIu0gzUG3XUzVA6N06M+Funf8PTEnrS9CFLajuzdFqkZmk7bhUhbpP3Uvlqn1YBNW6BOqSHQmAS1ZLfQZQz9za63pG3NDli8iRdbpWZAHFqWmqX90DQn8GdSM8MVWk9rBgo3RlC4pVtb
*/