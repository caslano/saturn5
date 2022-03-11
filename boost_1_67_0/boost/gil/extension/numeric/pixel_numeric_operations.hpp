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