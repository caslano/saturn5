//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CONTAINER_DETAIL_SCALAR_HPP
#define BOOST_COMPUTE_CONTAINER_DETAIL_SCALAR_HPP

#include <boost/compute/buffer.hpp>
#include <boost/compute/event.hpp>
#include <boost/compute/detail/read_write_single_value.hpp>

namespace boost {
namespace compute {
namespace detail {

// scalar<T> provides a trivial "container" that stores a
// single value in a memory buffer on a compute device
template<class T>
class scalar
{
public:
    typedef T value_type;

    scalar(const context &context)
        : m_buffer(context, sizeof(T))
    {
    }

    ~scalar()
    {
    }

    T read(command_queue &queue) const
    {
        return read_single_value<T>(m_buffer, 0, queue);
    }

    event write(const T &value, command_queue &queue)
    {
        return write_single_value<T>(value, m_buffer, 0, queue);
    }

    const buffer& get_buffer() const
    {
        return m_buffer;
    }

private:
    buffer m_buffer;
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_CONTAINER_DETAIL_SCALAR_HPP

/* scalar.hpp
cbPXlhZ8v7fBrdFfQM+uLOQqmnECtJ9LaAhUgxzJ5dE2Byl0GbetXIGQQ1Jp+sP45c9la9MHz7M2jPEjYoFx9gmKeGL4vQwevQjr8YgTvGP9d6Vmqs+2EdQSXshFmSzKEFOfSCvdi29wELi1fFh3Wx1+efima4boHh1NB/wvGYIrJdR9XLa9F4OihvbVha5O6Zxl7YxP9yuP7sNntWbNYeVt2jOL6CeMhnrnhD/ytP0KLfhlLA3eXX2Zld1LvKrWhvYjXUTBezYnIP29PrR1WZV3hWiq+I9Kddh16QA+dhv6BLBW05zIGSapwqDl3NViefb9bojnALQSXnEgD+MHpiYrOzbvG5MVsLrpIWS1SEY4FG6SZluBGjNYi0bj3jZLsQqs54WV+0ReCVIV777Usgvr/G8cjs+wnDs5KZumMW9Ovi3ixQcDpB0szwAf8BESu4A66n+yZmSRSIDyXu/ReCmVhylybsMpr6JqX5YniDO5MWQZp50nCIMEsdpkBf8Dzv4yWWgUQdkxA0jfa1R5q0sfjOg7W6W3nNWytnn+PSbENxOxsc4Oyz5iNQ==
*/