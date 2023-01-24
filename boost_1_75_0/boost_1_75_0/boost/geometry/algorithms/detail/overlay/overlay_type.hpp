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
1U7aEKrgBuaSDVXwgy3h2sVrsfKRf8wOCv6gRISIqbq9Fu4Oj8JSGpgkOmSuLSr3HbPC5vp3HruD5GyMDJRGQN1VCu2xA4fVFRKSeEYua5PTxNyiBJFJmq5OKcdpHjFVCj4g4dOfGr1sTav4bzvlPlSIBnp0bZk9/5LoOHiSNdpAXWrp4HJfTkMquJn0y5PlApeKk54Q/u33c25bCNy9cX2I2svLhtcWjeSTIeww+IC5UG+q/TIbqZOPEmVS4BWtc6CDYJt4Qk7JxfmAGzixEgh3kcqZFNlKQWokJ10StXQNB+wllNebepfE6kk7j4VgX1GdsQNWvukSHimb5S4Ej0ZznZ81mtC5J8K2oZozst2Gb0dgpN9kP5grdam1uru+Ga4EH8DYz08HGumQD2u9TMt54wSOdsS3RZZVg1Mk9sDYVomAjHc8zqHbzFBBXQnXU8lJnnbwtHMKvpNpnBO3Ui68U7SDSqZ6mzJsvCS3MG6/dLEF0U524HlTwWueez/gKQWX+wpLjSBlceSo4TlHuFDk8aC68TQaDxLfFD9Ygiyfkhkl5uh6G2ugKxewo1UKaD8Tg3LO7hU1dfz0i6rIm3oHczdxpYk9eGMXI4s/8Vl+0REF85P18IhlBvrWle2UO1C1S9TZVpty2QhJx/UbOQk0i97jzCOSPY0yS7InFZPRs3ML7vr8p6ng6tPy9TdMwRzNQvp4vWvf4paS
*/