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