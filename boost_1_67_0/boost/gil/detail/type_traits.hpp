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
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
*/