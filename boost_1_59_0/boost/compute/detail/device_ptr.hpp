//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DEVICE_PTR_HPP
#define BOOST_COMPUTE_DEVICE_PTR_HPP

#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>

#include <boost/compute/buffer.hpp>
#include <boost/compute/config.hpp>
#include <boost/compute/detail/is_buffer_iterator.hpp>
#include <boost/compute/detail/read_write_single_value.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T, class IndexExpr>
struct device_ptr_index_expr
{
    typedef T result_type;

    device_ptr_index_expr(const buffer &buffer,
                          uint_ index,
                          const IndexExpr &expr)
        : m_buffer(buffer),
          m_index(index),
          m_expr(expr)
    {
    }

    operator T() const
    {
        BOOST_STATIC_ASSERT_MSG(boost::is_integral<IndexExpr>::value,
                                "Index expression must be integral");

        BOOST_ASSERT(m_buffer.get());

        const context &context = m_buffer.get_context();
        const device &device = context.get_device();
        command_queue queue(context, device);

        return detail::read_single_value<T>(m_buffer, m_expr, queue);
    }

    const buffer &m_buffer;
    uint_ m_index;
    IndexExpr m_expr;
};

template<class T>
class device_ptr
{
public:
    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;
    typedef T* pointer;
    typedef T& reference;

    device_ptr()
        : m_index(0)
    {
    }

    device_ptr(const buffer &buffer, size_t index = 0)
        : m_buffer(buffer.get(), false),
          m_index(index)
    {
    }

    device_ptr(const device_ptr<T> &other)
        : m_buffer(other.m_buffer.get(), false),
          m_index(other.m_index)
    {
    }

    device_ptr<T>& operator=(const device_ptr<T> &other)
    {
        if(this != &other){
            m_buffer.get() = other.m_buffer.get();
            m_index = other.m_index;
        }

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    device_ptr(device_ptr<T>&& other) BOOST_NOEXCEPT
        : m_buffer(other.m_buffer.get(), false),
          m_index(other.m_index)
    {
        other.m_buffer.get() = 0;
    }

    device_ptr<T>& operator=(device_ptr<T>&& other) BOOST_NOEXCEPT
    {
        m_buffer.get() = other.m_buffer.get();
        m_index = other.m_index;

        other.m_buffer.get() = 0;

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    ~device_ptr()
    {
        // set buffer to null so that its reference count will
        // not be decremented when its destructor is called
        m_buffer.get() = 0;
    }

    size_type get_index() const
    {
        return m_index;
    }

    const buffer& get_buffer() const
    {
        return m_buffer;
    }

    template<class OT>
    device_ptr<OT> cast() const
    {
        return device_ptr<OT>(m_buffer, m_index);
    }

    device_ptr<T> operator+(difference_type n) const
    {
        return device_ptr<T>(m_buffer, m_index + n);
    }

    device_ptr<T> operator+(const device_ptr<T> &other) const
    {
        return device_ptr<T>(m_buffer, m_index + other.m_index);
    }

    device_ptr<T>& operator+=(difference_type n)
    {
        m_index += static_cast<size_t>(n);
        return *this;
    }

    difference_type operator-(const device_ptr<T> &other) const
    {
        return static_cast<difference_type>(m_index - other.m_index);
    }

    device_ptr<T>& operator-=(difference_type n)
    {
        m_index -= n;
        return *this;
    }

    bool operator==(const device_ptr<T> &other) const
    {
        return m_buffer.get() == other.m_buffer.get() &&
               m_index == other.m_index;
    }

    bool operator!=(const device_ptr<T> &other) const
    {
        return !(*this == other);
    }

    template<class Expr>
    detail::device_ptr_index_expr<T, Expr>
    operator[](const Expr &expr) const
    {
        BOOST_ASSERT(m_buffer.get());

        return detail::device_ptr_index_expr<T, Expr>(m_buffer,
                                                      uint_(m_index),
                                                      expr);
    }

private:
    const buffer m_buffer;
    size_t m_index;
};

// is_buffer_iterator specialization for device_ptr
template<class Iterator>
struct is_buffer_iterator<
    Iterator,
    typename boost::enable_if<
        boost::is_same<
            device_ptr<typename Iterator::value_type>,
            typename boost::remove_const<Iterator>::type
        >
    >::type
> : public boost::true_type {};

} // end detail namespace

// is_device_iterator specialization for device_ptr
template<class T>
struct is_device_iterator<detail::device_ptr<T> > : boost::true_type {};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DEVICE_PTR_HPP

/* device_ptr.hpp
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
*/