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
wiuzYVknO03J928oaDFXltHZhQm8tmyG9Y31O5acKAxVi3Quo1xZ9+K9qvfkxUo9F3J91q5W6mvE5c7q94W8+V9QSwMECgAAAAgALWdKUg0uH4SGAgAAjwUAABsACQBjdXJsLW1hc3Rlci9saWIvaW5ldF9wdG9uLmhVVAUAAbZIJGCtVO9v2jAQ/c5f8QRfAGWk49O6VdUiygbaBAjSVkiVLJM4jadgR7bDj6l//M6BFrVaxZcawZnzvffOd8m1ZKZSkWE0jG6Gcza4nf9m48kwZrN4OmGjRosOpRLvnofdj1sNdHF2sfrLaJGtETOj/4jE/T+asSccPoR6IHtOJMQJ8sQ6OA95QruGsKPKld8zdk7owefmf0KPfGB+Sx6CeeRAl3sjH3OH9qCDz5eXX/AJ/Yv+RYAbrqQosHBCrYR5DHCV1p7vOd/telZcBxAOvOgdqeJcWliduS03ArQvZCKUFSm4RSpsYuSK/kgFlwtkshAYTGfL8eRngG0uk9yT7HUFm+uqSJHzjYARiZCbA0fJjYPOCE7kqbSOCCsnteqRtoATZm09h5fnhdXgGy4LviIh7pA7V9qvYZhUpqDsw1QnNkyer9/L3frlJktKYs330KWD06isCOAjA6x1KjNvqSDkLKtVIW0enLIh
*/