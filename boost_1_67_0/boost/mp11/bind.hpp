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