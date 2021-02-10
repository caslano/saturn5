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
aYPr0yua4PKwSxj30/wM60u2RIf6AL4Vse0buCgRV0H48Qw3ITbNM7c5NN4KKxrSMa6YgBALmvciNp0sp/hBUsB1SyluLMDwJi6Dlec3+MXAIV5HmAbDIAyygKaAWHuMSQh+Cjg/ghsjYIGrDc5AHaNl4F4Y3qoqBbSvcdklXhUKxLSBMZw9lkjFo9gp3tA0Jbi9DNDqx5gKTTPq+QyK2tU0t5fiamHu4zCs8N7kAFijJXpYh0deZLPRjFMXJp6qC46sEiIhIG9r3NAy7SaIPEdlvC6xKO0I70Xl6ydkf0H2mmTukIgfcw9yQ3jW/IYffX2DRY5lXWD8gGTGuqNZPtGxmHJLuj93huUxdH9JJi7KIS7FxvJE4wOIvrRpL10ezx+urweRnOcwIkR8WHbePS5fTEfelN3lzXOTnlziw3JOw1Dcq/P7XMNnzIlQhmnKDpSPZ5mYU7NyVPACQGnrf+avQy+dbwE7HWdeeL8DoDE7Rrn9ojzvGY/xPCx5cRePZVlf1C1Nomcye2XdD8BIoe1rgAHQOiha3CqmHcuvjeUC+Po6guZ0A9gMKFmXb3fF+iv5fk8yACEomhaS4bxhBKwpo6Tp112z9oRf3mO1rE1E46pVXlrivuD+Hr61VuwoqqaaMhIc+Oev6+u4
*/