//
// Copyright 2017-2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_DETAIL_TYPE_TRAITS_HPP
#define BOOST_GIL_DETAIL_TYPE_TRAITS_HPP

#include <boost/config.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

#if defined(BOOST_LIBSTDCXX_VERSION) && BOOST_LIBSTDCXX_VERSION < 50100

template<class T>
struct is_trivially_default_constructible
    : std::integral_constant
    <
        bool,
        std::is_default_constructible<T>::value &&
        std::has_trivial_default_constructor<T>::value
    >
{};

#else

using std::is_trivially_default_constructible;

#endif

using std::is_trivially_destructible;

}}} //namespace boost::gil::detail

#endif

/* type_traits.hpp
nDMiYjqEozD8zxEPClu0EF9uG0/1x89/ufDvFGuetsc1xtir9YIwbEqs2AkKm2Q1i86mbvUUl8FXppWJu1KLjHSlizXaXu160ZfSyu0GVZhMUW+cMDpQYYrMztS299MsAatliUL6wW4sYl+SuaT0DryoBhsdV/Uv0ur3qCtfu1vrS5wmHqHc7/Oc1BbrC8ye4j1zh/iJtVGE3NeLDiwI3w9QkhZAigoq0F5zORQlm7h4i70nrnaN1h/RsJCZ3PQ=
*/