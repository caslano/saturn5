// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_RING_PROPERTIES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_RING_PROPERTIES_HPP


#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/within.hpp>
#include <boost/geometry/algorithms/detail/point_on_border.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

template <typename Point, typename AreaType>
struct ring_properties
{
    typedef Point point_type;
    typedef AreaType area_type;

    bool valid;

    // Filled by "select_rings"
    Point point;
    area_type area;

    // Filled by "update_ring_selection"
    bool reversed;

    // Filled/used by "assign_rings"
    bool discarded;
    ring_identifier parent;
    area_type parent_area;
    std::vector<ring_identifier> children;

    inline ring_properties()
        : valid(false)
        , area(area_type())
        , reversed(false)
        , discarded(false)
        , parent_area(-1)
    {}

    template <typename RingOrBox, typename AreaStrategy>
    inline ring_properties(RingOrBox const& ring_or_box, AreaStrategy const& strategy)
        : reversed(false)
        , discarded(false)
        , parent_area(-1)
    {
        this->area = geometry::area(ring_or_box, strategy);
        valid = geometry::point_on_border(this->point, ring_or_box);
    }

    inline area_type get_area() const
    {
        return reversed ? -area : area;
    }
};

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_RING_PROPERTIES_HPP

/* ring_properties.hpp
K5EDrFRErA7co3FBtkW/Pu4x4a0PArfoPVxRfPo4hMs/VtX+28bNhniY/TfqWPLrxt70h4vPEJ3na2dWZXNmuqFtrMfcRankJ6os2lK3jasvV87is64AQG89wKjj8UgL4e46MT0aPrDBviliy16yxXhwSmkNJwtIzEcb5SVZwPoNDlnXrIIRSkNLFouM8kFoAVZSH3k1AIDpzeTPw4iXbeQeCGk1Up5FCU+MintRRedCxZ76sgx+rCjxqFYooXMOgXVFlU+07OPULNx3RCeXRUcZY1e04/7p0qiqo9XMcQKuHyF7MITABD2m7uKjXFyVS54dB8CNm8Rqt+6qbQcAGZ0XouhdXMYJMwwsKq8PhANsK3SEu5hR1eTzCc9ScqnTgqkIQlhf04hIQbVc8Ec1MCZYZPIPzC7MsFjkzD/idN5cXITachdzn2hJWmOvZnQu9Hax9ad9qr/I75qNOpoKxpPTR6EjPG7MDVYY/juGZUPkbyI1lC7Aljal502VEFr0y6hoEEOehEj12pLuJTlN66wYwWBFpDpdEckfucBX3HVeLOb5GKunHiqWNzNRSKx+UI3BAcJf/YdbRg89snR9jDvLjuqUzSsuWj1WvdIdB9Edvkq7wLLPY8crHlyEtmEcF6teEO02IlLpt4NXN3RhDOFijVTJtmUWiAdjoPiTKxhPS7YOm0x+WVL2G3mANcupRypAd0eh4EdDYmg/
*/