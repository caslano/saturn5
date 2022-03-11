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