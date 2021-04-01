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
vM7qsX/yiqfKqXLygo/InB9xz0h8XVhRTYxHn6kVDIr1Y5oYG4uq5EqyRWpcG0C+23IbxpqR0mHcCkF/M+OHumZxWSzumkxZpaMuTbSm87kOZziahV4xu7wwOmnT0VHP51rYTIvzKNz99eCT87aIuVp+jJrMbir59lTIyA2e6w52q/40pMRHpia0S23FAjnFpzPGyllraRl9eXbCzU1+Ps4AK83KQrdlxZWUCJeWK5VVDaGxBd1Qjcv1okAwx1fB6r8tSayHvmrki3h/GRb312YASntfIDBAzVVirkj3nJdoaaZDDB146VdbMpbNg9KC2Dtb8jWMhyCMQupfYD0LwuXoQZ4eZX6/QyzuGTr8stOGeqWxpKBvPX81GlppJ3R5F7Y1UZltXIUVaWQKu4UOnCEB4nTCOUrGpOYwu5DCDeczenfMpTIzZAAem+KPSgUsR8x/KLkfEGUZkQFvkyQjbugjuIx+fC0Pke3oddC8rJxjSo7LzLpWILpBob5bArheVt2HfrhtW3EsoJx+cqesx9WDLd4w9vX+4u51/hk+Dprs/UavZoQF0V7LiQ==
*/