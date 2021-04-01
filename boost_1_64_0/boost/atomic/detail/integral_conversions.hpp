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

#endif // BOOST_ATOMIC_DETAIL_INTEGRAL_CONVERSIONS_HPP_INCLUDED_

/* integral_conversions.hpp
7X4vQ57mE719eHI5WeafYoSdVUx3Hnwxbb/eCii2xK9bGhHyik0kw9bImdFgv2EDYLLmprwcMmhRArxkxlPyjQGHBbmzixPIU08aIFanjGLlnC7dcIhzxUQmIeXUXPIX1OWVZ53jH0lwbL+owLrGQ6+XScBWfy2AH/QgrOarhC1OxIvVZ/ZmZjQSwpw96wpT4K77B/MXBCCasxBBt3c3+QdQ7+Pl09qk61dN0fg0OV/Y11bDObXb9vr5kbjcWyfh25bTq9Tz1aLiZ230z3w7AUK+ZZl5MISaDfErd0JySg9eFvK7ed0zHfVrOzUI1a+9WGE7lXjnzGiUcyf4WDo1gBTaB6pMlzWVWP3IBTDwcdUxjyjDAXr7s3sfS04/LV0GhgIOLwYKVw7aPknNBC22/0I/J8vJCZevZBxGCf0NQMqPqQY2GgXzxr0WU4ypdhVeJ9Q6ygruxPZJXoVUIXFq3QPf95F+j+KK6zuyVsDYWaHNPvKjUVH6neq3IhZzyhpokGnlSp1A46riyiYpRzQUpx+UNuOmozaM961x1uPiIH0A8qNXIp+V/CyGbA==
*/