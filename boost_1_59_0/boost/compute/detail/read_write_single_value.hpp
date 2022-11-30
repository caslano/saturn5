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
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
*/