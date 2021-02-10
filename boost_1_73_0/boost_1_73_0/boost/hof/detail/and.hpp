/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    and.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_AND_H
#define BOOST_HOF_GUARD_AND_H

#include <type_traits>
#include <boost/hof/detail/using.hpp>
#include <boost/hof/detail/intrinsics.hpp>

namespace boost { namespace hof { namespace detail {

constexpr bool and_c()
{
    return true;
}

template<class... Ts>
constexpr bool and_c(bool b, Ts... bs)
{
    return b && and_c(bs...);
}

#ifdef _MSC_VER

template<class... Ts>
struct and_;

template<class T, class... Ts>
struct and_<T, Ts...>
: std::integral_constant<bool, (T::value && and_<Ts...>::value)>
{};

template<>
struct and_<>
: std::true_type
{};

#define BOOST_HOF_AND_UNPACK(Bs) (boost::hof::detail::and_c(Bs...))
#else
template<bool...> struct bool_seq {};
template<class... Ts>
BOOST_HOF_USING(and_, std::is_same<bool_seq<Ts::value...>, bool_seq<(Ts::value, true)...>>);

#define BOOST_HOF_AND_UNPACK(Bs) BOOST_HOF_IS_BASE_OF(boost::hof::detail::bool_seq<Bs...>, boost::hof::detail::bool_seq<(Bs || true)...>)

#endif

}}} // namespace boost::hof

#endif

/* and.hpp
6lAisbrF2mfrDZQt1uanzFDwxr/FzkRvYDU3QbAFxwtyrnjg45bTqJD7Q694uZn16nbLiLzSD/TlZUAijelqIDwnB0jwbDClfdQ7qZ5MtpCQbiLgQXbSUF2RGxXVI2yNHXGj1pSQ+x1evYmj4OI+JixaiR2u0pm+EeE5D70oBOukp00yRWoGnkCtBpqGTVuqPgRyLJqyoSh7J2eUYOiciYcjwLfy2Y4KuL0XbODtBnwA2QmPvasIMreEIEZJBoEMX5jS9XCszhVbF+mbjrMzphXyPPCDYuXH3h14N8gg4pbYHLHAELpQcukEZ9mNElpQ7dSbuvA609XOsDyQlVGfaejUEQaKrD4Rvpmo8fgxo69Ov9mQq1ptyrSuoztWqGpdsipvTgfXJoTt3TP+fdDVurppI5umhHGD7loxrsS3r49YaeE/lhqzzz6b/r0SSSphyw4J7C6O7ni31ftY3rqZjzY5IxbCEP1ObuN6SukczFh9U9Kypi+0gZZdoV3q9ITui/+fHaEtg7v1g40ZI9098zG6wof0ah1BuSPJq5Fe9T2XAhfsf0zzr2Sa5bSPNcOjJ35arqrrmP/B97XZH7kfR5o+Xm4nQ7evuoZFKgo5M4vjtaa5HWs7JVbGrxKkXGExo3J86Z6eN7cxaaw9
*/