// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_OVERLAY_TYPE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_OVERLAY_TYPE_HPP



namespace boost { namespace geometry
{

// TODO: move to detail
enum overlay_type
{
    overlay_union,
    overlay_intersection,
    overlay_difference,
    overlay_buffer,
    overlay_dissolve
};

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

enum operation_type
{
    operation_none,
    operation_union,
    operation_intersection,
    operation_blocked,
    operation_continue,
    operation_opposite
};


template <overlay_type OverlayType>
struct operation_from_overlay
{
};

template <>
struct operation_from_overlay<overlay_union>
{
    static const operation_type value = operation_union;
};

template <>
struct operation_from_overlay<overlay_buffer>
{
    static const operation_type value = operation_union;
};

template <>
struct operation_from_overlay<overlay_intersection>
{
    static const operation_type value = operation_intersection;
};

template <>
struct operation_from_overlay<overlay_difference>
{
    static const operation_type value = operation_intersection;
};

template <>
struct operation_from_overlay<overlay_dissolve>
{
    static const operation_type value = operation_union;
};


}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_OVERLAY_TYPE_HPP

/* overlay_type.hpp
7KSMLKPFiHfXkUo22w5Oi9Waaaz9fqmFNxlzrEmmbGPtd00tQmayKTM1PTW99jWtRbAmJRszUozptS+rIqQYcjJsJ1NKWo5yANTC2pYtO9tkOykd74Za2CxjSnrm/1N2rTGSXNW5Yju2Y4M9s7smy3sBA7bxmpnZ9XoXGbbe75e6e/ZBnJR7umt22jvdPXT37M4axMPYFooSFBIpJIrJj0goJEr+kAgi+EEUBykhBCyLICTzI0qiKEosCCLCERA=
*/