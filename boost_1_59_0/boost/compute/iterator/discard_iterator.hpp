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
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
*/