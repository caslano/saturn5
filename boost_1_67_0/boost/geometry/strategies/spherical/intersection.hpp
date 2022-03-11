// Boost.Geometry

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2016-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_INTERSECTION_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_INTERSECTION_HPP

#include <algorithm>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/assign_values.hpp>
#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/recalculate.hpp>

#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/arithmetic/cross_product.hpp>
#include <boost/geometry/arithmetic/dot_product.hpp>
#include <boost/geometry/arithmetic/normalize.hpp>
#include <boost/geometry/formulas/spherical.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/geometries/concepts/segment_concept.hpp>

#include <boost/geometry/policies/robustness/segment_ratio.hpp>

#include <boost/geometry/strategies/covered_by.hpp>
#include <boost/geometry/strategies/intersection.hpp>
#include <boost/geometry/strategies/intersection_result.hpp>
#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/strategies/side_info.hpp>
#include <boost/geometry/strategies/spherical/area.hpp>
#include <boost/geometry/strategies/spherical/disjoint_box_box.hpp>
#include <boost/geometry/strategies/spherical/disjoint_segment_box.hpp>
#include <boost/geometry/strategies/spherical/distance_haversine.hpp>
#include <boost/geometry/strategies/spherical/envelope.hpp>
#include <boost/geometry/strategies/spherical/expand_box.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>
#include <boost/geometry/strategies/spherical/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/spherical/ssf.hpp>
#include <boost/geometry/strategies/within.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace intersection
{

// NOTE:
// The coordinates of crossing IP may be calculated with small precision in some cases.
// For double, near the equator noticed error ~1e-9 so far greater than
// machine epsilon which is ~1e-16. This error is ~0.04m.
// E.g. consider two cases, one near the origin and the second one rotated by 90 deg around Z or SN axis.
// After the conversion from spherical degrees to cartesian 3d the following coordinates
// are calculated:
// for sph (-1 -1,  1 1) deg cart3d ys are -0.017449748351250485 and  0.017449748351250485
// for sph (89 -1, 91 1) deg cart3d xs are  0.017449748351250571 and -0.017449748351250450
// During the conversion degrees must first be converted to radians and then radians
// are passed into trigonometric functions. The error may have several causes:
// 1. Radians cannot represent exactly the same angles as degrees.
// 2. Different longitudes are passed into sin() for x, corresponding to cos() for y,
//    and for different angle the error of the result may be different.
// 3. These non-corresponding cartesian coordinates are used in calculation,
//    e.g. multiplied several times in cross and dot products.
// If it was a problem this strategy could e.g. "normalize" longitudes before the conversion using the source units
// by rotating the globe around Z axis, so moving longitudes always the same way towards the origin,
// assuming this could help which is not clear.
// For now, intersection points near the endpoints are checked explicitly if needed (if the IP is near the endpoint)
// to generate precise result for them. Only the crossing (i) case may suffer from lower precision.

template
<
    typename CalcPolicy,
    typename CalculationType = void
>
struct ecef_segments
{
    typedef spherical_tag cs_tag;

    typedef side::spherical_side_formula<CalculationType> side_strategy_type;

    static inline side_strategy_type get_side_strategy()
    {
        return side_strategy_type();
    }

    template <typename Geometry1, typename Geometry2>
    struct point_in_geometry_strategy
    {
        typedef strategy::within::spherical_winding
            <
                typename point_type<Geometry1>::type,
                typename point_type<Geometry2>::type,
                CalculationType
            > type;
    };

    template <typename Geometry1, typename Geometry2>
    static inline typename point_in_geometry_strategy<Geometry1, Geometry2>::type
        get_point_in_geometry_strategy()
    {
        typedef typename point_in_geometry_strategy
            <
                Geometry1, Geometry2
            >::type strategy_type;
        return strategy_type();
    }

    template <typename Geometry>
    struct area_strategy
    {
        typedef area::spherical
            <
                typename coordinate_type<Geometry>::type,
                CalculationType
            > type;
    };

    template <typename Geometry>
    static inline typename area_strategy<Geometry>::type get_area_strategy()
    {
        typedef typename area_strategy<Geometry>::type strategy_type;
        return strategy_type();
    }

    template <typename Geometry>
    struct distance_strategy
    {
        typedef distance::haversine
            <
                typename coordinate_type<Geometry>::type,
                CalculationType
            > type;
    };

    template <typename Geometry>
    static inline typename distance_strategy<Geometry>::type get_distance_strategy()
    {
        typedef typename distance_strategy<Geometry>::type strategy_type;
        return strategy_type();
    }

    typedef envelope::spherical<CalculationType>
        envelope_strategy_type;

    static inline envelope_strategy_type get_envelope_strategy()
    {
        return envelope_strategy_type();
    }

    typedef expand::spherical_segment<CalculationType>
        expand_strategy_type;

    static inline expand_strategy_type get_expand_strategy()
    {
        return expand_strategy_type();
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

    typedef disjoint::segment_box_spherical disjoint_segment_box_strategy_type;

    static inline disjoint_segment_box_strategy_type get_disjoint_segment_box_strategy()
    {
        return disjoint_segment_box_strategy_type();
    }

    typedef covered_by::spherical_point_box disjoint_point_box_strategy_type;
    typedef covered_by::spherical_point_box covered_by_point_box_strategy_type;
    typedef within::spherical_point_box within_point_box_strategy_type;
    typedef envelope::spherical_box envelope_box_strategy_type;
    typedef expand::spherical_box expand_box_strategy_type;

    enum intersection_point_flag { ipi_inters = 0, ipi_at_a1, ipi_at_a2, ipi_at_b1, ipi_at_b2 };

    // segment_intersection_info cannot outlive relate_ecef_segments
    template <typename CoordinateType, typename SegmentRatio, typename Vector3d>
    struct segment_intersection_info
    {
        segment_intersection_info(CalcPolicy const& calc)
            : calc_policy(calc)
        {}

        template <typename Point, typename Segment1, typename Segment2>
        void calculate(Point& point, Segment1 const& a, Segment2 const& b) const
        {
            if (ip_flag == ipi_inters)
            {
                // TODO: assign the rest of coordinates
                point = calc_policy.template from_cart3d<Point>(intersection_point);
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

        Vector3d intersection_point;
        SegmentRatio robust_ra;
        SegmentRatio robust_rb;
        intersection_point_flag ip_flag;

        CalcPolicy const& calc_policy;
    };

    // Relate segments a and b
    template
    <
        typename UniqueSubRange1,
        typename UniqueSubRange2,
        typename Policy
    >
    static inline typename Policy::return_type
        apply(UniqueSubRange1 const& range_p, UniqueSubRange2 const& range_q,
              Policy const&)
    {
        // For now create it using default constructor. In the future it could
        //  be stored in strategy. However then apply() wouldn't be static and
        //  all relops and setops would have to take the strategy or model.
        // Initialize explicitly to prevent compiler errors in case of PoD type
        CalcPolicy const calc_policy = CalcPolicy();

        typedef typename UniqueSubRange1::point_type point1_type;
        typedef typename UniqueSubRange2::point_type point2_type;

        BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<point1_type>) );
        BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<point2_type>) );

        point1_type const& a1 = range_p.at(0);
        point1_type const& a2 = range_p.at(1);
        point2_type const& b1 = range_q.at(0);
        point2_type const& b2 = range_q.at(1);

        typedef model::referring_segment<point1_type const> segment1_type;
        typedef model::referring_segment<point2_type const> segment2_type;
        segment1_type const a(a1, a2);
        segment2_type const b(b1, b2);

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

        typedef typename select_calculation_type
            <segment1_type, segment2_type, CalculationType>::type calc_t;

        calc_t const c0 = 0;
        calc_t const c1 = 1;

        typedef model::point<calc_t, 3, cs::cartesian> vec3d_t;

        vec3d_t const a1v = calc_policy.template to_cart3d<vec3d_t>(a1);
        vec3d_t const a2v = calc_policy.template to_cart3d<vec3d_t>(a2);
        vec3d_t const b1v = calc_policy.template to_cart3d<vec3d_t>(b1);
        vec3d_t const b2v = calc_policy.template to_cart3d<vec3d_t>(b2);
        
        bool degen_neq_coords = false;
        side_info sides;

        typename CalcPolicy::template plane<vec3d_t>
            plane2 = calc_policy.get_plane(b1v, b2v);

        calc_t dist_b1_b2 = 0;
        if (! b_is_point)
        {
            calculate_dist(b1v, b2v, plane2, dist_b1_b2);
            if (math::equals(dist_b1_b2, c0))
            {
                degen_neq_coords = true;
                b_is_point = true;
                dist_b1_b2 = 0;
            }
            else
            {
                // not normalized normals, the same as in side strategy
                sides.set<0>(plane2.side_value(a1v), plane2.side_value(a2v));
                if (sides.same<0>())
                {
                    // Both points are at same side of other segment, we can leave
                    return Policy::disjoint();
                }
            }
        }

        typename CalcPolicy::template plane<vec3d_t>
            plane1 = calc_policy.get_plane(a1v, a2v);

        calc_t dist_a1_a2 = 0;
        if (! a_is_point)
        {
            calculate_dist(a1v, a2v, plane1, dist_a1_a2);
            if (math::equals(dist_a1_a2, c0))
            {
                degen_neq_coords = true;
                a_is_point = true;
                dist_a1_a2 = 0;
            }
            else
            {
                // not normalized normals, the same as in side strategy
                sides.set<1>(plane1.side_value(b1v), plane1.side_value(b2v));
                if (sides.same<1>())
                {
                    // Both points are at same side of other segment, we can leave
                    return Policy::disjoint();
                }
            }
        }

        // NOTE: at this point the segments may still be disjoint

        calc_t len1 = 0;
        // point or opposite sides of a sphere/spheroid, assume point
        if (! a_is_point && ! detail::vec_normalize(plane1.normal, len1))
        {
            a_is_point = true;
            if (sides.get<0, 0>() == 0 || sides.get<0, 1>() == 0)
            {
                sides.set<0>(0, 0);
            }
        }

        calc_t len2 = 0;
        if (! b_is_point && ! detail::vec_normalize(plane2.normal, len2))
        {
            b_is_point = true;
            if (sides.get<1, 0>() == 0 || sides.get<1, 1>() == 0)
            {
                sides.set<1>(0, 0);
            }
        }

        // check both degenerated once more
        if (a_is_point && b_is_point)
        {
            return equals_point_point(a1, b2)
                ? Policy::degenerate(a, true)
                : Policy::disjoint()
                ;
        }

        // NOTE: at this point the segments may still be disjoint
        // NOTE: at this point one of the segments may be degenerated

        bool collinear = sides.collinear();       

        if (! collinear)
        {
            // NOTE: for some approximations it's possible that both points may lie
            // on the same geodesic but still some of the sides may be != 0.
            // This is e.g. true for long segments represented as elliptic arcs
            // with origin different than the center of the coordinate system.
            // So make the sides consistent

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

        calc_t dot_n1n2 = dot_product(plane1.normal, plane2.normal);

        // NOTE: this is technically not needed since theoretically above sides
        //       are calculated, but just in case check the normals.
        //       Have in mind that SSF side strategy doesn't check this.
        // collinear if normals are equal or opposite: cos(a) in {-1, 1}
        if (! collinear && math::equals(math::abs(dot_n1n2), c1))
        {
            collinear = true;
            sides.set<0>(0, 0);
            sides.set<1>(0, 0);
        }
        
        if (collinear)
        {
            if (a_is_point)
            {
                return collinear_one_degenerated<Policy, calc_t>(a, true, b1, b2, a1, a2, b1v, b2v,
                                                                 plane2, a1v, a2v, dist_b1_b2, degen_neq_coords);
            }
            else if (b_is_point)
            {
                // b2 used to be consistent with (degenerated) checks above (is it needed?)
                return collinear_one_degenerated<Policy, calc_t>(b, false, a1, a2, b1, b2, a1v, a2v,
                                                                 plane1, b1v, b2v, dist_a1_a2, degen_neq_coords);
            }
            else
            {
                calc_t dist_a1_b1, dist_a1_b2;
                calc_t dist_b1_a1, dist_b1_a2;
                calculate_collinear_data(a1, a2, b1, b2, a1v, a2v, plane1, b1v, b2v, dist_a1_a2, dist_a1_b1);
                calculate_collinear_data(a1, a2, b2, b1, a1v, a2v, plane1, b2v, b1v, dist_a1_a2, dist_a1_b2);
                calculate_collinear_data(b1, b2, a1, a2, b1v, b2v, plane2, a1v, a2v, dist_b1_b2, dist_b1_a1);
                calculate_collinear_data(b1, b2, a2, a1, b1v, b2v, plane2, a2v, a1v, dist_b1_b2, dist_b1_a2);
                // NOTE: The following optimization causes problems with consitency
                // It may either be caused by numerical issues or the way how distance is coded:
                //   as cosine of angle scaled and translated, see: calculate_dist()
                /*dist_b1_b2 = dist_a1_b2 - dist_a1_b1;
                dist_b1_a1 = -dist_a1_b1;
                dist_b1_a2 = dist_a1_a2 - dist_a1_b1;
                dist_a1_a2 = dist_b1_a2 - dist_b1_a1;
                dist_a1_b1 = -dist_b1_a1;
                dist_a1_b2 = dist_b1_b2 - dist_b1_a1;*/

                segment_ratio<calc_t> ra_from(dist_b1_a1, dist_b1_b2);
                segment_ratio<calc_t> ra_to(dist_b1_a2, dist_b1_b2);
                segment_ratio<calc_t> rb_from(dist_a1_b1, dist_a1_a2);
                segment_ratio<calc_t> rb_to(dist_a1_b2, dist_a1_a2);
                
                // NOTE: this is probably not needed
                int const a1_wrt_b = position_value(c0, dist_a1_b1, dist_a1_b2);
                int const a2_wrt_b = position_value(dist_a1_a2, dist_a1_b1, dist_a1_b2);
                int const b1_wrt_a = position_value(c0, dist_b1_a1, dist_b1_a2);
                int const b2_wrt_a = position_value(dist_b1_b2, dist_b1_a1, dist_b1_a2);

                if (a1_wrt_b == 1)
                {
                    ra_from.assign(0, dist_b1_b2);
                    rb_from.assign(0, dist_a1_a2);
                }
                else if (a1_wrt_b == 3)
                {
                    ra_from.assign(dist_b1_b2, dist_b1_b2);
                    rb_to.assign(0, dist_a1_a2);
                }

                if (a2_wrt_b == 1)
                {
                    ra_to.assign(0, dist_b1_b2);
                    rb_from.assign(dist_a1_a2, dist_a1_a2);
                }
                else if (a2_wrt_b == 3)
                {
                    ra_to.assign(dist_b1_b2, dist_b1_b2);
                    rb_to.assign(dist_a1_a2, dist_a1_a2);
                }

                if ((a1_wrt_b < 1 && a2_wrt_b < 1) || (a1_wrt_b > 3 && a2_wrt_b > 3))
                {
                    return Policy::disjoint();
                }

                bool const opposite = dot_n1n2 < c0;

                return Policy::segments_collinear(a, b, opposite,
                    a1_wrt_b, a2_wrt_b, b1_wrt_a, b2_wrt_a,
                    ra_from, ra_to, rb_from, rb_to);
            }
        }
        else // crossing
        {
            if (a_is_point || b_is_point)
            {
                return Policy::disjoint();
            }

            vec3d_t i1;
            intersection_point_flag ip_flag;
            calc_t dist_a1_i1, dist_b1_i1;
            if (calculate_ip_data(a1, a2, b1, b2, a1v, a2v, b1v, b2v,
                                  plane1, plane2, calc_policy,
                                  sides, dist_a1_a2, dist_b1_b2,
                                  i1, dist_a1_i1, dist_b1_i1, ip_flag))
            {
                // intersects
                segment_intersection_info
                    <
                        calc_t,
                        segment_ratio<calc_t>,
                        vec3d_t
                    > sinfo(calc_policy);

                sinfo.robust_ra.assign(dist_a1_i1, dist_a1_a2);
                sinfo.robust_rb.assign(dist_b1_i1, dist_b1_b2);
                sinfo.intersection_point = i1;
                sinfo.ip_flag = ip_flag;

                return Policy::segments_crosses(sides, sinfo, a, b);
            }
            else
            {
                return Policy::disjoint();
            }
        }
    }

private:
    template <typename Policy, typename CalcT, typename Segment, typename Point1, typename Point2, typename Vec3d, typename Plane>
    static inline typename Policy::return_type
        collinear_one_degenerated(Segment const& segment, bool degenerated_a,
                                  Point1 const& a1, Point1 const& a2,
                                  Point2 const& b1, Point2 const& b2,
                                  Vec3d const& a1v, Vec3d const& a2v,
                                  Plane const& plane,
                                  Vec3d const& b1v, Vec3d const& b2v,
                                  CalcT const& dist_1_2,
                                  bool degen_neq_coords)
    {
        CalcT dist_1_o;
        return ! calculate_collinear_data(a1, a2, b1, b2, a1v, a2v, plane, b1v, b2v, dist_1_2, dist_1_o, degen_neq_coords)
                ? Policy::disjoint()
                : Policy::one_degenerate(segment, segment_ratio<CalcT>(dist_1_o, dist_1_2), degenerated_a);
    }

    template <typename Point1, typename Point2, typename Vec3d, typename Plane, typename CalcT>
    static inline bool calculate_collinear_data(Point1 const& a1, Point1 const& a2, // in
                                                Point2 const& b1, Point2 const& /*b2*/, // in
                                                Vec3d const& a1v,                   // in
                                                Vec3d const& a2v,                   // in
                                                Plane const& plane1,                // in
                                                Vec3d const& b1v,                   // in
                                                Vec3d const& b2v,                   // in
                                                CalcT const& dist_a1_a2,            // in
                                                CalcT& dist_a1_b1,                  // out
                                                bool degen_neq_coords = false)      // in
    {
        // calculate dist_a1_b1
        calculate_dist(a1v, a2v, plane1, b1v, dist_a1_b1);

        // if b1 is equal to a1
        if (is_endpoint_equal(dist_a1_b1, a1, b1))
        {
            dist_a1_b1 = 0;
            return true;
        }
        // or b1 is equal to a2
        else if (is_endpoint_equal(dist_a1_a2 - dist_a1_b1, a2, b1))
        {
            dist_a1_b1 = dist_a1_a2;
            return true;
        }

        // check the other endpoint of degenerated segment near a pole
        if (degen_neq_coords)
        {
            static CalcT const c0 = 0;

            CalcT dist_a1_b2 = 0;
            calculate_dist(a1v, a2v, plane1, b2v, dist_a1_b2);

            if (math::equals(dist_a1_b2, c0))
            {
                dist_a1_b1 = 0;
                return true;
            }
            else if (math::equals(dist_a1_a2 - dist_a1_b2, c0))
            {
                dist_a1_b1 = dist_a1_a2;
                return true;
            }
        }

        // or i1 is on b
        return segment_ratio<CalcT>(dist_a1_b1, dist_a1_a2).on_segment();
    }

    template <typename Point1, typename Point2, typename Vec3d, typename Plane, typename CalcT>
    static inline bool calculate_ip_data(Point1 const& a1, Point1 const& a2, // in
                                         Point2 const& b1, Point2 const& b2, // in
                                         Vec3d const& a1v, Vec3d const& a2v, // in
                                         Vec3d const& b1v, Vec3d const& b2v, // in
                                         Plane const& plane1,                // in
                                         Plane const& plane2,                // in
                                         CalcPolicy const& calc_policy,      // in
                                         side_info const& sides,             // in
                                         CalcT const& dist_a1_a2,            // in
                                         CalcT const& dist_b1_b2,            // in
                                         Vec3d & ip,                         // out
                                         CalcT& dist_a1_ip,                  // out
                                         CalcT& dist_b1_ip,                  // out
                                         intersection_point_flag& ip_flag)   // out
    {
        Vec3d ip1, ip2;
        calc_policy.intersection_points(plane1, plane2, ip1, ip2);
        
        calculate_dist(a1v, a2v, plane1, ip1, dist_a1_ip);
        ip = ip1;

        // choose the opposite side of the globe if the distance is shorter
        {
            CalcT const d = abs_distance(dist_a1_a2, dist_a1_ip);
            if (d > CalcT(0))
            {
                // TODO: this should be ok not only for sphere
                //       but requires more investigation
                CalcT const dist_a1_i2 = dist_of_i2(dist_a1_ip);
                CalcT const d2 = abs_distance(dist_a1_a2, dist_a1_i2);
                if (d2 < d)
                {
                    dist_a1_ip = dist_a1_i2;
                    ip = ip2;
                }
            }
        }

        bool is_on_a = false, is_near_a1 = false, is_near_a2 = false;
        if (! is_potentially_crossing(dist_a1_a2, dist_a1_ip, is_on_a, is_near_a1, is_near_a2))
        {
            return false;
        }

        calculate_dist(b1v, b2v, plane2, ip, dist_b1_ip);

        bool is_on_b = false, is_near_b1 = false, is_near_b2 = false;
        if (! is_potentially_crossing(dist_b1_b2, dist_b1_ip, is_on_b, is_near_b1, is_near_b2))
        {
            return false;
        }

        // reassign the IP if some endpoints overlap
        if (is_near_a1)
        {
            if (is_near_b1 && equals_point_point(a1, b1))
            {
                dist_a1_ip = 0;
                dist_b1_ip = 0;
                //i1 = a1v;
                ip_flag = ipi_at_a1;
                return true;
            }
            
            if (is_near_b2 && equals_point_point(a1, b2))
            {
                dist_a1_ip = 0;
                dist_b1_ip = dist_b1_b2;
                //i1 = a1v;
                ip_flag = ipi_at_a1;
                return true;
            }
        }

        if (is_near_a2)
        {
            if (is_near_b1 && equals_point_point(a2, b1))
            {
                dist_a1_ip = dist_a1_a2;
                dist_b1_ip = 0;
                //i1 = a2v;
                ip_flag = ipi_at_a2;
                return true;
            }

            if (is_near_b2 && equals_point_point(a2, b2))
            {
                dist_a1_ip = dist_a1_a2;
                dist_b1_ip = dist_b1_b2;
                //i1 = a2v;
                ip_flag = ipi_at_a2;
                return true;
            }
        }

        // at this point we know that the endpoints doesn't overlap
        // reassign IP and distance if the IP is on a segment and one of
        //   the endpoints of the other segment lies on the former segment
        if (is_on_a)
        {
            if (is_near_b1 && sides.template get<1, 0>() == 0) // b1 wrt a
            {
                calculate_dist(a1v, a2v, plane1, b1v, dist_a1_ip); // for consistency
                dist_b1_ip = 0;
                //i1 = b1v;
                ip_flag = ipi_at_b1;
                return true;
            }

            if (is_near_b2 && sides.template get<1, 1>() == 0) // b2 wrt a
            {
                calculate_dist(a1v, a2v, plane1, b2v, dist_a1_ip); // for consistency
                dist_b1_ip = dist_b1_b2;
                //i1 = b2v;
                ip_flag = ipi_at_b2;
                return true;
            }
        }

        if (is_on_b)
        {
            if (is_near_a1 && sides.template get<0, 0>() == 0) // a1 wrt b
            {
                dist_a1_ip = 0;
                calculate_dist(b1v, b2v, plane2, a1v, dist_b1_ip); // for consistency
                //i1 = a1v;
                ip_flag = ipi_at_a1;
                return true;
            }

            if (is_near_a2 && sides.template get<0, 1>() == 0) // a2 wrt b
            {
                dist_a1_ip = dist_a1_a2;
                calculate_dist(b1v, b2v, plane2, a2v, dist_b1_ip); // for consistency
                //i1 = a2v;
                ip_flag = ipi_at_a2;
                return true;
            }
        }

        ip_flag = ipi_inters;

        return is_on_a && is_on_b;
    }

    template <typename Vec3d, typename Plane, typename CalcT>
    static inline void calculate_dist(Vec3d const& a1v,    // in
                                      Vec3d const& a2v,    // in
                                      Plane const& plane1, // in
                                      CalcT& dist_a1_a2)   // out
    {
        static CalcT const c1 = 1;
        CalcT const cos_a1_a2 = plane1.cos_angle_between(a1v, a2v);
        dist_a1_a2 = -cos_a1_a2 + c1; // [1, -1] -> [0, 2] representing [0, pi]
    }

    template <typename Vec3d, typename Plane, typename CalcT>
    static inline void calculate_dist(Vec3d const& a1v,     // in
                                      Vec3d const& /*a2v*/, // in
                                      Plane const& plane1,  // in
                                      Vec3d const& i1,      // in
                                      CalcT& dist_a1_i1)    // out
    {
        static CalcT const c1 = 1;
        static CalcT const c2 = 2;
        static CalcT const c4 = 4;

        bool is_forward = true;
        CalcT cos_a1_i1 = plane1.cos_angle_between(a1v, i1, is_forward);
        dist_a1_i1 = -cos_a1_i1 + c1; // [0, 2] representing [0, pi]
        if (! is_forward) // left or right of a1 on a
        {
            dist_a1_i1 = -dist_a1_i1; // [0, 2] -> [0, -2] representing [0, -pi]
        }
        if (dist_a1_i1 <= -c2) // <= -pi
        {
            dist_a1_i1 += c4; // += 2pi
        }
    }
    /*
    template <typename Vec3d, typename Plane, typename CalcT>
    static inline void calculate_dists(Vec3d const& a1v,    // in
                                       Vec3d const& a2v,    // in
                                       Plane const& plane1, // in
                                       Vec3d const& i1,     // in
                                       CalcT& dist_a1_a2, // out
                                       CalcT& dist_a1_i1) // out
    {
        calculate_dist(a1v, a2v, plane1, dist_a1_a2);
        calculate_dist(a1v, a2v, plane1, i1, dist_a1_i1);
    }
    */
    // the dist of the ip on the other side of the sphere
    template <typename CalcT>
    static inline CalcT dist_of_i2(CalcT const& dist_a1_i1)
    {
        CalcT const c2 = 2;
        CalcT const c4 = 4;

        CalcT dist_a1_i2 = dist_a1_i1 - c2; // dist_a1_i2 = dist_a1_i1 - pi;
        if (dist_a1_i2 <= -c2)          // <= -pi
        {
            dist_a1_i2 += c4;           // += 2pi;
        }
        return dist_a1_i2;
    }

    template <typename CalcT>
    static inline CalcT abs_distance(CalcT const& dist_a1_a2, CalcT const& dist_a1_i1)
    {
        if (dist_a1_i1 < CalcT(0))
            return -dist_a1_i1;
        else if (dist_a1_i1 > dist_a1_a2)
            return dist_a1_i1 - dist_a1_a2;
        else
            return CalcT(0);
    }

    template <typename CalcT>
    static inline bool is_potentially_crossing(CalcT const& dist_a1_a2, CalcT const& dist_a1_i1, // in
                                               bool& is_on_a, bool& is_near_a1, bool& is_near_a2) // out
    {
        is_on_a = segment_ratio<CalcT>(dist_a1_i1, dist_a1_a2).on_segment();
        is_near_a1 = is_near(dist_a1_i1);
        is_near_a2 = is_near(dist_a1_a2 - dist_a1_i1);
        return is_on_a || is_near_a1 || is_near_a2;
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

    template <typename Point1, typename Point2>
    static inline bool equals_point_point(Point1 const& point1, Point2 const& point2)
    {
        return detail::equals::equals_point_point(point1, point2,
                                                  point_in_point_strategy_type());
    }
};

struct spherical_segments_calc_policy
{
    template <typename Point, typename Point3d>
    static Point from_cart3d(Point3d const& point_3d)
    {
        return formula::cart3d_to_sph<Point>(point_3d);
    }

    template <typename Point3d, typename Point>
    static Point3d to_cart3d(Point const& point)
    {
        return formula::sph_to_cart3d<Point3d>(point);
    }

    template <typename Point3d>
    struct plane
    {
        typedef typename coordinate_type<Point3d>::type coord_t;

        // not normalized
        plane(Point3d const& p1, Point3d const& p2)
            : normal(cross_product(p1, p2))
        {}

        int side_value(Point3d const& pt) const
        {
            return formula::sph_side_value(normal, pt);
        }

        static coord_t cos_angle_between(Point3d const& p1, Point3d const& p2)
        {
            return dot_product(p1, p2);
        }

        coord_t cos_angle_between(Point3d const& p1, Point3d const& p2, bool & is_forward) const
        {
            coord_t const c0 = 0;
            is_forward = dot_product(normal, cross_product(p1, p2)) >= c0;
            return dot_product(p1, p2);
        }

        Point3d normal;
    };

    template <typename Point3d>
    static plane<Point3d> get_plane(Point3d const& p1, Point3d const& p2)
    {
        return plane<Point3d>(p1, p2);
    }

    template <typename Point3d>
    static bool intersection_points(plane<Point3d> const& plane1,
                                    plane<Point3d> const& plane2,
                                    Point3d & ip1, Point3d & ip2)
    {
        typedef typename coordinate_type<Point3d>::type coord_t;

        ip1 = cross_product(plane1.normal, plane2.normal);
        // NOTE: the length should be greater than 0 at this point
        //       if the normals were not normalized and their dot product
        //       not checked before this function is called the length
        //       should be checked here (math::equals(len, c0))
        coord_t const len = math::sqrt(dot_product(ip1, ip1));
        divide_value(ip1, len); // normalize i1

        ip2 = ip1;
        multiply_value(ip2, coord_t(-1));

        return true;
    }    
};


template
<
    typename CalculationType = void
>
struct spherical_segments
    : ecef_segments
        <
            spherical_segments_calc_policy,
            CalculationType
        >
{};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

/*template <typename CalculationType>
struct default_strategy<spherical_polar_tag, CalculationType>
{
    typedef spherical_segments<CalculationType> type;
};*/

template <typename CalculationType>
struct default_strategy<spherical_equatorial_tag, CalculationType>
{
    typedef spherical_segments<CalculationType> type;
};

template <typename CalculationType>
struct default_strategy<geographic_tag, CalculationType>
{
    // NOTE: Spherical strategy returns the same result as the geographic one
    // representing segments as great elliptic arcs. If the elliptic arcs are
    // not great elliptic arcs (the origin not in the center of the coordinate
    // system) then there may be problems with consistency of the side and
    // intersection strategies.
    typedef spherical_segments<CalculationType> type;
};

} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::intersection


namespace strategy
{

namespace within { namespace services
{

template <typename Geometry1, typename Geometry2, typename AnyTag1, typename AnyTag2>
struct default_strategy<Geometry1, Geometry2, AnyTag1, AnyTag2, linear_tag, linear_tag, spherical_tag, spherical_tag>
{
    typedef strategy::intersection::spherical_segments<> type;
};

template <typename Geometry1, typename Geometry2, typename AnyTag1, typename AnyTag2>
struct default_strategy<Geometry1, Geometry2, AnyTag1, AnyTag2, linear_tag, polygonal_tag, spherical_tag, spherical_tag>
{
    typedef strategy::intersection::spherical_segments<> type;
};

template <typename Geometry1, typename Geometry2, typename AnyTag1, typename AnyTag2>
struct default_strategy<Geometry1, Geometry2, AnyTag1, AnyTag2, polygonal_tag, linear_tag, spherical_tag, spherical_tag>
{
    typedef strategy::intersection::spherical_segments<> type;
};

template <typename Geometry1, typename Geometry2, typename AnyTag1, typename AnyTag2>
struct default_strategy<Geometry1, Geometry2, AnyTag1, AnyTag2, polygonal_tag, polygonal_tag, spherical_tag, spherical_tag>
{
    typedef strategy::intersection::spherical_segments<> type;
};

}} // within::services

namespace covered_by { namespace services
{

template <typename Geometry1, typename Geometry2, typename AnyTag1, typename AnyTag2>
struct default_strategy<Geometry1, Geometry2, AnyTag1, AnyTag2, linear_tag, linear_tag, spherical_tag, spherical_tag>
{
    typedef strategy::intersection::spherical_segments<> type;
};

template <typename Geometry1, typename Geometry2, typename AnyTag1, typename AnyTag2>
struct default_strategy<Geometry1, Geometry2, AnyTag1, AnyTag2, linear_tag, polygonal_tag, spherical_tag, spherical_tag>
{
    typedef strategy::intersection::spherical_segments<> type;
};

template <typename Geometry1, typename Geometry2, typename AnyTag1, typename AnyTag2>
struct default_strategy<Geometry1, Geometry2, AnyTag1, AnyTag2, polygonal_tag, linear_tag, spherical_tag, spherical_tag>
{
    typedef strategy::intersection::spherical_segments<> type;
};

template <typename Geometry1, typename Geometry2, typename AnyTag1, typename AnyTag2>
struct default_strategy<Geometry1, Geometry2, AnyTag1, AnyTag2, polygonal_tag, polygonal_tag, spherical_tag, spherical_tag>
{
    typedef strategy::intersection::spherical_segments<> type;
};

}} // within::services

} // strategy


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_INTERSECTION_HPP

/* intersection.hpp
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
*/