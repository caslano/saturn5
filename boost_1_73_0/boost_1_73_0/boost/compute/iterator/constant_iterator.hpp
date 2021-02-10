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
ysyFqQIRENC8NmWUlnOfOE1W9oKhCVuV0CT+GgXBYmUP3TQoPVF6EvXiMMZujuYAyZHo4Wm1vYvbbsa8gx6UiavJGEJhAG3nJUgOTVVQNJKurrCzGCyQIhC8R0wbTUYQhQORib/5p9/8dhgBg69HXyl83uZBFpaPzUh94nuayWHJf8yKNHucbpfHu9c68nndFc6KRtE+H2FEkouJA5xnOR2GO0r26+NtVb3LH8ffhwWsDh3apuInfJQv2jeYjuFpjPePxaY8Sy+VPE2m1giFOzxozsA4q75Ft2i53DJpgI4rkefClusri3vxGs4mBOsu4OA7i3YmXsavGUThCoy7Xf1z/QrU1GuF6mq+p4O0mqrwpidrbbVRigFCjNqGX+FUVGHPLUmNUQ9GYRYD3WVcXJUhSpWoc7lQUWOAQU2sca96uAqfhPNkqeaP7zAtgYHwmw/wbzct735iXqYneof8a/x+WPwaD+zSFTjSs9Ozl5doAIC69i4PPvrgk9NXF8evLs53pQMfOH719OCXTsHFwufOIhMSf7c57EiHe1/B/bep5GLi1mx+qdCAxahCAwv5R8oLjERxYR8iH3kZNZNkaELfps3WRqPNKBvX4VDrsZtMaAxiiaqeXG2tI2rmjPl4FI5oq74saQkVay6T
*/