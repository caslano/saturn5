//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ITERATOR_COUNTING_ITERATOR_HPP
#define BOOST_COMPUTE_ITERATOR_COUNTING_ITERATOR_HPP

#include <string>
#include <cstddef>
#include <iterator>

#include <boost/config.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

// forward declaration for counting_iterator<T>
template<class T> class counting_iterator;

namespace detail {

// helper class which defines the iterator_facade super-class
// type for counting_iterator<T>
template<class T>
class counting_iterator_base
{
public:
    typedef ::boost::iterator_facade<
        ::boost::compute::counting_iterator<T>,
        T,
        ::std::random_access_iterator_tag
    > type;
};

template<class T, class IndexExpr>
struct counting_iterator_index_expr
{
    typedef T result_type;

    counting_iterator_index_expr(const T init, const IndexExpr &expr)
        : m_init(init),
          m_expr(expr)
    {
    }

    const T m_init;
    const IndexExpr m_expr;
};

template<class T, class IndexExpr>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const counting_iterator_index_expr<T, IndexExpr> &expr)
{
    return kernel << '(' << expr.m_init << '+' << expr.m_expr << ')';
}

} // end detail namespace

/// \class counting_iterator
/// \brief The counting_iterator class implements a counting iterator.
///
/// A counting iterator returns an internal value (initialized with \p init)
/// which is incremented each time the iterator is incremented.
///
/// For example, this could be used to implement the iota() algorithm in terms
/// of the copy() algorithm by copying from a range of counting iterators:
///
/// \snippet test/test_counting_iterator.cpp iota_with_copy
///
/// \see make_counting_iterator()
template<class T>
class counting_iterator : public detail::counting_iterator_base<T>::type
{
public:
    typedef typename detail::counting_iterator_base<T>::type super_type;
    typedef typename super_type::reference reference;
    typedef typename super_type::difference_type difference_type;

    counting_iterator(const T &init)
        : m_init(init)
    {
    }

    counting_iterator(const counting_iterator<T> &other)
        : m_init(other.m_init)
    {
    }

    counting_iterator<T>& operator=(const counting_iterator<T> &other)
    {
        if(this != &other){
            m_init = other.m_init;
        }

        return *this;
    }

    ~counting_iterator()
    {
    }

    size_t get_index() const
    {
        return 0;
    }

    template<class Expr>
    detail::counting_iterator_index_expr<T, Expr>
    operator[](const Expr &expr) const
    {
        return detail::counting_iterator_index_expr<T, Expr>(m_init, expr);
    }

private:
    friend class ::boost::iterator_core_access;

    reference dereference() const
    {
        return m_init;
    }

    bool equal(const counting_iterator<T> &other) const
    {
        return m_init == other.m_init;
    }

    void increment()
    {
        m_init++;
    }

    void decrement()
    {
        m_init--;
    }

    void advance(difference_type n)
    {
        m_init += static_cast<T>(n);
    }

    difference_type distance_to(const counting_iterator<T> &other) const
    {
        return difference_type(other.m_init) - difference_type(m_init);
    }

private:
    T m_init;
};

/// Returns a new counting_iterator starting at \p init.
///
/// \param init the initial value
///
/// \return a counting_iterator with \p init.
///
/// For example, to create a counting iterator which returns unsigned integers
/// and increments from one:
/// \code
/// auto iter = make_counting_iterator<uint_>(1);
/// \endcode
template<class T>
inline counting_iterator<T> make_counting_iterator(const T &init)
{
    return counting_iterator<T>(init);
}

/// \internal_ (is_device_iterator specialization for counting_iterator)
template<class T>
struct is_device_iterator<counting_iterator<T> > : boost::true_type {};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_COUNTING_ITERATOR_HPP

/* counting_iterator.hpp
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
*/