#ifndef BOOST_MP11_SET_HPP_INCLUDED
#define BOOST_MP11_SET_HPP_INCLUDED

// Copyright 2015, 2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/utility.hpp>
#include <boost/mp11/function.hpp>
#include <boost/mp11/detail/mp_list.hpp>
#include <boost/mp11/detail/mp_append.hpp>
#include <boost/mp11/detail/mp_copy_if.hpp>
#include <boost/mp11/detail/mp_remove_if.hpp>
#include <boost/mp11/detail/mp_is_list.hpp>
#include <type_traits>

namespace boost
{
namespace mp11
{

// mp_set_contains<S, V>
namespace detail
{

template<class S, class V> struct mp_set_contains_impl
{
};

template<template<class...> class L, class... T, class V> struct mp_set_contains_impl<L<T...>, V>
{
    using type = mp_to_bool<std::is_base_of<mp_identity<V>, mp_inherit<mp_identity<T>...> > >;
};

} // namespace detail

template<class S, class V> using mp_set_contains = typename detail::mp_set_contains_impl<S, V>::type;

// mp_set_push_back<S, T...>
namespace detail
{

template<class S, class... T> struct mp_set_push_back_impl
{
};

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

// mp_set_push_front<S, T...>
namespace detail
{

template<class S, class... T> struct mp_set_push_front_impl
{
};

template<template<class...> class L, class... U> struct mp_set_push_front_impl<L<U...>>
{
    using type = L<U...>;
};

template<template<class...> class L, class... U, class T1> struct mp_set_push_front_impl<L<U...>, T1>
{
    using type = mp_if<mp_set_contains<L<U...>, T1>, L<U...>, L<T1, U...>>;
};

template<template<class...> class L, class... U, class T1, class... T> struct mp_set_push_front_impl<L<U...>, T1, T...>
{
    using S = typename mp_set_push_front_impl<L<U...>, T...>::type;
    using type = typename mp_set_push_front_impl<S, T1>::type;
};

} // namespace detail

template<class S, class... T> using mp_set_push_front = typename detail::mp_set_push_front_impl<S, T...>::type;

// mp_is_set<S>
namespace detail
{

template<class S> struct mp_is_set_impl
{
    using type = mp_false;
};

template<template<class...> class L, class... T> struct mp_is_set_impl<L<T...>>
{
    using type = mp_to_bool<std::is_same<mp_list<T...>, mp_set_push_back<mp_list<>, T...> > >;
};

} // namespace detail

template<class S> using mp_is_set = typename detail::mp_is_set_impl<S>::type;

// mp_set_union<L...>
namespace detail
{

template<class... L> struct mp_set_union_impl
{
};

template<> struct mp_set_union_impl<>
{
    using type = mp_list<>;
};

template<template<class...> class L, class... T> struct mp_set_union_impl<L<T...>>
{
    using type = L<T...>;
};

template<template<class...> class L1, class... T1, template<class...> class L2, class... T2> struct mp_set_union_impl<L1<T1...>, L2<T2...>>
{
    using type = mp_set_push_back<L1<T1...>, T2...>;
};

template<class L1, class... L> using mp_set_union_ = typename mp_set_union_impl<L1, mp_append<mp_list<>, L...>>::type;

template<class L1, class L2, class L3, class... L> struct mp_set_union_impl<L1, L2, L3, L...>: mp_defer<mp_set_union_, L1, L2, L3, L...>
{
};

} // namespace detail

template<class... L> using mp_set_union = typename detail::mp_set_union_impl<L...>::type;

// mp_set_intersection<S...>
namespace detail
{

template<class... S> struct in_all_sets
{
    template<class T> using fn = mp_all< mp_set_contains<S, T>... >;
};

template<class L, class... S> using mp_set_intersection_ = mp_if< mp_all<mp_is_list<S>...>, mp_copy_if_q<L, detail::in_all_sets<S...>> >;

template<class... S> struct mp_set_intersection_impl
{
};

template<> struct mp_set_intersection_impl<>
{
    using type = mp_list<>;
};

template<class L, class... S> struct mp_set_intersection_impl<L, S...>: mp_defer<mp_set_intersection_, L, S...>
{
};

} // namespace detail

template<class... S> using mp_set_intersection = typename detail::mp_set_intersection_impl<S...>::type;

// mp_set_difference<L, S...>
namespace detail
{

template<class... S> struct in_any_set
{
    template<class T> using fn = mp_any< mp_set_contains<S, T>... >;
};

} // namespace detail

template<class L, class... S> using mp_set_difference = mp_if< mp_all<mp_is_list<S>...>, mp_remove_if_q<L, detail::in_any_set<S...>> >;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_SET_HPP_INCLUDED

/* set.hpp
1jtlfeXv3hGkP/keKukn7trygMmk9Ji8ln2gg+21bNx/D+7/3dmyP4KymRRPBH0jktdzunckf/WzclOOtuY6U+M05HZs0FJ0ATkEjZlQsWdyWeT1O0i3z0GdbHttcrk8zx9llnVERXvOrTMhQS6y+EaQi1DVR3tHgl5PW4vnnKUz0NfCD+QH7a9fg77RtpZRU6MDPeZB3/Zhe493O7qDxsV2eQL3HF0yGizxoGGo9KMsEjbJDcnVe+TqR5W696rehm5WR3bZ11P97a77esYnnfjNwR65sCeTIjs2yorgd+XPq7N4Peh28Nw6pgGiU7A/bsf+yLUkjiesRf2hiRYKfNA4yd9EVJqVqBIu2uBCRYOBOrSkDDt75H9l64Xwp2CoES85gWvHY6cRdOHP+LkhH17Gfx0Ne0lyGSmE/2JbuNcEiwPdw+9P+FtPwyHkt+jhkx+55+6TH3JSVbA9tBz37I1N2eTgImz9CnOBpQt37IVssmLhmajCUfCi/LUPf5WKPQWny51vcPcEFqN/zbgLTvyZdEeuMDykFLaE8I2Ei0F0UakQtUMOeFxj2gUHFdZupWC0BznSevlORW63fKVvIPpTp9Qq3yia1B29Yon+xJXwE3JF6VKW3CVHQaHcWlRxN2oVVUFO3IleQ0slKugsKOxIKJhLCiodJwsnrrHCc0Thzbhg9GIeajpVD3umgvmkILF/tAtZUoW124L77iF9J+vwZnx4p7kA/dayQXacohquwh/TRekeOhujuxCZBs1a98qzVPSGG9tLMbpyDRe2EDuS81yKUJVuxWYxFxVP6i5EFiiL7EeqVArIVaYaGlUhV+kh/YlGJ0iJDU5ZifYurITSXVyF3xGtxB0bkcW50RYfvyfeYs3bSImYfS3Kj9ChNLLZlO4GkRn9dsWoSmncL2KXWaRKpQCuEp8VUvsvNi0JzaK9s8r2SVWmbzBNF6KibL3YmFGuYq8Wou6VR76+O9EhuQnWy1F+hBW3yM8COToFDzy/W+mOUhprTKrsTKrSiquk0gGd9qKlhENdib0ZlbCrK9FzV5oS+NCWa/7FvZINHq3JFqvZQ8bJJjMZdOhcO4+sS2dguTzlkJOj0Lj1xx7N6MX4OChNajYvQRNntL28FE2cSe6wKaXjmuy8M7FKG6kyce6yqXjDmuoNoneSM/KiF+O+WHsnmwZ2dQ1OT9WA+KKR+CJxsrWjH2WarmyZpytL0nSVr1QWn67CdyS2nJ+gjEv5UYoyriR32JXScWVqk6q0J1RpiVZhzziiaj6wp44oUtwitxjro1JZvMWxjWxK2NWVeDSpSjvxCJmuUpYka7pHyIxIs4Dkpy8gx6sq41R+pPmAWNOHV//tqY+6UmVsAVbxSE5mj5gyesQUb9F/O5sSdnUl9kxVIu6RlGjCpqKMM0UZJWRImrHcytX4lHX3bZmX9Pjwcms+I7b04XVJUpW2xBVkgjnLRbOCuNNXkE9vZVPCrq5E4NaMs1ZtfAWZ4Hl3U6wguWkrSF5Ss7kZIqxctQiL9Ea5GjfOS10pT3vqCmJX8UYuxQqSm7aCFHexaWBX1+DvDUkaqKwg5HR/ZN4MzsjTmnw9ymqXPvmuSGo5L0NokqceX5FYkVyNh5/HbFALeC3qAS855jVzwGtJCnjzFNXiLW66JTHgzcPWVrqlKBb3CDkcT67SrhhVuRqfxxfeohrwYs80/R5fSdI9IyuZAEU2ZBHPdMVXkveVeUs1iv9uPVsU71aP4tevT1FKC0/JVSZAkXYHWQ4Dcc+ETXKLsWkpfSUpWM+Gp+zqeKr35uThpb6SkGUx1SN9A2kOIaomPSq5ytV4wxU3JzokN8Moy804yhSzWNMfFXM=
*/