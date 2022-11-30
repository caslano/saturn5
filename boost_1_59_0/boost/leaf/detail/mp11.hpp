#ifndef BOOST_LEAF_DETAIL_MP11_HPP_INCLUDED
#define BOOST_LEAF_DETAIL_MP11_HPP_INCLUDED

//  Copyright 2015-2017 Peter Dimov.
//  Copyright 2018-2022 Emil Dotchevski and Reverge Studios, Inc.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <type_traits>
#include <cstddef>

namespace boost { namespace leaf { namespace leaf_detail_mp11 {

// mp_list<T...>
template<class... T> struct mp_list
{
};

// mp_identity
template<class T> struct mp_identity
{
    using type = T;
};

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

// mp_bool
template<bool B> using mp_bool = std::integral_constant<bool, B>;

using mp_true = mp_bool<true>;
using mp_false = mp_bool<false>;

// mp_to_bool
template<class T> using mp_to_bool = mp_bool<static_cast<bool>( T::value )>;

// mp_not<T>
template<class T> using mp_not = mp_bool< !T::value >;

// mp_int
template<int I> using mp_int = std::integral_constant<int, I>;

// mp_size_t
template<std::size_t N> using mp_size_t = std::integral_constant<std::size_t, N>;

// mp_set_contains<S, V>
namespace detail
{

template<class S, class V> struct mp_set_contains_impl;

template<template<class...> class L, class... T, class V> struct mp_set_contains_impl<L<T...>, V>
{
    using type = mp_to_bool<std::is_base_of<mp_identity<V>, mp_inherit<mp_identity<T>...> > >;
};

} // namespace detail

template<class S, class V> using mp_set_contains = typename detail::mp_set_contains_impl<S, V>::type;

// mp_set_push_back<S, T...>
namespace detail
{

template<class S, class... T> struct mp_set_push_back_impl;

template<template<class...> class L, class... U> struct mp_set_push_back_impl<L<U...>>
{
    using type = L<U...>;
};

template<template<class...> class L, class... U, class T1, class... T> struct mp_set_push_back_impl<L<U...>, T1, T...>
{
    using S = mp_if<mp_set_contains<L<U...>, T1>, L<U...>, L<U..., T1>>;
    using type = typename mp_set_push_back_impl<S, T...>::type;
};

} // namespace detail

template<class S, class... T> using mp_set_push_back = typename detail::mp_set_push_back_impl<S, T...>::type;

// mp_unique<L>
namespace detail
{

template<class L> struct mp_unique_impl;

template<template<class...> class L, class... T> struct mp_unique_impl<L<T...>>
{
    using type = mp_set_push_back<L<>, T...>;
};

} // namespace detail

template<class L> using mp_unique = typename detail::mp_unique_impl<L>::type;

// mp_append<L...>

namespace detail
{

template<class... L> struct mp_append_impl;

template<> struct mp_append_impl<>
{
    using type = mp_list<>;
};

template<template<class...> class L, class... T> struct mp_append_impl<L<T...>>
{
    using type = L<T...>;
};

template<template<class...> class L1, class... T1, template<class...> class L2, class... T2, class... Lr> struct mp_append_impl<L1<T1...>, L2<T2...>, Lr...>
{
    using type = typename mp_append_impl<L1<T1..., T2...>, Lr...>::type;
};

}

template<class... L> using mp_append = typename detail::mp_append_impl<L...>::type;

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

// mp_remove_if<L, P>
namespace detail
{

template<class L, template<class...> class P> struct mp_remove_if_impl;

template<template<class...> class L, class... T, template<class...> class P> struct mp_remove_if_impl<L<T...>, P>
{
    template<class U> using _f = mp_if<P<U>, mp_list<>, mp_list<U>>;
    using type = mp_append<L<>, _f<T>...>;
};

} // namespace detail

template<class L, template<class...> class P> using mp_remove_if = typename detail::mp_remove_if_impl<L, P>::type;

// integer_sequence
template<class T, T... I> struct integer_sequence
{
};

// detail::make_integer_sequence_impl
namespace detail
{

// iseq_if_c
template<bool C, class T, class E> struct iseq_if_c_impl;

template<class T, class E> struct iseq_if_c_impl<true, T, E>
{
    using type = T;
};

template<class T, class E> struct iseq_if_c_impl<false, T, E>
{
    using type = E;
};

template<bool C, class T, class E> using iseq_if_c = typename iseq_if_c_impl<C, T, E>::type;

// iseq_identity
template<class T> struct iseq_identity
{
    using type = T;
};

template<class S1, class S2> struct append_integer_sequence;

template<class T, T... I, T... J> struct append_integer_sequence<integer_sequence<T, I...>, integer_sequence<T, J...>>
{
    using type = integer_sequence< T, I..., ( J + sizeof...(I) )... >;
};

template<class T, T N> struct make_integer_sequence_impl;

template<class T, T N> struct make_integer_sequence_impl_
{
private:

    static_assert( N >= 0, "make_integer_sequence<T, N>: N must not be negative" );

    static T const M = N / 2;
    static T const R = N % 2;

    using S1 = typename make_integer_sequence_impl<T, M>::type;
    using S2 = typename append_integer_sequence<S1, S1>::type;
    using S3 = typename make_integer_sequence_impl<T, R>::type;
    using S4 = typename append_integer_sequence<S2, S3>::type;

public:

    using type = S4;
};

template<class T, T N> struct make_integer_sequence_impl: iseq_if_c<N == 0, iseq_identity<integer_sequence<T>>, iseq_if_c<N == 1, iseq_identity<integer_sequence<T, 0>>, make_integer_sequence_impl_<T, N> > >
{
};

} // namespace detail

// make_integer_sequence
template<class T, T N> using make_integer_sequence = typename detail::make_integer_sequence_impl<T, N>::type;

// index_sequence
template<std::size_t... I> using index_sequence = integer_sequence<std::size_t, I...>;

// make_index_sequence
template<std::size_t N> using make_index_sequence = make_integer_sequence<std::size_t, N>;

// index_sequence_for
template<class... T> using index_sequence_for = make_integer_sequence<std::size_t, sizeof...(T)>;

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

} } }

#endif

/* mp11.hpp
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
*/