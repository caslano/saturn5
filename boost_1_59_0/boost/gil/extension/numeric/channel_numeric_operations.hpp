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
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
*/