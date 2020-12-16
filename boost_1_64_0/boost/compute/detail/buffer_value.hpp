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
hbj9UeK1MeY78UVSOXk6/SE9duR5XszjbZz3SvREO9Yh9t6b9bHvNiv0O/Kw1inE1XzfsB+9HO8B+v7+Rg9gv35oLfOF++L/JTrWXn7/J3TkAeLKhRY8x3ESzxumT3LQzP5g4l50pwx34iLsZ+ogOuNJ7MadfM5W/Cb2fT/n33IffUFGPRfdt24mcSe6YBTvJerheVzxzxCHote0oZ/6O3N9C1jnjvT5JPD3zfTlJuKPqf+nXoV/53pt8qgjnEOv8iNeR1915XkMplR0e/Jvx5vJj+7muvBrnugdSY+hL9RS/3984s/0YvSLadbME+LxNPIr4tuda5nn1NvH4umnDSKeog/YYz5xKjpl/QoT94f3BX7Hz81lPD9Ef/nYmvfgM9+MvowbmBdb0V/I57zZ1+hlos95xIQ9taGOh85EHeT4Evz3OtYzcbU//u2QM597J/2a6Iz+XIfjO/hH7LE388OzgD7OKOq/6Ltm1p25mPPmc/ZW4Q+LiUPWMx+nokc9SrzwDfnpU+Ql+LNZxJOzTNjlX/BPZtb1h1Pp22P9oZv4z0M/8UTHxo6O0e/p9SB2lP2dh6xYT+QpOV7oktijAtaTN7pw6sXkI/bk+e7Y3TcmkxeRDxrzfQd5lsvEeg8sscZfU+9jP8HAj9hx4u3SPdihI5zXU9RJ9qHzWJvpm0XnTWcfTgq/x/FN1P19ZtHX9AZ9l6yXFnRtZ/Sz4THW73IT8RX19LX4p3zuG/Pq+E72uxeQn+HXM56nvs3+zRD28w3cYoH+yvg0YwfeJ+6iX8yXOKWNfRtZ5DPDNuSr9BusT2K+3Mt6byIu4TlQAeRDBcP4Zezkgl7jfU74X953lUSfdUYJ+fy/p/A8BuoUaxi/m7AbxDWpruhpy4g30cGibAz9jnwHv+Qba8P6ZL8Ifede2PmW/dSjGIeIENZvKHalmfO2YV2ZybvQF23QL3wLiWOv4P6QFwfSNxKwER2IdXv8M+zZXH7vAeKcn8i3r0MHO8vvT2bePkheO5f+tt3YQepPY79zv1gXzjegyxn7t//AfkxHz3iF/G4t6x6dKZS+R1937BL2f8Gb9E8QB3pw/mNrjLiW9xYcpR49QBywiLo+fq3gVu4r8Xn6j+RH1LUiiJe63czoLcQFkzkuOoorx7H/lfluNmPvmCf0NZnmEqdfgl+jv9h+ETrAEfx0O8flz9Tj2BXqVwXl2MPZ+KEy1p0v/ozvH0S3PriUuOJy6imvkl+2sN6z0CV4Hlzst/gn8v36jdQ9fZknnO9G+pdythNXfEr9Ajvhehx7P5P62jF0W/bR+LKe4zuxa8Z8xq/tJ77d+wBx4RH8vT9x6TDzLos4mf2VG1eiJ31nxX4jdHvsYDx94z7vUdfsmji/gnfRM92ZF+QzsT8S317NekohTjzGOrfieeEHsDfkU6t+RCf6i31bxnsZsVfHGUcf9uml8lyr+C8Zz5sZH+IbsyvjVEY8xD7s0q/o2yTfXW88N4u8LH4a55VGfLGa6zbx3q6L8LPbGGf6/5ozJ8Ypgzil8Xr80sXEOTn0Y9SQ9xE3DfC8Fz/084COSfQ9UC/kOU3tg+MX/jlz4f/64ovxkfEvx8+d+WP83LnNY+MT/xzQ357Tv9oH9VPHPj83Pnjg/LeNv/5LtLefGx85c2Zcf3f+55P4q8Fbdazx4Qv/ffX5f+3fPK7vHGi/8HnnJn7mwM/jYxe+5lzO6GcufMAIP/LFufEDI+e/HvxynH9GLvzEkfP/2X7+X7+dGx9bOv7Hmc3t42PtE792bnDw2IUfPXNAZz7xg4Pjm/W/kQtfnBo/8Pf5Aw3+feEKzrWPT1zUFwfGz4y0TXzxsP5qs35o5Pw=
*/