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