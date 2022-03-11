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