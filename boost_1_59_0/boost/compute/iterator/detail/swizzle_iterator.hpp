//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ITERATOR_DETAIL_SWIZZLE_ITERATOR_HPP
#define BOOST_COMPUTE_ITERATOR_DETAIL_SWIZZLE_ITERATOR_HPP

#include <string>
#include <cstddef>
#include <iterator>

#include <boost/config.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

#include <boost/compute/functional.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/type_traits/make_vector_type.hpp>
#include <boost/compute/detail/is_buffer_iterator.hpp>
#include <boost/compute/detail/read_write_single_value.hpp>
#include <boost/compute/iterator/detail/get_base_iterator_buffer.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

// forward declaration for swizzle_iterator
template<class InputIterator, size_t Size>
class swizzle_iterator;

// meta-function returing the value_type for a swizzle_iterator
template<class InputIterator, size_t Size>
struct make_swizzle_iterator_value_type
{
    typedef
        typename make_vector_type<
            typename scalar_type<
                typename std::iterator_traits<InputIterator>::value_type
            >::type,
            Size
        >::type type;
};

// helper class which defines the iterator_adaptor super-class
// type for swizzle_iterator
template<class InputIterator, size_t Size>
class swizzle_iterator_base
{
public:
    typedef ::boost::iterator_adaptor<
        swizzle_iterator<InputIterator, Size>,
        InputIterator,
        typename make_swizzle_iterator_value_type<InputIterator, Size>::type,
        typename std::iterator_traits<InputIterator>::iterator_category,
        typename make_swizzle_iterator_value_type<InputIterator, Size>::type
    > type;
};

template<class InputIterator, size_t Size, class IndexExpr>
struct swizzle_iterator_index_expr
{
    typedef typename make_swizzle_iterator_value_type<InputIterator, Size>::type result_type;

    swizzle_iterator_index_expr(const InputIterator &input_iter,
                                const IndexExpr &index_expr,
                                const std::string &components)
        : m_input_iter(input_iter),
          m_index_expr(index_expr),
          m_components(components)
    {
    }

    InputIterator m_input_iter;
    IndexExpr m_index_expr;
    std::string m_components;
};

template<class InputIterator, size_t Size, class IndexExpr>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const swizzle_iterator_index_expr<InputIterator,
                                                                 Size,
                                                                 IndexExpr> &expr)
{
    return kernel << expr.m_input_iter[expr.m_index_expr]
                  << "." << expr.m_components;
}

template<class InputIterator, size_t Size>
class swizzle_iterator :
    public swizzle_iterator_base<InputIterator, Size>::type
{
public:
    typedef typename
        swizzle_iterator_base<InputIterator, Size>::type
        super_type;
    typedef typename super_type::value_type value_type;
    typedef typename super_type::reference reference;
    typedef typename super_type::base_type base_type;
    typedef typename super_type::difference_type difference_type;

    BOOST_STATIC_CONSTANT(size_t, vector_size = Size);

    swizzle_iterator(InputIterator iterator, const std::string &components)
        : super_type(iterator),
          m_components(components)
    {
        BOOST_ASSERT(components.size() == Size);
    }

    swizzle_iterator(const swizzle_iterator<InputIterator, Size> &other)
        : super_type(other.base()),
          m_components(other.m_components)
    {
        BOOST_ASSERT(m_components.size() == Size);
    }

    swizzle_iterator<InputIterator, Size>&
    operator=(const swizzle_iterator<InputIterator, Size> &other)
    {
        if(this != &other){
            super_type::operator=(other);

            m_components = other.m_components;
        }

        return *this;
    }

    ~swizzle_iterator()
    {
    }

    size_t get_index() const
    {
        return super_type::base().get_index();
    }

    const buffer& get_buffer() const
    {
        return get_base_iterator_buffer(*this);
    }

    template<class IndexExpression>
    swizzle_iterator_index_expr<InputIterator, Size, IndexExpression>
    operator[](const IndexExpression &expr) const
    {
        return swizzle_iterator_index_expr<InputIterator,
                                           Size,
                                           IndexExpression>(super_type::base(),
                                                            expr,
                                                            m_components);
    }

private:
    friend class ::boost::iterator_core_access;

    reference dereference() const
    {
        return reference();
    }

private:
    std::string m_components;
};

template<size_t Size, class InputIterator>
inline swizzle_iterator<InputIterator, Size>
make_swizzle_iterator(InputIterator iterator, const std::string &components)
{
    return swizzle_iterator<InputIterator, Size>(iterator, components);
}

} // end detail namespace

// is_device_iterator specialization for swizzle_iterator
template<size_t Size, class InputIterator>
struct is_device_iterator<detail::swizzle_iterator<InputIterator, Size> > : boost::true_type {};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_SWIZZLE_ITERATOR_HPP

/* swizzle_iterator.hpp
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
*/