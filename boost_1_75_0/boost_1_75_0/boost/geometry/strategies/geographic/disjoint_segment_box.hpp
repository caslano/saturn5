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
mBe742LWpjtx90rpB3aAhCNfsVdqgu1ewgINt1xiv0Y2exlArzL0zvszOenByoKBPZI7j0uPtFgBcL53YSb/zCTk2J8QvXTFrOTV1tcpniTH4du4K8Kp2WLHUvNx3nLht8AG5TVrbK6DHxM5gT/ZpRe+MgxwO/NNDtrgWz2TjUtvTJ62XTSZzbOXIEd6eVHuMZ1anOhXTB4qOtac7m8J3rIzCzNNzqCuNBi3fAWTFL5KfLfrtjyg0+jESzxj2I1bZ3HKL9SfQH0oqSltbo2ftEYOm6kNRXbB6DG2y3bITufxXVIeX0YZcVww/NAhP92ZGo7zrRB8isVr6MgVrs+du01E3FLMbHaIqWjgk4u15JZJ5YARSf2JJm2HL9uKiqkK5YmktdZNTw1dQV+1u0ZWa1WcjCGSJfVtqD2vs3SNTI2V0JpXn7FXUlYSXmxn7ili09Eab0tYc72OtSWR9VvvThfHcAXPqiyAOUtVblbBnpSTqYas/o7ceHT4wYVOj/fdQnJTniuS+sLHjd9VYpTtRO1Y7UlvGz+0mKSiVkWdIdMZJyBKYga+1tgV7WBChmsgPTgQ3PcAtb9ci/Q5mgJOqXZAX3JGeKkdav2+1aNLK5G/Vlcd7qikzutWtNq9wohwDiFzyrXazZFT2Yf04+wS91O+ekKEDMmfal8TgPRBPnaPyzP+Mgpi3lSJXtpBD5QPyJ7J1DNnD74vsvJ5
*/