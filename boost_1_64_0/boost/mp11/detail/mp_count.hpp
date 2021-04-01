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
IA8npO11fkN76PnpXjzCp/Cj9yU+66LGRwNFfydVKAlfVCq1JpLMpz1vWHT+vWtsYSYyEf6e3OVvtFwTJloE8+jzd/PxJaO5FZ8GoQ34ZHMvYt6vImW85xpOrlHIMwgDKbKcB8ijCkl47YovOdHfaJUm/+xt/eoximSMbAuIJAKGxLyGJfwQleItai1fGWqM3iQEaJ3qAf5rIMH5kYUH+iv7b4p84Fnbz3PCZWxBybEtkYAUNiXQ/WrZ4rz7ocW9PqJfTBvna5qLJCcHy4S5Tlq2LHKK4H03G0JlxcSZp2ROM9jNU1DKzsMNp6LehwpWJVdKcVsuSL4NCoKx/dUWTBYtdE0cz11gtgqes+OqOyc6dWME3huGiUiAfOc/eU41OWbj3bnaQhSMYWB4TKZT6S/zL8qL28IoLdkQR91LvnK2fEE2oTQpWe6IPwA+HfCUrQ+jwklHAdaHwqkdTfqBa959bEkz6mgNjjRnVyOpl9LesU0x18TAy0PhJUNV4tzdQYNC3vWg0nAShQ2ZqQYZ3zG8upCQPE0FANko1OLybbME/VEhfTcmT+SXiQ==
*/