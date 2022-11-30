// Boost.Geometry

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2016-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_INTERSECTION_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_INTERSECTION_HPP

#include <algorithm>
#include <type_traits>

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
#include <boost/geometry/geometries/segment.hpp>

#include <boost/geometry/policies/robustness/segment_ratio.hpp>

#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/strategy/geographic/area.hpp>
#include <boost/geometry/strategy/geographic/envelope.hpp>
#include <boost/geometry/strategy/geographic/expand_segment.hpp>
#include <boost/geometry/strategy/spherical/expand_box.hpp>

#include <boost/geometry/strategies/geographic/disjoint_segment_box.hpp>
#include <boost/geometry/strategies/geographic/distance.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/strategies/geographic/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/geographic/side.hpp>
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
    std::size_t Order = strategy::default_order<FormulaPolicy>::value,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
struct geographic_segments
{
    typedef geographic_tag cs_tag;

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

    Spheroid model() const
    {
        return m_spheroid;
    }

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

        point1_type const& p0 = range_p.at(0);
        point1_type const& p1 = range_p.at(1);
        point2_type const& q0 = range_q.at(0);
        point2_type const& q1 = range_q.at(1);

        bool const is_p_reversed = get<1>(p0) > get<1>(p1);
        bool const is_q_reversed = get<1>(q0) > get<1>(q1);

        // Call apply with original segments and ordered points
        return apply<Policy>(segment_type1(p0, p1),
                             segment_type2(q0, q1),
                             (is_p_reversed ? p1 : p0),
                             (is_p_reversed ? p0 : p1),
                             (is_q_reversed ? q1 : q0),
                             (is_q_reversed ? q0 : q1),
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
        CalcT const small_number = CalcT(std::is_same<CalcT, float>::value ? 0.0001 : 0.00000001);
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
        return strategy::within::spherical_point_point::apply(point1, point2);
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