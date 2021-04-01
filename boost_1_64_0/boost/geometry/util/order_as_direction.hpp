// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_ORDER_AS_DIRECTION_HPP
#define BOOST_GEOMETRY_UTIL_ORDER_AS_DIRECTION_HPP

#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/views/reversible_view.hpp>

namespace boost { namespace geometry
{


template<order_selector Order>
struct order_as_direction
{};


template<>
struct order_as_direction<clockwise>
{
    static const iterate_direction value = iterate_forward;
};


template<>
struct order_as_direction<counterclockwise>
{
    static const iterate_direction value = iterate_reverse;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_ORDER_AS_DIRECTION_HPP

/* order_as_direction.hpp
wCIKVa8nV1hZq/MRKg3jTDRoTjy8m7qD7eViUbhrvcItLDrTE907FSUjNppoCMywEvhwrLYLxCmPPHqU2DmEknpR9e75fY9wlqmbM55yHCAjPhxGeolX/eITd/Phv+ELiScZYCE1rA+Hyhe0nSn7Ya9ZzA09bpSqeLerPuVvSq+OkSeoCg7AcU9sDSMtBMqRWdpVkziKj06zJ+YGs9kfoIPGP3U7UnYjNp5k3xmDSyVBCZwO+SiPHcijTO4mixWnpOs0ef8uPgl4y/1oZtipqRPO9eUQPjm78knURBgny+2JnTf5yxGTiRoG3MiqqyiiLOTk0tvvDpRr3QMgPIHnhitI1eQzhhPTWCeFG6D94tEEVPPft3ThTCO5c6FgG4tGVLsIHWHmfw16rc2A8v9Rs35JGbhJpnh7FdWZwYTgoJY0OMaTLpXbpZ0XgUpffU6yB1BL53Hh4Q93PiwX/94tPUeQs28LnBEgIu1sK3YvgO494H/3hGE78Gae6WArqcFqzRecz1jcbLTVGhayP4Qrj/jKeOJQmfJD2n2uE7konedFDHjVrNMIIGS7Ug==
*/