//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ITERATOR_PERMUTATION_ITERATOR_HPP
#define BOOST_COMPUTE_ITERATOR_PERMUTATION_ITERATOR_HPP

#include <string>
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

namespace boost {
namespace compute {

// forward declaration for transform_iterator
template<class ElementIterator, class IndexIterator>
class permutation_iterator;

namespace detail {

// helper class which defines the iterator_adaptor super-class
// type for permutation_iterator
template<class ElementIterator, class IndexIterator>
class permutation_iterator_base
{
public:
    typedef ::boost::iterator_adaptor<
        ::boost::compute::permutation_iterator<ElementIterator, IndexIterator>,
        ElementIterator
    > type;
};

template<class ElementIterator, class IndexIterator, class IndexExpr>
struct permutation_iterator_access_expr
{
    typedef typename std::iterator_traits<ElementIterator>::value_type result_type;

    permutation_iterator_access_expr(const ElementIterator &e,
                                     const IndexIterator &i,
                                     const IndexExpr &expr)
        : m_element_iter(e),
          m_index_iter(i),
          m_expr(expr)
    {
    }

    const ElementIterator m_element_iter;
    const IndexIterator m_index_iter;
    const IndexExpr m_expr;
};

template<class ElementIterator, class IndexIterator, class IndexExpr>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const permutation_iterator_access_expr<ElementIterator,
                                                                      IndexIterator,
                                                                      IndexExpr> &expr)
{
    return kernel << expr.m_element_iter[expr.m_index_iter[expr.m_expr]];
}

} // end detail namespace

/// \class permutation_iterator
/// \brief The permutation_iterator class provides a permuation iterator
///
/// A permutation iterator iterates over a value range and an index range. When
/// dereferenced, it returns the value from the value range using the current
/// index from the index range.
///
/// For example, to reverse a range using the copy() algorithm and a permutation
/// sequence:
///
/// \snippet test/test_permutation_iterator.cpp reverse_range
///
/// \see make_permutation_iterator()
template<class ElementIterator, class IndexIterator>
class permutation_iterator
    : public detail::permutation_iterator_base<ElementIterator,
                                               IndexIterator>::type
{
public:
    typedef typename
        detail::permutation_iterator_base<ElementIterator,
                                          IndexIterator>::type super_type;
    typedef typename super_type::value_type value_type;
    typedef typename super_type::reference reference;
    typedef typename super_type::base_type base_type;
    typedef typename super_type::difference_type difference_type;
    typedef IndexIterator index_iterator;

    permutation_iterator(ElementIterator e, IndexIterator i)
        : super_type(e),
          m_map(i)
    {
    }

    permutation_iterator(const permutation_iterator<ElementIterator,
                                                    IndexIterator> &other)
        : super_type(other),
          m_map(other.m_map)
    {
    }

    permutation_iterator<ElementIterator, IndexIterator>&
    operator=(const permutation_iterator<ElementIterator,
                                         IndexIterator> &other)
    {
        if(this != &other){
            super_type::operator=(other);
            m_map = other.m_map;
        }

        return *this;
    }

    ~permutation_iterator()
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

    template<class IndexExpr>
    detail::permutation_iterator_access_expr<ElementIterator,
                                             IndexIterator,
                                             IndexExpr>
    operator[](const IndexExpr &expr) const
    {
        return detail::permutation_iterator_access_expr<ElementIterator,
                                                        IndexIterator,
                                                        IndexExpr>(super_type::base(),
                                                                   m_map,
                                                                   expr);
    }

private:
    friend class ::boost::iterator_core_access;

    reference dereference() const
    {
        return reference();
    }

private:
    IndexIterator m_map;
};

/// Returns a permutation_iterator for \p e using indices from \p i.
///
/// \param e the element range iterator
/// \param i the index range iterator
///
/// \return a \c permutation_iterator for \p e using \p i
template<class ElementIterator, class IndexIterator>
inline permutation_iterator<ElementIterator, IndexIterator>
make_permutation_iterator(ElementIterator e, IndexIterator i)
{
    return permutation_iterator<ElementIterator, IndexIterator>(e, i);
}

/// \internal_ (is_device_iterator specialization for permutation_iterator)
template<class ElementIterator, class IndexIterator>
struct is_device_iterator<
    permutation_iterator<ElementIterator, IndexIterator> > : boost::true_type {};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_PERMUTATION_ITERATOR_HPP

/* permutation_iterator.hpp
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
*/