// Boost.Geometry

// Copyright (c) 2017-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISJOINT_SEGMENT_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISJOINT_SEGMENT_BOX_HPP


#include <cstddef>
#include <utility>

#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/calculation_type.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/algorithms/detail/disjoint/segment_box.hpp>

#include <boost/geometry/srs/spheroid.hpp>

// TODO: spherical_point_box currently defined in the same file as cartesian
#include <boost/geometry/strategies/cartesian/point_in_box.hpp>
#include <boost/geometry/strategies/disjoint.hpp>
#include <boost/geometry/strategies/geographic/azimuth.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/strategies/normalize.hpp>
#include <boost/geometry/strategies/spherical/disjoint_box_box.hpp>


namespace boost { namespace geometry { namespace strategy { namespace disjoint
{

// NOTE: This may be temporary place for this or corresponding strategy
// It seems to be more appropriate to implement the opposite of it
// e.g. intersection::segment_box because in disjoint() algorithm
// other strategies that are used are intersection and covered_by strategies.
template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
struct segment_box_geographic
{
public:
    typedef Spheroid model_type;

    inline segment_box_geographic()
        : m_spheroid()
    {}

    explicit inline segment_box_geographic(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

    typedef covered_by::spherical_point_box disjoint_point_box_strategy_type;
    
    static inline disjoint_point_box_strategy_type get_disjoint_point_box_strategy()
    {
        return disjoint_point_box_strategy_type();
    }

    template <typename Segment, typename Box>
    inline bool apply(Segment const& segment, Box const& box) const
    {
        geometry::strategy::azimuth::geographic
            <
                FormulaPolicy,
                Spheroid,
                CalculationType
            > azimuth_geographic(m_spheroid);

        return geometry::detail::disjoint::disjoint_segment_box_sphere_or_spheroid
                <
                    geographic_tag
                >::apply(segment, box,
                         azimuth_geographic,
                         strategy::normalize::spherical_point(),
                         strategy::covered_by::spherical_point_box(),
                         strategy::disjoint::spherical_box_box());
    }

private:
    Spheroid m_spheroid;
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


namespace services
{

template <typename Linear, typename Box, typename LinearTag>
struct default_strategy<Linear, Box, LinearTag, box_tag, 1, 2,
                        geographic_tag, geographic_tag>
{
    typedef segment_box_geographic<> type;
};

template <typename Box, typename Linear, typename LinearTag>
struct default_strategy<Box, Linear, box_tag, LinearTag, 2, 1,
                        geographic_tag, geographic_tag>
{
    typedef segment_box_geographic<> type;
};


} // namespace services


#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}}}} // namespace boost::geometry::strategy::disjoint


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISJOINT_SEGMENT_BOX_HPP

/* disjoint_segment_box.hpp
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
*/