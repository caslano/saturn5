// Boost.Geometry

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2016-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_INTERSECTION_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_INTERSECTION_HPP

#include <algorithm>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/assign_values.hpp>
#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/recalculate.hpp>

#include <boost/geometry/formulas/andoyer_inverse.hpp>
#include <boost/geometry/formulas/sjoberg_intersection.hpp>
#include <boost/geometry/formulas/spherical.hpp>
#include <boost/geometry/formulas/unit_spheroid.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/geometries/concepts/segment_concept.hpp>

#include <boost/geometry/policies/robustness/segment_ratio.hpp>

#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/strategies/geographic/area.hpp>
#include <boost/geometry/strategies/geographic/disjoint_segment_box.hpp>
#include <boost/geometry/strategies/geographic/distance.hpp>
#include <boost/geometry/strategies/geographic/envelope.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/strategies/geographic/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/geographic/side.hpp>
#include <boost/geometry/strategies/spherical/expand_box.hpp>
#include <boost/geometry/strategies/spherical/disjoint_box_box.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>
#include <boost/geometry/strategies/intersection.hpp>
#include <boost/geometry/strategies/intersection_result.hpp>
#include <boost/geometry/strategies/side_info.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace intersection
{

// CONSIDER: Improvement of the robustness/accuracy/repeatability by
// moving all segments to 0 longitude
// picking latitudes closer to 0
// etc.

template
<
    typename FormulaPolicy = strategy::andoyer,
    unsigned int Order = strategy::default_order<FormulaPolicy>::value,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
struct geographic_segments
{
    typedef geographic_tag cs_tag;

    typedef side::geographic
        <
            FormulaPolicy, Spheroid, CalculationType
        > side_strategy_type;

    inline side_strategy_type get_side_strategy() const
    {
        return side_strategy_type(m_spheroid);
    }

    template <typename Geometry1, typename Geometry2>
    struct point_in_geometry_strategy
    {
        typedef strategy::within::geographic_winding
            <
                typename point_type<Geometry1>::type,
                typename point_type<Geometry2>::type,
                FormulaPolicy,
                Spheroid,
                CalculationType
            > type;
    };

    template <typename Geometry1, typename Geometry2>
    inline typename point_in_geometry_strategy<Geometry1, Geometry2>::type
        get_point_in_geometry_strategy() const
    {
        typedef typename point_in_geometry_strategy
            <
                Geometry1, Geometry2
            >::type strategy_type;
        return strategy_type(m_spheroid);
    }

    template <typename Geometry>
    struct area_strategy
    {
        typedef area::geographic
            <
                FormulaPolicy,
                Order,
                Spheroid,
                CalculationType
            > type;
    };

    template <typename Geometry>
    inline typename area_strategy<Geometry>::type get_area_strategy() const
    {
        typedef typename area_strategy<Geometry>::type strategy_type;
        return strategy_type(m_spheroid);
    }

    template <typename Geometry>
    struct distance_strategy
    {
        typedef distance::geographic
            <
                FormulaPolicy,
                Spheroid,
                CalculationType
            > type;
    };

    template <typename Geometry>
    inline typename distance_strategy<Geometry>::type get_distance_strategy() const
    {
        typedef typename distance_strategy<Geometry>::type strategy_type;
        return strategy_type(m_spheroid);
    }

    typedef envelope::geographic<FormulaPolicy, Spheroid, CalculationType>
        envelope_strategy_type;

    inline envelope_strategy_type get_envelope_strategy() const
    {
        return envelope_strategy_type(m_spheroid);
    }

    typedef expand::geographic_segment<FormulaPolicy, Spheroid, CalculationType>
        expand_strategy_type;

    inline expand_strategy_type get_expand_strategy() const
    {
        return expand_strategy_type(m_spheroid);
    }

    typedef within::spherical_point_point point_in_point_strategy_type;

    static inline point_in_point_strategy_type get_point_in_point_strategy()
    {
        return point_in_point_strategy_type();
    }

    typedef within::spherical_point_point equals_point_point_strategy_type;

    static inline equals_point_point_strategy_type get_equals_point_point_strategy()
    {
        return equals_point_point_strategy_type();
    }

    typedef disjoint::spherical_box_box disjoint_box_box_strategy_type;

    static inline disjoint_box_box_strategy_type get_disjoint_box_box_strategy()
    {
        return disjoint_box_box_strategy_type();
    }

    typedef disjoint::segment_box_geographic
        <
            FormulaPolicy, Spheroid, CalculationType
        > disjoint_segment_box_strategy_type;

    inline disjoint_segment_box_strategy_type get_disjoint_segment_box_strategy() const
    {
        return disjoint_segment_box_strategy_type(m_spheroid);
    }

    typedef covered_by::spherical_point_box disjoint_point_box_strategy_type;
    typedef covered_by::spherical_point_box covered_by_point_box_strategy_type;
    typedef within::spherical_point_box within_point_box_strategy_type;
    typedef envelope::spherical_box envelope_box_strategy_type;
    typedef expand::spherical_box expand_box_strategy_type;

    enum intersection_point_flag { ipi_inters = 0, ipi_at_a1, ipi_at_a2, ipi_at_b1, ipi_at_b2 };

    template <typename CoordinateType, typename SegmentRatio>
    struct segment_intersection_info
    {
        template <typename Point, typename Segment1, typename Segment2>
        void calculate(Point& point, Segment1 const& a, Segment2 const& b) const
        {
            if (ip_flag == ipi_inters)
            {
                // TODO: assign the rest of coordinates
                set_from_radian<0>(point, lon);
                set_from_radian<1>(point, lat);
            }
            else if (ip_flag == ipi_at_a1)
            {
                detail::assign_point_from_index<0>(a, point);
            }
            else if (ip_flag == ipi_at_a2)
            {
                detail::assign_point_from_index<1>(a, point);
            }
            else if (ip_flag == ipi_at_b1)
            {
                detail::assign_point_from_index<0>(b, point);
            }
            else // ip_flag == ipi_at_b2
            {
                detail::assign_point_from_index<1>(b, point);
            }
        }

        CoordinateType lon;
        CoordinateType lat;
        SegmentRatio robust_ra;
        SegmentRatio robust_rb;
        intersection_point_flag ip_flag;
    };

    explicit geographic_segments(Spheroid const& spheroid = Spheroid())
        : m_spheroid(spheroid)
    {}

    // Relate segments a and b
    template
    <
        typename UniqueSubRange1,
        typename UniqueSubRange2,
        typename Policy
    >
    inline typename Policy::return_type apply(UniqueSubRange1 const& range_p,
                                              UniqueSubRange2 const& range_q,
                                              Policy const&) const
    {
        typedef typename UniqueSubRange1::point_type point1_type;
        typedef typename UniqueSubRange2::point_type point2_type;
        typedef model::referring_segment<point1_type const> segment_type1;
        typedef model::referring_segment<point2_type const> segment_type2;

        BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<point1_type>) );
        BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<point2_type>) );

        /*
        typename coordinate_type<Point1>::type
            const a1_lon = get<0>(a1),
            const a2_lon = get<0>(a2);
        typename coordinate_type<Point2>::type
            const b1_lon = get<0>(b1),
            const b2_lon = get<0>(b2);
        bool is_a_reversed = a1_lon > a2_lon || a1_lon == a2_lon && get<1>(a1) > get<1>(a2);
        bool is_b_reversed = b1_lon > b2_lon || b1_lon == b2_lon && get<1>(b1) > get<1>(b2);
        */

        bool const is_p_reversed = get<1>(range_p.at(0)) > get<1>(range_p.at(1));
        bool const is_q_reversed = get<1>(range_q.at(0)) > get<1>(range_q.at(1));

        // Call apply with original segments and ordered points
        return apply<Policy>(segment_type1(range_p.at(0), range_p.at(1)),
                             segment_type2(range_q.at(0), range_q.at(1)),
                             range_p.at(is_p_reversed ? 1 : 0),
                             range_p.at(is_p_reversed ? 0 : 1),
                             range_q.at(is_q_reversed ? 1 : 0),
                             range_q.at(is_q_reversed ? 0 : 1),
                             is_p_reversed, is_q_reversed);
    }

private:
    // Relate segments a and b
    template
    <
        typename Policy,
        typename Segment1,
        typename Segment2,
        typename Point1,
        typename Point2
    >
    inline typename Policy::return_type apply(Segment1 const& a, Segment2 const& b,
                                              Point1 const& a1, Point1 const& a2,
                                              Point2 const& b1, Point2 const& b2,
                                              bool is_a_reversed, bool is_b_reversed) const
    {
        BOOST_CONCEPT_ASSERT( (concepts::ConstSegment<Segment1>) );
        BOOST_CONCEPT_ASSERT( (concepts::ConstSegment<Segment2>) );

        typedef typename select_calculation_type
            <Segment1, Segment2, CalculationType>::type calc_t;

        typedef srs::spheroid<calc_t> spheroid_type;

        static const calc_t c0 = 0;

        // normalized spheroid
        spheroid_type spheroid = formula::unit_spheroid<spheroid_type>(m_spheroid);

        // TODO: check only 2 first coordinates here?
        bool a_is_point = equals_point_point(a1, a2);
        bool b_is_point = equals_point_point(b1, b2);

        if(a_is_point && b_is_point)
        {
            return equals_point_point(a1, b2)
                ? Policy::degenerate(a, true)
                : Policy::disjoint()
                ;
        }
        
        calc_t const a1_lon = get_as_radian<0>(a1);
        calc_t const a1_lat = get_as_radian<1>(a1);
        calc_t const a2_lon = get_as_radian<0>(a2);
        calc_t const a2_lat = get_as_radian<1>(a2);
        calc_t const b1_lon = get_as_radian<0>(b1);
        calc_t const b1_lat = get_as_radian<1>(b1);
        calc_t const b2_lon = get_as_radian<0>(b2);
        calc_t const b2_lat = get_as_radian<1>(b2);

        side_info sides;

        // NOTE: potential optimization, don't calculate distance at this point
        // this would require to reimplement inverse strategy to allow
        // calculation of distance if needed, probably also storing intermediate
        // results somehow inside an object.
        typedef typename FormulaPolicy::template inverse<calc_t, true, true, false, false, false> inverse_dist_azi;
        typedef typename inverse_dist_azi::result_type inverse_result;

        // TODO: no need to call inverse formula if we know that the points are equal
        // distance can be set to 0 in this case and azimuth may be not calculated
        bool is_equal_a1_b1 = equals_point_point(a1, b1);
        bool is_equal_a2_b1 = equals_point_point(a2, b1);
        bool degen_neq_coords = false;

        inverse_result res_b1_b2, res_b1_a1, res_b1_a2;
        if (! b_is_point)
        {
            res_b1_b2 = inverse_dist_azi::apply(b1_lon, b1_lat, b2_lon, b2_lat, spheroid);
            if (math::equals(res_b1_b2.distance, c0))
            {
                b_is_point = true;
                degen_neq_coords = true;
            }
            else
            {
                res_b1_a1 = inverse_dist_azi::apply(b1_lon, b1_lat, a1_lon, a1_lat, spheroid);
                if (math::equals(res_b1_a1.distance, c0))
                {
                    is_equal_a1_b1 = true;
                }
                res_b1_a2 = inverse_dist_azi::apply(b1_lon, b1_lat, a2_lon, a2_lat, spheroid);
                if (math::equals(res_b1_a2.distance, c0))
                {
                    is_equal_a2_b1 = true;
                }
                sides.set<0>(is_equal_a1_b1 ? 0 : formula::azimuth_side_value(res_b1_a1.azimuth, res_b1_b2.azimuth),
                             is_equal_a2_b1 ? 0 : formula::azimuth_side_value(res_b1_a2.azimuth, res_b1_b2.azimuth));
                if (sides.same<0>())
                {
                    // Both points are at the same side of other segment, we can leave
                    return Policy::disjoint();
                }
            }
        }

        bool is_equal_a1_b2 = equals_point_point(a1, b2);

        inverse_result res_a1_a2, res_a1_b1, res_a1_b2;
        if (! a_is_point)
        {
            res_a1_a2 = inverse_dist_azi::apply(a1_lon, a1_lat, a2_lon, a2_lat, spheroid);
            if (math::equals(res_a1_a2.distance, c0))
            {
                a_is_point = true;
                degen_neq_coords = true;
            }
            else
            {
                res_a1_b1 = inverse_dist_azi::apply(a1_lon, a1_lat, b1_lon, b1_lat, spheroid);
                if (math::equals(res_a1_b1.distance, c0))
                {
                    is_equal_a1_b1 = true;
                }
                res_a1_b2 = inverse_dist_azi::apply(a1_lon, a1_lat, b2_lon, b2_lat, spheroid);
                if (math::equals(res_a1_b2.distance, c0))
                {
                    is_equal_a1_b2 = true;
                }
                sides.set<1>(is_equal_a1_b1 ? 0 : formula::azimuth_side_value(res_a1_b1.azimuth, res_a1_a2.azimuth),
                             is_equal_a1_b2 ? 0 : formula::azimuth_side_value(res_a1_b2.azimuth, res_a1_a2.azimuth));
                if (sides.same<1>())
                {
                    // Both points are at the same side of other segment, we can leave
                    return Policy::disjoint();
                }
            }
        }

        if(a_is_point && b_is_point)
        {
            return is_equal_a1_b2
                ? Policy::degenerate(a, true)
                : Policy::disjoint()
                ;
        }

        // NOTE: at this point the segments may still be disjoint
        // NOTE: at this point one of the segments may be degenerated

        bool collinear = sides.collinear();       

        if (! collinear)
        {
            // WARNING: the side strategy doesn't have the info about the other
            // segment so it may return results inconsistent with this intersection
            // strategy, as it checks both segments for consistency

            if (sides.get<0, 0>() == 0 && sides.get<0, 1>() == 0)
            {
                collinear = true;
                sides.set<1>(0, 0);
            }
            else if (sides.get<1, 0>() == 0 && sides.get<1, 1>() == 0)
            {
                collinear = true;
                sides.set<0>(0, 0);
            }
        }

        if (collinear)
        {
            if (a_is_point)
            {
                return collinear_one_degenerated<Policy, calc_t>(a, true, b1, b2, a1, a2, res_b1_b2, res_b1_a1, res_b1_a2, is_b_reversed, degen_neq_coords);
            }
            else if (b_is_point)
            {
                return collinear_one_degenerated<Policy, calc_t>(b, false, a1, a2, b1, b2, res_a1_a2, res_a1_b1, res_a1_b2, is_a_reversed, degen_neq_coords);
            }
            else
            {
                calc_t dist_a1_a2, dist_a1_b1, dist_a1_b2;
                calc_t dist_b1_b2, dist_b1_a1, dist_b1_a2;
                // use shorter segment
                if (res_a1_a2.distance <= res_b1_b2.distance)
                {
                    calculate_collinear_data(a1, a2, b1, b2, res_a1_a2, res_a1_b1, res_a1_b2, dist_a1_a2, dist_a1_b1);
                    calculate_collinear_data(a1, a2, b2, b1, res_a1_a2, res_a1_b2, res_a1_b1, dist_a1_a2, dist_a1_b2);
                    dist_b1_b2 = dist_a1_b2 - dist_a1_b1;
                    dist_b1_a1 = -dist_a1_b1;
                    dist_b1_a2 = dist_a1_a2 - dist_a1_b1;
                }
                else
                {
                    calculate_collinear_data(b1, b2, a1, a2, res_b1_b2, res_b1_a1, res_b1_a2, dist_b1_b2, dist_b1_a1);
                    calculate_collinear_data(b1, b2, a2, a1, res_b1_b2, res_b1_a2, res_b1_a1, dist_b1_b2, dist_b1_a2);
                    dist_a1_a2 = dist_b1_a2 - dist_b1_a1;
                    dist_a1_b1 = -dist_b1_a1;
                    dist_a1_b2 = dist_b1_b2 - dist_b1_a1;
                }

                // NOTE: this is probably not needed
                int a1_on_b = position_value(c0, dist_a1_b1, dist_a1_b2);
                int a2_on_b = position_value(dist_a1_a2, dist_a1_b1, dist_a1_b2);
                int b1_on_a = position_value(c0, dist_b1_a1, dist_b1_a2);
                int b2_on_a = position_value(dist_b1_b2, dist_b1_a1, dist_b1_a2);

                if ((a1_on_b < 1 && a2_on_b < 1) || (a1_on_b > 3 && a2_on_b > 3))
                {
                    return Policy::disjoint();
                }

                if (a1_on_b == 1)
                {
                    dist_b1_a1 = 0;
                    dist_a1_b1 = 0;
                }
                else if (a1_on_b == 3)
                {
                    dist_b1_a1 = dist_b1_b2;
                    dist_a1_b2 = 0;
                }

                if (a2_on_b == 1)
                {
                    dist_b1_a2 = 0;
                    dist_a1_b1 = dist_a1_a2;
                }
                else if (a2_on_b == 3)
                {
                    dist_b1_a2 = dist_b1_b2;
                    dist_a1_b2 = dist_a1_a2;
                }

                bool opposite = ! same_direction(res_a1_a2.azimuth, res_b1_b2.azimuth);

                // NOTE: If segment was reversed opposite, positions and segment ratios has to be altered
                if (is_a_reversed)
                {
                    // opposite
                    opposite = ! opposite;
                    // positions
                    std::swap(a1_on_b, a2_on_b);
                    b1_on_a = 4 - b1_on_a;
                    b2_on_a = 4 - b2_on_a;
                    // distances for ratios
                    std::swap(dist_b1_a1, dist_b1_a2);
                    dist_a1_b1 = dist_a1_a2 - dist_a1_b1;
                    dist_a1_b2 = dist_a1_a2 - dist_a1_b2;
                }
                if (is_b_reversed)
                {
                    // opposite
                    opposite = ! opposite;
                    // positions
                    a1_on_b = 4 - a1_on_b;
                    a2_on_b = 4 - a2_on_b;
                    std::swap(b1_on_a, b2_on_a);
                    // distances for ratios
                    dist_b1_a1 = dist_b1_b2 - dist_b1_a1;
                    dist_b1_a2 = dist_b1_b2 - dist_b1_a2;
                    std::swap(dist_a1_b1, dist_a1_b2);
                }

                segment_ratio<calc_t> ra_from(dist_b1_a1, dist_b1_b2);
                segment_ratio<calc_t> ra_to(dist_b1_a2, dist_b1_b2);
                segment_ratio<calc_t> rb_from(dist_a1_b1, dist_a1_a2);
                segment_ratio<calc_t> rb_to(dist_a1_b2, dist_a1_a2);

                return Policy::segments_collinear(a, b, opposite,
                    a1_on_b, a2_on_b, b1_on_a, b2_on_a,
                    ra_from, ra_to, rb_from, rb_to);
            }
        }
        else // crossing or touching
        {
            if (a_is_point || b_is_point)
            {
                return Policy::disjoint();
            }

            calc_t lon = 0, lat = 0;
            intersection_point_flag ip_flag;
            calc_t dist_a1_a2, dist_a1_i1, dist_b1_b2, dist_b1_i1;
            if (calculate_ip_data(a1, a2, b1, b2,
                                  a1_lon, a1_lat, a2_lon, a2_lat,
                                  b1_lon, b1_lat, b2_lon, b2_lat,
                                  res_a1_a2, res_a1_b1, res_a1_b2,
                                  res_b1_b2, res_b1_a1, res_b1_a2,
                                  sides, spheroid,
                                  lon, lat,
                                  dist_a1_a2, dist_a1_i1, dist_b1_b2, dist_b1_i1,
                                  ip_flag))
            {
                // NOTE: If segment was reversed sides and segment ratios has to be altered
                if (is_a_reversed)
                {
                    // sides
                    sides_reverse_segment<0>(sides);
                    // distance for ratio
                    dist_a1_i1 = dist_a1_a2 - dist_a1_i1;
                    // ip flag
                    ip_flag_reverse_segment(ip_flag, ipi_at_a1, ipi_at_a2);
                }
                if (is_b_reversed)
                {
                    // sides
                    sides_reverse_segment<1>(sides);
                    // distance for ratio
                    dist_b1_i1 = dist_b1_b2 - dist_b1_i1;
                    // ip flag
                    ip_flag_reverse_segment(ip_flag, ipi_at_b1, ipi_at_b2);
                }

                // intersects
                segment_intersection_info
                    <
                        calc_t,
                        segment_ratio<calc_t>
                    > sinfo;

                sinfo.lon = lon;
                sinfo.lat = lat;
                sinfo.robust_ra.assign(dist_a1_i1, dist_a1_a2);
                sinfo.robust_rb.assign(dist_b1_i1, dist_b1_b2);
                sinfo.ip_flag = ip_flag;

                return Policy::segments_crosses(sides, sinfo, a, b);
            }
            else
            {
                return Policy::disjoint();
            }
        }
    }

    template <typename Policy, typename CalcT, typename Segment, typename Point1, typename Point2, typename ResultInverse>
    static inline typename Policy::return_type
        collinear_one_degenerated(Segment const& segment, bool degenerated_a,
                                  Point1 const& a1, Point1 const& a2,
                                  Point2 const& b1, Point2 const& b2,
                                  ResultInverse const& res_a1_a2,
                                  ResultInverse const& res_a1_b1,
                                  ResultInverse const& res_a1_b2,
                                  bool is_other_reversed,
                                  bool degen_neq_coords)
    {
        CalcT dist_1_2, dist_1_o;
        if (! calculate_collinear_data(a1, a2, b1, b2, res_a1_a2, res_a1_b1, res_a1_b2, dist_1_2, dist_1_o, degen_neq_coords))
        {
            return Policy::disjoint();
        }

        // NOTE: If segment was reversed segment ratio has to be altered
        if (is_other_reversed)
        {
            // distance for ratio
            dist_1_o = dist_1_2 - dist_1_o;
        }
        
        return Policy::one_degenerate(segment, segment_ratio<CalcT>(dist_1_o, dist_1_2), degenerated_a);
    }

    // TODO: instead of checks below test bi against a1 and a2 here?
    //       in order to make this independent from is_near()
    template <typename Point1, typename Point2, typename ResultInverse, typename CalcT>
    static inline bool calculate_collinear_data(Point1 const& a1, Point1 const& a2, // in
                                                Point2 const& b1, Point2 const& /*b2*/, // in
                                                ResultInverse const& res_a1_a2,     // in
                                                ResultInverse const& res_a1_b1,     // in
                                                ResultInverse const& res_a1_b2,     // in
                                                CalcT& dist_a1_a2,                  // out
                                                CalcT& dist_a1_b1,                  // out
                                                bool degen_neq_coords = false)      // in
    {
        dist_a1_a2 = res_a1_a2.distance;

        dist_a1_b1 = res_a1_b1.distance;
        if (! same_direction(res_a1_b1.azimuth, res_a1_a2.azimuth))
        {
            dist_a1_b1 = -dist_a1_b1;
        }

        // if b1 is close a1
        if (is_endpoint_equal(dist_a1_b1, a1, b1))
        {
            dist_a1_b1 = 0;
            return true;
        }
        // if b1 is close a2
        else if (is_endpoint_equal(dist_a1_a2 - dist_a1_b1, a2, b1))
        {
            dist_a1_b1 = dist_a1_a2;
            return true;
        }

        // check the other endpoint of degenerated segment near a pole
        if (degen_neq_coords)
        {
            static CalcT const c0 = 0;
            if (math::equals(res_a1_b2.distance, c0))
            {
                dist_a1_b1 = 0;
                return true;
            }
            else if (math::equals(dist_a1_a2 - res_a1_b2.distance, c0))
            {
                dist_a1_b1 = dist_a1_a2;
                return true;
            }
        }

        // or i1 is on b
        return segment_ratio<CalcT>(dist_a1_b1, dist_a1_a2).on_segment();
    }

    template <typename Point1, typename Point2, typename CalcT, typename ResultInverse, typename Spheroid_>
    static inline bool calculate_ip_data(Point1 const& a1, Point1 const& a2,       // in
                                         Point2 const& b1, Point2 const& b2,       // in
                                         CalcT const& a1_lon, CalcT const& a1_lat, // in
                                         CalcT const& a2_lon, CalcT const& a2_lat, // in
                                         CalcT const& b1_lon, CalcT const& b1_lat, // in
                                         CalcT const& b2_lon, CalcT const& b2_lat, // in
                                         ResultInverse const& res_a1_a2,           // in
                                         ResultInverse const& res_a1_b1,           // in
                                         ResultInverse const& res_a1_b2,           // in
                                         ResultInverse const& res_b1_b2,           // in
                                         ResultInverse const& res_b1_a1,           // in
                                         ResultInverse const& res_b1_a2,           // in
                                         side_info const& sides,                   // in
                                         Spheroid_ const& spheroid,                // in
                                         CalcT & lon, CalcT & lat,             // out
                                         CalcT& dist_a1_a2, CalcT& dist_a1_ip, // out
                                         CalcT& dist_b1_b2, CalcT& dist_b1_ip, // out
                                         intersection_point_flag& ip_flag)     // out
    {
        dist_a1_a2 = res_a1_a2.distance;
        dist_b1_b2 = res_b1_b2.distance;

        // assign the IP if some endpoints overlap
        if (equals_point_point(a1, b1))
        {
            lon = a1_lon;
            lat = a1_lat;
            dist_a1_ip = 0;
            dist_b1_ip = 0;
            ip_flag = ipi_at_a1;
            return true;
        }
        else if (equals_point_point(a1, b2))
        {
            lon = a1_lon;
            lat = a1_lat;
            dist_a1_ip = 0;
            dist_b1_ip = dist_b1_b2;
            ip_flag = ipi_at_a1;
            return true;
        }
        else if (equals_point_point(a2, b1))
        {
            lon = a2_lon;
            lat = a2_lat;
            dist_a1_ip = dist_a1_a2;
            dist_b1_ip = 0;
            ip_flag = ipi_at_a2;
            return true;
        }
        else if (equals_point_point(a2, b2))
        {
            lon = a2_lon;
            lat = a2_lat;
            dist_a1_ip = dist_a1_a2;
            dist_b1_ip = dist_b1_b2;
            ip_flag = ipi_at_a2;
            return true;
        }

        // at this point we know that the endpoints doesn't overlap
        // check cases when an endpoint lies on the other geodesic
        if (sides.template get<0, 0>() == 0) // a1 wrt b
        {
            if (res_b1_a1.distance <= res_b1_b2.distance
                && same_direction(res_b1_a1.azimuth, res_b1_b2.azimuth))
            {
                lon = a1_lon;
                lat = a1_lat;
                dist_a1_ip = 0;
                dist_b1_ip = res_b1_a1.distance;
                ip_flag = ipi_at_a1;
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (sides.template get<0, 1>() == 0) // a2 wrt b
        {
            if (res_b1_a2.distance <= res_b1_b2.distance
                && same_direction(res_b1_a2.azimuth, res_b1_b2.azimuth))
            {
                lon = a2_lon;
                lat = a2_lat;
                dist_a1_ip = res_a1_a2.distance;
                dist_b1_ip = res_b1_a2.distance;
                ip_flag = ipi_at_a2;
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (sides.template get<1, 0>() == 0) // b1 wrt a
        {
            if (res_a1_b1.distance <= res_a1_a2.distance
                && same_direction(res_a1_b1.azimuth, res_a1_a2.azimuth))
            {
                lon = b1_lon;
                lat = b1_lat;
                dist_a1_ip = res_a1_b1.distance;
                dist_b1_ip = 0;
                ip_flag = ipi_at_b1;
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (sides.template get<1, 1>() == 0) // b2 wrt a
        {
            if (res_a1_b2.distance <= res_a1_a2.distance
                && same_direction(res_a1_b2.azimuth, res_a1_a2.azimuth))
            {
                lon = b2_lon;
                lat = b2_lat;
                dist_a1_ip = res_a1_b2.distance;
                dist_b1_ip = res_b1_b2.distance;
                ip_flag = ipi_at_b2;
                return true;
            }
            else
            {
                return false;
            }
        }

        // At this point neither the endpoints overlaps
        // nor any andpoint lies on the other geodesic
        // So the endpoints should lie on the opposite sides of both geodesics

        bool const ok = formula::sjoberg_intersection<CalcT, FormulaPolicy::template inverse, Order>
                        ::apply(a1_lon, a1_lat, a2_lon, a2_lat, res_a1_a2.azimuth,
                                b1_lon, b1_lat, b2_lon, b2_lat, res_b1_b2.azimuth,
                                lon, lat, spheroid);

        if (! ok)
        {
            return false;
        }

        typedef typename FormulaPolicy::template inverse<CalcT, true, true, false, false, false> inverse_dist_azi;
        typedef typename inverse_dist_azi::result_type inverse_result;

        inverse_result const res_a1_ip = inverse_dist_azi::apply(a1_lon, a1_lat, lon, lat, spheroid);
        dist_a1_ip = res_a1_ip.distance;
        if (! same_direction(res_a1_ip.azimuth, res_a1_a2.azimuth))
        {
            dist_a1_ip = -dist_a1_ip;
        }

        bool is_on_a = segment_ratio<CalcT>(dist_a1_ip, dist_a1_a2).on_segment();
        // NOTE: not fully consistent with equals_point_point() since radians are always used.
        bool is_on_a1 = math::equals(lon, a1_lon) && math::equals(lat, a1_lat);
        bool is_on_a2 = math::equals(lon, a2_lon) && math::equals(lat, a2_lat);

        if (! (is_on_a || is_on_a1 || is_on_a2))
        {
            return false;
        }

        inverse_result const res_b1_ip = inverse_dist_azi::apply(b1_lon, b1_lat, lon, lat, spheroid);
        dist_b1_ip = res_b1_ip.distance;
        if (! same_direction(res_b1_ip.azimuth, res_b1_b2.azimuth))
        {
            dist_b1_ip = -dist_b1_ip;
        }

        bool is_on_b = segment_ratio<CalcT>(dist_b1_ip, dist_b1_b2).on_segment();
        // NOTE: not fully consistent with equals_point_point() since radians are always used.
        bool is_on_b1 = math::equals(lon, b1_lon) && math::equals(lat, b1_lat);
        bool is_on_b2 = math::equals(lon, b2_lon) && math::equals(lat, b2_lat);

        if (! (is_on_b || is_on_b1 || is_on_b2))
        {
            return false;
        }
        
        typedef typename FormulaPolicy::template inverse<CalcT, true, false, false, false, false> inverse_dist;

        ip_flag = ipi_inters;

        if (is_on_b1)
        {
            lon = b1_lon;
            lat = b1_lat;
            dist_a1_ip = inverse_dist::apply(a1_lon, a1_lat, lon, lat, spheroid).distance; // for consistency
            dist_b1_ip = 0;
            ip_flag = ipi_at_b1;
        }
        else if (is_on_b2)
        {
            lon = b2_lon;
            lat = b2_lat;
            dist_a1_ip = inverse_dist::apply(a1_lon, a1_lat, lon, lat, spheroid).distance; // for consistency
            dist_b1_ip = res_b1_b2.distance;
            ip_flag = ipi_at_b2;
        }

        if (is_on_a1)
        {
            lon = a1_lon;
            lat = a1_lat;
            dist_a1_ip = 0;
            dist_b1_ip = inverse_dist::apply(b1_lon, b1_lat, lon, lat, spheroid).distance; // for consistency
            ip_flag = ipi_at_a1;
        }
        else if (is_on_a2)
        {
            lon = a2_lon;
            lat = a2_lat;
            dist_a1_ip = res_a1_a2.distance;
            dist_b1_ip = inverse_dist::apply(b1_lon, b1_lat, lon, lat, spheroid).distance; // for consistency
            ip_flag = ipi_at_a2;
        }        

        return true;
    }

    template <typename CalcT, typename P1, typename P2>
    static inline bool is_endpoint_equal(CalcT const& dist,
                                         P1 const& ai, P2 const& b1)
    {
        static CalcT const c0 = 0;
        return is_near(dist) && (math::equals(dist, c0) || equals_point_point(ai, b1));
    }

    template <typename CalcT>
    static inline bool is_near(CalcT const& dist)
    {
        // NOTE: This strongly depends on the Inverse method
        CalcT const small_number = CalcT(boost::is_same<CalcT, float>::value ? 0.0001 : 0.00000001);
        return math::abs(dist) <= small_number;
    }

    template <typename ProjCoord1, typename ProjCoord2>
    static inline int position_value(ProjCoord1 const& ca1,
                                     ProjCoord2 const& cb1,
                                     ProjCoord2 const& cb2)
    {
        // S1x  0   1    2     3   4
        // S2       |---------->
        return math::equals(ca1, cb1) ? 1
             : math::equals(ca1, cb2) ? 3
             : cb1 < cb2 ?
                ( ca1 < cb1 ? 0
                : ca1 > cb2 ? 4
                : 2 )
              : ( ca1 > cb1 ? 0
                : ca1 < cb2 ? 4
                : 2 );
    }

    template <typename CalcT>
    static inline bool same_direction(CalcT const& azimuth1, CalcT const& azimuth2)
    {
        // distance between two angles normalized to (-180, 180]
        CalcT const angle_diff = math::longitude_distance_signed<radian>(azimuth1, azimuth2);
        return math::abs(angle_diff) <= math::half_pi<CalcT>();
    }

    template <int Which>
    static inline void sides_reverse_segment(side_info & sides)
    {
        // names assuming segment A is reversed (Which == 0)
        int a1_wrt_b = sides.template get<Which, 0>();
        int a2_wrt_b = sides.template get<Which, 1>();
        std::swap(a1_wrt_b, a2_wrt_b);
        sides.template set<Which>(a1_wrt_b, a2_wrt_b);
        int b1_wrt_a = sides.template get<1 - Which, 0>();
        int b2_wrt_a = sides.template get<1 - Which, 1>();
        sides.template set<1 - Which>(-b1_wrt_a, -b2_wrt_a);
    }

    static inline void ip_flag_reverse_segment(intersection_point_flag & ip_flag,
                                               intersection_point_flag const& ipi_at_p1,
                                               intersection_point_flag const& ipi_at_p2)
    {
        ip_flag = ip_flag == ipi_at_p1 ? ipi_at_p2 :
                  ip_flag == ipi_at_p2 ? ipi_at_p1 :
                  ip_flag;
    }

    template <typename Point1, typename Point2>
    static inline bool equals_point_point(Point1 const& point1, Point2 const& point2)
    {
        return detail::equals::equals_point_point(point1, point2,
                                                  point_in_point_strategy_type());
    }

private:
    Spheroid m_spheroid;
};


}} // namespace strategy::intersection

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_INTERSECTION_HPP

/* intersection.hpp
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
*/