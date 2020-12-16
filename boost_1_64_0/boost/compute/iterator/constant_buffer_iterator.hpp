//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ITERATOR_CONSTANT_BUFFER_ITERATOR_HPP
#define BOOST_COMPUTE_ITERATOR_CONSTANT_BUFFER_ITERATOR_HPP

#include <cstddef>
#include <iterator>

#include <boost/iterator/iterator_facade.hpp>

#include <boost/compute/buffer.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

// forward declaration for constant_buffer_iterator<T>
template<class T> class constant_buffer_iterator;

namespace detail {

// helper class which defines the iterator_facade super-class
// type for constant_buffer_iterator<T>
template<class T>
class constant_buffer_iterator_base
{
public:
    typedef ::boost::iterator_facade<
        ::boost::compute::constant_buffer_iterator<T>,
        T,
        ::std::random_access_iterator_tag,
        ::boost::compute::detail::buffer_value<T>
    > type;
};

} // end detail namespace

/// \class constant_buffer_iterator
/// \brief An iterator for a buffer in the \c constant memory space.
///
/// The constant_buffer_iterator class provides an iterator for values in a
/// buffer in the \c constant memory space.
///
/// For iterating over values in the \c global memory space (the most common
/// case), use the buffer_iterator class.
///
/// \see buffer_iterator
template<class T>
class constant_buffer_iterator :
    public detail::constant_buffer_iterator_base<T>::type
{
public:
    typedef typename detail::constant_buffer_iterator_base<T>::type super_type;
    typedef typename super_type::reference reference;
    typedef typename super_type::difference_type difference_type;

    constant_buffer_iterator()
        : m_buffer(0),
          m_index(0)
    {
    }

    constant_buffer_iterator(const buffer &buffer, size_t index)
        : m_buffer(&buffer),
          m_index(index)
    {
    }

    constant_buffer_iterator(const constant_buffer_iterator<T> &other)
        : m_buffer(other.m_buffer),
          m_index(other.m_index)
    {
    }

    constant_buffer_iterator<T>& operator=(const constant_buffer_iterator<T> &other)
    {
        if(this != &other){
            m_buffer = other.m_buffer;
            m_index = other.m_index;
        }

        return *this;
    }

    ~constant_buffer_iterator()
    {
    }

    const buffer& get_buffer() const
    {
        return *m_buffer;
    }

    size_t get_index() const
    {
        return m_index;
    }

    T read(command_queue &queue) const
    {
        BOOST_ASSERT(m_buffer && m_buffer->get());
        BOOST_ASSERT(m_index < m_buffer->size() / sizeof(T));

        return detail::read_single_value<T>(m_buffer, m_index, queue);
    }

    void write(const T &value, command_queue &queue)
    {
        BOOST_ASSERT(m_buffer && m_buffer->get());
        BOOST_ASSERT(m_index < m_buffer->size() / sizeof(T));

        detail::write_single_value<T>(m_buffer, m_index, queue);
    }

    template<class Expr>
    detail::buffer_iterator_index_expr<T, Expr>
    operator[](const Expr &expr) const
    {
        BOOST_ASSERT(m_buffer);
        BOOST_ASSERT(m_buffer->get());

        return detail::buffer_iterator_index_expr<T, Expr>(
            *m_buffer, m_index, memory_object::constant_memory, expr
        );
    }

private:
    friend class ::boost::iterator_core_access;

    reference dereference() const
    {
        return detail::buffer_value<T>(*m_buffer, m_index);
    }

    bool equal(const constant_buffer_iterator<T> &other) const
    {
        return m_buffer == other.m_buffer && m_index == other.m_index;
    }

    void increment()
    {
        m_index++;
    }

    void decrement()
    {
        m_index--;
    }

    void advance(difference_type n)
    {
        m_index = static_cast<size_t>(static_cast<difference_type>(m_index) + n);
    }

    difference_type distance_to(const constant_buffer_iterator<T> &other) const
    {
        return static_cast<difference_type>(other.m_index - m_index);
    }

private:
    const buffer *m_buffer;
    size_t m_index;
};

/// Creates a new constant_buffer_iterator for \p buffer at \p index.
///
/// \param buffer the \ref buffer object
/// \param index the index in the buffer
///
/// \return a \c constant_buffer_iterator for \p buffer at \p index
template<class T>
inline constant_buffer_iterator<T>
make_constant_buffer_iterator(const buffer &buffer, size_t index = 0)
{
    return constant_buffer_iterator<T>(buffer, index);
}

/// \internal_ (is_device_iterator specialization for constant_buffer_iterator)
template<class T>
struct is_device_iterator<constant_buffer_iterator<T> > : boost::true_type {};

namespace detail {

// is_buffer_iterator specialization for constant_buffer_iterator
template<class Iterator>
struct is_buffer_iterator<
    Iterator,
    typename boost::enable_if<
        boost::is_same<
            constant_buffer_iterator<typename Iterator::value_type>,
            typename boost::remove_const<Iterator>::type
        >
    >::type
> : public boost::true_type {};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_CONSTANT_BUFFER_ITERATOR_HPP

/* constant_buffer_iterator.hpp
unrzW0vjZpyivKjKMk+YXupk3cSj4mpsvcuytzi+77hxxOjea2m+sZ8N6A9jk8QwBg1+nwVVwAs/7LJjDLbr3QcNXpe5UZllbsbpMLkhcmgQvzJgq4N4s+YYfDlL/KpMvUie64QNj/jUpr3uAOvbIeeSIadieZUGcV64Qg5EGH1oSoIeO2m2YcKj3KlIDzV78Enh3SEsnDIwONYO5BB9t7l2pIUfJZXfstfrnlWTtc31tVWjL9m7rX1AUMQRDSl4kzY6kIwGQ5md3pw7p3R+zvyAx34ZFkyqPpuJ5jdsM0a5PumhzKO1L2kY5SBYH9AKsDKYt3KHTjxl3MjZVbh+4VQ5sVqdr829l7/bznMTZSV3K8m0oRmfJnEqN+bNhcdYuXbCoiItljKlHzCCxKKFPjf9o6836lCwuBBvwSNuy6AvrhN8WYMwbOpiyal4GGd+mTdyNsQnDcW/G8rAqMJFKEHQl++2zs0FLyIRp7Zee+zeOxM2emh93LT3F9wJcidihuaZnF8dNMZ0KUWNxXYt2/ceKz9OkGdRTLqodewWIf3XrGa4DnrkztY74bJIuV95DP2A58KdfJ8TRtkpS4oio4VUmOIJLYLPKgv86soAk6kWst6Uzw0ZPsuTJCqdJJfv1KVvO92JLhm1B++CweuxwAuyLHFKJoYf3DeoIdrBvN6M/3M6b8U4rTw8SQvFanLh3sAqL/X8KucOMdFaPUlvEbuTFeVdb5YXR7lfpqVTs5KlQyautPYpH7X61s/SIOdVxjAoezsXe8tv6fwF8x0nDKOUuOubVtEhmOPNN14yygzE3Uhe+DzAO/46i56+G3ea8TD2XuvejrqjoK9khifO8rzm6w//Hui0F48b5UdJXCRZleky8N7A8n24s15+xarIrXhEa/xTZ0kL0I7CCC5F7RQ241jxwc8qSxLHLQvsCeitab0mnlk8S0JUkoLOvnDicZY+LvNceKcw6esDvapvbGZFjKv3HqWx9QLxtn36hB3jatsECX4RaCNjXG1rY1wJIGJcIWeDlgeLYr4v6u9Zz73JzM/nFeL4XpX/r10EuRp1eYeLKk+T0iOTRRMCATEidVzBwjCIMqdwWXM9hC2w7mfyRt2+4Tp5nOZFzABFbuw3mfNbxBGMaarWdaZT8VMXm2PF0n2a+aLzPDgtQ+6XAWenNxeXyPHNjJn+Ux17NI1T36nSmM1RDPCO/91lQ26VFE4RZCVTGzvVKJi39I9515+IPMBJkrKeYzjqvnBmTPOdiEM/TP2c4eLA8GnYp8vPWZgViReHOWu9zK0Yl5a9winDQqSvNjzYVVtif6HzcOblYZGkkY++hQLRyolNnoTWIV4WnK2KBaXmWGxuoJFDVOd5cJ65bhbykNV1Uli8R3mjedYoeRJXOTNPuZotbUmXfbQIy6DIaHmjm/f2rhU+kzr2WOk4hed4PpO3/BoD7HovNPBVkgZ+5LhMWhV0/MObdVrhcS+ZlpWXFhXrfyqBeB7wxTG+XeSKL0VKsuahYoNfafDn36zj8zzykiL0xTyTj+6Bh23PqJ/HiiApozyT9iI5YukUThfzs8080m1749vU5XDz/nNmWAcCErY2+GIAp196Qwde2NZLH+o28oM7gdEuv7XYx7s0uvWmBT4aN7AwqpjDjX/FXpve30FGLKgb2zyGlhI4+AsAd5X3Lh+9GXC9F+6Gv8d+G6umjiYvv5WN6XQq5C3c2sbiLSwwWwcsDOZ2i/n47WwM3sCiPd59BxNjv79BDIA79ePUpwJ35S69OLy7Qbz5u9u4Zlq0vu7sHoQxfakMH/6Lgn4Nvlbn79nBNW5bKOvV9xKY0TkZJw6CPjIn47572xgUg3J+amA=
*/