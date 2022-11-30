#ifndef BOOST_MP11_BIND_HPP_INCLUDED
#define BOOST_MP11_BIND_HPP_INCLUDED

//  Copyright 2017, 2018 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/utility.hpp>
#include <cstddef>

namespace boost
{
namespace mp11
{

// mp_bind_front
template<template<class...> class F, class... T> struct mp_bind_front
{
    // the indirection through mp_defer works around the language inability
    // to expand U... into a fixed parameter list of an alias template

    template<class... U> using fn = typename mp_defer<F, T..., U...>::type;
};

template<class Q, class... T> using mp_bind_front_q = mp_bind_front<Q::template fn, T...>;

// mp_bind_back
template<template<class...> class F, class... T> struct mp_bind_back
{
    template<class... U> using fn = typename mp_defer<F, U..., T...>::type;
};

template<class Q, class... T> using mp_bind_back_q = mp_bind_back<Q::template fn, T...>;

// mp_arg
template<std::size_t I> struct mp_arg
{
    template<class... T> using fn = mp_at_c<mp_list<T...>, I>;
};

using _1 = mp_arg<0>;
using _2 = mp_arg<1>;
using _3 = mp_arg<2>;
using _4 = mp_arg<3>;
using _5 = mp_arg<4>;
using _6 = mp_arg<5>;
using _7 = mp_arg<6>;
using _8 = mp_arg<7>;
using _9 = mp_arg<8>;

// mp_bind
template<template<class...> class F, class... T> struct mp_bind;

namespace detail
{

template<class V, class... T> struct eval_bound_arg
{
    using type = V;
};

template<std::size_t I, class... T> struct eval_bound_arg<mp_arg<I>, T...>
{
    using type = typename mp_arg<I>::template fn<T...>;
};

template<template<class...> class F, class... U, class... T> struct eval_bound_arg<mp_bind<F, U...>, T...>
{
    using type = typename mp_bind<F, U...>::template fn<T...>;
};

template<template<class...> class F, class... U, class... T> struct eval_bound_arg<mp_bind_front<F, U...>, T...>
{
    using type = typename mp_bind_front<F, U...>::template fn<T...>;
};

template<template<class...> class F, class... U, class... T> struct eval_bound_arg<mp_bind_back<F, U...>, T...>
{
    using type = typename mp_bind_back<F, U...>::template fn<T...>;
};

} // namespace detail

template<template<class...> class F, class... T> struct mp_bind
{
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, == 1915 )
private:

    template<class... U> struct _f { using type = F<typename detail::eval_bound_arg<T, U...>::type...>; };

public:

    template<class... U> using fn = typename _f<U...>::type;

#else

    template<class... U> using fn = F<typename detail::eval_bound_arg<T, U...>::type...>;

#endif
};

template<class Q, class... T> using mp_bind_q = mp_bind<Q::template fn, T...>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_BIND_HPP_INCLUDED

/* bind.hpp
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
*/