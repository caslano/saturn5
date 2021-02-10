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
T6KZnARc1sqRM5XfCSsJ740qpHayJOGolK6waoNflCZfS6pUI+lifn07u/ozp12tijrF2ZueXG36pqRa3EmyspDqLobphPVkKkRA/FI5j5i9V0ZPkF6Sl7Z1KQyDEI0zJO6EasQG6YSn2vvO/Xp+XvS2QSXnpSnceTFQMal9+1lVt0DTij2ZzpM31DuZE9vn1JpSVfwERTjs+k2jXJ0fYSGhLs+NJSebJoWDq5IuliBpkdjK2ZI6oFeeH85ox9l2tWlPDEFrClT1ViMdaIFdaUB8Tr0upQ32gYghS2I5UP6Nlh2xl2Q0UNFouqDZYkQb4ZTL6eNs+W7+YUkfpzc306vlLc3/oOnVbYr31+zqLbShkNWSvO+sdEBhSbVdo2R5kvwHTvryHbS24ZbSSxo9f0UL2UHKz38e0Sh9cXwjKdweKgRFlSjkKJss3tHV9O/LLBk8DQarp58ZkrmT9k7JXXB4e7m4uJldL2fzq+xjLTWEofR2gPHE0Yi9R4/cWdZKo794YUk4pwLDJW15mKB1XTYyO0M3EM7KSlobuwvdcyMCnGg1GqeRCVGhSbZRuuuDRrnnbJwdk1e9LnhM3OAwoQ/wWlUzhrtm6zWDO3s5XlXXHIRBcaCYcJJlPAiF0V7pXtJmjwq855JF0wRD
*/