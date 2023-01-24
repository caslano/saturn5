//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_BUFFER_VALUE_HPP
#define BOOST_COMPUTE_DETAIL_BUFFER_VALUE_HPP

#include <boost/compute/context.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/device_ptr.hpp>
#include <boost/compute/detail/read_write_single_value.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
class buffer_value
{
public:
    typedef T value_type;

    buffer_value()
    {
    }

    buffer_value(const value_type &value)
        : m_value(value)
    {
    }

    // creates a reference for the value in buffer at index (in bytes).
    buffer_value(const buffer &buffer, size_t index)
        : m_buffer(buffer.get(), false),
          m_index(index)
    {
    }

    buffer_value(const buffer_value<T> &other)
        : m_buffer(other.m_buffer.get(), false),
          m_index(other.m_index)
    {
    }

    ~buffer_value()
    {
        // set buffer to null so that its reference count will
        // not be decremented when its destructor is called
        m_buffer.get() = 0;
    }

    operator value_type() const
    {
        if(m_buffer.get()){
            const context &context = m_buffer.get_context();
            const device &device = context.get_device();
            command_queue queue(context, device);

            return detail::read_single_value<T>(m_buffer, m_index / sizeof(T), queue);
        }
        else {
            return m_value;
        }
    }

    buffer_value<T> operator-() const
    {
        return -T(*this);
    }

    bool operator<(const T &value) const
    {
        return T(*this) < value;
    }

    bool operator>(const T &value) const
    {
        return T(*this) > value;
    }

    bool operator<=(const T &value) const
    {
        return T(*this) <= value;
    }

    bool operator>=(const T &value) const
    {
        return T(*this) <= value;
    }

    bool operator==(const T &value) const
    {
        return T(*this) == value;
    }

    bool operator==(const buffer_value<T> &other) const
    {
        if(m_buffer.get() != other.m_buffer.get()){
            return false;
        }

        if(m_buffer.get()){
            return m_index == other.m_index;
        }
        else {
            return m_value == other.m_value;
        }
    }

    bool operator!=(const T &value) const
    {
        return T(*this) != value;
    }

    buffer_value<T>& operator=(const T &value)
    {
        if(m_buffer.get()){
            const context &context = m_buffer.get_context();
            command_queue queue(context, context.get_device());

            detail::write_single_value<T>(
                value, m_buffer, m_index / sizeof(T), queue
            ).wait();

            return *this;
        }
        else {
            m_value = value;
            return *this;
        }
    }

    buffer_value<T>& operator=(const buffer_value<T> &value)
    {
        return operator=(T(value));
    }

    detail::device_ptr<T> operator&() const
    {
        return detail::device_ptr<T>(m_buffer, m_index);
    }

    buffer_value<T>& operator++()
    {
        if(m_buffer.get()){
            T value = T(*this);
            value++;
            *this = value;
        }
        else {
            m_value++;
        }

        return *this;
    }

    buffer_value<T> operator++(int)
    {
        buffer_value<T> result(*this);
        ++(*this);
        return result;
    }

private:
    const buffer m_buffer;
    size_t m_index;
    value_type m_value;
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_BUFFER_VALUE_HPP

/* buffer_value.hpp
w37UYBbilw2x+pio51LSHy/Ciu2xqepDQD6pWn0IH7bDaJcVnEJBRvN+2YRl5T6aEZqjmcHR/KWK0KS0mlIj4bkImpef4I5nsGA2/uZxhmcGx/MoYWac9Djh+eGjiNsfH1Vxe/lRFbc3Hu2J26vwjLy9Pf1B5U66FSF2MIgzqF9Tuaf/AcV8VRXC8GEnLWAowGuzLRsWqJdWMbl/A9t2wCVNMUWAtUvkSJdlZ9H1SvAmA22M9+Ay+fBStmc0h7nl7+AxuNTWPqTX/8TWshXazCXrDOgNby9l7Y0OtzcH2ysJt0exTOdGt7cIPlMa3ErM4n9Qi/fO0OaCK7sUhRvI1X0Hh2QBsbytQNotJyHNNH2c4LRJKXhE3v1Np11qsnToYu3Sbmc/i5RncpQWxp5otRt2i6WN9rTdBaV1k6T+yaKUnwzTHEas6LDqDYIzQfgA/rrb2u2GRns2NNM0I/jECRidZ/UNLpDuAoCO0eAMAlgiRq/vsnvzY+VHMLuhLTa9rKOV4LQN9ltOtFoNfmtNfqwTZqBmchjdB7OQ/LdYdacuPPFEKM08TibzKoAha/woAbjqwxte++qaFzNRW6pzOUX37BQ0/aYo5nuXYG029JpJVszrF8P04Bevx+vjlXTtdaSy+5FQUrLBqIAlWaAtVcy24X9YngXETSzNB9SUBjfZ4aZArAWAo0cjCACyKJ5ogdvLE5g8nVkHDHsN
*/