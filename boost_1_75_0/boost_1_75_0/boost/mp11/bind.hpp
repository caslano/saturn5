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
yspaaq3cVs3MylorKisrt8i1lszq/7vOuW5mBrFd22f12f/nuT+fM9/rnDn3eb3O6/1GcYZqx2z/0YHtH5aMaG7/0cHtf46GfsqL9hXH9/v2wvooXITvUtdAy6N5b/ZSCLfBOAK+/7We+8/AHSxZvoPKMHMdZY225duHO/L5W6BpWgqtP/VI4bRFOzrn5S7MReZhLlJ41FxkH6KTzxd9A+GU/nYxEMYR+HyeWji0jXKdaxNbqffs1d9/pe4GOJaERc+ihUN/zXqtZrvOXqJjmVCoV4oVWpz8xurQoPKzd5ZfMQKS9ypWQFje387PiR7rGyLFYUu14dap9kI9RuTbY9FnYPxw5qH/SwaTHOr5XwQT/zR+tvW387PLHr4xUd6hYHMhjFxdvW/kGO/O6ejPffGS34YKS4xdnBaj9pF6xAT3xf3NYQdQBcX0VVn1ep9fvEaZG8PrgDkQboixd/McOz9ad6zn2OMvE4O1OGuK7Ta5E9/oXOagSRHd8RiB0dWpVuFh4U6+5t4H64XIo94XuMdIBz1P/yEs8XUIdrB1NCrvBgS7ioNVD8iXBgYrevagcTZU9EhSrZbKPG4AghiGn7QBRpkbjzvKfVlbsZaPufsgWebdfIO0fABfg7sUwg0D7PxuW9YDOZ1Vb+FNi6wTXqvLFovijtXjRYSuPkTbuafdT8Qk9xUx6FO67mlvo6Dl9Y8BNP2183OHrQFt
*/