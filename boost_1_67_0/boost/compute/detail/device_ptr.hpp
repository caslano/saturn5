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