#ifndef BOOST_BIND_DETAIL_RESULT_TRAITS_HPP_INCLUDED
#define BOOST_BIND_DETAIL_RESULT_TRAITS_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  bind/detail/result_traits.hpp
//
//  boost/bind.hpp support header, return type deduction
//
//  Copyright 2006, 2020 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  See http://www.boost.org/libs/bind/bind.html for documentation.
//

#include <boost/config.hpp>

#if BOOST_CXX_VERSION >= 201700L
#include <functional>
#endif

namespace boost
{

namespace _bi
{

template<class R, class F> struct result_traits
{
    typedef R type;
};

struct unspecified {};

template<class F> struct result_traits<unspecified, F>
{
    typedef typename F::result_type type;
};

template<class F> struct result_traits< unspecified, reference_wrapper<F> >
{
    typedef typename F::result_type type;
};

#if BOOST_CXX_VERSION >= 201700L

template<class T> struct result_traits< unspecified, std::plus<T> >
{
    typedef T type;
};

template<class T> struct result_traits< unspecified, std::minus<T> >
{
    typedef T type;
};

template<class T> struct result_traits< unspecified, std::multiplies<T> >
{
    typedef T type;
};

template<class T> struct result_traits< unspecified, std::divides<T> >
{
    typedef T type;
};

template<class T> struct result_traits< unspecified, std::modulus<T> >
{
    typedef T type;
};

template<class T> struct result_traits< unspecified, std::negate<T> >
{
    typedef T type;
};

template<class T> struct result_traits< unspecified, std::equal_to<T> >
{
    typedef bool type;
};

template<class T> struct result_traits< unspecified, std::not_equal_to<T> >
{
    typedef bool type;
};

template<class T> struct result_traits< unspecified, std::greater<T> >
{
    typedef bool type;
};

template<class T> struct result_traits< unspecified, std::less<T> >
{
    typedef bool type;
};

template<class T> struct result_traits< unspecified, std::greater_equal<T> >
{
    typedef bool type;
};

template<class T> struct result_traits< unspecified, std::less_equal<T> >
{
    typedef bool type;
};

template<class T> struct result_traits< unspecified, std::logical_and<T> >
{
    typedef bool type;
};

template<class T> struct result_traits< unspecified, std::logical_or<T> >
{
    typedef bool type;
};

template<class T> struct result_traits< unspecified, std::logical_not<T> >
{
    typedef bool type;
};

template<class T> struct result_traits< unspecified, std::bit_and<T> >
{
    typedef T type;
};

template<class T> struct result_traits< unspecified, std::bit_or<T> >
{
    typedef T type;
};

template<class T> struct result_traits< unspecified, std::bit_xor<T> >
{
    typedef T type;
};

#if defined(BOOST_LIBSTDCXX_VERSION) && BOOST_LIBSTDCXX_VERSION < 40900

// libstdc++ 4.8 and below don't have std::bit_not

#else

template<class T> struct result_traits< unspecified, std::bit_not<T> >
{
    typedef T type;
};

#endif

#endif

} // namespace _bi

} // namespace boost

#endif // #ifndef BOOST_BIND_DETAIL_RESULT_TRAITS_HPP_INCLUDED

/* result_traits.hpp
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
*/