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