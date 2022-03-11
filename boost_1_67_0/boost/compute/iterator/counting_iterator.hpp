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