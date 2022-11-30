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
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
*/