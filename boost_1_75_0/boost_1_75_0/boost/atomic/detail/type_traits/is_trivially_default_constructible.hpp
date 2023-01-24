/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_trivially_default_constructible.hpp
 *
 * This header defines \c is_trivially_default_constructible type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#else
#include <boost/type_traits/has_trivial_constructor.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
using std::is_trivially_default_constructible;
#elif !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
template< typename T >
using is_trivially_default_constructible = boost::has_trivial_constructor< T >;
#else
template< typename T >
struct is_trivially_default_constructible : public boost::has_trivial_constructor< T > {};
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_HPP_INCLUDED_

/* is_trivially_default_constructible.hpp
gs6dz22cjG8sgBGsC15xWOW3Lm/6UXTVqvSG3kM37EYY9JvT1aQz5Z95p13IC04YR64kU/mKf3C/f2OT0nMoej6e5XjU6ZJAPiukMQbhtkwgdZ2TNlQYxVGZFDNKbviRzcs4k96ApQdc4RAuWFj+rsqUy6E73+CAjs9uddv+6Xv1Xgv2s4T+UasSL0o27uJba03Ur/nmvXOqnXSsJ2OptqxnOgwBDiwCGfvtWI2WGmPq42nzoK90A85Wkk6w0T/S7f1IoI7o/CMj5yyOK+loxRCQHzQqAuz47Wm3AmaXldjfns7gmCgBZM1gp3C6sQuk0V5+t7HuBo/K/PZ0xHlV2O9PkTRlYDIym2xYuHJlAt30I6zR2mdpzXrTWABpk5NhxQUgFdkjue1ImoKiZmd8QfJMPWSvareyIYcIff8Sgacw90Y5V6VpUz0zpqq9FaVFE6Pl3vR4FelyDwXtA5OjLF1pQBI11ngR+6GNpBdX5gvLUg3WEtIEO62h1AUzUAWgZoGGuoz3WuNd0M+u8M6tmcR5juOwOopSoa28RzAyh6CM18BBb6zs0QaE4hvqzCz7LAzyLm8o+1IbV9y4MJafGE4Y8BLrjANKA6MIiBHFcr6LhLz0XyyYa7r8aFwqBugLHXvkFP6peEkALtPexoXHwnN75cAFnIRbD+N8kQ9HukU79E4HD9G7FRgfR9QO5EfYKBc5BrgE2bzjNcla
*/