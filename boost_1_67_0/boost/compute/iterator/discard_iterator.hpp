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