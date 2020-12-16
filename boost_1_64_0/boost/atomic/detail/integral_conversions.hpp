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
LkH6dLzKT6bdvurIB2elJiUlBbsnJQT7onU9YDFhVOqo1DN1sZij6IHvGN1GrEbKmRdzjPaCXaR9LrKyJG6bNLexLdcORI9d1dOdIvcOZ/MC3RZKm22fyNZY4zkLfihyFRyTuOuYN7BtIPlEjXPt36lS1gF+fdvuWM+GXUX2ZFmbJ42+mpQSGuu3O2M99ezU4TLM6cdjHudO2R6XOhT6lc13rJ9v04eSZrWVJfFwOzSwra+dJPrihCzVmQWUeZujM6mFacFulvl2d47qVkfeUzTC5nydD/SdxMYY80GT//WJGfu58i86iZKPgN+HznXh4ZaIsc+FkPea0Ix9lT3dtMnYrznx5oDvuNd1M6aJzM0BnQc0j3n+41rf7+RKmq9LmmKTZqI5Fw2T/VMCj1iz9XoGT/oPqT9+nbeSdd4Kff/eR9LsDTxi38K2aek9tLGf/bqzfYVuQ5DfpySvDTouVBd0MIa+jS+XdH2kzIXER0n+uygz9cqQNBOpmbGlm4+803YBPfcVmTIPk+PslYvVsrCPCx27syTfqwKuuc2MzVWy7592lrHxc+4rFpTVl5WwkkpY35+UY2/XeOi42a7jUlI9cmhNlwmS952BcBvQnp5z/W5HBu3P0PmoSeIH7Wy2RbYdCbV/i+AQkXtQ2uopGWtLy7BjMvazGaY+bJe3aVaE3W6DpfuYN0L7imE3c8za5ZYebzY8XY63JZAVUSaXLan2aX9ppyqsHedK2ulsG6867u5XyzWX3PU1MycTD7XBYdbP+Ry+mbe3+YFJIRVzwArxnbDAzAV/Ds0FKrMTmWY5z6xJS+zJqSk/LTHR8j83hfJ9jDT3OGmOa2z2zjGDVKb++ND8+RfnrCXz5xjmz7Suxz5/OuPvd1JHn7HnnTu1jf4m8pNitpG7Ptso62qnPseveyhUnws8dX4EmeUyt64zdZ7nkTmITKPks/7BWPkkdDcyO2LJMEdpedY3eWVOJ96N+Bl5be1WCKcQWgiTCJMJD9OOJ8GdhLN7oKukXa/BOQccsHx/09iNnpyS3iLvn205H1h29P1qsu1/Puhu+18f1kDGHNtlzJn33Iw3tpnxZu55Gyzd7lq36nQ9pzzKvyJLOE7DeM4pTXvknFK3uMTjqqO6YWnI5mAsctjeL3bZHGi6LDM+0PV2/FzkRtwvkh/lJD8t41Qt4+6M6DJmItsSq4w1y2pKFtZWoL96LokuJ2mNb4vdcn/oJFjYUF3uev7hqcsFx1AXjql1Cfux4DhsM8eJ6IfGzOg6nkgdD8Sq4/KyJQ0VMftB02W5v3lYsFL3cyiz38w3x1A3dz9lRPjo4Bjad6dovd7wqVcK6Q9H1Gui8zQL1VqyhN3hubUDZXJfH13dI/pYp3Os7g9HHgsVlnaZHN1uyHZefyebdolsg9Ke0eXKQTbfUy6jtqq3e330ljRGb5/P8NVbZDqvt3t99JbjROntSVq3/KzounWlbsXeujXUVbZXL+SNvg6XetWY9aJmufabc0Un6xTS1+FSJzlGRH2sXtH1KaQ+NZ766PCLpUfItzv+2N/58Te5A+PvXfiYHcvu59jtdfztk2LZ8cSyT4plzxTLXieWPVMsO6SYdjOx7X7E3qjpjsWv7k76zNsVX374guCBtEGx7HVi2ffEsk+KZZcTy24ptn3PX8Ufi/zkGvQwvIWw3PV3o/kbWf7ept/BNbu23+P6+zYjA11/85xE1vO4w5n/9O8W9U3TaOmze30/kev5nmCgywdJHhwKp8NhcAacCC+Ao2E5HAM3wLHwGt2/FRbAXXA8/DE8AT4OJxrfNfosW5/X53p81zyI3DjYAqfBr8Ei+BA8D+6BJfBhuBDuhdXwG7A=
*/