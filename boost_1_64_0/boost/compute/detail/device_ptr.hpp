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
is/nsxBg4QzrODhVv0nOSNNHgKtG9GvN5/pZqmLVbsADNGy5xJ37Le96Ms6COYDI7GjNbjo+5q3f0bWaOh9OW2QaFu0z+3mBrH0bb06812WDqMs4iEPNVTL3tk2lPaMcXT2OTimS9KOd4DCWR7afsr2e0ajzt4LUwuw50dg8GZ2RUysdLolTyfYzqJamuSgLwabNrsRIheEZX1LuPMrgwScYgWBSvIp9581YeFyLEzb5tTj1hrIt2Qe0Ove9jTrwEPvABZWwiXrhQvjDemjZ6HeXsUQYTEXSb2rzrP0j1x+R98Z9cafvZdbzVFNU753wxM0Wj7EqQVcA8C/fLRDf2p3CaXINyrcPm+QR1mVOP4GCjUPFGu2rvIjfrPQGPLq8WLeYsFoGw51H1V/LxEzjO/+hfPF9nk1Ixu+RFhfzM9K/SD6yd6CTZ4hKRF0aj1He3m4pm8NKkskfqFJNsl/m2wgyK0yLwfB9+QCInMfqZOX0Vf3WxThGiR7WBeF6MENVbkdWJe1h1Ko6Z6TT62fvHDVIXEY/AID5Nl8onvGt1+LLHYOfn8gODcaxwQ==
*/