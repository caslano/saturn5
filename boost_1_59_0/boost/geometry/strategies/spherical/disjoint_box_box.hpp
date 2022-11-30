// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISJOINT_BOX_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISJOINT_BOX_BOX_HPP

#include <cstddef>

#include <boost/geometry/core/cs.hpp>

#include <boost/geometry/strategies/cartesian/disjoint_box_box.hpp>
#include <boost/geometry/strategies/disjoint.hpp>

#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry { namespace strategy { namespace disjoint
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct box_box_on_spheroid
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        typedef typename geometry::select_most_precise
            <
                typename coordinate_type<Box1>::type,
                typename coordinate_type<Box2>::type
            >::type calc_t;
        typedef typename geometry::detail::cs_angular_units<Box1>::type units_t;
        typedef math::detail::constants_on_spheroid<calc_t, units_t> constants;

        calc_t const b1_min = get<min_corner, 0>(box1);
        calc_t const b1_max = get<max_corner, 0>(box1);
        calc_t const b2_min = get<min_corner, 0>(box2);
        calc_t const b2_max = get<max_corner, 0>(box2);

        // min <= max <=> diff >= 0
        calc_t const diff1 = b1_max - b1_min;
        calc_t const diff2 = b2_max - b2_min;

        // check the intersection if neither box cover the whole globe
        if (diff1 < constants::period() && diff2 < constants::period())
        {
            // calculate positive longitude translation with b1_min as origin
            calc_t const diff_min = math::longitude_distance_unsigned<units_t>(b1_min, b2_min);
            calc_t const b2_min_transl = b1_min + diff_min; // always right of b1_min
            calc_t b2_max_transl = b2_min_transl - constants::period() + diff2;

            // if the translation is too close then use the original point
            // note that math::abs(b2_max_transl - b2_max) takes values very
            // close to k*2*constants::period() for k=0,1,2,...
            if (math::abs(b2_max_transl - b2_max) < constants::period() / 2)
            {
                b2_max_transl = b2_max;
            }

            if (b2_min_transl > b1_max  // b2_min right of b1_max
             && b2_max_transl < b1_min) // b2_max left of b1_min
            {
                return true;
            }
        }

        return box_box
            <
                Box1, Box2, 1
            >::apply(box1, box2);
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


struct spherical_box_box
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        return detail::box_box_on_spheroid::apply(box1, box2);
    }
};


namespace services
{

template <typename Box1, typename Box2, int TopDim1, int TopDim2>
struct default_strategy<Box1, Box2, box_tag, box_tag, TopDim1, TopDim2, spherical_equatorial_tag, spherical_equatorial_tag>
{
    typedef disjoint::spherical_box_box type;
};

template <typename Box1, typename Box2, int TopDim1, int TopDim2>
struct default_strategy<Box1, Box2, box_tag, box_tag, TopDim1, TopDim2, spherical_polar_tag, spherical_polar_tag>
{
    typedef disjoint::spherical_box_box type;
};

template <typename Box1, typename Box2, int TopDim1, int TopDim2>
struct default_strategy<Box1, Box2, box_tag, box_tag, TopDim1, TopDim2, geographic_tag, geographic_tag>
{
    typedef disjoint::spherical_box_box type;
};

} // namespace services

}}}} // namespace boost::geometry::strategy::disjoint


#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISJOINT_BOX_BOX_HPP

/* disjoint_box_box.hpp
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
*/