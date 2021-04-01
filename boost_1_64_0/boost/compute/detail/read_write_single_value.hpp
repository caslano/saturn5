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
/xdhK+FjQfWi1oWZgXsvMS/RlVnWetWQtP/w2kfU6eSW8wRYGqJe3kHrOcE5VzK8zIdfKC/vJjdjEbEZ0D0eoc156vlwp+MmFKWaVsoBiTCICCHW2abWSve4QCVanpCmbybvytMuAErW4tUF/4sck43FlOOdr6xRi/V9M+GEeTaCpdb3Bc4HXYmcm0LsfahEIjIiG9GngoFWK4EoWo+5tWg25h1gtvqEoxk8dXY43Ob/YXkW4zmELQag8T/XWuAvVtKrDvqYg3dw1ksgYAzhVJk+vRA75nl8VTVWjSZ1KjyK/9nW/3gVWCv1N5WAABdaHI0O8BahvararEca9Ro3rtA94pQmMf8yGI6c+SMqn4uzCCdLQlPWW+g8ycsN3qxRFPcCHtvztp2IrwNvH0KS6ycsJRQyiuVWMptzH3qgppQd7RGEQfyCDyqHz9xs8d2lPs/x20xMxPYdaDQNLZfZnospsdhaIYbEe8SLDlzKVGVnyDiuHwjWopxALc7C9cW+I8jhhcT0yS0VItdIo33Pu+1QVMhq38kfFpJjIg29+C0V0hYSJxt5O3SiQQ==
*/