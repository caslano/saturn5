//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_READ_WRITE_SINGLE_VALUE_HPP
#define BOOST_COMPUTE_DETAIL_READ_WRITE_SINGLE_VALUE_HPP

#include <boost/throw_exception.hpp>

#include <boost/compute/buffer.hpp>
#include <boost/compute/event.hpp>
#include <boost/compute/exception.hpp>
#include <boost/compute/command_queue.hpp>

namespace boost {
namespace compute {
namespace detail {

// reads and returns a single value at index in the buffer
template<class T>
inline T read_single_value(const buffer &buffer,
                           size_t index,
                           command_queue &queue)
{
    BOOST_ASSERT(index < buffer.size() / sizeof(T));
    BOOST_ASSERT(buffer.get_context() == queue.get_context());

    T value;
    queue.enqueue_read_buffer(buffer,
                              sizeof(T) * index,
                              sizeof(T),
                              &value);
    return value;
}

// reads and returns a the first value in the buffer
template<class T>
inline T read_single_value(const buffer &buffer, command_queue &queue)
{
    return read_single_value<T>(buffer, 0, queue);
}

// writes a single value at index to the buffer
template<class T>
inline event write_single_value(const T &value,
                                const buffer &buffer,
                                size_t index,
                                command_queue &queue)
{
    BOOST_ASSERT(index < buffer.size() / sizeof(T));
    BOOST_ASSERT(buffer.get_context() == queue.get_context());

    return queue.enqueue_write_buffer(buffer,
                                      index * sizeof(T),
                                      sizeof(T),
                                      &value);
}

// writes value to the first location in buffer
template<class T>
inline void write_single_value(const T &value,
                               const buffer &buffer,
                               command_queue &queue)
{
    write_single_value<T>(value, buffer, 0, queue);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_READ_WRITE_SINGLE_VALUE_HPP

/* read_write_single_value.hpp
1Pzyg3QbpOmi5dJFyKXjf5d6IUnJCqB1IElZj+uKujSHJKIDy8V45BL8RnVM/bPFnGhqFnHe+GU1d3MxNmdTNie+XThGs0KblRc7G898HNFxZTH5DdOa8R0YpuHobDbLLJYyueHCmguKNVC8tOwvadmxtOz5qsr2Qtmm0rLtUfZwadms7Pe9Y/siRIPTgZpbD5Cix97XYLipruYiGn/Mx2/R+NwHiG+g8bo/IW5xkKZ/hHhzGt9YhPiqYySeycfH0PhtPr6Vxq/y8WU0fl6U/1s+PkdU3hc0flBU/h4+7knj2/i43TEhf340vpqP96Px5TROxmr948+o3Gvx2sD/JkP4oDHPqMSHa5NsA9hoSCM2S38+S0WT0TWluvYt91usdPx7cgkivi2KyK0obXjKUjuiqNrCOpKYuli9ocNx9XeXs311eBX3DepPl6rLxbUhQQ9gIHAx0MyLogR4BngYuA24GrgAGAR0B/LXpEk03gdYF9geaD9JmP6hpzCuLSrPYTSNewNDgJHABOAeYNZoYf7LaOc94Fug7kiKRkBLoCvQGxgCXAJMACYD04CZPB3lFyL+DMiMoqgFbA80A1oD3YCBwFBgAjAFeBh4BngbmA/5/Qx8xsvTG/UD9YCfAQcCnYAZaIcx5NkKqAXMQ7veo97JvpAfcALKCQRGAhOBB4FngA+AjA/6B2gItAZOAIYCVwD3AM8A7wGfAN8C
*/