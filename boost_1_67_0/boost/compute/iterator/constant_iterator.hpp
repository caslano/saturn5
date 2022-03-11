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