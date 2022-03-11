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

template<template<class...> class F, class P, class... L> struct mp_product_impl_2;

template<template<class...> class F, class P> struct mp_product_impl_2<F, P>
{
    using type = mp_list<mp_rename<P, F>>;
};

template<template<class...> class F, class P, template<class...> class L1, class... T1, class... L> struct mp_product_impl_2<F, P, L1<T1...>, L...>
{
    using type = mp_append<typename mp_product_impl_2<F, mp_push_back<P, T1>, L...>::type...>;
};

template<template<class...> class F, class... L> struct mp_product_impl;

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

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_ALGORITHM_HPP_INCLUDED

/* algorithm.hpp
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
*/