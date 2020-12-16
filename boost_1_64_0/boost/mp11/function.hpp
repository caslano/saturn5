#ifndef BOOST_MP11_FUNCTION_HPP_INCLUDED
#define BOOST_MP11_FUNCTION_HPP_INCLUDED

// Copyright 2015-2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/mp11/detail/mp_list.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/mp11/detail/mp_plus.hpp>
#include <boost/mp11/detail/mp_min_element.hpp>
#include <boost/mp11/detail/mp_void.hpp>
#include <boost/mp11/detail/config.hpp>
#include <type_traits>

namespace boost
{
namespace mp11
{

// mp_void<T...>
//   in detail/mp_void.hpp

// mp_and<T...>
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1910 )

namespace detail
{

template<class... T> struct mp_and_impl;

} // namespace detail

template<class... T> using mp_and = mp_to_bool< typename detail::mp_and_impl<T...>::type >;

namespace detail
{

template<> struct mp_and_impl<>
{
    using type = mp_true;
};

template<class T> struct mp_and_impl<T>
{
    using type = T;
};

template<class T1, class... T> struct mp_and_impl<T1, T...>
{
    using type = mp_eval_if< mp_not<T1>, T1, mp_and, T... >;
};

} // namespace detail

#else

namespace detail
{

template<class L, class E = void> struct mp_and_impl
{
    using type = mp_false;
};

template<class... T> struct mp_and_impl< mp_list<T...>, mp_void<mp_if<T, void>...> >
{
    using type = mp_true;
};

} // namespace detail

template<class... T> using mp_and = typename detail::mp_and_impl<mp_list<T...>>::type;

#endif

// mp_all<T...>
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=86355
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 ) || BOOST_MP11_WORKAROUND( BOOST_MP11_GCC, != 0 )

template<class... T> using mp_all = mp_bool< mp_count_if< mp_list<T...>, mp_not >::value == 0 >;

#elif defined( BOOST_MP11_HAS_FOLD_EXPRESSIONS )

template<class... T> using mp_all = mp_bool<(static_cast<bool>(T::value) && ...)>;

#else

template<class... T> using mp_all = mp_and<mp_to_bool<T>...>;

#endif

// mp_or<T...>
namespace detail
{

template<class... T> struct mp_or_impl;

} // namespace detail

template<class... T> using mp_or = mp_to_bool< typename detail::mp_or_impl<T...>::type >;

namespace detail
{

template<> struct mp_or_impl<>
{
    using type = mp_false;
};

template<class T> struct mp_or_impl<T>
{
    using type = T;
};

template<class T1, class... T> struct mp_or_impl<T1, T...>
{
    using type = mp_eval_if< T1, T1, mp_or, T... >;
};

} // namespace detail

// mp_any<T...>
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=86356
#if defined( BOOST_MP11_HAS_FOLD_EXPRESSIONS ) && !BOOST_MP11_WORKAROUND( BOOST_MP11_GCC, != 0 ) && !BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 )

template<class... T> using mp_any = mp_bool<(static_cast<bool>(T::value) || ...)>;

#else

template<class... T> using mp_any = mp_bool< mp_count_if< mp_list<T...>, mp_to_bool >::value != 0 >;

#endif

// mp_same<T...>
namespace detail
{

template<class... T> struct mp_same_impl;

template<> struct mp_same_impl<>
{
    using type = mp_true;
};

template<class T1, class... T> struct mp_same_impl<T1, T...>
{
    using type = mp_all<std::is_same<T1, T>...>;
};

} // namespace detail

template<class... T> using mp_same = typename detail::mp_same_impl<T...>::type;

// mp_similar<T...>
namespace detail
{

template<class... T> struct mp_similar_impl;

template<> struct mp_similar_impl<>
{
    using type = mp_true;
};

template<class T> struct mp_similar_impl<T>
{
    using type = mp_true;
};

template<class T> struct mp_similar_impl<T, T>
{
    using type = mp_true;
};

template<class T1, class T2> struct mp_similar_impl<T1, T2>
{
    using type = mp_false;
};

template<template<class...> class L, class... T1, class... T2> struct mp_similar_impl<L<T1...>, L<T2...>>
{
    using type = mp_true;
};

template<template<class...> class L, class... T> struct mp_similar_impl<L<T...>, L<T...>>
{
    using type = mp_true;
};

template<class T1, class T2, class T3, class... T> struct mp_similar_impl<T1, T2, T3, T...>
{
    using type = mp_all< typename mp_similar_impl<T1, T2>::type, typename mp_similar_impl<T1, T3>::type, typename mp_similar_impl<T1, T>::type... >;
};

} // namespace detail

template<class... T> using mp_similar = typename detail::mp_similar_impl<T...>::type;

#if BOOST_MP11_GCC
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wsign-compare"
#endif

// mp_less<T1, T2>
template<class T1, class T2> using mp_less = mp_bool<(T1::value < 0 && T2::value >= 0) || ((T1::value < T2::value) && !(T1::value >= 0 && T2::value < 0))>;

#if BOOST_MP11_GCC
# pragma GCC diagnostic pop
#endif

// mp_min<T...>
template<class T1, class... T> using mp_min = mp_min_element<mp_list<T1, T...>, mp_less>;

// mp_max<T...>
template<class T1, class... T> using mp_max = mp_max_element<mp_list<T1, T...>, mp_less>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_FUNCTION_HPP_INCLUDED

/* function.hpp
DAoXPphd2mPlUHyMHRGb4NNiL4W8YEoAFlo59NCzH+8W315IYS8ki46T5lNvQplxps6I43ZpcKnN613qn3D7oFnnw90b7qfgngv3Pl+51PEQZwqEL4D7ygYIg++lX8fZOoNRsg0XYLFo2Bx/+VIk+98EurOXju/sd1ZK++gWmNLgsCSsoklP9KD7B+tH1Br+H860YA+9tckees7urZttsYfW/P+eqft/ZGL4uE9eKs6BsSFLuCEusAAzt7G3dkaODnyr6P2xl3r/P4u4P47oAdhZgQ7wdZFhcg099PEHUNUD3+nxkDmLiyyYQxv279CXBNaJDHBHZLCNSVJ3Y5RnfMKRso56/ptgL1n4loMQHh93WVJ75zPoVX52cgJ7534nW7V3Ls5KYO9cAeXHSlEB2Duz5lHuDzqFdsd2z+zFMbx5Vyqzg/bOBYR/nK6fXyw6W7Q8LCDHnT4easj0mffYkOkzzojB9PkbF/XvsCD9wA+a6TNIyBiQNrKEGh48kt4RoeHByfCqxhxt2D37THbPXt3u2TmKDVjnu8y2xlNc+qoGxdd24sDR5fBJtsZNZGu8b+RAk61xM9ka9w6ew1TMFFS8cRSXMQ4NjXeDeE6M1x8L4ARlnOBmkWCmlmB7YWWcS1bGzcVBk10pNYR3TjOsjH+BbIUVeO9gBed5g8hzPy3PlU7DxDgX91fpJsZVEMIFoCq4pNBkYpxfElbLY811K8bw/7DjVBOCjibGIW4rsSbGi8ZT8Uy+ycTYq5sYXzKSYgSq9aZ2ERFeySkbuzuN86oK6FWRZfEawwj3/GOFISvpQO4SQeujJzGtYieGd6RowYbBLrY4//R1YgXqkWFiqjIgyA7E8/bm3JFfHtF35uOrDK/q27qZ/NiIAoftI3RlrPD4cKgkn5TmvqL9vD6AIpCpq4tmZZhFBtQFursn4hnoBAZWjEslynsfwAycozPwbGLggZyycQ0dv6nbzjaitsRKXnH4pv3Mtr5lEzXTqN7HsHvHBYpJYyZyvj8yFTmPjzCOzWdyziNy5mJKww5kpImkSJZYjxwY2ZlU6G2wh6PeoERs0Dd6Xmdku8bVeHoNxkSlkuysu9C0T4+pdcM3TYq41Fq4lzS51Cu+c6kHQQ8y7/v/bXytXgb+d6JpvBBgAKn20IUXGF4VNNESEEc0sg81rAV9NEnDzr2U1l+nnUCPTH68tGayOa+J02oN/AbqCrwEgu9MC8BnIdxCzbSXZtR2XiHF4aZDCxt9pCDUWP9BVP8TYvxPj15rRlI+WTr6Q0YOVhVQp4I7TN+HXzpqAhyqxgngRT91Zys1L/gv51rAqZfTLgXDmnTIBPoViLeqtBonkPlniP7rw5I2oEuYWLS2avQnOIiW98IJ3BW5vEsiOJAP7KZhUBz+PIb6Ay/Gq9gZJnol4T6ZBhcZl9lxDxMXga7QAX3o+VHZTCmUR85/p53Umnro36LL8P93nIbv3Pxj90T4zumbLOM7xdTTQn5HYT8Tb8BghsN8bHxIOA8qHwH/tbum0RIogDyzfiOQp+9vCPKoZgOqLmnG7zSMjwSeJt6uF7CBKice0J9gK/NH7vitzKhx0FbmJm0KrmlfoSK2oqKp+P1us8nWTPwnMm+c5jaouZh/U1ETMBZuRs88VshVFMC5beiVNxZRTM79AFMOe1JJ0dLwTywtGz+BEqkRVp9lQoacZV7ChNQIVLN1as0IkGSkuCe0xalv4E5utAKDWrWmYRBS/bmLjfgO6Nv4gYsKISyhLx+D37hQnHjcjxb40Ak8k3/YMSbyZ25N5Ed6cSQkGdsaEZj5A7W1xkmYO0YeXKAr2gibePmYfFikoLPxjeP3MTVtp3/je84=
*/