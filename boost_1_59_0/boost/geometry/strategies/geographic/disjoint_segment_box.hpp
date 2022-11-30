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

    Spheroid const& model() const
    {
        return m_spheroid;
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