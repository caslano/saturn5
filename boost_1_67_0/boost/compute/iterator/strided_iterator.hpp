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