#ifndef BOOST_MP11_DETAIL_MP_APPEND_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_APPEND_HPP_INCLUDED

//  Copyright 2015-2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/mp_list.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/mp11/detail/config.hpp>

namespace boost
{
namespace mp11
{

// mp_append<L...>

namespace detail
{

template<class... L> struct mp_append_impl;

#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, <= 1800 )

template<class... L> struct mp_append_impl
{
};

template<> struct mp_append_impl<>
{
    using type = mp_list<>;
};

template<template<class...> class L, class... T> struct mp_append_impl<L<T...>>
{
    using type = L<T...>;
};

template<template<class...> class L1, class... T1, template<class...> class L2, class... T2> struct mp_append_impl<L1<T1...>, L2<T2...>>
{
    using type = L1<T1..., T2...>;
};

template<template<class...> class L1, class... T1, template<class...> class L2, class... T2, template<class...> class L3, class... T3> struct mp_append_impl<L1<T1...>, L2<T2...>, L3<T3...>>
{
    using type = L1<T1..., T2..., T3...>;
};

template<template<class...> class L1, class... T1, template<class...> class L2, class... T2, template<class...> class L3, class... T3, template<class...> class L4, class... T4> struct mp_append_impl<L1<T1...>, L2<T2...>, L3<T3...>, L4<T4...>>
{
    using type = L1<T1..., T2..., T3..., T4...>;
};

template<template<class...> class L1, class... T1, template<class...> class L2, class... T2, template<class...> class L3, class... T3, template<class...> class L4, class... T4, template<class...> class L5, class... T5, class... Lr> struct mp_append_impl<L1<T1...>, L2<T2...>, L3<T3...>, L4<T4...>, L5<T5...>, Lr...>
{
    using type = typename mp_append_impl<L1<T1..., T2..., T3..., T4..., T5...>, Lr...>::type;
};

#else

template<class L1 = mp_list<>, class L2 = mp_list<>, class L3 = mp_list<>, class L4 = mp_list<>, class L5 = mp_list<>, class L6 = mp_list<>, class L7 = mp_list<>, class L8 = mp_list<>, class L9 = mp_list<>, class L10 = mp_list<>, class L11 = mp_list<>> struct append_11_impl
{
};

template<
    template<class...> class L1, class... T1,
    template<class...> class L2, class... T2,
    template<class...> class L3, class... T3,
    template<class...> class L4, class... T4,
    template<class...> class L5, class... T5,
    template<class...> class L6, class... T6,
    template<class...> class L7, class... T7,
    template<class...> class L8, class... T8,
    template<class...> class L9, class... T9,
    template<class...> class L10, class... T10,
    template<class...> class L11, class... T11>

struct append_11_impl<L1<T1...>, L2<T2...>, L3<T3...>, L4<T4...>, L5<T5...>, L6<T6...>, L7<T7...>, L8<T8...>, L9<T9...>, L10<T10...>, L11<T11...>>
{
    using type = L1<T1..., T2..., T3..., T4..., T5..., T6..., T7..., T8..., T9..., T10..., T11...>;
};

template<

    class L00 = mp_list<>, class L01 = mp_list<>, class L02 = mp_list<>, class L03 = mp_list<>, class L04 = mp_list<>, class L05 = mp_list<>, class L06 = mp_list<>, class L07 = mp_list<>, class L08 = mp_list<>, class L09 = mp_list<>, class L0A = mp_list<>,
    class L10 = mp_list<>, class L11 = mp_list<>, class L12 = mp_list<>, class L13 = mp_list<>, class L14 = mp_list<>, class L15 = mp_list<>, class L16 = mp_list<>, class L17 = mp_list<>, class L18 = mp_list<>, class L19 = mp_list<>,
    class L20 = mp_list<>, class L21 = mp_list<>, class L22 = mp_list<>, class L23 = mp_list<>, class L24 = mp_list<>, class L25 = mp_list<>, class L26 = mp_list<>, class L27 = mp_list<>, class L28 = mp_list<>, class L29 = mp_list<>,
    class L30 = mp_list<>, class L31 = mp_list<>, class L32 = mp_list<>, class L33 = mp_list<>, class L34 = mp_list<>, class L35 = mp_list<>, class L36 = mp_list<>, class L37 = mp_list<>, class L38 = mp_list<>, class L39 = mp_list<>,
    class L40 = mp_list<>, class L41 = mp_list<>, class L42 = mp_list<>, class L43 = mp_list<>, class L44 = mp_list<>, class L45 = mp_list<>, class L46 = mp_list<>, class L47 = mp_list<>, class L48 = mp_list<>, class L49 = mp_list<>,
    class L50 = mp_list<>, class L51 = mp_list<>, class L52 = mp_list<>, class L53 = mp_list<>, class L54 = mp_list<>, class L55 = mp_list<>, class L56 = mp_list<>, class L57 = mp_list<>, class L58 = mp_list<>, class L59 = mp_list<>,
    class L60 = mp_list<>, class L61 = mp_list<>, class L62 = mp_list<>, class L63 = mp_list<>, class L64 = mp_list<>, class L65 = mp_list<>, class L66 = mp_list<>, class L67 = mp_list<>, class L68 = mp_list<>, class L69 = mp_list<>,
    class L70 = mp_list<>, class L71 = mp_list<>, class L72 = mp_list<>, class L73 = mp_list<>, class L74 = mp_list<>, class L75 = mp_list<>, class L76 = mp_list<>, class L77 = mp_list<>, class L78 = mp_list<>, class L79 = mp_list<>,
    class L80 = mp_list<>, class L81 = mp_list<>, class L82 = mp_list<>, class L83 = mp_list<>, class L84 = mp_list<>, class L85 = mp_list<>, class L86 = mp_list<>, class L87 = mp_list<>, class L88 = mp_list<>, class L89 = mp_list<>,
    class L90 = mp_list<>, class L91 = mp_list<>, class L92 = mp_list<>, class L93 = mp_list<>, class L94 = mp_list<>, class L95 = mp_list<>, class L96 = mp_list<>, class L97 = mp_list<>, class L98 = mp_list<>, class L99 = mp_list<>,
    class LA0 = mp_list<>, class LA1 = mp_list<>, class LA2 = mp_list<>, class LA3 = mp_list<>, class LA4 = mp_list<>, class LA5 = mp_list<>, class LA6 = mp_list<>, class LA7 = mp_list<>, class LA8 = mp_list<>, class LA9 = mp_list<>

> struct append_111_impl
{
    using type = typename append_11_impl<

        typename append_11_impl<L00, L01, L02, L03, L04, L05, L06, L07, L08, L09, L0A>::type,
        typename append_11_impl<mp_list<>, L10, L11, L12, L13, L14, L15, L16, L17, L18, L19>::type,
        typename append_11_impl<mp_list<>, L20, L21, L22, L23, L24, L25, L26, L27, L28, L29>::type,
        typename append_11_impl<mp_list<>, L30, L31, L32, L33, L34, L35, L36, L37, L38, L39>::type,
        typename append_11_impl<mp_list<>, L40, L41, L42, L43, L44, L45, L46, L47, L48, L49>::type,
        typename append_11_impl<mp_list<>, L50, L51, L52, L53, L54, L55, L56, L57, L58, L59>::type,
        typename append_11_impl<mp_list<>, L60, L61, L62, L63, L64, L65, L66, L67, L68, L69>::type,
        typename append_11_impl<mp_list<>, L70, L71, L72, L73, L74, L75, L76, L77, L78, L79>::type,
        typename append_11_impl<mp_list<>, L80, L81, L82, L83, L84, L85, L86, L87, L88, L89>::type,
        typename append_11_impl<mp_list<>, L90, L91, L92, L93, L94, L95, L96, L97, L98, L99>::type,
        typename append_11_impl<mp_list<>, LA0, LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, LA9>::type

    >::type;
};

template<

    class L00, class L01, class L02, class L03, class L04, class L05, class L06, class L07, class L08, class L09, class L0A,
    class L10, class L11, class L12, class L13, class L14, class L15, class L16, class L17, class L18, class L19,
    class L20, class L21, class L22, class L23, class L24, class L25, class L26, class L27, class L28, class L29,
    class L30, class L31, class L32, class L33, class L34, class L35, class L36, class L37, class L38, class L39,
    class L40, class L41, class L42, class L43, class L44, class L45, class L46, class L47, class L48, class L49,
    class L50, class L51, class L52, class L53, class L54, class L55, class L56, class L57, class L58, class L59,
    class L60, class L61, class L62, class L63, class L64, class L65, class L66, class L67, class L68, class L69,
    class L70, class L71, class L72, class L73, class L74, class L75, class L76, class L77, class L78, class L79,
    class L80, class L81, class L82, class L83, class L84, class L85, class L86, class L87, class L88, class L89,
    class L90, class L91, class L92, class L93, class L94, class L95, class L96, class L97, class L98, class L99,
    class LA0, class LA1, class LA2, class LA3, class LA4, class LA5, class LA6, class LA7, class LA8, class LA9,
    class... Lr

> struct append_inf_impl
{
    using prefix = typename append_111_impl<

        L00, L01, L02, L03, L04, L05, L06, L07, L08, L09, L0A,
        L10, L11, L12, L13, L14, L15, L16, L17, L18, L19,
        L20, L21, L22, L23, L24, L25, L26, L27, L28, L29,
        L30, L31, L32, L33, L34, L35, L36, L37, L38, L39,
        L40, L41, L42, L43, L44, L45, L46, L47, L48, L49,
        L50, L51, L52, L53, L54, L55, L56, L57, L58, L59,
        L60, L61, L62, L63, L64, L65, L66, L67, L68, L69,
        L70, L71, L72, L73, L74, L75, L76, L77, L78, L79,
        L80, L81, L82, L83, L84, L85, L86, L87, L88, L89,
        L90, L91, L92, L93, L94, L95, L96, L97, L98, L99,
        LA0, LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, LA9

    >::type;

    using type = typename mp_append_impl<prefix, Lr...>::type;
};

#if BOOST_MP11_WORKAROUND( BOOST_MP11_CUDA, >= 9000000 && BOOST_MP11_CUDA < 10000000 )

template<class... L>
struct mp_append_impl_cuda_workaround
{
    using type = mp_if_c<(sizeof...(L) > 111), mp_quote<append_inf_impl>, mp_if_c<(sizeof...(L) > 11), mp_quote<append_111_impl>, mp_quote<append_11_impl> > >;
};

template<class... L> struct mp_append_impl: mp_append_impl_cuda_workaround<L...>::type::template fn<L...>
{
};

#else

template<class... L> struct mp_append_impl: mp_if_c<(sizeof...(L) > 111), mp_quote<append_inf_impl>, mp_if_c<(sizeof...(L) > 11), mp_quote<append_111_impl>, mp_quote<append_11_impl> > >::template fn<L...>
{
};

#endif

#endif

} // namespace detail

template<class... L> using mp_append = typename detail::mp_append_impl<L...>::type;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_APPEND_HPP_INCLUDED

/* mp_append.hpp
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
*/