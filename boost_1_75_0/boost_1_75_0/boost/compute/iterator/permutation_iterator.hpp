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
K27C4hpXZcaJ6slsnvrBvjJS45BF7GNXkyBcalW+XTJG7hlzh1f6X1pm+GmG3JbSqNfGWW9RxrkqElKneU2RwPXdTAR5xgw7hEwViZ/mimH4cjSeih8fS4AOsZTlWbc/R7ZIzFqvexKOuzgBjHByCiprALBSYjwLx/FPpP9whGPHv3draM3z+87wsJvn8oy3EzT2mNF81XVtgjP67SNF61RHkcGAT8h64O3vA3HJMlufGwIY2G19k0+Yz+vNarhZWzKP24CsdD1Wxwq44xGQ9pDCDs8EYO35irqqropcjCAvwyAv+zo1mpMMM7XNB4PqrjTLwzYTWd0o5sX2Rnueo/hJWaCTDVbaC2H8zGhewxFpNun/AXk51a+xvN54Ji1nmobVbTtagejvu5MIsq+ekBUteEjZ+6I+bDPQtLXqTSt0WfUq0wZFA2EwvnD3W53jo/YX6HUlLjhXG60X51uO7SXIoqL8CD/ZbCumq+yzIA075lmszO+jYRO4FqvTz8Q+vupJfS8N3L2I9pDjJrr9IG/CdtnZSN8MB06cWwdbJmsYZPbb492xnDTrSHPT/awgqKBAOTyzr8Wd6ztOSifHJd519PLcpUUOz+IzQs4CJuxYDbC0LXD2UzGyi6A41kU1qT5Y4DlqEkLXwMUJXzScjW7BmhhmS61xdodUkbCtw24W3tp5NJSvf/GecL+ts7qreoAu9z+RBo+M1VWf
*/