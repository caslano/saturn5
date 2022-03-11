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