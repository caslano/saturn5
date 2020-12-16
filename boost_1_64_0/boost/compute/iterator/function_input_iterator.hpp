//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ITERATOR_FUNCTION_INPUT_ITERATOR_HPP
#define BOOST_COMPUTE_ITERATOR_FUNCTION_INPUT_ITERATOR_HPP

#include <cstddef>
#include <iterator>

#include <boost/config.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>
#include <boost/compute/type_traits/result_of.hpp>

namespace boost {
namespace compute {

// forward declaration for function_input_iterator<Function>
template<class Function> class function_input_iterator;

namespace detail {

// helper class which defines the iterator_facade super-class
// type for function_input_iterator<Function>
template<class Function>
class function_input_iterator_base
{
public:
    typedef ::boost::iterator_facade<
        ::boost::compute::function_input_iterator<Function>,
        typename ::boost::compute::result_of<Function()>::type,
        ::std::random_access_iterator_tag,
        typename ::boost::compute::result_of<Function()>::type
    > type;
};

template<class Function>
struct function_input_iterator_expr
{
    typedef typename ::boost::compute::result_of<Function()>::type result_type;

    function_input_iterator_expr(const Function &function)
        : m_function(function)
    {
    }

    const Function m_function;
};

template<class Function>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const function_input_iterator_expr<Function> &expr)
{
    return kernel << expr.m_function();
}

} // end detail namespace

/// \class function_input_iterator
/// \brief Iterator which returns the result of a function when dereferenced
///
/// For example:
///
/// \snippet test/test_function_input_iterator.cpp generate_42
///
/// \see make_function_input_iterator()
template<class Function>
class function_input_iterator :
    public detail::function_input_iterator_base<Function>::type
{
public:
    typedef typename detail::function_input_iterator_base<Function>::type super_type;
    typedef typename super_type::reference reference;
    typedef typename super_type::difference_type difference_type;
    typedef Function function;

    function_input_iterator(const Function &function, size_t index = 0)
        : m_function(function),
          m_index(index)
    {
    }

    function_input_iterator(const function_input_iterator<Function> &other)
        : m_function(other.m_function),
          m_index(other.m_index)
    {
    }

    function_input_iterator<Function>&
    operator=(const function_input_iterator<Function> &other)
    {
        if(this != &other){
            m_function = other.m_function;
            m_index = other.m_index;
        }

        return *this;
    }

    ~function_input_iterator()
    {
    }

    size_t get_index() const
    {
        return m_index;
    }

    template<class Expr>
    detail::function_input_iterator_expr<Function>
    operator[](const Expr &expr) const
    {
        (void) expr;

        return detail::function_input_iterator_expr<Function>(m_function);
    }

private:
    friend class ::boost::iterator_core_access;

    reference dereference() const
    {
        return reference();
    }

    bool equal(const function_input_iterator<Function> &other) const
    {
        return m_function == other.m_function && m_index == other.m_index;
    }

    void increment()
    {
        m_index++;
    }

    void decrement()
    {
        m_index--;
    }

    void advance(difference_type n)
    {
        m_index = static_cast<size_t>(static_cast<difference_type>(m_index) + n);
    }

    difference_type
    distance_to(const function_input_iterator<Function> &other) const
    {
        return static_cast<difference_type>(other.m_index - m_index);
    }

private:
    Function m_function;
    size_t m_index;
};

/// Returns a function_input_iterator with \p function.
///
/// \param function function to execute when dereferenced
/// \param index index of the iterator
///
/// \return a \c function_input_iterator with \p function
template<class Function>
inline function_input_iterator<Function>
make_function_input_iterator(const Function &function, size_t index = 0)
{
    return function_input_iterator<Function>(function, index);
}

/// \internal_ (is_device_iterator specialization for function_input_iterator)
template<class Function>
struct is_device_iterator<function_input_iterator<Function> > : boost::true_type {};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_FUNCTION_INPUT_ITERATOR_HPP

/* function_input_iterator.hpp
RiJOhNXguslgfXHuusnHrDJlJ9gmnfF2jo3Xd48b8mw6HAuR4/upVt7KXDjS+P/3/pzedchz6cXniasr+rU+KMysEp9cffQ3zvTvL0T/qx5Xn4W2nBoXdCHj9NLiihwg1GhPNexRV7Z1MIsKgj7LdzQY+nDgWvr5nQ1d1vIMKYfhgjY3N3bpdFN37Nit0+S9Je0P2r5+/I0Muop2A/0F3KWb9uGgx4C7xS1N3CZ9zhzEmXqni4M4jLHrN81+953cSeLsmmNhqH437pp+Pl73ZxGFh/Rz2IXtRBuhSyon4LpuePXOq2Obgw98CG8IvKVLIB2yv7X3alhIRx9/6paE79E7yON1K9BH6pW1WwPTqzf+BfpovXHpADB9egPv7U5tGrEPeJQHvuOwUgYHo89WG8txnPOsMeCKYHZR8X+f826r5j7H3Cc7q5r1WKfp35/Jtidaz1xbGDfoi/qdJFVS0SB3dX5Mm2sGffRc27FDx42eax/YqeNGz7Xp3Tpu9Fw7aLVzXpRZnJf/90Ku+xf+tDNHxLFPe9OxzcYguvXAuJ/ZMOvGg9R3w/L/vvfQ9cBPRLmym4R9GzTyBddpcheK+vJtBo0U9sTM7NqavELW7zkudXEqIoHmD7vdxpDvDFS08b7PxmFcwt+og1EJcLX17GE7OxgSo8Xs6NCx19RictgYVBiYKx2MHMNiZALz8t39GBqVwBzcY2PE2JVigPl4L0aKwXfzG9iYeo8MH9YOHftkjImtGxoY6YOEeBY3MmjDUWNiba+NO9QZE6+/sYkZNSY2bmLjumPCv6mN6Y6JvftMjD0mvmbR+8bEu29mY7pjYmO/jemOifjmNqY7Jm5/CxvTHRO/sTB9Y+LjtzQx9ph43q06dIwJ3MVumOeeMnXCIPbS/1cniffPuw7S/c4PxLrU2ISbsomuvUP4saiTPNauozNvBb2l6PD5wfsB9btUQ3PrG7VVWvAix/R2HYPANKDP7zDoZ2bnyDVg2M4Pf6dBpzHSjul8F2itzRvLo5aPycANtpoJBHvMbp0Ofny/v0fRrTeO79Z/7yl34oYNfShc5xc3ni6v39o50NJHth/fC0xv+zzrxqB32udbNwHtqu2zdlPg9PZBGUv7QMdUx/tL+hO0HtkL+xv6xmDYMGuy737zhk4XAOsD4/x/zpoHflEFVRhesx91377hR6Is29Sn++FtI4w8P6hwcFBL7ZuuAwtW3oKIO1GYJwzhDjvxIbcjZoPOW7C08nNelVEdCHlgRC5ccBUPW7DizqZBUnh5VjOdWdySGUfpYYyIYau2aarcrzR1PmXVuSzS0PXzQgVuFn+cfroIRyrzcZn3vPsubtNjeZRZHCV+XnNascc3EffYKC9kQVymsRcxac+WkRH1xKYTzWW5gzhoFr/HQ6eg3h8l4LAVo/KjBn/GktAvvSRldabWs9JveZ3EUNJQkViXvgQX6l95UBNbRJfBWZCXQejwUMnYWF0lptn1s42xYR45Z42yC5b7kVM4edJlnCT3AhUBdrj4jEZQI+fAohmHucwCL/OSYpQc+ozNpSbCjZ67ZdH4jspPeeZGvi6GBuvSkmKcbMrni+Z3iA6ssrDsMI74DowFQ07EgiB1krgsVPS+bvTbmv8ZYTMWrHZI0yQIktQDv6zJ6cWzqh40e42A3hgThpyEeU7AuZ9EbH557ZAqf44ieK5vDlakVKpZMy4RE9yS4cdRnMaBkPGUa5VxxZARs9KL3DzMXSZUQL8MzA/ooCeZ8VvLKii9kCbYmcV10SSrlPGZ/sfIUoM4qDqvFzBeliLgbMEoGNTg7OxST1pldYii/tHsgZd/tE0fV27spGkVaGG56/5B7NmG75w=
*/