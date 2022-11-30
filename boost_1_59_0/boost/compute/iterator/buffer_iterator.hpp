//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ITERATOR_BUFFER_ITERATOR_HPP
#define BOOST_COMPUTE_ITERATOR_BUFFER_ITERATOR_HPP

#include <cstddef>
#include <iterator>

#include <boost/config.hpp>
#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include <boost/compute/buffer.hpp>
#include <boost/compute/detail/buffer_value.hpp>
#include <boost/compute/detail/is_buffer_iterator.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/read_write_single_value.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

// forward declaration for buffer_iterator<T>
template<class T> class buffer_iterator;

namespace detail {

// helper class which defines the iterator_facade super-class
// type for buffer_iterator<T>
template<class T>
class buffer_iterator_base
{
public:
    typedef ::boost::iterator_facade<
        ::boost::compute::buffer_iterator<T>,
        T,
        ::std::random_access_iterator_tag,
        ::boost::compute::detail::buffer_value<T>
    > type;
};

template<class T, class IndexExpr>
struct buffer_iterator_index_expr
{
    typedef T result_type;

    buffer_iterator_index_expr(const buffer &buffer,
                               size_t index,
                               const memory_object::address_space address_space,
                               const IndexExpr &expr)
        : m_buffer(buffer.get(), false),
          m_index(index),
          m_address_space(address_space),
          m_expr(expr)
    {
    }

    buffer_iterator_index_expr(const buffer_iterator_index_expr& other)
        : m_buffer(other.m_buffer.get(), false),
          m_index(other.m_index),
          m_address_space(other.m_address_space),
          m_expr(other.m_expr)
    {
    }

    ~buffer_iterator_index_expr()
    {
        // set buffer to null so that its reference count will
        // not be decremented when its destructor is called
        m_buffer.get() = 0;
    }

    operator T() const
    {
        BOOST_STATIC_ASSERT_MSG(boost::is_integral<IndexExpr>::value,
                                "Index expression must be integral");

        return buffer_value<T>(m_buffer, size_t(m_expr) * sizeof(T));
    }

    const buffer m_buffer;
    const size_t m_index;
    const memory_object::address_space m_address_space;
    const IndexExpr m_expr;
};

template<class T, class IndexExpr>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const buffer_iterator_index_expr<T, IndexExpr> &expr)
{
    if(expr.m_index == 0){
        return kernel <<
                   kernel.get_buffer_identifier<T>(expr.m_buffer, expr.m_address_space) <<
                   '[' << expr.m_expr << ']';
    }
    else {
        return kernel <<
                   kernel.get_buffer_identifier<T>(expr.m_buffer, expr.m_address_space) <<
                   '[' << uint_(expr.m_index) << "+(" << expr.m_expr << ")]";
    }
}

} // end detail namespace

/// \class buffer_iterator
/// \brief An iterator for values in a buffer.
///
/// The buffer_iterator class iterates over values in a memory buffer on a
/// compute device. It is the most commonly used iterator in Boost.Compute
/// and is used by the \ref vector "vector<T>" and \ref array "array<T, N>"
/// container classes.
///
/// Buffer iterators store a reference to a memory buffer along with an index
/// into that memory buffer.
///
/// The buffer_iterator class allows for arbitrary OpenCL memory objects
/// (including those created outside of Boost.Compute) to be used with the
/// Boost.Compute algorithms (such as transform() and sort()). For example,
/// to reverse the contents of an OpenCL memory buffer containing a set of
/// integers:
///
/// \snippet test/test_buffer_iterator.cpp reverse_external_buffer
///
/// \see buffer, make_buffer_iterator()
template<class T>
class buffer_iterator : public detail::buffer_iterator_base<T>::type
{
public:
    typedef typename detail::buffer_iterator_base<T>::type super_type;
    typedef typename super_type::reference reference;
    typedef typename super_type::difference_type difference_type;

    buffer_iterator()
        : m_index(0)
    {
    }

    buffer_iterator(const buffer &buffer, size_t index)
        : m_buffer(buffer.get(), false),
          m_index(index)
    {
    }

    buffer_iterator(const buffer_iterator<T> &other)
        : m_buffer(other.m_buffer.get(), false),
          m_index(other.m_index)
    {
    }

    buffer_iterator<T>& operator=(const buffer_iterator<T> &other)
    {
        if(this != &other){
            m_buffer.get() = other.m_buffer.get();
            m_index = other.m_index;
        }

        return *this;
    }

    ~buffer_iterator()
    {
        // set buffer to null so that its reference count will
        // not be decremented when its destructor is called
        m_buffer.get() = 0;
    }

    const buffer& get_buffer() const
    {
        return m_buffer;
    }

    size_t get_index() const
    {
        return m_index;
    }

    T read(command_queue &queue) const
    {
        BOOST_ASSERT(m_buffer.get());
        BOOST_ASSERT(m_index < m_buffer.size() / sizeof(T));

        return detail::read_single_value<T>(m_buffer, m_index, queue);
    }

    void write(const T &value, command_queue &queue)
    {
        BOOST_ASSERT(m_buffer.get());
        BOOST_ASSERT(m_index < m_buffer.size() / sizeof(T));

        detail::write_single_value<T>(value, m_buffer, m_index, queue);
    }

    /// \internal_
    template<class Expr>
    detail::buffer_iterator_index_expr<T, Expr>
    operator[](const Expr &expr) const
    {
        BOOST_ASSERT(m_buffer.get());

        return detail::buffer_iterator_index_expr<T, Expr>(
            m_buffer, m_index, memory_object::global_memory, expr
        );
    }

private:
    friend class ::boost::iterator_core_access;

    /// \internal_
    reference dereference() const
    {
        return detail::buffer_value<T>(m_buffer, m_index * sizeof(T));
    }

    /// \internal_
    bool equal(const buffer_iterator<T> &other) const
    {
        return m_buffer.get() == other.m_buffer.get() &&
               m_index == other.m_index;
    }

    /// \internal_
    void increment()
    {
        m_index++;
    }

    /// \internal_
    void decrement()
    {
        m_index--;
    }

    /// \internal_
    void advance(difference_type n)
    {
        m_index = static_cast<size_t>(static_cast<difference_type>(m_index) + n);
    }

    /// \internal_
    difference_type distance_to(const buffer_iterator<T> &other) const
    {
        return static_cast<difference_type>(other.m_index - m_index);
    }

private:
    const buffer m_buffer;
    size_t m_index;
};

/// Creates a new \ref buffer_iterator for \p buffer at \p index.
///
/// \param buffer the \ref buffer object
/// \param index the index in the buffer
///
/// \return a \c buffer_iterator for \p buffer at \p index
template<class T>
inline buffer_iterator<T>
make_buffer_iterator(const buffer &buffer, size_t index = 0)
{
    return buffer_iterator<T>(buffer, index);
}

/// \internal_ (is_device_iterator specialization for buffer_iterator)
template<class T>
struct is_device_iterator<buffer_iterator<T> > : boost::true_type {};

namespace detail {

// is_buffer_iterator specialization for buffer_iterator
template<class Iterator>
struct is_buffer_iterator<
    Iterator,
    typename boost::enable_if<
        boost::is_same<
            buffer_iterator<typename Iterator::value_type>,
            typename boost::remove_const<Iterator>::type
        >
    >::type
> : public boost::true_type {};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_BUFFER_ITERATOR_HPP

/* buffer_iterator.hpp
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
*/