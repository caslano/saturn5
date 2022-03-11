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