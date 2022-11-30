#ifndef BOOST_MP11_ALGORITHM_HPP_INCLUDED
#define BOOST_MP11_ALGORITHM_HPP_INCLUDED

//  Copyright 2015-2019 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/list.hpp>
#include <boost/mp11/set.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/mp11/function.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/mp11/detail/mp_plus.hpp>
#include <boost/mp11/detail/mp_map_find.hpp>
#include <boost/mp11/detail/mp_with_index.hpp>
#include <boost/mp11/detail/mp_fold.hpp>
#include <boost/mp11/detail/mp_min_element.hpp>
#include <boost/mp11/detail/mp_copy_if.hpp>
#include <boost/mp11/detail/mp_remove_if.hpp>
#include <boost/mp11/detail/config.hpp>
#include <boost/mp11/integer_sequence.hpp>
#include <type_traits>
#include <utility>

namespace boost
{
namespace mp11
{

// mp_transform<F, L...>
namespace detail
{

template<template<class...> class F, class... L> struct mp_transform_impl
{
};

template<template<class...> class F, template<class...> class L, class... T> struct mp_transform_impl<F, L<T...>>
{
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 )

    template<class... U> struct f { using type = F<U...>; };

    using type = L<typename f<T>::type...>;

#else

    using type = L<F<T>...>;

#endif
};

template<template<class...> class F, template<class...> class L1, class... T1, template<class...> class L2, class... T2> struct mp_transform_impl<F, L1<T1...>, L2<T2...>>
{
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 )

    template<class... U> struct f { using type = F<U...>; };

    using type = L1<typename f<T1, T2>::type...>;

#else

    using type = L1<F<T1,T2>...>;

#endif
};

template<template<class...> class F, template<class...> class L1, class... T1, template<class...> class L2, class... T2, template<class...> class L3, class... T3> struct mp_transform_impl<F, L1<T1...>, L2<T2...>, L3<T3...>>
{
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 )

    template<class... U> struct f { using type = F<U...>; };

    using type = L1<typename f<T1, T2, T3>::type...>;

#else

    using type = L1<F<T1,T2,T3>...>;

#endif
};

#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, == 1900 ) || BOOST_MP11_WORKAROUND( BOOST_MP11_GCC, < 40800 )

template<class... L> using mp_same_size_1 = mp_same<mp_size<L>...>;
template<class... L> struct mp_same_size_2: mp_defer<mp_same_size_1, L...> {};

#endif

struct list_size_mismatch
{
};

#if BOOST_MP11_WORKAROUND( BOOST_MP11_CUDA, >= 9000000 && BOOST_MP11_CUDA < 10000000 )

template<template<class...> class F, class... L> struct mp_transform_cuda_workaround
{
    using type = mp_if<mp_same<mp_size<L>...>, detail::mp_transform_impl<F, L...>, detail::list_size_mismatch>;
};

#endif

} // namespace detail

#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, == 1900 ) || BOOST_MP11_WORKAROUND( BOOST_MP11_GCC, < 40800 )

template<template<class...> class F, class... L> using mp_transform = typename mp_if<typename detail::mp_same_size_2<L...>::type, detail::mp_transform_impl<F, L...>, detail::list_size_mismatch>::type;

#else

#if BOOST_MP11_WORKAROUND( BOOST_MP11_CUDA, >= 9000000 && BOOST_MP11_CUDA < 10000000 )

template<template<class...> class F, class... L> using mp_transform = typename detail::mp_transform_cuda_workaround< F, L...>::type::type;

#else

template<template<class...> class F, class... L> using mp_transform = typename mp_if<mp_same<mp_size<L>...>, detail::mp_transform_impl<F, L...>, detail::list_size_mismatch>::type;

#endif

#endif

template<class Q, class... L> using mp_transform_q = mp_transform<Q::template fn, L...>;

namespace detail
{

template<template<class...> class F, template<class...> class L1, class... T1, template<class...> class L2, class... T2, template<class...> class L3, class... T3, template<class...> class L4, class... T4, class... L> struct mp_transform_impl<F, L1<T1...>, L2<T2...>, L3<T3...>, L4<T4...>, L...>
{
    using A1 = L1<mp_list<T1, T2, T3, T4>...>;

    template<class V, class T> using _f = mp_transform<mp_push_back, V, T>;

    using A2 = mp_fold<mp_list<L...>, A1, _f>;

    template<class T> using _g = mp_apply<F, T>;

    using type = mp_transform<_g, A2>;
};

} // namespace detail

// mp_transform_if<P, F, L...>
namespace detail
{

template<template<class...> class P, template<class...> class F, class... L> struct mp_transform_if_impl
{
    // the stupid quote-unquote dance avoids "pack expansion used as argument for non-pack parameter of alias template"

    using Qp = mp_quote<P>;
    using Qf = mp_quote<F>;

#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 )

    template<class... U> struct _f_ { using type = mp_eval_if_q<mp_not<mp_invoke_q<Qp, U...>>, mp_first<mp_list<U...>>, Qf, U...>; };
    template<class... U> using _f = typename _f_<U...>::type;

#else

    template<class... U> using _f = mp_eval_if_q<mp_not<mp_invoke_q<Qp, U...>>, mp_first<mp_list<U...>>, Qf, U...>;

#endif

    using type = mp_transform<_f, L...>;
};

} // namespace detail

template<template<class...> class P, template<class...> class F, class... L> using mp_transform_if = typename detail::mp_transform_if_impl<P, F, L...>::type;
template<class Qp, class Qf, class... L> using mp_transform_if_q = typename detail::mp_transform_if_impl<Qp::template fn, Qf::template fn, L...>::type;

// mp_filter<P, L...>
namespace detail
{

template<template<class...> class P, class L1, class... L> struct mp_filter_impl
{
    using Qp = mp_quote<P>;

    template<class T1, class... T> using _f = mp_if< mp_invoke_q<Qp, T1, T...>, mp_list<T1>, mp_list<> >;

    using _t1 = mp_transform<_f, L1, L...>;
    using _t2 = mp_apply<mp_append, _t1>;

    using type = mp_assign<L1, _t2>;
};

} // namespace detail

template<template<class...> class P, class... L> using mp_filter = typename detail::mp_filter_impl<P, L...>::type;
template<class Q, class... L> using mp_filter_q = typename detail::mp_filter_impl<Q::template fn, L...>::type;

// mp_fill<L, V>
namespace detail
{

template<class L, class V> struct mp_fill_impl;

template<template<class...> class L, class... T, class V> struct mp_fill_impl<L<T...>, V>
{
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, <= 1900 )

    template<class...> struct _f { using type = V; };
    using type = L<typename _f<T>::type...>;

#else

    template<class...> using _f = V;
    using type = L<_f<T>...>;

#endif
};

} // namespace detail

template<class L, class V> using mp_fill = typename detail::mp_fill_impl<L, V>::type;

// mp_contains<L, V>
template<class L, class V> using mp_contains = mp_to_bool<mp_count<L, V>>;

// mp_repeat(_c)<L, N>
namespace detail
{

template<class L, std::size_t N> struct mp_repeat_c_impl
{
    using _l1 = typename mp_repeat_c_impl<L, N/2>::type;
    using _l2 = typename mp_repeat_c_impl<L, N%2>::type;

    using type = mp_append<_l1, _l1, _l2>;
};

template<class L> struct mp_repeat_c_impl<L, 0>
{
    using type = mp_clear<L>;
};

template<class L> struct mp_repeat_c_impl<L, 1>
{
    using type = L;
};

} // namespace detail

template<class L, std::size_t N> using mp_repeat_c = typename detail::mp_repeat_c_impl<L, N>::type;
template<class L, class N> using mp_repeat = typename detail::mp_repeat_c_impl<L, std::size_t{ N::value }>::type;

// mp_product<F, L...>
namespace detail
{

template<template<class...> class F, class P, class... L> struct mp_product_impl_2
{
};

template<template<class...> class F, class P> struct mp_product_impl_2<F, P>
{
    using type = mp_list<mp_rename<P, F>>;
};

template<template<class...> class F, class P, template<class...> class L1, class... T1, class... L> struct mp_product_impl_2<F, P, L1<T1...>, L...>
{
    using type = mp_append<typename mp_product_impl_2<F, mp_push_back<P, T1>, L...>::type...>;
};

template<template<class...> class F, class... L> struct mp_product_impl
{
};

template<template<class...> class F> struct mp_product_impl<F>
{
    using type = mp_list< F<> >;
};

template<template<class...> class F, class L1, class... L> struct mp_product_impl<F, L1, L...>
{
    using type = mp_assign<L1, typename mp_product_impl_2<F, mp_list<>, L1, L...>::type>;
};

} // namespace detail

template<template<class...> class F, class... L> using mp_product = typename detail::mp_product_impl<F, L...>::type;
template<class Q, class... L> using mp_product_q = typename detail::mp_product_impl<Q::template fn, L...>::type;

// mp_drop(_c)<L, N>
namespace detail
{

template<class L, class L2> struct mp_drop_impl;

template<template<class...> class L, class... T, template<class...> class L2, class... U> struct mp_drop_impl<L<T...>, L2<U...>>
{
    template<class... W> static mp_identity<L<W...>> f( U*..., mp_identity<W>*... );

    using R = decltype( f( (mp_identity<T>*)0 ... ) );

    using type = typename R::type;
};

} // namespace detail

template<class L, std::size_t N> using mp_drop_c = typename detail::mp_drop_impl<L, mp_repeat_c<mp_list<void>, N>>::type;

template<class L, class N> using mp_drop = typename detail::mp_drop_impl<L, mp_repeat<mp_list<void>, N>>::type;

// mp_from_sequence<S>
namespace detail
{

template<class S> struct mp_from_sequence_impl;

template<template<class T, T... I> class S, class U, U... J> struct mp_from_sequence_impl<S<U, J...>>
{
    using type = mp_list<std::integral_constant<U, J>...>;
};

} // namespace detail

template<class S> using mp_from_sequence = typename detail::mp_from_sequence_impl<S>::type;

// mp_iota(_c)<N>
template<std::size_t N> using mp_iota_c = mp_from_sequence<make_index_sequence<N>>;
template<class N> using mp_iota = mp_from_sequence<make_integer_sequence<typename std::remove_const<decltype(N::value)>::type, N::value>>;

// mp_at(_c)<L, I>
namespace detail
{

template<class L, std::size_t I> struct mp_at_c_impl;

#if defined(BOOST_MP11_HAS_TYPE_PACK_ELEMENT)

template<template<class...> class L, class... T, std::size_t I> struct mp_at_c_impl<L<T...>, I>
{
    using type = __type_pack_element<I, T...>;
};

#else

template<class L, std::size_t I> struct mp_at_c_impl
{
    using _map = mp_transform<mp_list, mp_iota<mp_size<L> >, L>;
    using type = mp_second<mp_map_find<_map, mp_size_t<I> > >;
};

#endif

#if BOOST_MP11_WORKAROUND( BOOST_MP11_CUDA, >= 9000000 && BOOST_MP11_CUDA < 10000000 )

template<class L, std::size_t I> struct mp_at_c_cuda_workaround
{
    using type = mp_if_c<(I < mp_size<L>::value), detail::mp_at_c_impl<L, I>, void>;
};

#endif

} // namespace detail

#if BOOST_MP11_WORKAROUND( BOOST_MP11_CUDA, >= 9000000 && BOOST_MP11_CUDA < 10000000 )

template<class L, std::size_t I> using mp_at_c = typename detail::mp_at_c_cuda_workaround< L, I >::type::type;

#else

template<class L, std::size_t I> using mp_at_c = typename mp_if_c<(I < mp_size<L>::value), detail::mp_at_c_impl<L, I>, void>::type;

#endif

template<class L, class I> using mp_at = mp_at_c<L, std::size_t{ I::value }>;

// mp_take(_c)<L, N>
namespace detail
{

template<std::size_t N, class L, class E = void> struct mp_take_c_impl
{
};

template<template<class...> class L, class... T>
struct mp_take_c_impl<0, L<T...>>
{
    using type = L<>;
};

template<template<class...> class L, class T1, class... T>
struct mp_take_c_impl<1, L<T1, T...>>
{
    using type = L<T1>;
};

template<template<class...> class L, class T1, class T2, class... T>
struct mp_take_c_impl<2, L<T1, T2, T...>>
{
    using type = L<T1, T2>;
};

template<template<class...> class L, class T1, class T2, class T3, class... T>
struct mp_take_c_impl<3, L<T1, T2, T3, T...>>
{
    using type = L<T1, T2, T3>;
};

template<template<class...> class L, class T1, class T2, class T3, class T4, class... T>
struct mp_take_c_impl<4, L<T1, T2, T3, T4, T...>>
{
    using type = L<T1, T2, T3, T4>;
};

template<template<class...> class L, class T1, class T2, class T3, class T4, class T5, class... T>
struct mp_take_c_impl<5, L<T1, T2, T3, T4, T5, T...>>
{
    using type = L<T1, T2, T3, T4, T5>;
};

template<template<class...> class L, class T1, class T2, class T3, class T4, class T5, class T6, class... T>
struct mp_take_c_impl<6, L<T1, T2, T3, T4, T5, T6, T...>>
{
    using type = L<T1, T2, T3, T4, T5, T6>;
};

template<template<class...> class L, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class... T>
struct mp_take_c_impl<7, L<T1, T2, T3, T4, T5, T6, T7, T...>>
{
    using type = L<T1, T2, T3, T4, T5, T6, T7>;
};

template<template<class...> class L, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class... T>
struct mp_take_c_impl<8, L<T1, T2, T3, T4, T5, T6, T7, T8, T...>>
{
    using type = L<T1, T2, T3, T4, T5, T6, T7, T8>;
};

template<template<class...> class L, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class... T>
struct mp_take_c_impl<9, L<T1, T2, T3, T4, T5, T6, T7, T8, T9, T...>>
{
    using type = L<T1, T2, T3, T4, T5, T6, T7, T8, T9>;
};

template<template<class...> class L, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class... T, std::size_t N>
struct mp_take_c_impl<N, L<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T...>, typename std::enable_if<N >= 10>::type>
{
    using type = mp_append<L<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>, typename mp_take_c_impl<N-10, L<T...>>::type>;
};

} // namespace detail

template<class L, std::size_t N> using mp_take_c = typename detail::mp_take_c_impl<N, L>::type;
template<class L, class N> using mp_take = typename detail::mp_take_c_impl<std::size_t{ N::value }, L>::type;

// mp_back<L>
template<class L> using mp_back = mp_at_c<L, mp_size<L>::value - 1>;

// mp_pop_back<L>
template<class L> using mp_pop_back = mp_take_c<L, mp_size<L>::value - 1>;

// mp_replace<L, V, W>
namespace detail
{

template<class L, class V, class W> struct mp_replace_impl;

template<template<class...> class L, class... T, class V, class W> struct mp_replace_impl<L<T...>, V, W>
{
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, <= 1800 )
    template<class A> struct _f { using type = mp_if<std::is_same<A, V>, W, A>; };
    using type = L<typename _f<T>::type...>;
#else
    template<class A> using _f = mp_if<std::is_same<A, V>, W, A>;
    using type = L<_f<T>...>;
#endif
};

} // namespace detail

template<class L, class V, class W> using mp_replace = typename detail::mp_replace_impl<L, V, W>::type;

// mp_replace_if<L, P, W>
namespace detail
{

template<class L, template<class...> class P, class W> struct mp_replace_if_impl;

template<template<class...> class L, class... T, template<class...> class P, class W> struct mp_replace_if_impl<L<T...>, P, W>
{
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 )
    template<class U> struct _f { using type = mp_if<P<U>, W, U>; };
    using type = L<typename _f<T>::type...>;
#else
    template<class U> using _f = mp_if<P<U>, W, U>;
    using type = L<_f<T>...>;
#endif
};

} // namespace detail

template<class L, template<class...> class P, class W> using mp_replace_if = typename detail::mp_replace_if_impl<L, P, W>::type;
template<class L, class Q, class W> using mp_replace_if_q = mp_replace_if<L, Q::template fn, W>;

// mp_copy_if<L, P>
//   in detail/mp_copy_if.hpp

// mp_remove<L, V>
namespace detail
{

template<class L, class V> struct mp_remove_impl;

template<template<class...> class L, class... T, class V> struct mp_remove_impl<L<T...>, V>
{
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 )
    template<class U> struct _f { using type = mp_if<std::is_same<U, V>, mp_list<>, mp_list<U>>; };
    using type = mp_append<L<>, typename _f<T>::type...>;
#else
    template<class U> using _f = mp_if<std::is_same<U, V>, mp_list<>, mp_list<U>>;
    using type = mp_append<L<>, _f<T>...>;
#endif
};

} // namespace detail

template<class L, class V> using mp_remove = typename detail::mp_remove_impl<L, V>::type;

// mp_remove_if<L, P>
//   in detail/mp_remove_if.hpp

// mp_flatten<L, L2 = mp_clear<L>>
namespace detail
{

template<class L2> struct mp_flatten_impl
{
    template<class T> using fn = mp_if<mp_similar<L2, T>, T, mp_list<T>>;
};

} // namespace detail

template<class L, class L2 = mp_clear<L>> using mp_flatten = mp_apply<mp_append, mp_push_front<mp_transform_q<detail::mp_flatten_impl<L2>, L>, mp_clear<L>>>;

// mp_partition<L, P>
namespace detail
{

template<class L, template<class...> class P> struct mp_partition_impl;

template<template<class...> class L, class... T, template<class...> class P> struct mp_partition_impl<L<T...>, P>
{
    using type = L<mp_copy_if<L<T...>, P>, mp_remove_if<L<T...>, P>>;
};

} // namespace detail

template<class L, template<class...> class P> using mp_partition = typename detail::mp_partition_impl<L, P>::type;
template<class L, class Q> using mp_partition_q = mp_partition<L, Q::template fn>;

// mp_sort<L, P>
namespace detail
{

template<class L, template<class...> class P> struct mp_sort_impl;

#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, <= 1800 )

template<template<class...> class L, class... T, template<class...> class P> struct mp_sort_impl<L<T...>, P>
{
    static_assert( sizeof...(T) == 0, "T... must be empty" );
    using type = L<>;
};

#else

template<template<class...> class L, template<class...> class P> struct mp_sort_impl<L<>, P>
{
    using type = L<>;
};

#endif

template<template<class...> class L, class T1, template<class...> class P> struct mp_sort_impl<L<T1>, P>
{
    using type = L<T1>;
};

template<template<class...> class L, class T1, class... T, template<class...> class P> struct mp_sort_impl<L<T1, T...>, P>
{
    template<class U> using F = P<U, T1>;

    using part = mp_partition<L<T...>, F>;

    using S1 = typename mp_sort_impl<mp_first<part>, P>::type;
    using S2 = typename mp_sort_impl<mp_second<part>, P>::type;

    using type = mp_append<mp_push_back<S1, T1>, S2>;
};

} // namespace detail

template<class L, template<class...> class P> using mp_sort = typename detail::mp_sort_impl<L, P>::type;
template<class L, class Q> using mp_sort_q = mp_sort<L, Q::template fn>;

// mp_nth_element(_c)<L, I, P>
namespace detail
{

template<class L, std::size_t I, template<class...> class P> struct mp_nth_element_impl;

template<template<class...> class L, class T1, std::size_t I, template<class...> class P> struct mp_nth_element_impl<L<T1>, I, P>
{
    static_assert( I == 0, "mp_nth_element index out of range" );
    using type = T1;
};

template<template<class...> class L, class T1, class... T, std::size_t I, template<class...> class P> struct mp_nth_element_impl<L<T1, T...>, I, P>
{
    static_assert( I < 1 + sizeof...(T), "mp_nth_element index out of range" );

    template<class U> using F = P<U, T1>;

    using part = mp_partition<L<T...>, F>;

    using L1 = mp_first<part>;
    static std::size_t const N1 = mp_size<L1>::value;

    using L2 = mp_second<part>;

#if BOOST_MP11_WORKAROUND( BOOST_MP11_CUDA, >= 9000000 && BOOST_MP11_CUDA < 10000000 )

    struct detail
    {
        struct mp_nth_element_impl_cuda_workaround
        {
            using type = mp_cond<

                mp_bool<(I < N1)>, mp_nth_element_impl<L1, I, P>,
                mp_bool<(I == N1)>, mp_identity<T1>,
                mp_true, mp_nth_element_impl<L2, I - N1 - 1, P>

            >;
        };
    };

    using type = typename detail::mp_nth_element_impl_cuda_workaround::type::type;

#else

    using type = typename mp_cond<

        mp_bool<(I < N1)>, mp_nth_element_impl<L1, I, P>,
        mp_bool<(I == N1)>, mp_identity<T1>,
        mp_true, mp_nth_element_impl<L2, I - N1 - 1, P>

    >::type;

#endif
};

} // namespace detail

template<class L, std::size_t I, template<class...> class P> using mp_nth_element_c = typename detail::mp_nth_element_impl<L, I, P>::type;
template<class L, class I, template<class...> class P> using mp_nth_element = typename detail::mp_nth_element_impl<L, std::size_t{ I::value }, P>::type;
template<class L, class I, class Q> using mp_nth_element_q = mp_nth_element<L, I, Q::template fn>;

// mp_find<L, V>
namespace detail
{

template<class L, class V> struct mp_find_impl;

#if BOOST_MP11_CLANG && defined( BOOST_MP11_HAS_FOLD_EXPRESSIONS )

struct mp_index_holder
{
    std::size_t i_;
    bool f_;
};

constexpr inline mp_index_holder operator+( mp_index_holder const & v, bool f )
{
    if( v.f_ )
    {
        return v;
    }
    else if( f )
    {
        return { v.i_, true };
    }
    else
    {
        return { v.i_ + 1, false };
    }
}

template<template<class...> class L, class... T, class V> struct mp_find_impl<L<T...>, V>
{
    static constexpr mp_index_holder _v{ 0, false };
    using type = mp_size_t< (_v + ... + std::is_same<T, V>::value).i_ >;
};

#elif !defined( BOOST_MP11_NO_CONSTEXPR )

template<template<class...> class L, class V> struct mp_find_impl<L<>, V>
{
    using type = mp_size_t<0>;
};

#if defined( BOOST_MP11_HAS_CXX14_CONSTEXPR )

constexpr std::size_t cx_find_index( bool const * first, bool const * last )
{
    std::size_t m = 0;

    while( first != last && !*first )
    {
        ++m;
        ++first;
    }

    return m;
}

#else

constexpr std::size_t cx_find_index( bool const * first, bool const * last )
{
    return first == last || *first? 0: 1 + cx_find_index( first + 1, last );
}

#endif

template<template<class...> class L, class... T, class V> struct mp_find_impl<L<T...>, V>
{
    static constexpr bool _v[] = { std::is_same<T, V>::value... };
    using type = mp_size_t< cx_find_index( _v, _v + sizeof...(T) ) >;
};

#else

#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, <= 1800 )

template<template<class...> class L, class... T, class V> struct mp_find_impl<L<T...>, V>
{
    static_assert( sizeof...(T) == 0, "T... must be empty" );
    using type = mp_size_t<0>;
};

#else

template<template<class...> class L, class V> struct mp_find_impl<L<>, V>
{
    using type = mp_size_t<0>;
};

#endif

template<template<class...> class L, class... T, class V> struct mp_find_impl<L<V, T...>, V>
{
    using type = mp_size_t<0>;
};

template<template<class...> class L, class T1, class... T, class V> struct mp_find_impl<L<T1, T...>, V>
{
    using _r = typename mp_find_impl<mp_list<T...>, V>::type;
    using type = mp_size_t<1 + _r::value>;
};

#endif

} // namespace detail

template<class L, class V> using mp_find = typename detail::mp_find_impl<L, V>::type;

// mp_find_if<L, P>
namespace detail
{

template<class L, template<class...> class P> struct mp_find_if_impl;

#if BOOST_MP11_CLANG && defined( BOOST_MP11_HAS_FOLD_EXPRESSIONS )

template<template<class...> class L, class... T, template<class...> class P> struct mp_find_if_impl<L<T...>, P>
{
    static constexpr mp_index_holder _v{ 0, false };
    using type = mp_size_t< (_v + ... + P<T>::value).i_ >;
};

#elif !defined( BOOST_MP11_NO_CONSTEXPR )

template<template<class...> class L, template<class...> class P> struct mp_find_if_impl<L<>, P>
{
    using type = mp_size_t<0>;
};

template<template<class...> class L, class... T, template<class...> class P> struct mp_find_if_impl<L<T...>, P>
{
    static constexpr bool _v[] = { P<T>::value... };
    using type = mp_size_t< cx_find_index( _v, _v + sizeof...(T) ) >;
};

#else

#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, <= 1800 )

template<template<class...> class L, class... T, template<class...> class P> struct mp_find_if_impl<L<T...>, P>
{
    static_assert( sizeof...(T) == 0, "T... must be empty" );
    using type = mp_size_t<0>;
};

#else

template<template<class...> class L, template<class...> class P> struct mp_find_if_impl<L<>, P>
{
    using type = mp_size_t<0>;
};

#endif

template<class L, template<class...> class P> struct mp_find_if_impl_2
{
    using _r = typename mp_find_if_impl<L, P>::type;
    using type = mp_size_t<1 + _r::value>;
};

template<template<class...> class L, class T1, class... T, template<class...> class P> struct mp_find_if_impl<L<T1, T...>, P>
{
    using type = typename mp_if<P<T1>, mp_identity<mp_size_t<0>>, mp_find_if_impl_2<mp_list<T...>, P>>::type;
};

#endif

} // namespace detail

template<class L, template<class...> class P> using mp_find_if = typename detail::mp_find_if_impl<L, P>::type;
template<class L, class Q> using mp_find_if_q = mp_find_if<L, Q::template fn>;

// mp_reverse<L>
namespace detail
{

template<class L> struct mp_reverse_impl;

#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, <= 1800 )

template<template<class...> class L, class... T> struct mp_reverse_impl<L<T...>>
{
    static_assert( sizeof...(T) == 0, "T... must be empty" );
    using type = L<>;
};

#else

template<template<class...> class L> struct mp_reverse_impl<L<>>
{
    using type = L<>;
};

#endif

template<template<class...> class L, class T1> struct mp_reverse_impl<L<T1>>
{
    using type = L<T1>;
};

template<template<class...> class L, class T1, class T2> struct mp_reverse_impl<L<T1, T2>>
{
    using type = L<T2, T1>;
};

template<template<class...> class L, class T1, class T2, class T3> struct mp_reverse_impl<L<T1, T2, T3>>
{
    using type = L<T3, T2, T1>;
};

template<template<class...> class L, class T1, class T2, class T3, class T4> struct mp_reverse_impl<L<T1, T2, T3, T4>>
{
    using type = L<T4, T3, T2, T1>;
};

template<template<class...> class L, class T1, class T2, class T3, class T4, class T5> struct mp_reverse_impl<L<T1, T2, T3, T4, T5>>
{
    using type = L<T5, T4, T3, T2, T1>;
};

template<template<class...> class L, class T1, class T2, class T3, class T4, class T5, class T6> struct mp_reverse_impl<L<T1, T2, T3, T4, T5, T6>>
{
    using type = L<T6, T5, T4, T3, T2, T1>;
};

template<template<class...> class L, class T1, class T2, class T3, class T4, class T5, class T6, class T7> struct mp_reverse_impl<L<T1, T2, T3, T4, T5, T6, T7>>
{
    using type = L<T7, T6, T5, T4, T3, T2, T1>;
};

template<template<class...> class L, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8> struct mp_reverse_impl<L<T1, T2, T3, T4, T5, T6, T7, T8>>
{
    using type = L<T8, T7, T6, T5, T4, T3, T2, T1>;
};

template<template<class...> class L, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9> struct mp_reverse_impl<L<T1, T2, T3, T4, T5, T6, T7, T8, T9>>
{
    using type = L<T9, T8, T7, T6, T5, T4, T3, T2, T1>;
};

template<template<class...> class L, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class... T> struct mp_reverse_impl<L<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T...>>
{
    using type = mp_push_back<typename mp_reverse_impl<L<T...>>::type, T10, T9, T8, T7, T6, T5, T4, T3, T2, T1>;
};

} // namespace detail

template<class L> using mp_reverse = typename detail::mp_reverse_impl<L>::type;

// mp_fold<L, V, F>
//   in detail/mp_fold.hpp

// mp_reverse_fold<L, V, F>
namespace detail
{

template<class L, class V, template<class...> class F> struct mp_reverse_fold_impl;

#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, <= 1800 )

template<template<class...> class L, class... T, class V, template<class...> class F> struct mp_reverse_fold_impl<L<T...>, V, F>
{
    static_assert( sizeof...(T) == 0, "T... must be empty" );
    using type = V;
};

#else

template<template<class...> class L, class V, template<class...> class F> struct mp_reverse_fold_impl<L<>, V, F>
{
    using type = V;
};

#endif

template<template<class...> class L, class T1, class... T, class V, template<class...> class F> struct mp_reverse_fold_impl<L<T1, T...>, V, F>
{
    using rest = typename mp_reverse_fold_impl<L<T...>, V, F>::type;
    using type = F<T1, rest>;
};

template<template<class...> class L, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class... T, class V, template<class...> class F> struct mp_reverse_fold_impl<L<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T...>, V, F>
{
    using rest = typename mp_reverse_fold_impl<L<T...>, V, F>::type;
    using type = F<T1, F<T2, F<T3, F<T4, F<T5, F<T6, F<T7, F<T8, F<T9, F<T10, rest> > > > > > > > > >;
};

} // namespace detail

template<class L, class V, template<class...> class F> using mp_reverse_fold = typename detail::mp_reverse_fold_impl<L, V, F>::type;
template<class L, class V, class Q> using mp_reverse_fold_q = mp_reverse_fold<L, V, Q::template fn>;

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

// mp_unique_if<L, P>
namespace detail
{

template<template<class...> class P> struct mp_unique_if_push_back
{
    template<class...> struct impl
    {
    };

    template<template<class...> class L, class... Ts, class T>
    struct impl<L<Ts...>, T>
    {
        using type = mp_if<mp_any<P<Ts, T>...>, L<Ts...>, L<Ts..., T>>;
    };

    template<class... T> using fn = typename impl<T...>::type;
};

} // namespace detail

template<class L, template<class...> class P>
using mp_unique_if = mp_fold_q<L, mp_clear<L>, detail::mp_unique_if_push_back<P>>;

template<class L, class Q> using mp_unique_if_q = mp_unique_if<L, Q::template fn>;

// mp_all_of<L, P>
template<class L, template<class...> class P> using mp_all_of = mp_bool< mp_count_if<L, P>::value == mp_size<L>::value >;
template<class L, class Q> using mp_all_of_q = mp_all_of<L, Q::template fn>;

// mp_none_of<L, P>
template<class L, template<class...> class P> using mp_none_of = mp_bool< mp_count_if<L, P>::value == 0 >;
template<class L, class Q> using mp_none_of_q = mp_none_of<L, Q::template fn>;

// mp_any_of<L, P>
template<class L, template<class...> class P> using mp_any_of = mp_bool< mp_count_if<L, P>::value != 0 >;
template<class L, class Q> using mp_any_of_q = mp_any_of<L, Q::template fn>;

// mp_replace_at_c<L, I, W>
namespace detail
{

template<class L, class I, class W> struct mp_replace_at_impl
{
    static_assert( I::value >= 0, "mp_replace_at<L, I, W>: I must not be negative" );

    template<class T1, class T2> using _p = std::is_same<T2, mp_size_t<I::value>>;
    template<class T1, class T2> using _f = W;

    using type = mp_transform_if<_p, _f, L, mp_iota<mp_size<L> > >;
};

} // namespace detail

template<class L, class I, class W> using mp_replace_at = typename detail::mp_replace_at_impl<L, I, W>::type;
template<class L, std::size_t I, class W> using mp_replace_at_c = typename detail::mp_replace_at_impl<L, mp_size_t<I>, W>::type;

//mp_for_each<L>(f)
namespace detail
{

template<class... T, class F> BOOST_MP11_CONSTEXPR F mp_for_each_impl( mp_list<T...>, F && f )
{
    using A = int[sizeof...(T)];
    return (void)A{ ((void)f(T()), 0)... }, std::forward<F>(f);
}

template<class F> BOOST_MP11_CONSTEXPR F mp_for_each_impl( mp_list<>, F && f )
{
    return std::forward<F>(f);
}

} // namespace detail

#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, >= 1900 )

// msvc has a limit of 1024

template<class L, class F> BOOST_MP11_CONSTEXPR mp_if_c<mp_size<L>::value <= 1024, F> mp_for_each( F && f )
{
    return detail::mp_for_each_impl( mp_rename<L, mp_list>(), std::forward<F>(f) );
}

template<class L, class F> BOOST_MP11_CONSTEXPR mp_if_c<mp_size<L>::value >= 1025, F> mp_for_each( F && f )
{
    using L2 = mp_rename<L, mp_list>;

    using L3 = mp_take_c<L2, 1024>;
    using L4 = mp_drop_c<L2, 1024>;

    return mp_for_each<L4>( mp_for_each<L3>( std::forward<F>(f) ) );
}

#else

template<class L, class F> BOOST_MP11_CONSTEXPR F mp_for_each( F && f )
{
    return detail::mp_for_each_impl( mp_rename<L, mp_list>(), std::forward<F>(f) );
}

#endif

// mp_insert<L, I, T...>
template<class L, class I, class... T> using mp_insert = mp_append<mp_take<L, I>, mp_push_front<mp_drop<L, I>, T...>>;

// mp_insert_c<L, I, T...>
template<class L, std::size_t I, class... T> using mp_insert_c = mp_append<mp_take_c<L, I>, mp_push_front<mp_drop_c<L, I>, T...>>;

// mp_erase<L, I, J>
template<class L, class I, class J> using mp_erase = mp_append<mp_take<L, I>, mp_drop<L, J>>;

// mp_erase_c<L, I, J>
template<class L, std::size_t I, std::size_t J> using mp_erase_c = mp_append<mp_take_c<L, I>, mp_drop_c<L, J>>;

// mp_starts_with<L1, L2>
// contributed by Glen Joseph Fernandes (glenjofe@gmail.com)
namespace detail {

template<class L1, class L2>
struct mp_starts_with_impl { };

template<template<class...> class L1, class... T1, template<class...> class L2,
    class... T2>
struct mp_starts_with_impl<L1<T1...>, L2<T2...> > {
    template<class L>
    static mp_false check(L);

    template<class... T>
    static mp_true check(mp_list<T2..., T...>);

    using type = decltype(check(mp_list<T1...>()));
};

} // namespace detail

template<class L1, class L2>
using mp_starts_with = typename detail::mp_starts_with_impl<L1, L2>::type;

// mp_rotate_left(_c)<L, N>
namespace detail
{

// limit divisor to 1 to avoid division by 0 and give a rotation of 0 for lists containing 0 or 1 elements
template<std::size_t Ln, std::size_t N> using canonical_left_rotation = mp_size_t<N % (Ln == 0? 1: Ln)>;

// perform right rotation as a left rotation by inverting the number of elements to rotate
template<std::size_t Ln, std::size_t N> using canonical_right_rotation = mp_size_t<Ln - N % (Ln == 0? 1: Ln)>;

// avoid errors when rotating fixed-sized lists by using mp_list for the transformation
template<class L, class N, class L2 = mp_rename<L, mp_list>> using mp_rotate_impl = mp_assign<L, mp_append< mp_drop<L2, N>, mp_take<L2, N> >>;

} // namespace detail

template<class L, std::size_t N> using mp_rotate_left_c = detail::mp_rotate_impl<L, detail::canonical_left_rotation<mp_size<L>::value, N>>;
template<class L, class N> using mp_rotate_left = mp_rotate_left_c<L, std::size_t{ N::value }>;

// mp_rotate_right(_c)<L, N>
template<class L, std::size_t N> using mp_rotate_right_c = mp_rotate_left<L, detail::canonical_right_rotation<mp_size<L>::value, N>>;
template<class L, class N> using mp_rotate_right = mp_rotate_right_c<L, std::size_t{ N::value }>;

// mp_min_element<L, P>
// mp_max_element<L, P>
//   in detail/mp_min_element.hpp

// mp_power_set<L>
namespace detail
{

template<class L> struct mp_power_set_impl;

} // namespace detail

template<class L> using mp_power_set = typename detail::mp_power_set_impl<L>::type;

namespace detail
{

#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, <= 1800 )

template<template<class...> class L, class... T> struct mp_power_set_impl< L<T...> >
{
    static_assert( sizeof...(T) == 0, "T... must be empty" );
    using type = L< L<> >;
};

#else

template<template<class...> class L> struct mp_power_set_impl< L<> >
{
    using type = L< L<> >;
};

#endif

template<template<class...> class L, class T1, class... T> struct mp_power_set_impl< L<T1, T...> >
{
    using S1 = mp_power_set< L<T...> >;

    template<class L2> using _f = mp_push_front<L2, T1>;

    using S2 = mp_transform<_f, S1>;

    using type = mp_append< S1, S2 >;
};

} // namespace detail

// mp_partial_sum<L, V, F>
namespace detail
{

template<template<class...> class F> struct mp_partial_sum_impl_f
{
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, <= 1900 )

    template<class V, class T> using fn = mp_list<F<mp_first<V>, T>, mp_push_back<mp_second<V>, F<mp_first<V>, T>> >;

#else

    template<class V, class T, class N = F<mp_first<V>, T>> using fn = mp_list<N, mp_push_back<mp_second<V>, N>>;

#endif
};

} // namespace detail

template<class L, class V, template<class...> class F> using mp_partial_sum = mp_second<mp_fold_q<L, mp_list<V, mp_clear<L>>, detail::mp_partial_sum_impl_f<F>> >;
template<class L, class V, class Q> using mp_partial_sum_q = mp_partial_sum<L, V, Q::template fn>;

// mp_iterate<V, F, R>
namespace detail
{

template<class V, template<class...> class F, template<class...> class R, class N> struct mp_iterate_impl;

} // namespace detail

template<class V, template<class...> class F, template<class...> class R> using mp_iterate = typename detail::mp_iterate_impl<V, F, R, mp_valid<R, V>>::type;

namespace detail
{

template<class V, template<class...> class F, template<class...> class R> struct mp_iterate_impl<V, F, R, mp_false>
{
    template<class X> using _f = mp_list<F<X>>;
    using type = mp_eval_or<mp_list<>, _f, V>;
};

template<class V, template<class...> class F, template<class...> class R> struct mp_iterate_impl<V, F, R, mp_true>
{
    using type = mp_push_front<mp_iterate<R<V>, F, R>, F<V>>;
};

} // namespace detail

template<class V, class Qf, class Qr> using mp_iterate_q = mp_iterate<V, Qf::template fn, Qr::template fn>;

// mp_pairwise_fold<L, F>
namespace detail
{

template<class L, class Q> using mp_pairwise_fold_impl = mp_transform_q<Q, mp_pop_back<L>, mp_pop_front<L>>;

} // namespace detail

template<class L, class Q> using mp_pairwise_fold_q = mp_eval_if<mp_empty<L>, mp_clear<L>, detail::mp_pairwise_fold_impl, L, Q>;
template<class L, template<class...> class F> using mp_pairwise_fold = mp_pairwise_fold_q<L, mp_quote<F>>;

// mp_intersperse<L, S>
namespace detail
{

template<class L, class S> struct mp_intersperse_impl
{
};

#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, <= 1800 )

template<template<class...> class L, class... T, class S> struct mp_intersperse_impl<L<T...>, S>
{
    static_assert( sizeof...(T) == 0, "T... must be empty" );
    using type = L<>;
};

#else

template<template<class...> class L, class S> struct mp_intersperse_impl<L<>, S>
{
    using type = L<>;
};

#endif

template<template<class...> class L, class T1, class... T, class S> struct mp_intersperse_impl<L<T1, T...>, S>
{
    using type = mp_append<L<T1>, L<S, T>...>;
};

} // namespace detail

template<class L, class S> using mp_intersperse = typename detail::mp_intersperse_impl<L, S>::type;

// mp_split<L, S>
namespace detail
{

template<class L, class S, class J> struct mp_split_impl;

} // namespace detail

template<class L, class S> using mp_split = typename detail::mp_split_impl<L, S, mp_find<L, S>>::type;

namespace detail
{

template<class L, class S, class J> using mp_split_impl_ = mp_push_front<mp_split<mp_drop_c<L, J::value + 1>, S>, mp_take<L, J>>;

template<class L, class S, class J> struct mp_split_impl
{
    using type = mp_eval_if_c<mp_size<L>::value == J::value, mp_push_back<mp_clear<L>, L>, mp_split_impl_, L, S, J>;
};

} // namespace detail

// mp_join<L, S>

template<class L, class S> using mp_join = mp_apply<mp_append, mp_intersperse<L, mp_list<S>>>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_ALGORITHM_HPP_INCLUDED

/* algorithm.hpp
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
*/