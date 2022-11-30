//---------------------------------------------------------------------------//
// Copyright (c) 2015 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ITERATOR_STRIDED_ITERATOR_HPP
#define BOOST_COMPUTE_ITERATOR_STRIDED_ITERATOR_HPP

#include <cstddef>
#include <iterator>

#include <boost/config.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

#include <boost/compute/functional.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/is_buffer_iterator.hpp>
#include <boost/compute/detail/read_write_single_value.hpp>
#include <boost/compute/iterator/detail/get_base_iterator_buffer.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>
#include <boost/compute/type_traits/result_of.hpp>

namespace boost {
namespace compute {

// forward declaration for strided_iterator
template<class Iterator>
class strided_iterator;

namespace detail {

// helper class which defines the iterator_adaptor super-class
// type for strided_iterator
template<class Iterator>
class strided_iterator_base
{
public:
    typedef ::boost::iterator_adaptor<
        ::boost::compute::strided_iterator<Iterator>,
        Iterator,
        typename std::iterator_traits<Iterator>::value_type,
        typename std::iterator_traits<Iterator>::iterator_category
    > type;
};

// helper class for including stride value in index expression
template<class IndexExpr, class Stride>
struct stride_expr
{
    stride_expr(const IndexExpr &expr, const Stride &stride)
        : m_index_expr(expr),
          m_stride(stride)
    {
    }

    const IndexExpr m_index_expr;
    const Stride m_stride;
};

template<class IndexExpr, class Stride>
inline stride_expr<IndexExpr, Stride> make_stride_expr(const IndexExpr &expr,
                                                       const Stride &stride)
{
    return stride_expr<IndexExpr, Stride>(expr, stride);
}

template<class IndexExpr, class Stride>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const stride_expr<IndexExpr, Stride> &expr)
{
    // (expr.m_stride * (expr.m_index_expr))
    return kernel << "(" << static_cast<ulong_>(expr.m_stride)
                  << " * (" << expr.m_index_expr << "))";
}

template<class Iterator, class Stride, class IndexExpr>
struct strided_iterator_index_expr
{
    typedef typename std::iterator_traits<Iterator>::value_type result_type;

    strided_iterator_index_expr(const Iterator &input_iter,
                                const Stride &stride,
                                const IndexExpr &index_expr)
        : m_input_iter(input_iter),
          m_stride(stride),
          m_index_expr(index_expr)
    {
    }

    const Iterator m_input_iter;
    const Stride m_stride;
    const IndexExpr m_index_expr;
};

template<class Iterator, class Stride, class IndexExpr>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const strided_iterator_index_expr<Iterator,
                                                                 Stride,
                                                                 IndexExpr> &expr)
{
    return kernel << expr.m_input_iter[make_stride_expr(expr.m_index_expr, expr.m_stride)];
}

} // end detail namespace

/// \class strided_iterator
/// \brief An iterator adaptor with adjustable iteration step.
///
/// The strided iterator adaptor skips over multiple elements each time
/// it is incremented or decremented.
///
/// \see buffer_iterator, make_strided_iterator(), make_strided_iterator_end()
template<class Iterator>
class strided_iterator :
    public detail::strided_iterator_base<Iterator>::type
{
public:
    typedef typename
        detail::strided_iterator_base<Iterator>::type super_type;
    typedef typename super_type::value_type value_type;
    typedef typename super_type::reference reference;
    typedef typename super_type::base_type base_type;
    typedef typename super_type::difference_type difference_type;

    strided_iterator(Iterator iterator, difference_type stride)
        : super_type(iterator),
          m_stride(static_cast<difference_type>(stride))
    {
        // stride must be greater than zero
        BOOST_ASSERT_MSG(stride > 0, "Stride must be greater than zero");
    }

    strided_iterator(const strided_iterator<Iterator> &other)
        : super_type(other.base()),
          m_stride(other.m_stride)
    {
    }

    strided_iterator<Iterator>&
    operator=(const strided_iterator<Iterator> &other)
    {
        if(this != &other){
            super_type::operator=(other);

            m_stride = other.m_stride;
        }

        return *this;
    }

    ~strided_iterator()
    {
    }

    size_t get_index() const
    {
        return super_type::base().get_index();
    }

    const buffer& get_buffer() const
    {
        return detail::get_base_iterator_buffer(*this);
    }

    template<class IndexExpression>
    detail::strided_iterator_index_expr<Iterator, difference_type, IndexExpression>
    operator[](const IndexExpression &expr) const
    {
        typedef
            typename detail::strided_iterator_index_expr<Iterator,
                                                         difference_type,
                                                         IndexExpression>
            StridedIndexExprType;
        return StridedIndexExprType(super_type::base(),m_stride, expr);
    }

private:
    friend class ::boost::iterator_core_access;

    reference dereference() const
    {
        return reference();
    }

    bool equal(const strided_iterator<Iterator> &other) const
    {
        return (other.m_stride == m_stride)
                   && (other.base_reference() == this->base_reference());
    }

    void increment()
    {
        std::advance(super_type::base_reference(), m_stride);
    }

    void decrement()
    {
        std::advance(super_type::base_reference(),-m_stride);
    }

    void advance(typename super_type::difference_type n)
    {
        std::advance(super_type::base_reference(), n * m_stride);
    }

    difference_type distance_to(const strided_iterator<Iterator> &other) const
    {
        return std::distance(this->base_reference(), other.base_reference()) / m_stride;
    }

private:
    difference_type m_stride;
};

/// Returns a strided_iterator for \p iterator with \p stride.
///
/// \param iterator the underlying iterator
/// \param stride the iteration step for strided_iterator
///
/// \return a \c strided_iterator for \p iterator with \p stride.
///
/// For example, to create an iterator which iterates over every other
/// element in a \c vector<int>:
/// \code
/// auto strided_iterator = make_strided_iterator(vec.begin(), 2);
/// \endcode
template<class Iterator>
inline strided_iterator<Iterator>
make_strided_iterator(Iterator iterator,
                      typename std::iterator_traits<Iterator>::difference_type stride)
{
    return strided_iterator<Iterator>(iterator, stride);
}

/// Returns a strided_iterator which refers to element that would follow
/// the last element accessible through strided_iterator for \p first iterator
/// with \p stride.
///
/// Parameter \p stride must be greater than zero.
///
/// \param first the iterator referring to the first element accessible
///        through strided_iterator for \p first with \p stride
/// \param last the iterator referring to the last element that may be
////       accessible through strided_iterator for \p first with \p stride
/// \param stride the iteration step
///
/// \return a \c strided_iterator referring to element that would follow
///         the last element accessible through strided_iterator for \p first
///         iterator with \p stride.
///
/// It can be helpful when iterating over strided_iterator:
/// \code
/// // vec.size() may not be divisible by 3
/// auto strided_iterator_begin = make_strided_iterator(vec.begin(), 3);
/// auto strided_iterator_end = make_strided_iterator_end(vec.begin(), vec.end(), 3);
///
/// // copy every 3rd element to result
/// boost::compute::copy(
///         strided_iterator_begin,
///         strided_iterator_end,
///         result.begin(),
///         queue
/// );
/// \endcode
template<class Iterator>
strided_iterator<Iterator>
make_strided_iterator_end(Iterator first,
                          Iterator last,
                          typename std::iterator_traits<Iterator>::difference_type stride)
{
    typedef typename std::iterator_traits<Iterator>::difference_type difference_type;

    // calculate distance from end to the last element that would be
    // accessible through strided_iterator.
    difference_type range = std::distance(first, last);
    difference_type d = (range - 1) / stride;
    d *= stride;
    d -= range;
    // advance from end to the element that would follow the last
    // accessible element
    Iterator end_for_strided_iterator = last;
    std::advance(end_for_strided_iterator, d + stride);
    return strided_iterator<Iterator>(end_for_strided_iterator, stride);
}

/// \internal_ (is_device_iterator specialization for strided_iterator)
template<class Iterator>
struct is_device_iterator<strided_iterator<Iterator> > : boost::true_type {};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_STRIDED_ITERATOR_HPP

/* strided_iterator.hpp
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
*/