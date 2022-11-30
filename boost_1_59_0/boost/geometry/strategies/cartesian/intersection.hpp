// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013-2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021, Oracle and/or its affiliates.

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
#include <boost/geometry/geometries/segment.hpp>

#include <boost/geometry/arithmetic/determinant.hpp>
#include <boost/geometry/algorithms/detail/assign_values.hpp>
#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/recalculate.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/promote_integral.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

#include <boost/geometry/strategy/cartesian/area.hpp>
#include <boost/geometry/strategy/cartesian/envelope.hpp>
#include <boost/geometry/strategy/cartesian/expand_box.hpp>
#include <boost/geometry/strategy/cartesian/expand_segment.hpp>

#include <boost/geometry/strategies/cartesian/disjoint_box_box.hpp>
#include <boost/geometry/strategies/cartesian/disjoint_segment_box.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras.hpp>
#include <boost/geometry/strategies/cartesian/point_in_point.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_winding.hpp>
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

namespace detail_usage
{

// When calculating the intersection, the information of "a" or "b" can be used.
// Theoretically this gives equal results, but due to floating point precision
// there might be tiny differences. These are edge cases.
// This structure is to determine if "a" or "b" should be used.
// Prefer the segment closer to the endpoint.
// If both are about equally close, then prefer the longer segment
// To avoid hard thresholds, behavior is made fluent.
// Calculate comparable length indications,
// the longer the segment (relatively), the lower the value
// such that the shorter lengths are evaluated higher and will
// be preferred.
template <bool IsArithmetic>
struct use_a
{
  template <typename Ct, typename Ev>
  static bool apply(Ct const& cla, Ct const& clb, Ev const& eva, Ev const& evb)
  {
      auto const clm = (std::max)(cla, clb);
      if (clm <= 0)
      {
          return true;
      }

      // Relative comparible length
      auto const rcla = Ct(1.0) - cla / clm;
      auto const rclb = Ct(1.0) - clb / clm;

      // Multipliers for edgevalue (ev) and relative comparible length (rcl)
      // They determine the balance between edge value (should be larger)
      // and segment length. In 99.9xx% of the cases there is no difference
      // at all (if either a or b is used). Therefore the values of the
      // constants are not sensitive for the majority of the situations.
      // One known case is #mysql_23023665_6 (difference) which needs mev >= 2
      Ev const mev = 5;
      Ev const mrcl = 1;

      return mev * eva + mrcl * rcla > mev * evb + mrcl * rclb;
  }
};

// Specialization for non arithmetic types. They will always use "a"
template <>
struct use_a<false>
{
    template <typename Ct, typename Ev>
    static bool apply(Ct const& , Ct const& , Ev const& , Ev const& )
    {
        return true;
    }
};

}

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
        void assign(Point& point, Segment const& segment,
                    CoordinateType const& dx, CoordinateType const& dy,
                    SegmentRatio const& ratio) const
        {
            // Calculate the intersection point based on segment_ratio
            // The division, postponed until here, is done now. In case of integer this
            // results in an integer which rounds to the nearest integer.
            BOOST_GEOMETRY_ASSERT(ratio.denominator() != typename SegmentRatio::int_type(0));

            typedef typename promote_integral<CoordinateType>::type calc_type;

            calc_type const numerator
                = boost::numeric_cast<calc_type>(ratio.numerator());
            calc_type const denominator
                = boost::numeric_cast<calc_type>(ratio.denominator());
            calc_type const dx_calc = boost::numeric_cast<calc_type>(dx);
            calc_type const dy_calc = boost::numeric_cast<calc_type>(dy);

            set<0>(point, get<0, 0>(segment)
                   + boost::numeric_cast<CoordinateType>(
                         math::divide<calc_type>(numerator * dx_calc, denominator)));
            set<1>(point, get<0, 1>(segment)
                   + boost::numeric_cast<CoordinateType>(
                         math::divide<calc_type>(numerator * dy_calc, denominator)));
        }

        template <int Index, int Dim, typename Point, typename Segment>
        static bool exceeds_side_in_dimension(Point& p, Segment const& s)
        {
            // Situation a (positive)
            //     0>-------------->1     segment
            // *                          point left of segment<I> in D x or y
            // Situation b (negative)
            //     1<--------------<0     segment
            // *                          point right of segment<I>
            // Situation c (degenerate), return false (check other dimension)
            auto const& c = get<Dim>(p);
            auto const& c0 = get<Index, Dim>(s);
            auto const& c1 = get<1 - Index, Dim>(s);
            return c0 < c1 ? math::smaller(c, c0)
                 : c0 > c1 ? math::larger(c, c0)
                 : false;
        }

        template <int Index, typename Point, typename Segment>
        static bool exceeds_side_of_segment(Point& p, Segment const& s)
        {
            return exceeds_side_in_dimension<Index, 0>(p, s)
                || exceeds_side_in_dimension<Index, 1>(p, s);
        }

        template <typename Point, typename Segment>
        static void assign_if_exceeds(Point& point, Segment const& s)
        {
            if (exceeds_side_of_segment<0>(point, s))
            {
                detail::assign_point_from_index<0>(s, point);
            }
            else if (exceeds_side_of_segment<1>(point, s))
            {
                detail::assign_point_from_index<1>(s, point);
            }
        }

    public :
        template <typename Point, typename Segment1, typename Segment2>
        void calculate(Point& point, Segment1 const& a, Segment2 const& b) const
        {
            bool const use_a
                = detail_usage::use_a
                     <
                         std::is_arithmetic<CoordinateType>::value
                     >::apply(comparable_length_a(), comparable_length_b(),
                         robust_ra.edge_value(), robust_rb.edge_value());

            if (use_a)
            {
                assign_a(point, a, b);
            }
            else
            {
                assign_b(point, a, b);
            }

#if defined(BOOST_GEOMETRY_USE_RESCALING)
            return;
#endif

            // Verify nearly collinear cases (the threshold is arbitrary
            // but influences performance). If the intersection is located
            // outside the segments, then it should be moved.
            if (robust_ra.possibly_collinear(1.0e-3)
                && robust_rb.possibly_collinear(1.0e-3))
            {
                // The segments are nearly collinear and because of the calculation
                // method with very small denominator, the IP appears outside the
                // segment(s). Correct it to the end point.
                // Because they are nearly collinear, it doesn't really matter to
                // to which endpoint (or it is corrected twice).
                assign_if_exceeds(point, a);
                assign_if_exceeds(point, b);
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
        ResultType& nominator, ResultType& denominator)
    {
        // Cramers rule
        nominator = geometry::detail::determinant<ResultType>(dx_b, dy_b, wx, wy);
        denominator = geometry::detail::determinant<ResultType>(dx_a, dy_a, dx_b, dy_b);
        // Ratio r = nominator/denominator
        // Collinear if denominator == 0, intersecting if 0 <= r <= 1
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
        // Pass the same ranges both as normal ranges and as modelled ranges
        return apply(range_p, range_q, policy, range_p, range_q);
    }

    // Version for non rescaled versions.
    // The "modelled" parameter might be rescaled (will be removed later)
    template
    <
        typename UniqueSubRange1,
        typename UniqueSubRange2,
        typename Policy,
        typename ModelledUniqueSubRange1,
        typename ModelledUniqueSubRange2
    >
    static inline typename Policy::return_type
        apply(UniqueSubRange1 const& range_p,
              UniqueSubRange2 const& range_q,
              Policy const& policy,
              ModelledUniqueSubRange1 const& modelled_range_p,
              ModelledUniqueSubRange2 const& modelled_range_q)
    {
        typedef typename UniqueSubRange1::point_type point1_type;
        typedef typename UniqueSubRange2::point_type point2_type;

        BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<point1_type>) );
        BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<point2_type>) );

        point1_type const& p1 = range_p.at(0);
        point1_type const& p2 = range_p.at(1);
        point2_type const& q1 = range_q.at(0);
        point2_type const& q2 = range_q.at(1);

        // Declare segments, currently necessary for the policies
        // (segment_crosses, segment_colinear, degenerate, one_degenerate, etc)
        model::referring_segment<point1_type const> const p(p1, p2);
        model::referring_segment<point2_type const> const q(q1, q2);

        typedef typename select_most_precise
            <
                typename geometry::coordinate_type<typename ModelledUniqueSubRange1::point_type>::type,
                typename geometry::coordinate_type<typename ModelledUniqueSubRange1::point_type>::type
            >::type modelled_coordinate_type;

        typedef segment_ratio<modelled_coordinate_type> ratio_type;
        segment_intersection_info
            <
                typename select_calculation_type<point1_type, point2_type, CalculationType>::type,
                ratio_type
            > sinfo;

        sinfo.dx_a = get<0>(p2) - get<0>(p1); // distance in x-dir
        sinfo.dx_b = get<0>(q2) - get<0>(q1);
        sinfo.dy_a = get<1>(p2) - get<1>(p1); // distance in y-dir
        sinfo.dy_b = get<1>(q2) - get<1>(q1);

        return unified<ratio_type>(sinfo, p, q, policy, modelled_range_p, modelled_range_q);
    }

    //! Returns true if two segments do not overlap.
    //! If not, then no further calculations need to be done.
    template
    <
        std::size_t Dimension,
        typename PointP,
        typename PointQ
    >
    static inline bool disjoint_by_range(PointP const& p1, PointP const& p2,
                                         PointQ const& q1, PointQ const& q2)
    {
        auto minp = get<Dimension>(p1);
        auto maxp = get<Dimension>(p2);
        auto minq = get<Dimension>(q1);
        auto maxq = get<Dimension>(q2);
        if (minp > maxp)
        {
            std::swap(minp, maxp);
        }
        if (minq > maxq)
        {
            std::swap(minq, maxq);
        }

        // In this case, max(p) < min(q)
        //     P         Q
        // <-------> <------->
        // (and the space in between is not extremely small)
        return math::smaller(maxp, minq) || math::smaller(maxq, minp);
    }

    // Implementation for either rescaled or non rescaled versions.
    template
    <
        typename RatioType,
        typename SegmentInfo,
        typename Segment1,
        typename Segment2,
        typename Policy,
        typename UniqueSubRange1,
        typename UniqueSubRange2
    >
    static inline typename Policy::return_type
        unified(SegmentInfo& sinfo,
                Segment1 const& p, Segment2 const& q, Policy const&,
                UniqueSubRange1 const& range_p,
                UniqueSubRange2 const& range_q)
    {
        typedef typename UniqueSubRange1::point_type point1_type;
        typedef typename UniqueSubRange2::point_type point2_type;
        typedef typename select_most_precise
            <
                typename geometry::coordinate_type<point1_type>::type,
                typename geometry::coordinate_type<point2_type>::type
            >::type coordinate_type;

        point1_type const& p1 = range_p.at(0);
        point1_type const& p2 = range_p.at(1);
        point2_type const& q1 = range_q.at(0);
        point2_type const& q2 = range_q.at(1);

        bool const p_is_point = equals_point_point(p1, p2);
        bool const q_is_point = equals_point_point(q1, q2);

        if (p_is_point && q_is_point)
        {
            return equals_point_point(p1, q2)
                ? Policy::degenerate(p, true)
                : Policy::disjoint()
                ;
        }

        if (disjoint_by_range<0>(p1, p2, q1, q2)
         || disjoint_by_range<1>(p1, p2, q1, q2))
        {
            return Policy::disjoint();
        }

        using side_strategy_type
            = typename side::services::default_strategy
                <cartesian_tag, CalculationType>::type;
        side_info sides;
        sides.set<0>(side_strategy_type::apply(q1, q2, p1),
                     side_strategy_type::apply(q1, q2, p2));

        if (sides.same<0>())
        {
            // Both points are at same side of other segment, we can leave
            return Policy::disjoint();
        }

        sides.set<1>(side_strategy_type::apply(p1, p2, q1),
                     side_strategy_type::apply(p1, p2, q2));
        
        if (sides.same<1>())
        {
            // Both points are at same side of other segment, we can leave
            return Policy::disjoint();
        }

        bool collinear = sides.collinear();

        // Calculate the differences again
        // (for rescaled version, this is different from dx_p etc)
        coordinate_type const dx_p = get<0>(p2) - get<0>(p1);
        coordinate_type const dx_q = get<0>(q2) - get<0>(q1);
        coordinate_type const dy_p = get<1>(p2) - get<1>(p1);
        coordinate_type const dy_q = get<1>(q2) - get<1>(q1);

        // r: ratio 0-1 where intersection divides A/B
        // (only calculated for non-collinear segments)
        if (! collinear)
        {
            coordinate_type denominator_a, nominator_a;
            coordinate_type denominator_b, nominator_b;

            cramers_rule(dx_p, dy_p, dx_q, dy_q,
                get<0>(p1) - get<0>(q1),
                get<1>(p1) - get<1>(q1),
                nominator_a, denominator_a);

            cramers_rule(dx_q, dy_q, dx_p, dy_p,
                get<0>(q1) - get<0>(p1),
                get<1>(q1) - get<1>(p1),
                nominator_b, denominator_b);

            math::detail::equals_factor_policy<coordinate_type>
                policy(dx_p, dy_p, dx_q, dy_q);

            coordinate_type const zero = 0;
            if (math::detail::equals_by_policy(denominator_a, zero, policy)
             || math::detail::equals_by_policy(denominator_b, zero, policy))
            {
                // If this is the case, no rescaling is done for FP precision.
                // We set it to collinear, but it indicates a robustness issue.
                sides.set<0>(0, 0);
                sides.set<1>(0, 0);
                collinear = true;
            }
            else
            {
                sinfo.robust_ra.assign(nominator_a, denominator_a);
                sinfo.robust_rb.assign(nominator_b, denominator_b);
            }
        }

        if (collinear)
        {
            std::pair<bool, bool> const collinear_use_first
                    = is_x_more_significant(geometry::math::abs(dx_p),
                                            geometry::math::abs(dy_p),
                                            geometry::math::abs(dx_q),
                                            geometry::math::abs(dy_q),
                                            p_is_point, q_is_point);

            if (collinear_use_first.second)
            {
                // Degenerate cases: segments of single point, lying on other segment, are not disjoint
                // This situation is collinear too

                if (collinear_use_first.first)
                {
                    return relate_collinear<0, Policy, RatioType>(p, q,
                            p1, p2, q1, q2,
                            p_is_point, q_is_point);
                }
                else
                {
                    // Y direction contains larger segments (maybe dx is zero)
                    return relate_collinear<1, Policy, RatioType>(p, q,
                            p1, p2, q1, q2,
                            p_is_point, q_is_point);
                }
            }
        }

        return Policy::segments_crosses(sides, sinfo, p, q);
    }

private:
    // first is true if x is more significant
    // second is true if the more significant difference is not 0
    template <typename CoordinateType>
    static inline std::pair<bool, bool>
        is_x_more_significant(CoordinateType const& abs_dx_a,
                              CoordinateType const& abs_dy_a,
                              CoordinateType const& abs_dx_b,
                              CoordinateType const& abs_dy_b,
                              bool const a_is_point,
                              bool const b_is_point)
    {
        //BOOST_GEOMETRY_ASSERT_MSG(!(a_is_point && b_is_point), "both segments shouldn't be degenerated");

        // for degenerated segments the second is always true because this function
        // shouldn't be called if both segments were degenerated

        if (a_is_point)
        {
            return std::make_pair(abs_dx_b >= abs_dy_b, true);
        }
        else if (b_is_point)
        {
            return std::make_pair(abs_dx_a >= abs_dy_a, true);
        }
        else
        {
            CoordinateType const min_dx = (std::min)(abs_dx_a, abs_dx_b);
            CoordinateType const min_dy = (std::min)(abs_dy_a, abs_dy_b);
            return min_dx == min_dy ?
                    std::make_pair(true, min_dx > CoordinateType(0)) :
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
        typename Type1,
        typename Type2
    >
    static inline typename Policy::return_type
        relate_collinear(Segment1 const& a, Segment2 const& b,
                         Type1 oa_1, Type1 oa_2,
                         Type2 ob_1, Type2 ob_2)
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
        Type1 const length_a = oa_2 - oa_1; // no abs, see above
        Type2 const length_b = ob_2 - ob_1;

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
        typename Type1,
        typename Type2
    >
    static inline typename Policy::return_type
        relate_one_degenerate(DegenerateSegment const& degenerate_segment,
                              Type1 d, Type2 s1, Type2 s2,
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

    template <typename Point1, typename Point2>
    static inline bool equals_point_point(Point1 const& point1, Point2 const& point2)
    {
        return strategy::within::cartesian_point_point::apply(point1, point2);
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