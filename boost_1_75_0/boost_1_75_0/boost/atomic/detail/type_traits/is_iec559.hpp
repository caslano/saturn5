/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_iec559.hpp
 *
 * This header defines \c is_iec559 type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_IEC559_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_IEC559_HPP_INCLUDED_

#include <limits>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename T >
struct is_iec559
{
    static BOOST_CONSTEXPR_OR_CONST bool value = !!std::numeric_limits< T >::is_iec559;
};

#if defined(BOOST_HAS_FLOAT128)
// libstdc++ does not specialize numeric_limits for __float128
template< >
struct is_iec559< boost::float128_type >
{
    static BOOST_CONSTEXPR_OR_CONST bool value = true;
};
#endif // defined(BOOST_HAS_FLOAT128)

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_IEC559_HPP_INCLUDED_

/* is_iec559.hpp
+xKfMx8ZVOmKxzTiqX2wiGsHlqesAP5WboC8jSyjQoBY0WkSc8TPe1QOZwfenU9eQ/D0Uksjb8EmFxf8pscA0eyVcIkJLpUVf8OnMBoJMTGIkKAglhhVdjhikIsgJ932KcZXnHIzU6OE8W0WQtYsx0BqGbPCMvxTAJe/i9HK4lQrATG+QV+lXDro+DbYT7T5EF5g4emyGHZKIJaVbUTUgRPg4+FURpq41EHVTpwsdvJiMOms6Kzz8WTN5NGf0PPG0yBZX43c9tF3C8JFIDFcRtSfoz7ndfqFsvo8GGC5l3+R5AR2LYz5TmxZynu4rKaf/I1rYdWDFXWdqVtTbuGHF1/haxF6GSJQPObLleYyyO3w6xt5omVA2UlTB4QM8kcykvhzD5ZB70yvtWnXVXeJrfPOfTfneguHZPNiJK6lSPEI9e4h6KdkJ38aOD2zVYO9fhXdhKUlq8HL8JoeMDjGBpFa9tmb6PLppcAolMkgaROw7YjifvCF8f1woVgE49pkbtNmgLTLPu20r8Xpsfv8sa2EWIXn29fJcbVX+fhqYNoWjBt8/gtdYYfOBgpXZU+jguBvZizKFcdG1Uex9Ubk4SDcwEcUnX0dBi/dnLMzFTn7TYSNJllYkJk5lHzx0W7+KHC2ULGdJ6Odr/SPeZKkYyTjIG6dD0Yem1bJgyYK3XRsdFKJ2pJEz9A0JV4x5mXEYqmSnYUyKWUZZUbr
*/