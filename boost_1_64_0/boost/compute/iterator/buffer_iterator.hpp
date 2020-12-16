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
p7873tHSNVMc6PTUG3RBsH23z+3S6Ah7RWuiVsbe3SbGtvV9rUOH2Q2Yi3s6GJjb7tN86w16MDCzWbaiG9pYmNiAefWNbAzMa/i2z+3tYAx/Un5jg26bfSDnooGDyQd1WbiJRYcZR8utpGEsk1V7R3hTDTM0+gt1nt6nY0bX+Xk3M3F2nV+9X6f31/kjN7cwqLN2B3ALgbm6HShs1u33WTF0M1rsPTfS4rSqPRuF7JvvriS6Tt3R1Auqpo1Ls+P1+jpf+PSPk/hsYsvyCT/5XnOvnkRpHPjZNcfYaPQN1iBz7S8j38+DKmB9EYFx3tF5jkV54fluKCKrNxNDxTNu8B/Q8UerlCdFGmSMBKOpjNg7H9HxR6LKi90krcObH1WrlYNYGXps+AeXoVOWZeCxR5ZZWT26NN/xfPS95hnPS73QFf70McXpM8PA2/uBNcT0eK/5vpJ7QUB6RTMFGVlJQj2H3Xbq/3r9IuUaRMFxbSAAt41wth4GrB1PbIfCkcLS6JAzv7Omq1wveVTppbVyNnYpHOkZHXArrJNE1+4vkY/6zWY+wyrgAeclM24srfe0V95snju8MM554DDtJrOzx9zzFnNPX1ReWeapw/pMIVYu64MWLy/TskidivVdj1rvcGODN2NeGLlRGkZs5LWp6Yu9YPCnLCjS2El5yka5NVp1f6FV9zKIY56kFZM+fvXLBOyr1JyA36zBG7Ow9JLKC2hz3esm1Xkv9zmLP8p930uTAPym+1Q3bq/ix3s7Lw5Dz3HBb7lV2W+L97zVys2SumlUuiXruBCa55g7Kz74+xJPlPOKWa6FdnlTFp/rVn6Why6zXA7tt95c8aGdijIPyjxj/W6GnbG9ZvCHzI+LwPGClPW5H9bcONO8XPHifXPkO8Tus65bIvb3uDewvrcsHJ47sSxXbptVMm/FCL7zVr9wnqVVGHHq15oPEXvN96nfsupappXDuZt2+Yadul5WvHifGmdxmJeJyYuExgx6422Wrk+SsEyzCN9YR6OV1tHmO91mHBm8Ocu4H7t5EKNMPa7EYOXs4sqgezY2ZPhUfhZUCVWk69rZiQd+0uBNmFvklePlnI3Yxjf1b/i3DP6YdA/306RymLkFGzk+Xm/wuyxIMj8JopLZWzPr/cQHFR/0beaUse+nrG/LVvOizhesb/YDL/Z8N2IjzHL2N1+2+MOyCKOQdP2Ia3a7z/e93cxlTuoqCbyCjbamQwb6fMqQ4bPYCcuEFy7rmtAb1lXoEoM3Jp1XRC73Q9ZvWu/cp6wZ/A7LIrHLSpllAe+MtRcafCnpAj+JMlqUR5nG7XgHBn/EKidxq9xNbX59eiPXksGbsyIpIp7HFRtpEsd3Q8YlQ0bBktyJXIfHbLRZGwMeff8OU4bHuRMEacZGm5q7fW/I8FkUJl7FSUl2zTfo+6Z8rvN6pMvj0o/LEH0/0tSs7VfOGeUnjDsJTaAsgIz++g+R19zgD1mURE4We7nOj8ljxZ44r/OWLHSyqsxdTD3Z9Kq8M5jvRnkpK3gSFbGLfus8M1Ex4zDfLX6/DKqSpw4b5T6p+NHn77TGTUCjL+E5u4pbZafPDRkRi+KQqpEmugxbWULHK16cK5MoiGJu8XYVJnR8w489XlGKd26s3+2ysz693uAPWZXQtKEuYH3umNba+lGDN2Bh6jiZ76Ns3U2z0bN4N6jzHit45PEo8BkefSr8Bt4N6njOsiR1ipiWQvNlg3WfrXiwTyky30u5yzpPXq34Eu8yy0pDcb3s0RtF4RD35Lnhg80k/c03HdT5pkIRK8b1S8Fm4OFfOaXwWKvCKg9iGsSNxWdJ5QfADYOpN09a/Ens+Dx3MotfZd4WCdY=
*/