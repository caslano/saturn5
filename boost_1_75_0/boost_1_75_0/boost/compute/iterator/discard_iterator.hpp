//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ITERATOR_DISCARD_ITERATOR_HPP
#define BOOST_COMPUTE_ITERATOR_DISCARD_ITERATOR_HPP

#include <string>
#include <cstddef>
#include <iterator>

#include <boost/config.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

// forward declaration for discard_iterator
class discard_iterator;

namespace detail {

// helper class which defines the iterator_facade super-class
// type for discard_iterator
struct discard_iterator_base
{
    typedef ::boost::iterator_facade<
        ::boost::compute::discard_iterator,
        void,
        ::std::random_access_iterator_tag,
        void *
    > type;
};

template<class IndexExpr>
struct discard_iterator_index_expr
{
    typedef void result_type;

    discard_iterator_index_expr(const IndexExpr &expr)
        : m_expr(expr)
    {
    }

    IndexExpr m_expr;
};

template<class IndexExpr>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const discard_iterator_index_expr<IndexExpr> &expr)
{
    (void) expr;

    return kernel;
}

} // end detail namespace

/// \class discard_iterator
/// \brief An iterator which discards all values written to it.
///
/// \see make_discard_iterator(), constant_iterator
class discard_iterator : public detail::discard_iterator_base::type
{
public:
    typedef detail::discard_iterator_base::type super_type;
    typedef super_type::reference reference;
    typedef super_type::difference_type difference_type;

    discard_iterator(size_t index = 0)
        : m_index(index)
    {
    }

    discard_iterator(const discard_iterator &other)
        : m_index(other.m_index)
    {
    }

    discard_iterator& operator=(const discard_iterator &other)
    {
        if(this != &other){
            m_index = other.m_index;
        }

        return *this;
    }

    ~discard_iterator()
    {
    }

    /// \internal_
    template<class Expr>
    detail::discard_iterator_index_expr<Expr>
    operator[](const Expr &expr) const
    {
        return detail::discard_iterator_index_expr<Expr>(expr);
    }

private:
    friend class ::boost::iterator_core_access;

    /// \internal_
    reference dereference() const
    {
        return 0;
    }

    /// \internal_
    bool equal(const discard_iterator &other) const
    {
        return m_index == other.m_index;
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
    difference_type distance_to(const discard_iterator &other) const
    {
        return static_cast<difference_type>(other.m_index - m_index);
    }

private:
    size_t m_index;
};

/// Returns a new discard_iterator with \p index.
///
/// \param index the index of the iterator
///
/// \return a \c discard_iterator at \p index
inline discard_iterator make_discard_iterator(size_t index = 0)
{
    return discard_iterator(index);
}

/// internal_ (is_device_iterator specialization for discard_iterator)
template<>
struct is_device_iterator<discard_iterator> : boost::true_type {};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_DISCARD_ITERATOR_HPP

/* discard_iterator.hpp
SZcRvONsCkq58TS95GV8sOUaNLs2O+WP6q+VdjgSmnnyyZjGBvqmz6Uq1cHSf6T4cchcJZuZdMZI5KvcfGRiDi98XbfxdSaTBrQQc/+YI6khET0GsWmxqijUe2VqSyiwTgK49C4Fekl/sL6keDnuQrh4Xv91lZFjcJtQAGgxDOGh7dIGnDMY2Z4A5HMZwoAkG7Gbh+Gr/334Sb2n8SgAqL+yDJl1gqhvE/8+bGzUwryi3d7t/CiRwTlg5Dz63/mBFJ7codPUd4jVVUeCq+zW1ysyStwmNadwdl5njf89AoDaetTojVjkekOhLb1d8IF8CYSwKfQ7cOplKcOhbMz8ucS/b3CjMR7vai9GCZJ66a3Hk3V/a4Rl0AAMaSdzwiCydbvrITl7aCHnkhGLJFycyutUC5SyEz3XpLN+TzGKw+VVQMl6T2spuLZ62dDvCmeHpa30SafhbuCif280DOWWYE6pmxBRHetZEPiwmxgVXHF8Gz/N8706TzbYUQaTXXRkkO3mLS8kf9pPZa7kNy0ahMByrtak5N751p8tHcfAcehHKM+oFRXvqkjc6vKRCzGm9M4t/gOWl3Q/6OJUkehzpYw4XyzvE9cOfyYEtSSE2YKJabtZA2FlJ3hL6TilRmoKt7F0dR5HuYYW3l1saqo79CEzeHMuR7WeDy1mbHJ2j1Rk9/2VDqzf0gjnwjPBVvynqi5rsFWZYlGpCce0
*/