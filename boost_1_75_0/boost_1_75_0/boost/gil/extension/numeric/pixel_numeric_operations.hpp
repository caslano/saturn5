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
kmlHPbfA1PmmOcmz/TMglkO82yE0P9IciybMCgs/1Vahtq75XjsstYYsKXYw3e6ZMoFsuYL+XkROvspAACHvMUu9L3WMM93TLziD2V8F155gCw5br+kFuiuBP4II7DI5lsWPpPrz7a8L2pUrH79KAm1y6bsvX1xj4ozsGg4sbziZdQAmjUkPBFzspzDKmAcr0lbK7VA+CbiTnStdj/kEsocF1CbNSKI19KctBze9OIIk3uSElPgFc+xse33g+kOQwEqbghuvcaecp5qPFBU4Iv+IatJcOXNiiBkpeZjTZt8COidjxxS69vOvbnjEStwzHo4feOvRXFTVRIoYojY1oXaieomhS8TC3WzZiQpVn3ye0j+FLkcvcZkxbRaj2GhjL4k2HUU7ZqxSv29pdmx7nJSNPOm2i5WkPzNhLN03bn+iUYSOidtpisqkYs7443NzzY6TYx5ZMGHk1DAT9jJA708cT1mo/PpL9BFWfgOTrF9PYmkvUgAu5DrzGd7v4ijGwpkrFOu64Ce3o5gnRRkn1OUIxQxfO41Dkf5QJG+m68sdODM4I26LunLpSvRp2GhVJP4pWFDPSiI6DNQJCiBX7QfqyLARO5P8BJ0YsA0KWQO59Nbr/FNayxGO4w/rdioSomu+/dDXD7JabhrH0dxvAk0heUelkk6SPvTfBKKYVvioXXnqGqfjm7xahyZv2rkACnzwsQEmAKGA32YK
*/