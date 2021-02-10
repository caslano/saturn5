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
HFqwtszYMkVGSpMtWvEpsN9+Soc3D9y2jYW/XC2m+OhNVr61eCqzyS77vjfZHDyDapKENi9rhGM2cLqaTExYNu3xK1gh64eO0f/bu5lPfMstMwtdc4kkWerkfP+ME6Pub/hSE1DCF6FIMT2g0ekQc2+xjGjiwN6fWHYfk4uYm8jCdnDaUvBs8EOdDPGvZb56SR7XOFFJzgp23kaOS9w+LxGOr/0b38HPHWrP+zUzUNW0D9nANoJ2uea4/KQ2m5K66SI9FF1F2iw2OFr4bD0tmjsRjJxYmZbahM+Wm/FWUu+jF0y8y2ASLNeWl6bdV7M17y/u2zP3tM2yQ9+HNwlnZOXLxTNe2IM3Q9Lv6P2fB9UheEyTHiis/wBQSwMECgAAAAgALWdKUvYODG7uAgAAcwYAACsACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvY3VybF91cmxfY2xlYW51cC4zVVQFAAG2SCRgrVRhb9owEP2eX3HLvtAqC10nde3WTUspW6NRQCR0Q0KKTGyIJ2NHttNSqT9+5ySUsU5qP8wo2FzuvXt+ZxPOfTj8b8MLHR08O7L6yXDgvAWNtfrFcvtvQJY9QPNB4BznF5Tqwg71kB3Ai1AP0KlRWVvr3K2z7AXl5k6k++o68Dxz
*/