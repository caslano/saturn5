//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_NUMERIC_PIXEL_NUMERIC_OPERATIONS_HPP
#define BOOST_GIL_EXTENSION_NUMERIC_PIXEL_NUMERIC_OPERATIONS_HPP

#include <boost/gil/extension/numeric/channel_numeric_operations.hpp>

#include <boost/gil/color_base_algorithm.hpp>
#include <boost/gil/pixel.hpp>

namespace boost { namespace gil {

// Function objects and utilities for pixel-wise numeric operations.
//
// List of currently defined functors:
//   pixel_plus_t (+)
//   pixel_minus_t (-)
//   pixel_multiplies_scalar_t (*)
//   pixel_divides_scalar_t (/)
//   pixel_halves_t (/=2),
//   pixel_zeros_t (=0)
//   pixel_assigns_t (=)

/// \ingroup PixelNumericOperations
/// \brief Performs channel-wise addition of two pixels.
/// \tparam PixelRef1 - models PixelConcept
/// \tparam PixelRef2 - models PixelConcept
/// \tparam PixelResult - models PixelValueConcept
template <typename PixelRef1, typename PixelRef2, typename PixelResult>
struct pixel_plus_t
{
    auto operator()(PixelRef1 const& p1, PixelRef2 const& p2) const -> PixelResult
    {
        PixelResult result;
        static_transform(p1, p2, result,
            channel_plus_t
            <
                typename channel_type<PixelRef1>::type,
                typename channel_type<PixelRef2>::type,
                typename channel_type<PixelResult>::type
            >());
        return result;
    }
};

/// \ingroup PixelNumericOperations
/// \brief Performs channel-wise subtraction of two pixels.
/// \tparam PixelRef1 - models PixelConcept
/// \tparam PixelRef2 - models PixelConcept
/// \tparam PixelResult - models PixelValueConcept
template <typename PixelRef1, typename PixelRef2, typename PixelResult>
struct pixel_minus_t
{
    auto operator()(PixelRef1 const& p1, PixelRef2 const& p2) const -> PixelResult
    {
        PixelResult result;
        static_transform(p1, p2, result,
            channel_minus_t
            <
                typename channel_type<PixelRef1>::type,
                typename channel_type<PixelRef2>::type,
                typename channel_type<PixelResult>::type
            >());
        return result;
    }
};

/// \ingroup PixelNumericOperations
/// \brief Performs channel-wise multiplication of pixel elements by scalar.
/// \tparam PixelRef - models PixelConcept
/// \tparam Scalar - models a scalar type
/// \tparam PixelResult - models PixelValueConcept
template <typename PixelRef, typename Scalar, typename PixelResult>
struct pixel_multiplies_scalar_t
{
    auto operator()(PixelRef const& p, Scalar const& s) const -> PixelResult
    {
        PixelResult result;
        static_transform(p, result,
            std::bind(
                channel_multiplies_scalar_t<typename channel_type<PixelRef>::type,
                Scalar,
                typename channel_type<PixelResult>::type>(),
                std::placeholders::_1, s));
        return result;
    }
};

/// \ingroup PixelNumericOperations
/// \brief Performs channel-wise multiplication of two pixels.
/// \tparam PixelRef1 - models PixelConcept
/// \tparam PixelRef1 - models PixelConcept
/// \tparam PixelResult - models PixelValueConcept
template <typename PixelRef1, typename PixelRef2, typename PixelResult>
struct pixel_multiply_t
{
    auto operator()(PixelRef1 const& p1, PixelRef2 const& p2) const -> PixelResult
    {
        PixelResult result;
        static_transform(p1, p2, result,
            channel_multiplies_t
            <
                typename channel_type<PixelRef1>::type,
                typename channel_type<PixelRef2>::type,
                typename channel_type<PixelResult>::type
            >());
        return result;
    }
};

/// \ingroup PixelNumericOperations
/// \brief Performs channel-wise division of pixel elements by scalar.
/// \tparam PixelRef - models PixelConcept
/// \tparam Scalar - models a scalar type
/// \tparam PixelResult - models PixelValueConcept
template <typename PixelRef, typename Scalar, typename PixelResult>
struct pixel_divides_scalar_t
{
    auto operator()(PixelRef const& p, Scalar const& s) const -> PixelResult
    {
        PixelResult result;
        static_transform(p, result,
            std::bind(channel_divides_scalar_t<typename channel_type<PixelRef>::type,
                Scalar,
                typename channel_type<PixelResult>::type>(),
                std::placeholders::_1, s));
        return result;
    }
};

/// \ingroup PixelNumericOperations
/// \brief Performs channel-wise division of two pixels.
/// \tparam PixelRef1 - models PixelConcept
/// \tparam PixelRef1 - models PixelConcept
/// \tparam PixelResult - models PixelValueConcept
template <typename PixelRef1, typename PixelRef2, typename PixelResult>
struct pixel_divide_t
{
    auto operator()(PixelRef1 const& p1, PixelRef2 const& p2) const -> PixelResult
    {
        PixelResult result;
        static_transform(p1, p2, result,
            channel_divides_t
            <
                typename channel_type<PixelRef1>::type,
                typename channel_type<PixelRef2>::type,
                typename channel_type<PixelResult>::type
            >());
        return result;
    }
};

/// \ingroup PixelNumericOperations
/// \brief Performs channel-wise division by 2
/// \tparam PixelRef - models PixelConcept
template <typename PixelRef>
struct pixel_halves_t
{
    auto operator()(PixelRef& p) const -> PixelRef&
    {
        static_for_each(p, channel_halves_t<typename channel_type<PixelRef>::type>());
        return p;
    }
};

/// \ingroup PixelNumericOperations
/// \brief Sets pixel elements to zero (for whatever zero means)
/// \tparam PixelRef - models PixelConcept
template <typename PixelRef>
struct pixel_zeros_t
{
    auto operator()(PixelRef& p) const -> PixelRef&
    {
        static_for_each(p, channel_zeros_t<typename channel_type<PixelRef>::type>());
        return p;
    }
};

/// \brief Sets pixel elements to zero (for whatever zero means)
/// \tparam Pixel - models PixelConcept
template <typename Pixel>
void zero_channels(Pixel& p)
{
    static_for_each(p, channel_zeros_t<typename channel_type<Pixel>::type>());
}

/// \ingroup PixelNumericOperations
/// \brief Casts and assigns a pixel to another
///
/// A generic implementation for casting and assigning a pixel to another.
/// User should specialize it for better performance.
///
/// \tparam PixelRef - models PixelConcept
/// \tparam PixelResult - models PixelValueConcept
template <typename PixelRef, typename PixelResult>
struct pixel_assigns_t
{
    auto operator()(PixelRef const& src, PixelResult& dst) const -> PixelResult
    {
        static_for_each(src, dst,
            channel_assigns_t
            <
                typename channel_type<PixelRef>::type,
                typename channel_type<PixelResult>::type
            >());
        return dst;
    }
};

}} // namespace boost::gil

#endif

/* pixel_numeric_operations.hpp
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
*/