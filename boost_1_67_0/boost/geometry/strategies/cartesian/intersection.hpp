// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013-2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014, 2016, 2017, 2018, 2019.
// Modifications copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_INTERSECTION_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_INTERSECTION_HPP

#include <algorithm>

#include <boost/geometry/core/exception.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/geometries/concepts/segment_concept.hpp>

#include <boost/geometry/arithmetic/determinant.hpp>
#include <boost/geometry/algorithms/detail/assign_values.hpp>
#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/recalculate.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/promote_integral.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

#include <boost/geometry/strategies/cartesian/area.hpp>
#include <boost/geometry/strategies/cartesian/disjoint_box_box.hpp>
#include <boost/geometry/strategies/cartesian/disjoint_segment_box.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras.hpp>
#include <boost/geometry/strategies/cartesian/envelope.hpp>
#include <boost/geometry/strategies/cartesian/expand_box.hpp>
#include <boost/geometry/strategies/cartesian/expand_segment.hpp>
#include <boost/geometry/strategies/cartesian/point_in_point.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/cartesian/side_by_triangle.hpp>
#include <boost/geometry/strategies/covered_by.hpp>
#include <boost/geometry/strategies/intersection.hpp>
#include <boost/geometry/strategies/intersection_result.hpp>
#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/strategies/side_info.hpp>
#include <boost/geometry/strategies/within.hpp>

#include <boost/geometry/policies/robustness/rescale_policy_tags.hpp>
#include <boost/geometry/policies/robustness/robust_point_type.hpp>

#if defined(BOOST_GEOMETRY_DEBUG_ROBUSTNESS)
#  include <boost/geometry/io/wkt/write.hpp>
#endif


namespace boost { namespace geometry
{


namespace strategy { namespace intersection
{


/*!
    \see http://mathworld.wolfram.com/Line-LineIntersection.html
 */
template
<
    typename CalculationType = void
>
struct cartesian_segments
{
    typedef cartesian_tag cs_tag;

    typedef side::side_by_triangle<CalculationType> side_strategy_type;

    static inline side_strategy_type get_side_strategy()
    {
        return side_strategy_type();
    }

    template <typename Geometry1, typename Geometry2>
    struct point_in_geometry_strategy
    {
        typedef strategy::within::cartesian_winding
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
        typedef area::cartesian
            <
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
        typedef distance::pythagoras
            <
                CalculationType
            > type;
    };

    template <typename Geometry>
    static inline typename distance_strategy<Geometry>::type get_distance_strategy()
    {
        typedef typename distance_strategy<Geometry>::type strategy_type;
        return strategy_type();
    }

    typedef envelope::cartesian<CalculationType> envelope_strategy_type;

    static inline envelope_strategy_type get_envelope_strategy()
    {
        return envelope_strategy_type();
    }

    typedef expand::cartesian_segment expand_strategy_type;

    static inline expand_strategy_type get_expand_strategy()
    {
        return expand_strategy_type();
    }

    typedef within::cartesian_point_point point_in_point_strategy_type;

    static inline point_in_point_strategy_type get_point_in_point_strategy()
    {
        return point_in_point_strategy_type();
    }

    typedef within::cartesian_point_point equals_point_point_strategy_type;

    static inline equals_point_point_strategy_type get_equals_point_point_strategy()
    {
        return equals_point_point_strategy_type();
    }

    typedef disjoint::cartesian_box_box disjoint_box_box_strategy_type;

    static inline disjoint_box_box_strategy_type get_disjoint_box_box_strategy()
    {
        return disjoint_box_box_strategy_type();
    }

    typedef disjoint::segment_box disjoint_segment_box_strategy_type;

    static inline disjoint_segment_box_strategy_type get_disjoint_segment_box_strategy()
    {
        return disjoint_segment_box_strategy_type();
    }

    typedef covered_by::cartesian_point_box disjoint_point_box_strategy_type;
    typedef covered_by::cartesian_point_box covered_by_point_box_strategy_type;
    typedef within::cartesian_point_box within_point_box_strategy_type;
    typedef envelope::cartesian_box envelope_box_strategy_type;
    typedef expand::cartesian_box expand_box_strategy_type;

    template <typename CoordinateType, typename SegmentRatio>
    struct segment_intersection_info
    {
    private :
        typedef typename select_most_precise
            <
                CoordinateType, double
            >::type promoted_type;

        promoted_type comparable_length_a() const
        {
            return dx_a * dx_a + dy_a * dy_a;
        }

        promoted_type comparable_length_b() const
        {
            return dx_b * dx_b + dy_b * dy_b;
        }

        template <typename Point, typename Segment1, typename Segment2>
        void assign_a(Point& point, Segment1 const& a, Segment2 const& ) const
        {
            assign(point, a, dx_a, dy_a, robust_ra);
        }
        template <typename Point, typename Segment1, typename Segment2>
        void assign_b(Point& point, Segment1 const& , Segment2 const& b) const
        {
            assign(point, b, dx_b, dy_b, robust_rb);
        }

        template <typename Point, typename Segment>
        void assign(Point& point, Segment const& segment, CoordinateType const& dx, CoordinateType const& dy, SegmentRatio const& ratio) const
        {
            // Calculate the intersection point based on segment_ratio
            // Up to now, division was postponed. Here we divide using numerator/
            // denominator. In case of integer this results in an integer
            // division.
            BOOST_GEOMETRY_ASSERT(ratio.denominator() != 0);

            typedef typename promote_integral<CoordinateType>::type calc_type;

            calc_type const numerator
                = boost::numeric_cast<calc_type>(ratio.numerator());
            calc_type const denominator
                = boost::numeric_cast<calc_type>(ratio.denominator());
            calc_type const dx_calc = boost::numeric_cast<calc_type>(dx);
            calc_type const dy_calc = boost::numeric_cast<calc_type>(dy);

            set<0>(point, get<0, 0>(segment)
                   + boost::numeric_cast<CoordinateType>(numerator * dx_calc
                                                         / denominator));
            set<1>(point, get<0, 1>(segment)
                   + boost::numeric_cast<CoordinateType>(numerator * dy_calc
                                                         / denominator));
        }

    public :
        template <typename Point, typename Segment1, typename Segment2>
        void calculate(Point& point, Segment1 const& a, Segment2 const& b) const
        {
            bool use_a = true;

            // Prefer one segment if one is on or near an endpoint
            bool const a_near_end = robust_ra.near_end();
            bool const b_near_end = robust_rb.near_end();
            if (a_near_end && ! b_near_end)
            {
                use_a = true;
            }
            else if (b_near_end && ! a_near_end)
            {
                use_a = false;
            }
            else
            {
                // Prefer shorter segment
                promoted_type const len_a = comparable_length_a();
                promoted_type const len_b = comparable_length_b();
                if (len_b < len_a)
                {
                    use_a = false;
                }
                // else use_a is true but was already assigned like that
            }

            if (use_a)
            {
                assign_a(point, a, b);
            }
            else
            {
                assign_b(point, a, b);
            }
        }

        CoordinateType dx_a, dy_a;
        CoordinateType dx_b, dy_b;
        SegmentRatio robust_ra;
        SegmentRatio robust_rb;
    };

    template <typename D, typename W, typename ResultType>
    static inline void cramers_rule(D const& dx_a, D const& dy_a,
        D const& dx_b, D const& dy_b, W const& wx, W const& wy,
        // out:
        ResultType& d, ResultType& da)
    {
        // Cramers rule
        d = geometry::detail::determinant<ResultType>(dx_a, dy_a, dx_b, dy_b);
        da = geometry::detail::determinant<ResultType>(dx_b, dy_b, wx, wy);
        // Ratio is da/d , collinear if d == 0, intersecting if 0 <= r <= 1
        // IntersectionPoint = (x1 + r * dx_a, y1 + r * dy_a)
    }

    // Version for non-rescaled policies
    template
    <
        typename UniqueSubRange1,
        typename UniqueSubRange2,
        typename Policy
    >
    static inline typename Policy::return_type
        apply(UniqueSubRange1 const& range_p,
              UniqueSubRange2 const& range_q,
              Policy const& policy)
    {
        // Pass the same ranges both as normal ranges and as robust ranges
        return apply(range_p, range_q, policy, range_p, range_q);
    }

    // Main entry-routine, calculating intersections of segments p / q
    template
    <
        typename UniqueSubRange1,
        typename UniqueSubRange2,
        typename Policy,
        typename RobustUniqueSubRange1,
        typename RobustUniqueSubRange2
    >
    static inline typename Policy::return_type
        apply(UniqueSubRange1 const& range_p,
              UniqueSubRange2 const& range_q,
              Policy const&,
              RobustUniqueSubRange1 const& robust_range_p,
              RobustUniqueSubRange2 const& robust_range_q)
    {
        typedef typename UniqueSubRange1::point_type point1_type;
        typedef typename UniqueSubRange2::point_type point2_type;

        BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<point1_type>) );
        BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<point2_type>) );

        // Get robust points (to be omitted later)
        typedef typename RobustUniqueSubRange1::point_type robust_point1_type;
        typedef typename RobustUniqueSubRange2::point_type robust_point2_type;

        point1_type const& p1 = range_p.at(0);
        point1_type const& p2 = range_p.at(1);
        point2_type const& q1 = range_q.at(0);
        point2_type const& q2 = range_q.at(1);

        robust_point1_type const& robust_a1 = robust_range_p.at(0);
        robust_point1_type const& robust_a2 = robust_range_p.at(1);
        robust_point2_type const& robust_b1 = robust_range_q.at(0);
        robust_point2_type const& robust_b2 = robust_range_q.at(1);

        using geometry::detail::equals::equals_point_point;
        bool const a_is_point = equals_point_point(robust_a1, robust_a2, point_in_point_strategy_type());
        bool const b_is_point = equals_point_point(robust_b1, robust_b2, point_in_point_strategy_type());

        if(a_is_point && b_is_point)
        {
            // Take either a or b
            model::referring_segment<point1_type const> const d(p1, p2);

            return equals_point_point(robust_a1, robust_b2, point_in_point_strategy_type())
                ? Policy::degenerate(d, true)
                : Policy::disjoint()
                ;
        }

        side_info sides;
        sides.set<0>(side_strategy_type::apply(robust_b1, robust_b2, robust_a1),
                     side_strategy_type::apply(robust_b1, robust_b2, robust_a2));

        if (sides.same<0>())
        {
            // Both points are at same side of other segment, we can leave
            return Policy::disjoint();
        }

        sides.set<1>(side_strategy_type::apply(robust_a1, robust_a2, robust_b1),
                     side_strategy_type::apply(robust_a1, robust_a2, robust_b2));
        
        if (sides.same<1>())
        {
            // Both points are at same side of other segment, we can leave
            return Policy::disjoint();
        }

        bool collinear = sides.collinear();

        typedef typename select_most_precise
            <
                typename geometry::coordinate_type<robust_point1_type>::type,
                typename geometry::coordinate_type<robust_point2_type>::type
            >::type robust_coordinate_type;

        typedef segment_ratio<robust_coordinate_type> ratio_type;

        segment_intersection_info
            <
                typename select_calculation_type<point1_type, point2_type, CalculationType>::type,
                ratio_type
            > sinfo;

        sinfo.dx_a = get<0>(p2) - get<0>(p1); // distance in x-dir
        sinfo.dx_b = get<0>(q2) - get<0>(q1);
        sinfo.dy_a = get<1>(p2) - get<1>(p1); // distance in y-dir
        sinfo.dy_b = get<1>(q2) - get<1>(q1);

        robust_coordinate_type const robust_dx_a = get<0>(robust_a2) - get<0>(robust_a1);
        robust_coordinate_type const robust_dx_b = get<0>(robust_b2) - get<0>(robust_b1);
        robust_coordinate_type const robust_dy_a = get<1>(robust_a2) - get<1>(robust_a1);
        robust_coordinate_type const robust_dy_b = get<1>(robust_b2) - get<1>(robust_b1);

        // r: ratio 0-1 where intersection divides A/B
        // (only calculated for non-collinear segments)
        if (! collinear)
        {
            robust_coordinate_type robust_da0, robust_da;
            robust_coordinate_type robust_db0, robust_db;

            cramers_rule(robust_dx_a, robust_dy_a, robust_dx_b, robust_dy_b,
                get<0>(robust_a1) - get<0>(robust_b1),
                get<1>(robust_a1) - get<1>(robust_b1),
                robust_da0, robust_da);

            cramers_rule(robust_dx_b, robust_dy_b, robust_dx_a, robust_dy_a,
                get<0>(robust_b1) - get<0>(robust_a1),
                get<1>(robust_b1) - get<1>(robust_a1),
                robust_db0, robust_db);

            math::detail::equals_factor_policy<robust_coordinate_type>
                policy(robust_dx_a, robust_dy_a, robust_dx_b, robust_dy_b);
            robust_coordinate_type const zero = 0;
            if (math::detail::equals_by_policy(robust_da0, zero, policy)
             || math::detail::equals_by_policy(robust_db0, zero, policy))
            {
                // If this is the case, no rescaling is done for FP precision.
                // We set it to collinear, but it indicates a robustness issue.
                sides.set<0>(0,0);
                sides.set<1>(0,0);
                collinear = true;
            }
            else
            {
                sinfo.robust_ra.assign(robust_da, robust_da0);
                sinfo.robust_rb.assign(robust_db, robust_db0);
            }
        }

        // Declare segments, currently necessary for the policies
        // (segment_crosses, segment_colinear, degenerate, one_degenerate, etc)
        model::referring_segment<point1_type const> const p(p1, p2);
        model::referring_segment<point2_type const> const q(q1, q2);

        if (collinear)
        {
            std::pair<bool, bool> const collinear_use_first
                    = is_x_more_significant(geometry::math::abs(robust_dx_a),
                                            geometry::math::abs(robust_dy_a),
                                            geometry::math::abs(robust_dx_b),
                                            geometry::math::abs(robust_dy_b),
                                            a_is_point, b_is_point);

            if (collinear_use_first.second)
            {
                // Degenerate cases: segments of single point, lying on other segment, are not disjoint
                // This situation is collinear too

                if (collinear_use_first.first)
                {
                    return relate_collinear<0, Policy, ratio_type>(p, q,
                            robust_a1, robust_a2, robust_b1, robust_b2,
                            a_is_point, b_is_point);
                }
                else
                {
                    // Y direction contains larger segments (maybe dx is zero)
                    return relate_collinear<1, Policy, ratio_type>(p, q,
                            robust_a1, robust_a2, robust_b1, robust_b2,
                            a_is_point, b_is_point);
                }
            }
        }

        return Policy::segments_crosses(sides, sinfo, p, q);
    }

private:
    // first is true if x is more significant
    // second is true if the more significant difference is not 0
    template <typename RobustCoordinateType>
    static inline std::pair<bool, bool>
        is_x_more_significant(RobustCoordinateType const& abs_robust_dx_a,
                              RobustCoordinateType const& abs_robust_dy_a,
                              RobustCoordinateType const& abs_robust_dx_b,
                              RobustCoordinateType const& abs_robust_dy_b,
                              bool const a_is_point,
                              bool const b_is_point)
    {
        //BOOST_GEOMETRY_ASSERT_MSG(!(a_is_point && b_is_point), "both segments shouldn't be degenerated");

        // for degenerated segments the second is always true because this function
        // shouldn't be called if both segments were degenerated

        if (a_is_point)
        {
            return std::make_pair(abs_robust_dx_b >= abs_robust_dy_b, true);
        }
        else if (b_is_point)
        {
            return std::make_pair(abs_robust_dx_a >= abs_robust_dy_a, true);
        }
        else
        {
            RobustCoordinateType const min_dx = (std::min)(abs_robust_dx_a, abs_robust_dx_b);
            RobustCoordinateType const min_dy = (std::min)(abs_robust_dy_a, abs_robust_dy_b);
            return min_dx == min_dy ?
                    std::make_pair(true, min_dx > RobustCoordinateType(0)) :
                    std::make_pair(min_dx > min_dy, true);
        }
    }

    template
    <
        std::size_t Dimension,
        typename Policy,
        typename RatioType,
        typename Segment1,
        typename Segment2,
        typename RobustPoint1,
        typename RobustPoint2
    >
    static inline typename Policy::return_type
        relate_collinear(Segment1 const& a,
                         Segment2 const& b,
                         RobustPoint1 const& robust_a1, RobustPoint1 const& robust_a2,
                         RobustPoint2 const& robust_b1, RobustPoint2 const& robust_b2,
                         bool a_is_point, bool b_is_point)
    {
        if (a_is_point)
        {
            return relate_one_degenerate<Policy, RatioType>(a,
                get<Dimension>(robust_a1),
                get<Dimension>(robust_b1), get<Dimension>(robust_b2),
                true);
        }
        if (b_is_point)
        {
            return relate_one_degenerate<Policy, RatioType>(b,
                get<Dimension>(robust_b1),
                get<Dimension>(robust_a1), get<Dimension>(robust_a2),
                false);
        }
        return relate_collinear<Policy, RatioType>(a, b,
                                get<Dimension>(robust_a1),
                                get<Dimension>(robust_a2),
                                get<Dimension>(robust_b1),
                                get<Dimension>(robust_b2));
    }

    /// Relate segments known collinear
    template
    <
        typename Policy,
        typename RatioType,
        typename Segment1,
        typename Segment2,
        typename RobustType1,
        typename RobustType2
    >
    static inline typename Policy::return_type
        relate_collinear(Segment1 const& a, Segment2 const& b,
                         RobustType1 oa_1, RobustType1 oa_2,
                         RobustType2 ob_1, RobustType2 ob_2)
    {
        // Calculate the ratios where a starts in b, b starts in a
        //         a1--------->a2         (2..7)
        //                b1----->b2      (5..8)
        // length_a: 7-2=5
        // length_b: 8-5=3
        // b1 is located w.r.t. a at ratio: (5-2)/5=3/5 (on a)
        // b2 is located w.r.t. a at ratio: (8-2)/5=6/5 (right of a)
        // a1 is located w.r.t. b at ratio: (2-5)/3=-3/3 (left of b)
        // a2 is located w.r.t. b at ratio: (7-5)/3=2/3 (on b)
        // A arrives (a2 on b), B departs (b1 on a)

        // If both are reversed:
        //         a2<---------a1         (7..2)
        //                b2<-----b1      (8..5)
        // length_a: 2-7=-5
        // length_b: 5-8=-3
        // b1 is located w.r.t. a at ratio: (8-7)/-5=-1/5 (before a starts)
        // b2 is located w.r.t. a at ratio: (5-7)/-5=2/5 (on a)
        // a1 is located w.r.t. b at ratio: (7-8)/-3=1/3 (on b)
        // a2 is located w.r.t. b at ratio: (2-8)/-3=6/3 (after b ends)

        // If both one is reversed:
        //         a1--------->a2         (2..7)
        //                b2<-----b1      (8..5)
        // length_a: 7-2=+5
        // length_b: 5-8=-3
        // b1 is located w.r.t. a at ratio: (8-2)/5=6/5 (after a ends)
        // b2 is located w.r.t. a at ratio: (5-2)/5=3/5 (on a)
        // a1 is located w.r.t. b at ratio: (2-8)/-3=6/3 (after b ends)
        // a2 is located w.r.t. b at ratio: (7-8)/-3=1/3 (on b)
        RobustType1 const length_a = oa_2 - oa_1; // no abs, see above
        RobustType2 const length_b = ob_2 - ob_1;

        RatioType ra_from(oa_1 - ob_1, length_b);
        RatioType ra_to(oa_2 - ob_1, length_b);
        RatioType rb_from(ob_1 - oa_1, length_a);
        RatioType rb_to(ob_2 - oa_1, length_a);

        // use absolute measure to detect endpoints intersection
        // NOTE: it'd be possible to calculate bx_wrt_a using ax_wrt_b values
        int const a1_wrt_b = position_value(oa_1, ob_1, ob_2);
        int const a2_wrt_b = position_value(oa_2, ob_1, ob_2);
        int const b1_wrt_a = position_value(ob_1, oa_1, oa_2);
        int const b2_wrt_a = position_value(ob_2, oa_1, oa_2);
        
        // fix the ratios if necessary
        // CONSIDER: fixing ratios also in other cases, if they're inconsistent
        // e.g. if ratio == 1 or 0 (so IP at the endpoint)
        // but position value indicates that the IP is in the middle of the segment
        // because one of the segments is very long
        // In such case the ratios could be moved into the middle direction
        // by some small value (e.g. EPS+1ULP)
        if (a1_wrt_b == 1)
        {
            ra_from.assign(0, 1);
            rb_from.assign(0, 1);
        }
        else if (a1_wrt_b == 3)
        {
            ra_from.assign(1, 1);
            rb_to.assign(0, 1);
        } 

        if (a2_wrt_b == 1)
        {
            ra_to.assign(0, 1);
            rb_from.assign(1, 1);
        }
        else if (a2_wrt_b == 3)
        {
            ra_to.assign(1, 1);
            rb_to.assign(1, 1);
        }

        if ((a1_wrt_b < 1 && a2_wrt_b < 1) || (a1_wrt_b > 3 && a2_wrt_b > 3))
        //if ((ra_from.left() && ra_to.left()) || (ra_from.right() && ra_to.right()))
        {
            return Policy::disjoint();
        }

        bool const opposite = math::sign(length_a) != math::sign(length_b);

        return Policy::segments_collinear(a, b, opposite,
                                          a1_wrt_b, a2_wrt_b, b1_wrt_a, b2_wrt_a,
                                          ra_from, ra_to, rb_from, rb_to);
    }

    /// Relate segments where one is degenerate
    template
    <
        typename Policy,
        typename RatioType,
        typename DegenerateSegment,
        typename RobustType1,
        typename RobustType2
    >
    static inline typename Policy::return_type
        relate_one_degenerate(DegenerateSegment const& degenerate_segment,
                              RobustType1 d, RobustType2 s1, RobustType2 s2,
                              bool a_degenerate)
    {
        // Calculate the ratios where ds starts in s
        //         a1--------->a2         (2..6)
        //              b1/b2      (4..4)
        // Ratio: (4-2)/(6-2)
        RatioType const ratio(d - s1, s2 - s1);

        if (!ratio.on_segment())
        {
            return Policy::disjoint();
        }

        return Policy::one_degenerate(degenerate_segment, ratio, a_degenerate);
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
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename CalculationType>
struct default_strategy<cartesian_tag, CalculationType>
{
    typedef cartesian_segments<CalculationType> type;
};

} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::intersection

namespace strategy
{

namespace within { namespace services
{

template <typename Geometry1, typename Geometry2, typename AnyTag1, typename AnyTag2>
struct default_strategy<Geometry1, Geometry2, AnyTag1, AnyTag2, linear_tag, linear_tag, cartesian_tag, cartesian_tag>
{
    typedef strategy::intersection::cartesian_segments<> type;
};

template <typename Geometry1, typename Geometry2, typename AnyTag1, typename AnyTag2>
struct default_strategy<Geometry1, Geometry2, AnyTag1, AnyTag2, linear_tag, polygonal_tag, cartesian_tag, cartesian_tag>
{
    typedef strategy::intersection::cartesian_segments<> type;
};

template <typename Geometry1, typename Geometry2, typename AnyTag1, typename AnyTag2>
struct default_strategy<Geometry1, Geometry2, AnyTag1, AnyTag2, polygonal_tag, linear_tag, cartesian_tag, cartesian_tag>
{
    typedef strategy::intersection::cartesian_segments<> type;
};

template <typename Geometry1, typename Geometry2, typename AnyTag1, typename AnyTag2>
struct default_strategy<Geometry1, Geometry2, AnyTag1, AnyTag2, polygonal_tag, polygonal_tag, cartesian_tag, cartesian_tag>
{
    typedef strategy::intersection::cartesian_segments<> type;
};

}} // within::services

namespace covered_by { namespace services
{

template <typename Geometry1, typename Geometry2, typename AnyTag1, typename AnyTag2>
struct default_strategy<Geometry1, Geometry2, AnyTag1, AnyTag2, linear_tag, linear_tag, cartesian_tag, cartesian_tag>
{
    typedef strategy::intersection::cartesian_segments<> type;
};

template <typename Geometry1, typename Geometry2, typename AnyTag1, typename AnyTag2>
struct default_strategy<Geometry1, Geometry2, AnyTag1, AnyTag2, linear_tag, polygonal_tag, cartesian_tag, cartesian_tag>
{
    typedef strategy::intersection::cartesian_segments<> type;
};

template <typename Geometry1, typename Geometry2, typename AnyTag1, typename AnyTag2>
struct default_strategy<Geometry1, Geometry2, AnyTag1, AnyTag2, polygonal_tag, linear_tag, cartesian_tag, cartesian_tag>
{
    typedef strategy::intersection::cartesian_segments<> type;
};

template <typename Geometry1, typename Geometry2, typename AnyTag1, typename AnyTag2>
struct default_strategy<Geometry1, Geometry2, AnyTag1, AnyTag2, polygonal_tag, polygonal_tag, cartesian_tag, cartesian_tag>
{
    typedef strategy::intersection::cartesian_segments<> type;
};

}} // within::services

} // strategy

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_INTERSECTION_HPP

/* intersection.hpp
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
*/