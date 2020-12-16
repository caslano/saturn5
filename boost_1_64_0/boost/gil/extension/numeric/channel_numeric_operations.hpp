//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_NUMERIC_CHANNEL_NUMERIC_OPERATIONS_HPP
#define BOOST_GIL_EXTENSION_NUMERIC_CHANNEL_NUMERIC_OPERATIONS_HPP

#include <boost/gil/channel.hpp>

namespace boost { namespace gil {

// Function objects and utilities for channel-wise numeric operations.
//
// List of currently defined functors:
//    channel_plus_t (+)
//    channel_minus_t (-)
//    channel_multiplies_t (*)
//    channel_divides_t (/),
//    channel_plus_scalar_t (+s)
//    channel_minus_scalar_t (-s),
//    channel_multiplies_scalar_t (*s)
//    channel_divides_scalar_t (/s),
//    channel_halves_t (/=2)
//    channel_zeros_t (=0)
//    channel_assigns_t (=)

/// \ingroup ChannelNumericOperations
/// \brief Arithmetic operation of addition of two channel values.
/// \note This is a generic implementation; user should specialize it for better performance.
template <typename Channel1, typename Channel2, typename ChannelResult>
struct channel_plus_t
{
    using ChannelRef1 = typename channel_traits<Channel1>::const_reference;
    using ChannelRef2 = typename channel_traits<Channel2>::const_reference;
    static_assert(std::is_convertible<ChannelRef1, ChannelResult>::value,
        "ChannelRef1 not convertible to ChannelResult");
    static_assert(std::is_convertible<ChannelRef2, ChannelResult>::value,
        "ChannelRef2 not convertible to ChannelResult");

    /// \param ch1 - first of the two addends (augend).
    /// \param ch2 - second of the two addends.
    auto operator()(ChannelRef1 ch1, ChannelRef2 ch2) const -> ChannelResult
    {
        return ChannelResult(ch1) + ChannelResult(ch2);
    }
};

/// \ingroup ChannelNumericOperations
/// \brief Arithmetic operation of subtraction of two channel values.
/// \note This is a generic implementation; user should specialize it for better performance.
template <typename Channel1, typename Channel2, typename ChannelResult>
struct channel_minus_t
{
    using ChannelRef1 = typename channel_traits<Channel1>::const_reference;
    using ChannelRef2 = typename channel_traits<Channel2>::const_reference;
    static_assert(std::is_convertible<ChannelRef1, ChannelResult>::value,
        "ChannelRef1 not convertible to ChannelResult");
    static_assert(std::is_convertible<ChannelRef2, ChannelResult>::value,
        "ChannelRef2 not convertible to ChannelResult");

    /// \param ch1 - minuend operand of the subtraction.
    /// \param ch2 - subtrahend operand of the subtraction.
    auto operator()(ChannelRef1 ch1, ChannelRef2 ch2) const -> ChannelResult
    {
        return ChannelResult(ch1) - ChannelResult(ch2);
    }
};

/// \ingroup ChannelNumericOperations
/// \brief Arithmetic operation of multiplication of two channel values.
/// \note This is a generic implementation; user should specialize it for better performance.
template <typename Channel1, typename Channel2, typename ChannelResult>
struct channel_multiplies_t
{
    using ChannelRef1 = typename channel_traits<Channel1>::const_reference;
    using ChannelRef2 = typename channel_traits<Channel2>::const_reference;
    static_assert(std::is_convertible<ChannelRef1, ChannelResult>::value,
        "ChannelRef1 not convertible to ChannelResult");
    static_assert(std::is_convertible<ChannelRef2, ChannelResult>::value,
        "ChannelRef2 not convertible to ChannelResult");

    /// \param ch1 - first of the two factors (multiplicand).
    /// \param ch2 - second of the two factors (multiplier).
    auto operator()(ChannelRef1 ch1, ChannelRef2 ch2) const -> ChannelResult
    {
        return ChannelResult(ch1) * ChannelResult(ch2);
    }
};

/// \ingroup ChannelNumericOperations
/// \brief Arithmetic operation of division of two channel values.
/// \note This is a generic implementation; user should specialize it for better performance.
template <typename Channel1, typename Channel2, typename ChannelResult>
struct channel_divides_t
{
    using ChannelRef1 = typename channel_traits<Channel1>::const_reference;
    using ChannelRef2 = typename channel_traits<Channel2>::const_reference;
    static_assert(std::is_convertible<ChannelRef1, ChannelResult>::value,
        "ChannelRef1 not convertible to ChannelResult");
    static_assert(std::is_convertible<ChannelRef2, ChannelResult>::value,
        "ChannelRef2 not convertible to ChannelResult");

    /// \param ch1 - dividend operand of the two division operation.
    /// \param ch2 - divisor operand of the two division operation.
    auto operator()(ChannelRef1 ch1, ChannelRef2 ch2) const -> ChannelResult
    {
        return ChannelResult(ch1) / ChannelResult(ch2);
    }
};

/// \ingroup ChannelNumericOperations
/// \brief Arithmetic operation of adding scalar to channel value.
/// \note This is a generic implementation; user should specialize it for better performance.
template <typename Channel, typename Scalar, typename ChannelResult>
struct channel_plus_scalar_t
{
    using ChannelRef = typename channel_traits<Channel>::const_reference;
    static_assert(std::is_convertible<ChannelRef, ChannelResult>::value,
        "ChannelRef not convertible to ChannelResult");
    static_assert(std::is_scalar<Scalar>::value, "Scalar not a scalar");
    static_assert(std::is_convertible<Scalar, ChannelResult>::value,
        "Scalar not convertible to ChannelResult");

    auto operator()(ChannelRef channel, Scalar const& scalar) const -> ChannelResult
    {
        return ChannelResult(channel) + ChannelResult(scalar);
    }
};

/// \ingroup ChannelNumericOperations
/// \brief Arithmetic operation of subtracting scalar from channel value.
/// \note This is a generic implementation; user should specialize it for better performance.
template <typename Channel, typename Scalar, typename ChannelResult>
struct channel_minus_scalar_t
{
    using ChannelRef = typename channel_traits<Channel>::const_reference;
    static_assert(std::is_convertible<ChannelRef, ChannelResult>::value,
        "ChannelRef not convertible to ChannelResult");
    static_assert(std::is_scalar<Scalar>::value, "Scalar not a scalar");
    static_assert(std::is_convertible<Scalar, ChannelResult>::value,
        "Scalar not convertible to ChannelResult");

    /// \param channel - minuend operand of the subtraction.
    /// \param scalar - subtrahend operand of the subtraction.
    auto operator()(ChannelRef channel, Scalar const& scalar) const -> ChannelResult
    {
        // TODO: Convertion after subtraction vs conversion of operands in channel_minus_t?
        return ChannelResult(channel - scalar);
    }
};

/// \ingroup ChannelNumericOperations
/// \brief Arithmetic operation of channel value by a scalar.
/// \note This is a generic implementation; user should specialize it for better performance.
template <typename Channel, typename Scalar, typename ChannelResult>
struct channel_multiplies_scalar_t
{
    using ChannelRef = typename channel_traits<Channel>::const_reference;
    static_assert(std::is_convertible<ChannelRef, ChannelResult>::value,
        "ChannelRef not convertible to ChannelResult");
    static_assert(std::is_scalar<Scalar>::value, "Scalar not a scalar");
    static_assert(std::is_convertible<Scalar, ChannelResult>::value,
        "Scalar not convertible to ChannelResult");

    /// \param channel - first of the two factors (multiplicand).
    /// \param scalar - second of the two factors (multiplier).
    auto operator()(ChannelRef channel, Scalar const& scalar) const -> ChannelResult
    {
        return ChannelResult(channel) * ChannelResult(scalar);
    }
};

/// \ingroup ChannelNumericOperations
/// \brief Arithmetic operation of dividing channel value by scalar.
/// \note This is a generic implementation; user should specialize it for better performance.
template <typename Channel, typename Scalar, typename ChannelResult>
struct channel_divides_scalar_t
{
    using ChannelRef = typename channel_traits<Channel>::const_reference;
    static_assert(std::is_convertible<ChannelRef, ChannelResult>::value,
        "ChannelRef not convertible to ChannelResult");
    static_assert(std::is_scalar<Scalar>::value, "Scalar not a scalar");
    static_assert(std::is_convertible<Scalar, ChannelResult>::value,
        "Scalar not convertible to ChannelResult");

    /// \param channel - dividend operand of the two division operation.
    /// \param scalar - divisor operand of the two division operation.
    auto operator()(ChannelRef channel, Scalar const& scalar) const -> ChannelResult
    {
        return ChannelResult(channel) / ChannelResult(scalar);
    }
};

/// \ingroup ChannelNumericOperations
/// \brief Arithmetic operation of dividing channel value by 2
/// \note This is a generic implementation; user should specialize it for better performance.
template <typename Channel>
struct channel_halves_t
{
    using ChannelRef = typename channel_traits<Channel>::reference;

    auto operator()(ChannelRef channel) const -> ChannelRef
    {
        // TODO: Split into steps: extract with explicit conversion to double, divide and assign?
        //double const v = ch;
        //ch = static_cast<Channel>(v / 2.0);
        channel /= 2.0;
        return channel;
    }
};

/// \ingroup ChannelNumericOperations
/// \brief Operation of setting channel value to zero
/// \note This is a generic implementation; user should specialize it for better performance.
template <typename Channel>
struct channel_zeros_t
{
    using ChannelRef = typename channel_traits<Channel>::reference;

    auto operator()(ChannelRef channel) const -> ChannelRef
    {
        channel = Channel(0);
        return channel;
    }
};

/// \ingroup ChannelNumericOperations
/// structure for assigning one channel to another
/// \note This is a generic implementation; user should specialize it for better performance.
template <typename Channel1, typename Channel2>
struct channel_assigns_t
{
    using ChannelRef1 = typename channel_traits<Channel1>::const_reference;
    using ChannelRef2 = typename channel_traits<Channel2>::reference;
    static_assert(std::is_convertible<ChannelRef1, Channel2>::value,
        "ChannelRef1 not convertible to Channel2");

    /// \param ch1 - assignor side (input) of the assignment operation
    /// \param ch2 - assignee side (output) of the assignment operation
    auto operator()(ChannelRef1 ch1, ChannelRef2 ch2) const -> ChannelRef2
    {
        ch2 = Channel2(ch1);
        return ch2;
    }
};

}}  // namespace boost::gil

#endif

/* channel_numeric_operations.hpp
lXEHZNIFRnZlPYzrsihTK6CVboI62cR9PMebphrepoM0dqeZyt32XC/T2Q6FxrdT6E2ABrPYmJXut2ws9DWXM8RbGEowZ9W7L9TBmAy7zhaaS4/IJunDUEPTZLQNLja7MwS8EOrFxRRrHU2iZRzTzqrhl5Ex6dPBFEgxzAIhGJugOXoqwBwVMFML85CpVD10WpkRjTn7Qe0wqSn+48H9etLr1GhNEc08jAiYLU7eWkEupoid3hIEuquwDzmoIaKc91ZgAO5sjEi3IBJ6FY70fgw+D5p8uC2ZG5m7getaXVTr6SZAradSplcQkVn7fZ20jxv5uAtxiN4c6DdUdLgc3ZyYUUXHPxqRQpugI7IQ3+alLXLstJCvYl2bkyp34IuTXMnF0oVUy/Y62n/RzBnwEpBbmblIivq6jFYfrurXkZmoP472UI0v6P9a/BUF5D9L29qI+jnHnXnst8sckLMTA/0icgalpaWdD+Ysf/fd1kn+dYlrTaOkyHWJ50+u/S3Svw5fkYU9AlXxP+UuXVAmgIxpRQpqZURtBVfCFPZrBcj2YnH0z41vgXnwUrhf9xCb4rukbax7MMdBTfVsVugNmkEgSWHQWk1m8e1StQnxfP98LefGEUwttj0BD63TSzy0KxLg+taGxdoBtMScthEaH3A2wFdrVbgbwq8uotEaucjss0BjzTbxpRhzfxuR+K4gHyeEO5Dwswj2ix47NFn00bSR3+kyuURN3qdeZfIetx1WSJmL9EaavvyPNl8KKd1WKWG0G+Iu7rbxlqhkla/dmh/QHWjBASMd/V00pjDHdwbG6gKJljLKDJLq8M1G3WFxgyUyfTkucSNqZjXio8LvHDtE7I4qtWFXUvvlhfLUYkANVBibBG1qZpRQ8q1KzLzD4asbth/iVcPZuaARHAp/ilzhKgDruHKMGY02LNvG9UGwH9M2zpzc5EQKtCUeLLBaArDH4DcDBVAr7eYKEt5XP3vhUxusswBIFQeU/vPwJaCIfzMb8/TCWuXc8jvFnb/LKdcN1CgoUISz+ULx17gKVnsbASBG1vgpFN1iaAriB2usHoER5ZIdhKkriRTzUG2vqZond4OlQW+IUlP5OPPkkoPJOrFjCgSsD82+Yr3J7Iz3hf3fuVafbaR7blpPDR5SLdwpVG+WixB6TzBGGiUtRqwPYJdOZoC1lI3KPgUh6WpFSIkx5zZFiBWqnwDl5j9CadkkapVM0xPDCigRhP98hS5XKAN25muBedOB1xKkRZ8ynHg1Nn6eokAxEUArKuHLbfg2zXg1T5foAJLykpmvT1oe0EI/QkJpC3ELpY68Gw6zjvDHWVZM4ygVZmcS7ZhrNoV3A2eng0DFS8KQJnd5YrbvIemNpgpShTrRPrmwNtmy3ru+QOIN5Pl3ez3/RnTz7FeCuxS43jHEexF4WoI48lnto6Rah3JfxuQWiuHCnaGXAehCwLSLrIxqWhl1GOVSpERZBow5xHgQGFSEXkjy3SQb3hkInMFAj7w4ZHW8UcgMFS5s0d/tCMThzRJ0gdU4DSrD8QMm6p9qTHVXmfzhn/lSzNuY1gb4EWPeWr3/1k5Kfcd0NZiR+aVAXYCaXqAZ3PwbTxWm46yC5MGHrcjXlNgsTAc5iSszC2f8kpL3RdncyTXPb9brJcyP18v4+eSmCvL5Lj7Z57Dtwi5ARUm0SBu7HT3BPClMnmvVwAYxAE3pCNAQgPR185hxxwBcXAfAXhHajuc2ivLmPYAvYPx2CoeltYMacrMnMCyu/H0k16oaQG5Nyk5F9gSGOGGTbjkiwCbdYYR2ZRI/WovwS0poIOFMYovTTmKihrRDEnUeupL+5tuB+bqzPP0BZfQP1kY=
*/