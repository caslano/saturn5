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
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
*/