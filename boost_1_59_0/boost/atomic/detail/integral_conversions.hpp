/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/integral_conversions.hpp
 *
 * This header defines sign/zero extension and truncation utilities for Boost.Atomic. The tools assume two's complement signed integer representation.
 */

#ifndef BOOST_ATOMIC_DETAIL_INTEGRAL_CONVERSIONS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_INTEGRAL_CONVERSIONS_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/bitwise_cast.hpp>
#include <boost/atomic/detail/type_traits/integral_constant.hpp>
#include <boost/atomic/detail/type_traits/is_signed.hpp>
#include <boost/atomic/detail/type_traits/make_signed.hpp>
#include <boost/atomic/detail/type_traits/make_unsigned.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename Output, typename Input >
BOOST_FORCEINLINE Output zero_extend_impl(Input input, atomics::detail::true_type) BOOST_NOEXCEPT
{
    // Note: If we are casting with truncation or to the same-sized output, don't cause signed integer overflow by this chain of conversions
    return atomics::detail::bitwise_cast< Output >(static_cast< typename atomics::detail::make_unsigned< Output >::type >(
        static_cast< typename atomics::detail::make_unsigned< Input >::type >(input)));
}

template< typename Output, typename Input >
BOOST_FORCEINLINE Output zero_extend_impl(Input input, atomics::detail::false_type) BOOST_NOEXCEPT
{
    return static_cast< Output >(static_cast< typename atomics::detail::make_unsigned< Input >::type >(input));
}

//! Zero-extends or truncates (wraps) input operand to fit in the output type
template< typename Output, typename Input >
BOOST_FORCEINLINE Output zero_extend(Input input) BOOST_NOEXCEPT
{
    return atomics::detail::zero_extend_impl< Output >(input, atomics::detail::integral_constant< bool, atomics::detail::is_signed< Output >::value >());
}

//! Truncates (wraps) input operand to fit in the output type
template< typename Output, typename Input >
BOOST_FORCEINLINE Output integral_truncate(Input input) BOOST_NOEXCEPT
{
    // zero_extend does the truncation
    return atomics::detail::zero_extend< Output >(input);
}

template< typename Output, typename Input >
BOOST_FORCEINLINE Output sign_extend_impl(Input input, atomics::detail::true_type) BOOST_NOEXCEPT
{
    return atomics::detail::integral_truncate< Output >(input);
}

template< typename Output, typename Input >
BOOST_FORCEINLINE Output sign_extend_impl(Input input, atomics::detail::false_type) BOOST_NOEXCEPT
{
    return static_cast< Output >(atomics::detail::bitwise_cast< typename atomics::detail::make_signed< Input >::type >(input));
}

//! Sign-extends or truncates (wraps) input operand to fit in the output type
template< typename Output, typename Input >
BOOST_FORCEINLINE Output sign_extend(Input input) BOOST_NOEXCEPT
{
    return atomics::detail::sign_extend_impl< Output >(input, atomics::detail::integral_constant< bool, sizeof(Output) <= sizeof(Input) >());
}

//! Sign-extends or truncates (wraps) input operand to fit in the output type
template< typename Output, typename Input >
BOOST_FORCEINLINE Output integral_extend(Input input, atomics::detail::true_type) BOOST_NOEXCEPT
{
    return atomics::detail::sign_extend< Output >(input);
}

//! Zero-extends or truncates (wraps) input operand to fit in the output type
template< typename Output, typename Input >
BOOST_FORCEINLINE Output integral_extend(Input input, atomics::detail::false_type) BOOST_NOEXCEPT
{
    return atomics::detail::zero_extend< Output >(input);
}

//! Sign- or zero-extends or truncates (wraps) input operand to fit in the output type
template< bool Signed, typename Output, typename Input >
BOOST_FORCEINLINE Output integral_extend(Input input) BOOST_NOEXCEPT
{
    return atomics::detail::integral_extend< Output >(input, atomics::detail::integral_constant< bool, Signed >());
}

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_INTEGRAL_CONVERSIONS_HPP_INCLUDED_

/* integral_conversions.hpp
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
*/