#ifndef BOOST_MP11_DETAIL_MP_COUNT_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_COUNT_HPP_INCLUDED

//  Copyright 2015, 2016 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integral.hpp>
#include <boost/mp11/detail/mp_plus.hpp>
#include <boost/mp11/detail/config.hpp>

namespace boost
{
namespace mp11
{

// mp_count<L, V>
namespace detail
{

template<class L, class V> struct mp_count_impl;

#if defined( BOOST_MP11_HAS_FOLD_EXPRESSIONS )

template<template<class...> class L, class... T, class V> struct mp_count_impl<L<T...>, V>
{
    using type = mp_size_t<(std::is_same<T, V>::value + ... + 0)>;
};

#elif !defined( BOOST_MP11_NO_CONSTEXPR )

constexpr std::size_t cx_plus()
{
    return 0;
}

template<class T1, class... T> constexpr std::size_t cx_plus(T1 t1, T... t)
{
    return static_cast<std::size_t>(t1) + cx_plus(t...);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class... T>
constexpr std::size_t cx_plus(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9, T10 t10, T... t)
{
    return static_cast<std::size_t>(t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + t9 + t10) + cx_plus(t...);
}

template<template<class...> class L, class... T, class V> struct mp_count_impl<L<T...>, V>
{
    using type = mp_size_t<cx_plus(std::is_same<T, V>::value...)>;
};

#else

template<template<class...> class L, class... T, class V> struct mp_count_impl<L<T...>, V>
{
    using type = mp_size_t<mp_plus<std::is_same<T, V>...>::value>;
};

#endif

} // namespace detail

template<class L, class V> using mp_count = typename detail::mp_count_impl<L, V>::type;

// mp_count_if<L, P>
namespace detail
{

template<class L, template<class...> class P> struct mp_count_if_impl;

#if defined( BOOST_MP11_HAS_FOLD_EXPRESSIONS ) && !BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 )

template<template<class...> class L, class... T, template<class...> class P> struct mp_count_if_impl<L<T...>, P>
{
    using type = mp_size_t<(mp_to_bool<P<T>>::value + ... + 0)>;
};

#elif !defined( BOOST_MP11_NO_CONSTEXPR )

template<template<class...> class L, class... T, template<class...> class P> struct mp_count_if_impl<L<T...>, P>
{
    using type = mp_size_t<cx_plus(mp_to_bool<P<T>>::value...)>;
};

#else

template<template<class...> class L, class... T, template<class...> class P> struct mp_count_if_impl<L<T...>, P>
{
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 )

    template<class T> struct _f { using type = mp_to_bool<P<T>>; };
    using type = mp_size_t<mp_plus<typename _f<T>::type...>::value>;

#else

    using type = mp_size_t<mp_plus<mp_to_bool<P<T>>...>::value>;

#endif
};

#endif

} // namespace detail

template<class L, template<class...> class P> using mp_count_if = typename detail::mp_count_if_impl<L, P>::type;
template<class L, class Q> using mp_count_if_q = mp_count_if<L, Q::template fn>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_COUNT_HPP_INCLUDED

/* mp_count.hpp
rNVoqRC9OIugKdMF0UnjADOgkEZXF+HSKc6zddLPLkbtb39BIA6SjnZQ6GgHIzS/6FbxL6axVWKNPRTroWSt2hbn3MjFeWoRWIgP3zzhxzRHYBFuhxi3FxAUB0hJOyCUtAOWwZNSXNfhySStRizOh0ec0RcNRcddSFFRXkLX2k+ExwwoJHYeIBwxjb1jJkZ5McpFBNx+0or2C61of4SuFd0q/sU0tsozzRY79tM/J2nVxs5ZsbVacR8Nq0R0H428U+UrFfgiCP9eoWVBAi17xupV1P8+0of2CX1oX7SWJZrEBO3M+CHB7ZlX3GQlawz5VxrzHodsYFT07TYiPIhsI8jgGxEw4oxwaBeMggR6ZRml9/0JodhLJN0rSLo3mlFmq1PZGF6UsFXheUoebZMTcWxcihUSFUweEhW0hUR96I8o1ctZVDkhYbnM8tzUo22kWDfpBO036cAVC+IuCH+bUBoggd5XZkFwAom1h5b3PWJ53xOpNCS/nydo22L+XLJWbbp7bswVS1zLYzpo6FoeylDxggQ0DxEZcXECJ8ACZNwKCIp20jjbhcbZbtVjo1u1dMndy/bN5h+Nx2k1jh47J3lwNE+pqMt/eNFZT4MfM/jOA9W/k5DcIZayHfQTM9H/R9DtokVnl1h0dkUvZWarsbap7VcKHf9D4lbZiRFT9uWYY1VcJWR6MdbQqFpL2fWID9+j4K8XSxkkcOowbpUERRstOm1i0WmzLmXRrVKXlNb8lPbZLyh6fixJq7axOjf5zTuzTJxFDKFpW0MGziTKpkJKa35K++wxhGsRupZK4cWotHgxKuN4MaKmVA4Or+jrk9hwpeuTKEPFOxAQVppSm9kc5oQGmez/05FYrWS4trLhGnkEKEarli6xe2zVtve9NWGrwhxOHiNiwXlWGGfzjiYzxo2gq+AJTzjXEs6Y5glPONcyzj//PULXTBO+WUz4ZqsYiW7V0iV2j63abn76QLJWbThfEF+MCJxzTZxFTKip7FNMKGYgzmYhV5QDtpjQk8/hsKtgr4nTjwkREgbpBCFh88KKngHf/PDBicxufubJPJkn82SezPMffcLfl/ODufDa1xmhBr7oj5pxqEHO2HFLnIGSFTaR45zmDrJD1jxs71ZdC8Kf1Gr5zWmxeW0UiV8xHWDyJNojyqQteGAStAw8/wqNmZED0NgcUS+GnxBvDJnQZF2Y0fwCZGjKBN5/9evTpoOeAYv+moGltRH6rOCI0P8FmiMQ6QCtffrXYchyRUcSfbAM1demw4Uqakqepj/gp8TGPiNCFN6e+Jz+kKrA2YAhQX9sWAL3M5xtH4Y+X8oYMAXNPl2iT7foMwv6HP/If41GhuOxkOJfwBIwzCrjY3vbk3xs79Zs82N7n4v62B4MRJOeGDRO/qBQiS9Y4gvYiIh2X7D+MrJtg1tn98mT4ruEk/zlQRyIhj8zsnnO8EAGnzwukYMlciCSEdHNT4jmJ7j5CdH84IjZOv+O0/jgyXht66JtndvWuW1x0IcIETK33z2a5CG7K1SiBEu4qhlqw81C8+ibp+ZHRfOj1DyeggpM6QN9NcYH+uY3tzpmlFe2b0gqI4CwZex7KGzHYwnb8VLYjnfsnWC7pP5h2//QY/l+cR1/EnPZd07jdzoBiYTfn37o2dPi+94YubTcUT8bibPd5WhYWKtCbu1GmGV1b6/bVOfUX/D0aeNrojuhBNl6r/d8gwQv9q30OpDe+cDZaiio0bugrvlB3Nc0NUoOYA8MrAoXf7y481lRIdcw2oEHVTiwq6UarOiGem7+XunhR6hjS900Y6sQ/3zCfxTxD6KsCYfZuR0NFyE16xx1Dr3m79i1BLNjHAU6f/M=
*/