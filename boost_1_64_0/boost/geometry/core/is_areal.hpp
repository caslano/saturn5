// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_CORE_IS_AREAL_HPP
#define BOOST_GEOMETRY_CORE_IS_AREAL_HPP


#include <boost/type_traits/integral_constant.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename GeometryTag> struct is_areal : boost::false_type {};

template <> struct is_areal<ring_tag> : boost::true_type {};
template <> struct is_areal<box_tag> : boost::true_type {};
template <> struct is_areal<polygon_tag> : boost::true_type {};
template <> struct is_areal<multi_polygon_tag> : boost::true_type {};

} // namespace core_dispatch
#endif



/*!
    \brief Meta-function defining "true" for areal types (box, (multi)polygon, ring),
    \note Used for tag dispatching and meta-function finetuning
    \note Also a "ring" has areal properties within Boost.Geometry
    \ingroup core
*/
template <typename Geometry>
struct is_areal : core_dispatch::is_areal<typename tag<Geometry>::type>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_IS_AREAL_HPP

/* is_areal.hpp
4bvrMoP6OT4yygqFuUSC5tpBRVphYtzGwnvePFHfILQA88YX53KNo7j5xr2akaQwN4EB70afikqAVLLA0ElrxTu8aXrxtx5GcllACG/+aiVKYnOAgsbkt7/xcDQRs9cBzJpvLOIP0V4blplnKEuP7+dO4VQYf8n7nKZRbZM0mvMgX7r9E/E6Duw6p95nrrQ7y5RxERkOqv6foB6aigqb3sMPww0biVavNM5WhHYVXoRRH3G1zi6GhLifABFq3y2iGBCKiT5Yve1JfYd3HsNRojzIxpqQMeiGNhklLUFILmL2PuI9GYWMjMJxgzhqEUKE6FlTT/N1MpV4ksrSwmOdhD6fHDU54SgkHVumaRTGqfgJ9nzNu6Nf78kE663pCtr61Qyr2z3BWtRkFJcyg0jYUQZkEBb6VWzQMA6s7UBBJ+d2MV3/HTiZkNSDFYkGZ369W9foMepETjYjI2zQBUsf74UDP+TzaiiXSTBRGcmDRBsJc6Gs7jK57xnoQdfmZH/EApckDMb0nzJm/y6HoHc8hH8LdZcOBU/MyIJJGSMACce9PY2HFCziY5T/Dw==
*/