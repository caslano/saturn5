#ifndef BOOST_MP11_UTILITY_HPP_INCLUDED
#define BOOST_MP11_UTILITY_HPP_INCLUDED

// Copyright 2015-2020 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integral.hpp>
#include <boost/mp11/detail/mp_list.hpp>
#include <boost/mp11/detail/mp_fold.hpp>
#include <boost/mp11/detail/mp_front.hpp>
#include <boost/mp11/detail/mp_rename.hpp>
#include <boost/mp11/detail/config.hpp>

namespace boost
{
namespace mp11
{

// mp_identity
template<class T> struct mp_identity
{
    using type = T;
};

// mp_identity_t
template<class T> using mp_identity_t = typename mp_identity<T>::type;

// mp_inherit
template<class... T> struct mp_inherit: T... {};

// mp_if, mp_if_c
namespace detail
{

template<bool C, class T, class... E> struct mp_if_c_impl
{
};

template<class T, class... E> struct mp_if_c_impl<true, T, E...>
{
    using type = T;
};

template<class T, class E> struct mp_if_c_impl<false, T, E>
{
    using type = E;
};

} // namespace detail

template<bool C, class T, class... E> using mp_if_c = typename detail::mp_if_c_impl<C, T, E...>::type;
template<class C, class T, class... E> using mp_if = typename detail::mp_if_c_impl<static_cast<bool>(C::value), T, E...>::type;

// mp_valid

#if BOOST_MP11_WORKAROUND( BOOST_MP11_INTEL, != 0 ) // tested at 1800

// contributed by Roland Schulz in https://github.com/boostorg/mp11/issues/17

namespace detail
{

template<class...> using void_t = void;

template<class, template<class...> class F, class... T>
struct mp_valid_impl: mp_false {};

template<template<class...> class F, class... T>
struct mp_valid_impl<void_t<F<T...>>, F, T...>: mp_true {};

} // namespace detail

template<template<class...> class F, class... T> using mp_valid = typename detail::mp_valid_impl<void, F, T...>;

#else

// implementation by Bruno Dutra (by the name is_evaluable)
namespace detail
{

template<template<class...> class F, class... T> struct mp_valid_impl
{
    template<template<class...> class G, class = G<T...>> static mp_true check(int);
    template<template<class...> class> static mp_false check(...);

    using type = decltype(check<F>(0));
};

} // namespace detail

template<template<class...> class F, class... T> using mp_valid = typename detail::mp_valid_impl<F, T...>::type;

#endif

template<class Q, class... T> using mp_valid_q = mp_valid<Q::template fn, T...>;

// mp_defer
namespace detail
{

template<template<class...> class F, class... T> struct mp_defer_impl
{
    using type = F<T...>;
};

struct mp_no_type
{
};

#if BOOST_MP11_WORKAROUND( BOOST_MP11_CUDA, >= 9000000 && BOOST_MP11_CUDA < 10000000 )

template<template<class...> class F, class... T> struct mp_defer_cuda_workaround
{
    using type = mp_if<mp_valid<F, T...>, detail::mp_defer_impl<F, T...>, detail::mp_no_type>;
};

#endif

} // namespace detail

#if BOOST_MP11_WORKAROUND( BOOST_MP11_CUDA, >= 9000000 && BOOST_MP11_CUDA < 10000000 )

template<template<class...> class F, class... T> using mp_defer = typename detail::mp_defer_cuda_workaround< F, T...>::type;

#else

template<template<class...> class F, class... T> using mp_defer = mp_if<mp_valid<F, T...>, detail::mp_defer_impl<F, T...>, detail::mp_no_type>;

#endif

// mp_eval_if, mp_eval_if_c
namespace detail
{

template<bool C, class T, template<class...> class F, class... U> struct mp_eval_if_c_impl;

template<class T, template<class...> class F, class... U> struct mp_eval_if_c_impl<true, T, F, U...>
{
    using type = T;
};

template<class T, template<class...> class F, class... U> struct mp_eval_if_c_impl<false, T, F, U...>: mp_defer<F, U...>
{
};

} // namespace detail

template<bool C, class T, template<class...> class F, class... U> using mp_eval_if_c = typename detail::mp_eval_if_c_impl<C, T, F, U...>::type;
template<class C, class T, template<class...> class F, class... U> using mp_eval_if = typename detail::mp_eval_if_c_impl<static_cast<bool>(C::value), T, F, U...>::type;
template<class C, class T, class Q, class... U> using mp_eval_if_q = typename detail::mp_eval_if_c_impl<static_cast<bool>(C::value), T, Q::template fn, U...>::type;

// mp_eval_if_not
template<class C, class T, template<class...> class F, class... U> using mp_eval_if_not = mp_eval_if<mp_not<C>, T, F, U...>;
template<class C, class T, class Q, class... U> using mp_eval_if_not_q = mp_eval_if<mp_not<C>, T, Q::template fn, U...>;

// mp_eval_or
template<class T, template<class...> class F, class... U> using mp_eval_or = mp_eval_if_not<mp_valid<F, U...>, T, F, U...>;
template<class T, class Q, class... U> using mp_eval_or_q = mp_eval_or<T, Q::template fn, U...>;

// mp_valid_and_true
template<template<class...> class F, class... T> using mp_valid_and_true = mp_eval_or<mp_false, F, T...>;
template<class Q, class... T> using mp_valid_and_true_q = mp_valid_and_true<Q::template fn, T...>;

// mp_cond

// so elegant; so doesn't work
// template<class C, class T, class... E> using mp_cond = mp_eval_if<C, T, mp_cond, E...>;

namespace detail
{

template<class C, class T, class... E> struct mp_cond_impl;

} // namespace detail

template<class C, class T, class... E> using mp_cond = typename detail::mp_cond_impl<C, T, E...>::type;

namespace detail
{

template<class C, class T, class... E> using mp_cond_ = mp_eval_if<C, T, mp_cond, E...>;

template<class C, class T, class... E> struct mp_cond_impl: mp_defer<mp_cond_, C, T, E...>
{
};

} // namespace detail

// mp_quote
template<template<class...> class F> struct mp_quote
{
    // the indirection through mp_defer works around the language inability
    // to expand T... into a fixed parameter list of an alias template

    template<class... T> using fn = typename mp_defer<F, T...>::type;
};

// mp_quote_trait
template<template<class...> class F> struct mp_quote_trait
{
    template<class... T> using fn = typename F<T...>::type;
};

// mp_invoke_q
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1900 )

namespace detail
{

template<class Q, class... T> struct mp_invoke_q_impl: mp_defer<Q::template fn, T...> {};

} // namespace detail

template<class Q, class... T> using mp_invoke_q = typename detail::mp_invoke_q_impl<Q, T...>::type;

#elif BOOST_MP11_WORKAROUND( BOOST_MP11_GCC, < 50000 )

template<class Q, class... T> using mp_invoke_q = typename mp_defer<Q::template fn, T...>::type;

#else

template<class Q, class... T> using mp_invoke_q = typename Q::template fn<T...>;

#endif

// mp_not_fn<P>
template<template<class...> class P> struct mp_not_fn
{
    template<class... T> using fn = mp_not< mp_invoke_q<mp_quote<P>, T...> >;
};

template<class Q> using mp_not_fn_q = mp_not_fn<Q::template fn>;

// mp_compose
namespace detail
{

template<class L, class Q> using mp_compose_helper = mp_list< mp_apply_q<Q, L> >;

} // namespace detail

#if !BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1900 )

template<template<class...> class... F> struct mp_compose
{
    template<class... T> using fn = mp_front< mp_fold<mp_list<mp_quote<F>...>, mp_list<T...>, detail::mp_compose_helper> >;
};

#endif

template<class... Q> struct mp_compose_q
{
    template<class... T> using fn = mp_front< mp_fold<mp_list<Q...>, mp_list<T...>, detail::mp_compose_helper> >;
};

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_UTILITY_HPP_INCLUDED

/* utility.hpp
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
*/