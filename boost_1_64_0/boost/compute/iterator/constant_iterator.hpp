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
8HoC9Pw+oPe+Kbj7fXW6fPcA3suSpgxMeE/X0i/dH/TWyKa10/ceALppoCIa9vxvMNZVL3UiP88c1nNNiTXj5TrPsZCXcVi5AcPNop3v/806frKqAiohcNWJ3Mrzcb2OnSrczImDnDVOQOY69zkd+yCfVjkvj11lHaqhwF7QsQ+OgjxPXD9isBgb+ZcMuUXq8TAPc7VuWXJ/amA594PUSQO1Zln+Cpetti5TNyrSSjdjK45W/pi+Rh31ci/wXR7Kk2AndtZBiYX8yk05tUmgX6N25E9JHrRhmsRBESYqLJWV44WZdUmKqCiKiBk2R+xbdGzJUmHKLvyc9dm7Gp6TOg9nobBSJqXLTM9Qc3+0Zn6zxyPfKaqA9ZhW8M3ndJ7JtMjSouIx0y9o8M0v1LEPTiuniMocVowaDTunwuIs7NJ4iHnBOoEyrT3/G81zsOeKbX/EjHA81l3V58zvjuM8S0ovYNpTsOa7sb/6lrHfyRMelTxymFq0hh3f6EtmGZHPeRlUHBNda9u74+5H8SDGXpQXaR75zA5Epjix/36TrlOSJCzKIPeYyHiq26SPN/g76/hcmHvCyElLyTCYF1YWs40ndDxnVI0kTQhgmsDNvOWxdQZM0zIsEp//v2dAcZ59zx1prL5SyIPx+ikzG7RXI9ppWvtPvaqmQRM0APpHYL5yhPSHwmA2axjIeY3CYMYAJuuxdWuSIzB4WT67uaXiyT2E+O/8Wo2myb+nor9c0jsDGsi7KtzY62ocRmOPrDVg9IEBIGRdlDijpxoU9qD7tokDv17evHpnp/ZFNl2tw3iHt92mmzFOP2DT1Ts25EPZIel2u8haIB7LCIy9v8l39uJkjZDrZQSGagXM0V0SY7evbBjEeOrFmPughd29GNlA8H/uxcjqAJPvEZg+h7Oxth9vKDDaPLD70abb/Xgji273o023+3GvoJtjTVUBmA/0YJpOxFvSG3cxoirYy/fQ7Xw1B2+iMKQvVB1A+6hGU2XDxzK+qUajMsGj/W6Xdft9oJ3gdWGgfUCnWfvXh9GfoKm2Bp9Os9p5335BM/WU3c7X92DsdmY372L0dv5oD11VBWPi7reoMRiOGHNKhk23xlx+S4tujbnzJh0VwBn8VoJOjvv6Q26tHe5+a9Dt+Q7MwQPAWHNQK+c2DUYb/3o5twXdGJc4XwrM7foxyg249fUfhTuzhvHxqdsDI8ek3mYfv4NJU/LB+7w7mnRdbn4ng3aCa3L9O1s0y395710sOgk27gZAN8cU6i4wdwVGV3Htvczdeuh1PYB58937MLIuKGfhHgKzeHh+xLiZuCfoI8fN2L2AGTluvghM/7h59UHQR46bU/cG5qrjZuI+wI0cN2P3BaYzbj4FWv+4ecn9TLoud/r+oHXGzYEHgNY7bi6C3j9urn8g6CPHzcYEML3j5mGHQB85bvYcBsYeN9DZX5OYjaF0fqzDfWCtf+FRjWbFfEQ8dC1XtUye6ql3GidwRQnsC8dbbD6YfeqgBwtbooZNVghG9xnPsBmclfkTa4srnnwKpeV21Xh98UysW9DqPRvfNCt/9ub6OpmgphdEao5kfmz1js1dhIabXho6IlOWmHYN/YMmnUQ9SsWpVec6k35C0WF/Om/SQ7GolM155ZX62SNjgV+kvptee/4V+hqmYkN9gs4OeUJjIaB0xY+pc7J8in7jx6fzGe94Mp14Tk6KwZsWr5b8wH1kJPMbfGYURsWXFmrOO/4YPl3NTMciL/JMXhGKaDVvzm3GUXyJ38Sx2t/SqtIL2hiFIrD8uMHVRNOgmy3EqEQOZgsrfdhn1wfibRdkPmxbFyefCNYDQmJxJz8Ca5f9+O1dHL3mAJA=
*/