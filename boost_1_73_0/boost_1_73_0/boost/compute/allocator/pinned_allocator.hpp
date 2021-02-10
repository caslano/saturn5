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
tEFY/a+GB43htDN8nSHQOE4QRY7Dqs6tIhc/qYh5WoCsA7YiSdwkEPB1g/BoaPx7r5yT5zSOWXnGArkicM8Fo67tnnaB7xxH7Y+i0SIaRJHrNdEI+BrDCT+8/gYwuAB1XHBaxx4Al24IddTSZnxkucwM1EhbhxjmRF0UYMJVBnG9hQK5+CSrBuGXCjMmlax5TGUUGvaObk/jYAfW1lOs+2a11FxYWg+A3M0Xl4QZyp1z7PL4I7nLSK52VuXBVfjuMjw/im5/Mh4P+vNgWjdtpTEK+nq/tSo6d3rYXCVzBexVZDikgx3SLYV/OCYAFWwXi0ktfVl/LPS6gFXYBjCjKm+YEal77ZntGBkPz9rVGbuW8I6LR8DAt1CNXV+0WSVFYiCwf0DKRRb8nFM4GW/m8+nZRXhBU1VK5DjHTnv8bsv52R2jbAcPvJ0kiWJ+IidbicKgFe/ShO1ekfJFD4SGY2YfCCifSa6cm5cZ5Wr+Ft9w21y2hcrUZamxpSSaeTY6YqqWAqsJfLcbCxrzm2TYTpQ7NQBM1HBjGO7TD8djhYvWixj8x1WIRW7ZxJCP08BZ6qo62PkQPnD2/1F4tlkT/LfC8yqOv1h/6Av1ZxqNXC+c8sYVU1SnqXqmEWwDzrra7ZgHAe/6Hmbu3TrI
*/