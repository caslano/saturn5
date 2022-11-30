//  Copyright Peter Dimov 2015-2021.
//  Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  Template metaprogramming classes and functions to replace MPL
//  Source: http://www.pdimov.com/cpp2/simple_cxx11_metaprogramming.html
//  Source: https://github.com/boostorg/mp11/

#ifndef BOOST_MATH_TOOLS_MP
#define BOOST_MATH_TOOLS_MP

#include <type_traits>
#include <cstddef>
#include <utility>

namespace boost { namespace math { namespace tools { namespace meta_programming {

// Types:
// Typelist 
template<typename... T>
struct mp_list {};

// Size_t
template<std::size_t N> 
using mp_size_t = std::integral_constant<std::size_t, N>;

// Boolean
template<bool B>
using mp_bool = std::integral_constant<bool, B>;

// Identity
template<typename T>
struct mp_identity
{
    using type = T;
};

// Turns struct into quoted metafunction
template<template<typename...> class F> 
struct mp_quote_trait
{
    template<typename... T> 
    using fn = typename F<T...>::type;
};

namespace detail {
// Size
template<typename L> 
struct mp_size_impl {};

template<template<typename...> class L, typename... T> // Template template parameter must use class
struct mp_size_impl<L<T...>>
{
    using type = std::integral_constant<std::size_t, sizeof...(T)>;
};
}

template<typename T> 
using mp_size = typename detail::mp_size_impl<T>::type;

namespace detail {
// Front
template<typename L>
struct mp_front_impl {};

template<template<typename...> class L, typename T1, typename... T> 
struct mp_front_impl<L<T1, T...>>
{
    using type = T1;
};
}

template<typename T>
using mp_front = typename detail::mp_front_impl<T>::type;

namespace detail {
// At
// TODO - Use tree based lookup for larger typelists
// http://odinthenerd.blogspot.com/2017/04/tree-based-lookup-why-kvasirmpl-is.html
template<typename L, std::size_t>
struct mp_at_c {};

template<template<typename...> class L, typename T0, typename... T>
struct mp_at_c<L<T0, T...>, 0>
{
    using type = T0;
};

template<template<typename...> class L, typename T0, typename T1, typename... T>
struct mp_at_c<L<T0, T1, T...>, 1>
{
    using type = T1;
};

template<template<typename...> class L, typename T0, typename T1, typename T2, typename... T>
struct mp_at_c<L<T0, T1, T2, T...>, 2>
{
    using type = T2;
};

template<template<typename...> class L, typename T0, typename T1, typename T2, typename T3, typename... T>
struct mp_at_c<L<T0, T1, T2, T3, T...>, 3>
{
    using type = T3;
};

template<template<typename...> class L, typename T0, typename T1, typename T2, typename T3, typename T4, typename... T>
struct mp_at_c<L<T0, T1, T2, T3, T4, T...>, 4>
{
    using type = T4;
};

template<template<typename...> class L, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename... T>
struct mp_at_c<L<T0, T1, T2, T3, T4, T5, T...>, 5>
{
    using type = T5;
};

template<template<typename...> class L, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
         typename... T>
struct mp_at_c<L<T0, T1, T2, T3, T4, T5, T6, T...>, 6>
{
    using type = T6;
};

template<template<typename...> class L, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
         typename T7, typename... T>
struct mp_at_c<L<T0, T1, T2, T3, T4, T5, T6, T7, T...>, 7>
{
    using type = T7;
};

template<template<typename...> class L, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
         typename T7, typename T8, typename... T>
struct mp_at_c<L<T0, T1, T2, T3, T4, T5, T6, T7, T8, T...>, 8>
{
    using type = T8;
};

template<template<typename...> class L, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
         typename T7, typename T8, typename T9, typename... T>
struct mp_at_c<L<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T...>, 9>
{
    using type = T9;
};

template<template<typename...> class L, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
         typename T7, typename T8, typename T9, typename T10, typename... T>
struct mp_at_c<L<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T...>, 10>
{
    using type = T10;
};

template<template<typename...> class L, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
         typename T7, typename T8, typename T9, typename T10, typename T11, typename... T>
struct mp_at_c<L<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T...>, 11>
{
    using type = T11;
};

template<template<typename...> class L, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
         typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename... T>
struct mp_at_c<L<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T...>, 12>
{
    using type = T12;
};
}

template<typename L, std::size_t I>
using mp_at_c = typename detail::mp_at_c<L, I>::type;

template<typename L, typename I>
using mp_at = typename detail::mp_at_c<L, I::value>::type;

// Back
template<typename L> 
using mp_back = mp_at_c<L, mp_size<L>::value - 1>;

namespace detail {
// Push back
template<typename L, typename... T> 
struct mp_push_back_impl {};

template<template<typename...> class L, typename... U, typename... T> 
struct mp_push_back_impl<L<U...>, T...>
{
    using type = L<U..., T...>;
};
}

template<typename L, typename... T>
using mp_push_back = typename detail::mp_push_back_impl<L, T...>::type;

namespace detail {
// Push front
template<typename L, typename... T>
struct mp_push_front_impl {};

template<template<typename...> class L, typename... U, typename... T>
struct mp_push_front_impl<L<U...>, T...>
{
    using type = L<T..., U...>;
};
}

template<typename L, typename... T> 
using mp_push_front = typename detail::mp_push_front_impl<L, T...>::type;

namespace detail{
// If
template<bool C, typename T, typename... E>
struct mp_if_c_impl{};

template<typename T, typename... E>
struct mp_if_c_impl<true, T, E...>
{
    using type = T;
};

template<typename T, typename E>
struct mp_if_c_impl<false, T, E>
{
    using type = E;
};
}

template<bool C, typename T, typename... E> 
using mp_if_c = typename detail::mp_if_c_impl<C, T, E...>::type;

template<typename C, typename T, typename... E> 
using mp_if = typename detail::mp_if_c_impl<static_cast<bool>(C::value), T, E...>::type;

namespace detail {
// Find if
template<typename L, template<typename...> class P>
struct mp_find_if_impl {};

template<template<typename...> class L, template<typename...> class P> 
struct mp_find_if_impl<L<>, P>
{
    using type = mp_size_t<0>;
};

template<typename L, template<typename...> class P> 
struct mp_find_if_impl_2
{
    using r = typename mp_find_if_impl<L, P>::type;
    using type = mp_size_t<1 + r::value>;
};

template<template<typename...> class L, typename T1, typename... T, template<typename...> class P> 
struct mp_find_if_impl<L<T1, T...>, P>
{
    using type = typename mp_if<P<T1>, mp_identity<mp_size_t<0>>, mp_find_if_impl_2<mp_list<T...>, P>>::type;
};
}

template<typename L, template<typename...> class P> 
using mp_find_if = typename detail::mp_find_if_impl<L, P>::type;

template<typename L, typename Q> 
using mp_find_if_q = mp_find_if<L, Q::template fn>;

namespace detail {
// Append
template<typename... L> 
struct mp_append_impl {};

template<> 
struct mp_append_impl<>
{
    using type = mp_list<>;
};

template<template<typename...> class L, typename... T>
struct mp_append_impl<L<T...>>
{
    using type = L<T...>;
};

template<template<typename...> class L1, typename... T1, template<typename...> class L2, typename... T2>
struct mp_append_impl<L1<T1...>, L2<T2...>>
{
    using type = L1<T1..., T2...>;
};

template<template<typename...> class L1, typename... T1, template<typename...> class L2, typename... T2, 
         template<typename...> class L3, typename... T3>
struct mp_append_impl<L1<T1...>, L2<T2...>, L3<T3...>>
{
    using type = L1<T1..., T2..., T3...>;
};

template<template<typename...> class L1, typename... T1, template<typename...> class L2, typename... T2, 
         template<typename...> class L3, typename... T3, template<typename...> class L4, typename... T4>
struct mp_append_impl<L1<T1...>, L2<T2...>, L3<T3...>, L4<T4...>>
{
    using type = L1<T1..., T2..., T3..., T4...>;
};

template<template<typename...> class L1, typename... T1, template<typename...> class L2, typename... T2,
         template<typename...> class L3, typename... T3, template<typename...> class L4, typename... T4, 
         template<typename...> class L5, typename... T5, typename... Lr> 
struct mp_append_impl<L1<T1...>, L2<T2...>, L3<T3...>, L4<T4...>, L5<T5...>, Lr...>
{
    using type = typename mp_append_impl<L1<T1..., T2..., T3..., T4..., T5...>, Lr...>::type;
};
}

template<typename... L> 
using mp_append = typename detail::mp_append_impl<L...>::type;

namespace detail {
// Remove if
template<typename L, template<typename...> class P> 
struct mp_remove_if_impl{};

template<template<typename...> class L, typename... T, template<typename...> class P>
struct mp_remove_if_impl<L<T...>, P>
{    
    template<typename U> 
    struct _f 
    { 
        using type = mp_if<P<U>, mp_list<>, mp_list<U>>; 
    };
    
    using type = mp_append<L<>, typename _f<T>::type...>;
};
}

template<typename L, template<class...> class P> 
using mp_remove_if = typename detail::mp_remove_if_impl<L, P>::type;

template<typename L, typename Q> 
using mp_remove_if_q = mp_remove_if<L, Q::template fn>;

// Index sequence
// Use C++14 index sequence if available
#if defined(__cpp_lib_integer_sequence) && (__cpp_lib_integer_sequence >= 201304)
template<std::size_t... I>
using index_sequence = std::index_sequence<I...>;

template<std::size_t N>
using make_index_sequence = std::make_index_sequence<N>;

template<typename... T>
using index_sequence_for = std::index_sequence_for<T...>;

#else

template<typename T, T... I>
struct integer_sequence {};

template<std::size_t... I>
using index_sequence = integer_sequence<std::size_t, I...>;

namespace detail {

template<bool C, typename T, typename E>
struct iseq_if_c_impl {};

template<typename T, typename F>
struct iseq_if_c_impl<true, T, F>
{
    using type = T;
};

template<typename T, typename F>
struct iseq_if_c_impl<false, T, F>
{
    using type = F;
};

template<bool C, typename T, typename F>
using iseq_if_c = typename iseq_if_c_impl<C, T, F>::type;

template<typename T>
struct iseq_identity
{
    using type = T;
};

template<typename T1, typename T2>
struct append_integer_sequence {};

template<typename T, T... I, T... J>
struct append_integer_sequence<integer_sequence<T, I...>, integer_sequence<T, J...>>
{
    using type = integer_sequence<T, I..., (J + sizeof...(I))...>;
};

template<typename T, T N>
struct make_integer_sequence_impl;

template<typename T, T N>
class make_integer_sequence_impl_
{
private:
    static_assert(N >= 0, "N must not be negative");

    static constexpr T M = N / 2;
    static constexpr T R = N % 2;

    using seq1 = typename make_integer_sequence_impl<T, M>::type;
    using seq2 = typename append_integer_sequence<seq1, seq1>::type;
    using seq3 = typename make_integer_sequence_impl<T, R>::type;
    using seq4 = typename append_integer_sequence<seq2, seq3>::type;

public:
    using type = seq4;
};

template<typename T, T N>
struct make_integer_sequence_impl
{
    using type = typename iseq_if_c<N == 0, 
                                    iseq_identity<integer_sequence<T>>, 
                                    iseq_if_c<N == 1, iseq_identity<integer_sequence<T, 0>>, 
                                    make_integer_sequence_impl_<T, N>>>::type;
};

} // namespace detail

template<typename T, T N>
using make_integer_sequence = typename detail::make_integer_sequence_impl<T, N>::type;

template<std::size_t N>
using make_index_sequence = make_integer_sequence<std::size_t, N>;

template<typename... T>
using index_sequence_for = make_integer_sequence<std::size_t, sizeof...(T)>;

#endif 

}}}} // namespaces

#endif // BOOST_MATH_TOOLS_MP

/* mp.hpp
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
*/