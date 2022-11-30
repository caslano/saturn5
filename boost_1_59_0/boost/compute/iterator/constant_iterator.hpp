//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ITERATOR_CONSTANT_ITERATOR_HPP
#define BOOST_COMPUTE_ITERATOR_CONSTANT_ITERATOR_HPP

#include <string>
#include <cstddef>
#include <iterator>

#include <boost/config.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

// forward declaration for constant_iterator<T>
template<class T> class constant_iterator;

namespace detail {

// helper class which defines the iterator_facade super-class
// type for constant_iterator<T>
template<class T>
class constant_iterator_base
{
public:
    typedef ::boost::iterator_facade<
        ::boost::compute::constant_iterator<T>,
        T,
        ::std::random_access_iterator_tag
    > type;
};

} // end detail namespace

/// \class constant_iterator
/// \brief An iterator with a constant value.
///
/// The constant_iterator class provides an iterator which returns a constant
/// value when dereferenced.
///
/// For example, this could be used to implement the fill() algorithm in terms
/// of the copy() algorithm by copying from a range of constant iterators:
///
/// \snippet test/test_constant_iterator.cpp fill_with_copy
///
/// \see make_constant_iterator()
template<class T>
class constant_iterator : public detail::constant_iterator_base<T>::type
{
public:
    typedef typename detail::constant_iterator_base<T>::type super_type;
    typedef typename super_type::reference reference;
    typedef typename super_type::difference_type difference_type;

    constant_iterator(const T &value, size_t index = 0)
        : m_value(value),
          m_index(index)
    {
    }

    constant_iterator(const constant_iterator<T> &other)
        : m_value(other.m_value),
          m_index(other.m_index)
    {
    }

    constant_iterator<T>& operator=(const constant_iterator<T> &other)
    {
        if(this != &other){
            m_value = other.m_value;
            m_index = other.m_index;
        }

        return *this;
    }

    ~constant_iterator()
    {
    }

    size_t get_index() const
    {
        return m_index;
    }

    /// \internal_
    template<class Expr>
    detail::meta_kernel_literal<T> operator[](const Expr &expr) const
    {
        (void) expr;

        return detail::meta_kernel::make_lit<T>(m_value);
    }

private:
    friend class ::boost::iterator_core_access;

    /// \internal_
    reference dereference() const
    {
        return m_value;
    }

    /// \internal_
    bool equal(const constant_iterator<T> &other) const
    {
        return m_value == other.m_value && m_index == other.m_index;
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
    difference_type distance_to(const constant_iterator<T> &other) const
    {
        return static_cast<difference_type>(other.m_index - m_index);
    }

private:
    T m_value;
    size_t m_index;
};

/// Returns a new constant_iterator with \p value at \p index.
///
/// \param value the constant value
/// \param index the iterators index
///
/// \return a \c constant_iterator with \p value
template<class T>
inline constant_iterator<T>
make_constant_iterator(const T &value, size_t index = 0)
{
    return constant_iterator<T>(value, index);
}

/// \internal_ (is_device_iterator specialization for constant_iterator)
template<class T>
struct is_device_iterator<constant_iterator<T> > : boost::true_type {};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_CONSTANT_ITERATOR_HPP

/* constant_iterator.hpp
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
*/