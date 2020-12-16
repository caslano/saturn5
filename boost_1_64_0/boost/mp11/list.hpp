#ifndef BOOST_MP11_LIST_HPP_INCLUDED
#define BOOST_MP11_LIST_HPP_INCLUDED

//  Copyright 2015-2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integral.hpp>
#include <boost/mp11/detail/mp_list.hpp>
#include <boost/mp11/detail/mp_is_list.hpp>
#include <boost/mp11/detail/mp_append.hpp>
#include <boost/mp11/detail/config.hpp>
#include <type_traits>

namespace boost
{
namespace mp11
{

// mp_list_c<T, I...>
template<class T, T... I> using mp_list_c = mp_list<std::integral_constant<T, I>...>;

// mp_is_list<L>
//   in detail/mp_is_list.hpp

// mp_size<L>
namespace detail
{

template<class L> struct mp_size_impl
{
// An error "no type named 'type'" here means that the argument to mp_size is not a list
};

template<template<class...> class L, class... T> struct mp_size_impl<L<T...>>
{
    using type = mp_size_t<sizeof...(T)>;
};

} // namespace detail

template<class L> using mp_size = typename detail::mp_size_impl<L>::type;

// mp_empty<L>
template<class L> using mp_empty = mp_bool< mp_size<L>::value == 0 >;

// mp_assign<L1, L2>
namespace detail
{

template<class L1, class L2> struct mp_assign_impl;

template<template<class...> class L1, class... T, template<class...> class L2, class... U> struct mp_assign_impl<L1<T...>, L2<U...>>
{
    using type = L1<U...>;
};

} // namespace detail

template<class L1, class L2> using mp_assign = typename detail::mp_assign_impl<L1, L2>::type;

// mp_clear<L>
template<class L> using mp_clear = mp_assign<L, mp_list<>>;

// mp_front<L>
namespace detail
{

template<class L> struct mp_front_impl
{
// An error "no type named 'type'" here means that the argument to mp_front
// is either not a list, or is an empty list
};

template<template<class...> class L, class T1, class... T> struct mp_front_impl<L<T1, T...>>
{
    using type = T1;
};

} // namespace detail

template<class L> using mp_front = typename detail::mp_front_impl<L>::type;

// mp_pop_front<L>
namespace detail
{

template<class L> struct mp_pop_front_impl
{
// An error "no type named 'type'" here means that the argument to mp_pop_front
// is either not a list, or is an empty list
};

template<template<class...> class L, class T1, class... T> struct mp_pop_front_impl<L<T1, T...>>
{
    using type = L<T...>;
};

} // namespace detail

template<class L> using mp_pop_front = typename detail::mp_pop_front_impl<L>::type;

// mp_first<L>
template<class L> using mp_first = mp_front<L>;

// mp_rest<L>
template<class L> using mp_rest = mp_pop_front<L>;

// mp_second<L>
namespace detail
{

template<class L> struct mp_second_impl
{
// An error "no type named 'type'" here means that the argument to mp_second
// is either not a list, or has fewer than two elements
};

template<template<class...> class L, class T1, class T2, class... T> struct mp_second_impl<L<T1, T2, T...>>
{
    using type = T2;
};

} // namespace detail

template<class L> using mp_second = typename detail::mp_second_impl<L>::type;

// mp_third<L>
namespace detail
{

template<class L> struct mp_third_impl
{
// An error "no type named 'type'" here means that the argument to mp_third
// is either not a list, or has fewer than three elements
};

template<template<class...> class L, class T1, class T2, class T3, class... T> struct mp_third_impl<L<T1, T2, T3, T...>>
{
    using type = T3;
};

} // namespace detail

template<class L> using mp_third = typename detail::mp_third_impl<L>::type;

// mp_push_front<L, T...>
namespace detail
{

template<class L, class... T> struct mp_push_front_impl
{
// An error "no type named 'type'" here means that the first argument to mp_push_front is not a list
};

template<template<class...> class L, class... U, class... T> struct mp_push_front_impl<L<U...>, T...>
{
    using type = L<T..., U...>;
};

} // namespace detail

template<class L, class... T> using mp_push_front = typename detail::mp_push_front_impl<L, T...>::type;

// mp_push_back<L, T...>
namespace detail
{

template<class L, class... T> struct mp_push_back_impl
{
// An error "no type named 'type'" here means that the first argument to mp_push_back is not a list
};

template<template<class...> class L, class... U, class... T> struct mp_push_back_impl<L<U...>, T...>
{
    using type = L<U..., T...>;
};

} // namespace detail

template<class L, class... T> using mp_push_back = typename detail::mp_push_back_impl<L, T...>::type;

// mp_rename<L, B>
namespace detail
{

template<class A, template<class...> class B> struct mp_rename_impl
{
// An error "no type named 'type'" here means that the first argument to mp_rename is not a list
};

template<template<class...> class A, class... T, template<class...> class B> struct mp_rename_impl<A<T...>, B>
{
    using type = B<T...>;
};

} // namespace detail

template<class A, template<class...> class B> using mp_rename = typename detail::mp_rename_impl<A, B>::type;

template<template<class...> class F, class L> using mp_apply = typename detail::mp_rename_impl<L, F>::type;

template<class Q, class L> using mp_apply_q = typename detail::mp_rename_impl<L, Q::template fn>::type;

// mp_replace_front<L, T>
namespace detail
{

template<class L, class T> struct mp_replace_front_impl
{
// An error "no type named 'type'" here means that the first argument to mp_replace_front
// is either not a list, or is an empty list
};

template<template<class...> class L, class U1, class... U, class T> struct mp_replace_front_impl<L<U1, U...>, T>
{
    using type = L<T, U...>;
};

} // namespace detail

template<class L, class T> using mp_replace_front = typename detail::mp_replace_front_impl<L, T>::type;

// mp_replace_first<L, T>
template<class L, class T> using mp_replace_first = typename detail::mp_replace_front_impl<L, T>::type;

// mp_replace_second<L, T>
namespace detail
{

template<class L, class T> struct mp_replace_second_impl
{
// An error "no type named 'type'" here means that the first argument to mp_replace_second
// is either not a list, or has fewer than two elements
};

template<template<class...> class L, class U1, class U2, class... U, class T> struct mp_replace_second_impl<L<U1, U2, U...>, T>
{
    using type = L<U1, T, U...>;
};

} // namespace detail

template<class L, class T> using mp_replace_second = typename detail::mp_replace_second_impl<L, T>::type;

// mp_replace_third<L, T>
namespace detail
{

template<class L, class T> struct mp_replace_third_impl
{
// An error "no type named 'type'" here means that the first argument to mp_replace_third
// is either not a list, or has fewer than three elements
};

template<template<class...> class L, class U1, class U2, class U3, class... U, class T> struct mp_replace_third_impl<L<U1, U2, U3, U...>, T>
{
    using type = L<U1, U2, T, U...>;
};

} // namespace detail

template<class L, class T> using mp_replace_third = typename detail::mp_replace_third_impl<L, T>::type;

// mp_transform_front<L, F>
namespace detail
{

template<class L, template<class...> class F> struct mp_transform_front_impl
{
// An error "no type named 'type'" here means that the first argument to mp_transform_front
// is either not a list, or is an empty list
};

template<template<class...> class L, class U1, class... U, template<class...> class F> struct mp_transform_front_impl<L<U1, U...>, F>
{
    using type = L<F<U1>, U...>;
};

} // namespace detail

template<class L, template<class...> class F> using mp_transform_front = typename detail::mp_transform_front_impl<L, F>::type;
template<class L, class Q> using mp_transform_front_q = mp_transform_front<L, Q::template fn>;

// mp_transform_first<L, F>
template<class L, template<class...> class F> using mp_transform_first = typename detail::mp_transform_front_impl<L, F>::type;
template<class L, class Q> using mp_transform_first_q = mp_transform_first<L, Q::template fn>;

// mp_transform_second<L, F>
namespace detail
{

template<class L, template<class...> class F> struct mp_transform_second_impl
{
// An error "no type named 'type'" here means that the first argument to mp_transform_second
// is either not a list, or has fewer than two elements
};

template<template<class...> class L, class U1, class U2, class... U, template<class...> class F> struct mp_transform_second_impl<L<U1, U2, U...>, F>
{
    using type = L<U1, F<U2>, U...>;
};

} // namespace detail

template<class L, template<class...> class F> using mp_transform_second = typename detail::mp_transform_second_impl<L, F>::type;
template<class L, class Q> using mp_transform_second_q = mp_transform_second<L, Q::template fn>;

// mp_transform_third<L, F>
namespace detail
{

template<class L, template<class...> class F> struct mp_transform_third_impl
{
// An error "no type named 'type'" here means that the first argument to mp_transform_third
// is either not a list, or has fewer than three elements
};

template<template<class...> class L, class U1, class U2, class U3, class... U, template<class...> class F> struct mp_transform_third_impl<L<U1, U2, U3, U...>, F>
{
    using type = L<U1, U2, F<U3>, U...>;
};

} // namespace detail

template<class L, template<class...> class F> using mp_transform_third = typename detail::mp_transform_third_impl<L, F>::type;
template<class L, class Q> using mp_transform_third_q = mp_transform_third<L, Q::template fn>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_LIST_HPP_INCLUDED

/* list.hpp
bPCTXacRP1s0fr69K9cB3qyTEEMVEMNhRdGKDHjfZPHMO70zgTDYcg/taCLwlrZThcXgTysCix1MLqbdqgqXhwAYdU6LZpZn0T4oB8J3zsiHiA3onaIDAVXjpCQo0wfpljixmcJsRY53E50fvaGBY+drNrBqOz+aSvOj5x1ifjRkK5ofeeEL2Y6n+QqXeEEx5GDbLc8WDdkNDTkbKi12vEW2xT8leKqhJoFh53ui0S11Ig81V14qNLuqzJC36lA3HIYGm2VDY7xVpb5Qsa9xBwfFgtQaAfuQAUhYaF1hziaMhyH/YTqkoqDxOyU2JTvTQP2zJ5nKNL3ioLmdQj7w3Ohcz0kHZgUZxEWrJxQRA7mNYjptA3S7PQa2DVCGIxOpuO3pnZ/IkxNMTQ2baYBS8Z3DLJq1X2zLe+uqb2Sgtjoa2V5Ppzd5Nf6UMq2POq6nW/0M7txebvV1uN+Fex3cP8K9Bu5D4J4Ftwfu33uR/pkFF7q08qRn/Q2XNyP2/3/0/H9oX5qk7MGSgi02LtxB4V1ThJc6koSzv8wTd9fsGwqCJWIwvRKGyKZ+winIExraVtGF8vt2qdaPNsO4UOQTHlmbwht++wOUhPMPbqMkTAAhZODE6BFxdA2VuEnsmzSxb0Ih50gOaKxVaqgLNAOMVQxx8TAv3ExJniCnvqs4tUX2XD71x+K+I6sX8mdcdqw+cgX9j/f/Msg4T49PTGZl2l95k35QJ/xBTUMo1ZfF+BstO1XrPqI6toNKSyY7FNRdVp2/6Q/kK42+uwXuFAoN6yvF4ffyecvUXXoAKocv8VOeFWzRPrC2+PduGv49meFYMWvoQxXxmryU0PlC0NO6h5WAF3/upEF74h8QTL+8+GNz3r6kr/s4jDWpjJCXf3BeI7AjLLRqzmLyfwRjcfAslmxveMfBZmMgfGd8Vj8qCOu6iwV/LBIdgeEgDcr9BEpN6uwZPSg9JLsV+/LzOF81vKpQeH5n/6YgtISO9KM6loSf/4PeXvACSkBQfk/Oinb5MceSD1TG8SoGBGJszkptzdTxi8/3jDmvr3Ax/jXPH33cvn3EvtVvUr+QsHAjfVv774Gm88F8YpnJwY0j6+JevMb09La0xjQbvrTICfbyXg+ht8CtKLzgA1+Wl3z0+bQjwXzawoTVPJ9OaxuX+9ucBOsxX8BWIbF7IMnuCkNRP7dvvB3AWk+8kcJYZ0fsANrafw2ItVcY1w5xa2OIW7l9PHHDPfFGCs86toQ4s7zM2VnT50+rkWKvcOLOidb3veyM6VT/tTfpi/tz+5IM3gNfVN87HeIgIu3QtAJ9m7zRSiPHxW7AF+vwRS3xG/BN6/D9xe771shWep5J4cCbzgOKLoW7Eu4cuPeBu7ov6l5pTmeafZfLvdy2yyq+pVjAt9qxF+ve8seW24ux/78dAR/p1YKqT9n+KddvB2ZYg0Mo/1GJ+os5O5jsQ6+8qj9+lu0n1ubx4bkX78mdZkt/Etgm+LJuKwr96FpI8FX/v3ndfnnnLsP+q3979qtfb9/R9fn9+mv9ze8FDja78b2CMN+AmbjiQLNPWL/D32zldEpx+LKFmm2nr4oi8TExp5AchLu5FAzUp/nCvgnfnLdie6AS042rAfXIXVNM2oS32v0u6N1bOzBh5P0Azkopr5m/ofR6ZQz7JG/U//cz2/8tGb1wxJLRrylLRi9yLBn9ugN2t41eDKpSb6TFG1Tgf9Fb4E+IaVsyejnEXKEEc3AX3Pul4QteJU4EVUy3FnbCmf4XNcGmJP5fPX4hd94e8D8tKsQGgY4dt8wg0MC/YMgUioXX9OYIdlPBd5n/mjc1RX0BPsdDGbSdi/CMXyDQVj1WPaU=
*/