// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2015, 2017, 2018, 2019.
// Modifications copyright (c) 2015-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_TURN_INFO_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_TURN_INFO_HPP


#include <boost/core/ignore_unused.hpp>
#include <boost/throw_exception.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/config.hpp>
#include <boost/geometry/core/exception.hpp>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_distance_measure.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>

#include <boost/geometry/geometries/segment.hpp>

#include <boost/geometry/policies/robustness/robust_point_type.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turn_info_helpers.hpp>

// Silence warning C4127: conditional expression is constant
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4127)
#endif


namespace boost { namespace geometry
{

#if ! defined(BOOST_GEOMETRY_OVERLAY_NO_THROW)
class turn_info_exception : public geometry::exception
{
    std::string message;
public:

    // NOTE: "char" will be replaced by enum in future version
    inline turn_info_exception(char const method)
    {
        message = "Boost.Geometry Turn exception: ";
        message += method;
    }

    virtual ~turn_info_exception() throw()
    {}

    virtual char const* what() const throw()
    {
        return message.c_str();
    }
};
#endif

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

struct base_turn_handler
{
    // Returns true if both sides are opposite
    static inline bool opposite(int side1, int side2)
    {
        // We cannot state side1 == -side2, because 0 == -0
        // So either side1*side2==-1 or side1==-side2 && side1 != 0
        return side1 * side2 == -1;
    }

    // Same side of a segment (not being 0)
    static inline bool same(int side1, int side2)
    {
        return side1 * side2 == 1;
    }

    // Both get the same operation
    template <typename TurnInfo>
    static inline void both(TurnInfo& ti, operation_type const op)
    {
        ti.operations[0].operation = op;
        ti.operations[1].operation = op;
    }

    // If condition, first union/second intersection, else vice versa
    template <typename TurnInfo>
    static inline void ui_else_iu(bool condition, TurnInfo& ti)
    {
        ti.operations[0].operation = condition
                    ? operation_union : operation_intersection;
        ti.operations[1].operation = condition
                    ? operation_intersection : operation_union;
    }

    // If condition, both union, else both intersection
    template <typename TurnInfo>
    static inline void uu_else_ii(bool condition, TurnInfo& ti)
    {
        both(ti, condition ? operation_union : operation_intersection);
    }

    template <typename TurnInfo, typename IntersectionInfo>
    static inline void assign_point(TurnInfo& ti,
                method_type method,
                IntersectionInfo const& info, unsigned int index)
    {
        ti.method = method;

        BOOST_GEOMETRY_ASSERT(index < info.count);

        geometry::convert(info.intersections[index], ti.point);
        ti.operations[0].fraction = info.fractions[index].robust_ra;
        ti.operations[1].fraction = info.fractions[index].robust_rb;
    }

    template <typename IntersectionInfo>
    static inline unsigned int non_opposite_to_index(IntersectionInfo const& info)
    {
        return info.fractions[0].robust_rb < info.fractions[1].robust_rb
            ? 1 : 0;
    }

    template <typename Point1, typename Point2>
    static inline typename geometry::coordinate_type<Point1>::type
            distance_measure(Point1 const& a, Point2 const& b)
    {
        // TODO: use comparable distance for point-point instead - but that
        // causes currently cycling include problems
        typedef typename geometry::coordinate_type<Point1>::type ctype;
        ctype const dx = get<0>(a) - get<0>(b);
        ctype const dy = get<1>(a) - get<1>(b);
        return dx * dx + dy * dy;
    }

    template
    <
            std::size_t IndexP,
            std::size_t IndexQ,
            typename UniqueSubRange1,
            typename UniqueSubRange2,
            typename UmbrellaStrategy,
            typename TurnInfo
    >
    static inline void both_collinear(
            UniqueSubRange1 const& range_p,
            UniqueSubRange2 const& range_q,
            UmbrellaStrategy const&,
            std::size_t index_p, std::size_t index_q,
            TurnInfo& ti)
    {
        boost::ignore_unused(range_p, range_q);
        BOOST_GEOMETRY_ASSERT(IndexP + IndexQ == 1);
        BOOST_GEOMETRY_ASSERT(index_p > 0 && index_p <= 2);
        BOOST_GEOMETRY_ASSERT(index_q > 0 && index_q <= 2);

#if ! defined(BOOST_GEOMETRY_USE_RESCALING)
        ti.operations[IndexP].remaining_distance = distance_measure(ti.point, range_p.at(index_p));
        ti.operations[IndexQ].remaining_distance = distance_measure(ti.point, range_q.at(index_q));

        // pk/q2 is considered as collinear, but there might be
        // a tiny measurable difference. If so, use that.
        // Calculate pk // qj-qk
        typedef detail::distance_measure
            <
                typename select_coordinate_type
                <
                    typename UniqueSubRange1::point_type,
                    typename UniqueSubRange2::point_type
                    >::type
            > dm_type;

        const bool p_closer =
                ti.operations[IndexP].remaining_distance
                <  ti.operations[IndexQ].remaining_distance;
        dm_type const dm
                = p_closer
                ? get_distance_measure<typename UmbrellaStrategy::cs_tag>(range_q.at(index_q - 1),
                    range_q.at(index_q), range_p.at(index_p))
                : get_distance_measure<typename UmbrellaStrategy::cs_tag>(range_p.at(index_p - 1),
                    range_p.at(index_p), range_q.at(index_q));

        if (! dm.is_zero())
        {
            // Not truely collinear, distinguish for union/intersection
            // If p goes left (positive), take that for a union

            bool p_left = p_closer ? dm.is_positive() : dm.is_negative();

            ti.operations[IndexP].operation = p_left
                        ? operation_union : operation_intersection;
            ti.operations[IndexQ].operation = p_left
                        ? operation_intersection : operation_union;
            return;
        }
#endif

        both(ti, operation_continue);
    }

};


template
<
    typename TurnInfo
>
struct touch_interior : public base_turn_handler
{
    // Index: 0, P is the interior, Q is touching and vice versa
    template
    <
        unsigned int Index,
        typename UniqueSubRange1,
        typename UniqueSubRange2,
        typename IntersectionInfo,
        typename DirInfo,
        typename SidePolicy,
        typename UmbrellaStrategy
    >
    static inline void apply(UniqueSubRange1 const& range_p,
                UniqueSubRange2 const& range_q,
                TurnInfo& ti,
                IntersectionInfo const& intersection_info,
                DirInfo const& dir_info,
                SidePolicy const& side,
                UmbrellaStrategy const& umbrella_strategy)
    {
        assign_point(ti, method_touch_interior, intersection_info, 0);

        // Both segments of q touch segment p somewhere in its interior
        // 1) We know: if q comes from LEFT or RIGHT
        // (i.e. dir_info.sides.get<Index,0>() == 1 or -1)
        // 2) Important is: if q_k goes to LEFT, RIGHT, COLLINEAR
        //    and, if LEFT/COLL, if it is lying LEFT or RIGHT w.r.t. q_i

        BOOST_STATIC_ASSERT(Index <= 1);
        static unsigned int const index_p = Index;
        static unsigned int const index_q = 1 - Index;

        bool const has_pk = ! range_p.is_last_segment();
        bool const has_qk = ! range_q.is_last_segment();
        int const side_qi_p = dir_info.sides.template get<index_q, 0>();
        int const side_qk_p = has_qk ? side.qk_wrt_p1() : 0;

        if (side_qi_p == -side_qk_p)
        {
            // Q crosses P from left->right or from right->left (test "ML1")
            // Union: folow P (left->right) or Q (right->left)
            // Intersection: other turn
            unsigned int index = side_qk_p == -1 ? index_p : index_q;
            ti.operations[index].operation = operation_union;
            ti.operations[1 - index].operation = operation_intersection;
            return;
        }

        int const side_qk_q = has_qk ? side.qk_wrt_q1() : 0;

        // Only necessary if rescaling is turned off:
        int const side_pj_q2 = has_qk ? side.pj_wrt_q2() : 0;

        if (side_qi_p == -1 && side_qk_p == -1 && side_qk_q == 1)
        {
            // Q turns left on the right side of P (test "MR3")
            // Both directions for "intersection"
            both(ti, operation_intersection);
            ti.touch_only = true;
        }
        else if (side_qi_p == 1 && side_qk_p == 1 && side_qk_q == -1)
        {
            if (has_qk && side_pj_q2 == -1)
            {
                // Q turns right on the left side of P (test "ML3")
                // Union: take both operations
                // Intersection: skip
                both(ti, operation_union);
            }
            else
            {
                // q2 is collinear with p1, so it does not turn back. This
                // can happen in floating point precision. In this case,
                // block one of the operations to avoid taking that path.
                ti.operations[index_p].operation = operation_union;
                ti.operations[index_q].operation = operation_blocked;
            }
            ti.touch_only = true;
        }
        else if (side_qi_p == side_qk_p && side_qi_p == side_qk_q)
        {
            // Q turns left on the left side of P (test "ML2")
            // or Q turns right on the right side of P (test "MR2")
            // Union: take left turn (Q if Q turns left, P if Q turns right)
            // Intersection: other turn
            unsigned int index = side_qk_q == 1 ? index_q : index_p;
            if (has_qk && side_pj_q2 == 0)
            {
                // Even though sides xk w.r.t. 1 are distinct, pj is collinear
                // with q. Therefore swap the path
                index = 1 - index;
            }

            if (has_pk && has_qk && opposite(side_pj_q2, side_qi_p))
            {
                // Without rescaling, floating point requires extra measures
                int const side_qj_p1 = side.qj_wrt_p1();
                int const side_qj_p2 = side.qj_wrt_p2();

                if (same(side_qj_p1, side_qj_p2))
                {
                    int const side_pj_q1 = side.pj_wrt_q1();
                    if (opposite(side_pj_q1, side_pj_q2))
                    {
                        index = 1 - index;
                    }
                }
            }

            ti.operations[index].operation = operation_union;
            ti.operations[1 - index].operation = operation_intersection;
            ti.touch_only = true;
        }
        else if (side_qk_p == 0)
        {
            // Q intersects on interior of P and continues collinearly
            if (side_qk_q == side_qi_p)
            {
                both_collinear<index_p, index_q>(range_p, range_q, umbrella_strategy, 1, 2, ti);
                return;
            }
            else
            {
                // Opposite direction, which is never travelled.
                // If Q turns left, P continues for intersection
                // If Q turns right, P continues for union
                ti.operations[index_p].operation = side_qk_q == 1
                    ? operation_intersection
                    : operation_union;
                ti.operations[index_q].operation = operation_blocked;
            }
        }
        else
        {
            // Should not occur!
            ti.method = method_error;
        }
    }
};


template
<
    typename TurnInfo
>
struct touch : public base_turn_handler
{
    static inline bool between(int side1, int side2, int turn)
    {
        return side1 == side2 && ! opposite(side1, turn);
    }

    /*static inline void block_second(bool block, TurnInfo& ti)
    {
        if (block)
        {
            ti.operations[1].operation = operation_blocked;
        }
    }*/


    template
    <
        typename UniqueSubRange1,
        typename UniqueSubRange2,
        typename IntersectionInfo,
        typename DirInfo,
        typename SideCalculator,
        typename UmbrellaStrategy
    >
    static inline void apply(UniqueSubRange1 const& range_p,
                UniqueSubRange2 const& range_q,
                TurnInfo& ti,
                IntersectionInfo const& intersection_info,
                DirInfo const& dir_info,
                SideCalculator const& side,
                UmbrellaStrategy const& umbrella_strategy)
    {
        assign_point(ti, method_touch, intersection_info, 0);

        bool const has_pk = ! range_p.is_last_segment();
        bool const has_qk = ! range_q.is_last_segment();

        int const side_qi_p1 = dir_info.sides.template get<1, 0>();
        int const side_qk_p1 = has_qk ? side.qk_wrt_p1() : 0;


        // If Qi and Qk are both at same side of Pi-Pj,
        // or collinear (so: not opposite sides)
        if (! opposite(side_qi_p1, side_qk_p1))
        {
            int const side_pk_q2 = has_pk && has_qk ? side.pk_wrt_q2() : 0;
            int const side_pk_p  = has_pk ? side.pk_wrt_p1() : 0;
            int const side_qk_q  = has_qk ? side.qk_wrt_q1() : 0;

            bool const q_turns_left = side_qk_q == 1;
            bool const block_q = side_qk_p1 == 0
                        && ! same(side_qi_p1, side_qk_q)
                        ;

            // If Pk at same side as Qi/Qk
            // (the "or" is for collinear case)
            // or Q is fully collinear && P turns not to left
            if (side_pk_p == side_qi_p1
                || side_pk_p == side_qk_p1
                || (side_qi_p1 == 0 && side_qk_p1 == 0 && side_pk_p != -1)
                )
            {
                // Collinear -> lines join, continue
                // (#BRL2)
                if (side_pk_q2 == 0 && ! block_q)
                {
                    both_collinear<0, 1>(range_p, range_q, umbrella_strategy, 2, 2, ti);
                    return;
                }

                int const side_pk_q1 = has_pk && has_qk ? side.pk_wrt_q1() : 0;

                // Collinear opposite case -> block P
                // (#BRL4, #BLR8)
                if (side_pk_q1 == 0)
                {
                    ti.operations[0].operation = operation_blocked;
                    // Q turns right -> union (both independent),
                    // Q turns left -> intersection
                    ti.operations[1].operation = block_q ? operation_blocked
                        : q_turns_left ? operation_intersection
                        : operation_union;
                    return;
                }

                // Pk between Qi and Qk
                // (#BRL3, #BRL7)
                if (between(side_pk_q1, side_pk_q2, side_qk_q))
                {
                    ui_else_iu(q_turns_left, ti);
                    if (block_q)
                    {
                        ti.operations[1].operation = operation_blocked;
                    }
                    //block_second(block_q, ti);
                    return;
                }

                // Pk between Qk and P, so left of Qk (if Q turns right) and vv
                // (#BRL1)
                if (side_pk_q2 == -side_qk_q)
                {
                    ui_else_iu(! q_turns_left, ti);
                    ti.touch_only = true;
                    return;
                }

                //
                // (#BRL5, #BRL9)
                if (side_pk_q1 == -side_qk_q)
                {
                    uu_else_ii(! q_turns_left, ti);
                    if (block_q)
                    {
                        ti.operations[1].operation = operation_blocked;
                    }
                    else
                    {
                        ti.touch_only = true;
                    }
                    //block_second(block_q, ti);
                    return;
                }
            }
            else
            {
                // Pk at other side than Qi/Pk
                ti.operations[0].operation = q_turns_left
                            ? operation_intersection
                            : operation_union;
                ti.operations[1].operation = block_q
                            ? operation_blocked
                            : side_qi_p1 == 1 || side_qk_p1 == 1
                            ? operation_union
                            : operation_intersection;
                if (! block_q)
                {
                    ti.touch_only = true;
                }

                return;
            }
        }
        else
        {
            // From left to right or from right to left
            int const side_pk_p = has_pk ? side.pk_wrt_p1() : 0;
            bool const right_to_left = side_qk_p1 == 1;

            // If p turns into direction of qi (1,2)
            if (side_pk_p == side_qi_p1)
            {
                int const side_pk_q1 = has_pk ? side.pk_wrt_q1() : 0;

                // Collinear opposite case -> block P
                if (side_pk_q1 == 0)
                {
                    ti.operations[0].operation = operation_blocked;
                    ti.operations[1].operation = right_to_left
                                ? operation_union : operation_intersection;
                    return;
                }

                if (side_pk_q1 == side_qk_p1)
                {
                    uu_else_ii(right_to_left, ti);
                    ti.touch_only = true;
                    return;
                }
            }

            // If p turns into direction of qk (4,5)
            if (side_pk_p == side_qk_p1)
            {
                int const side_pk_q2 = has_pk ? side.pk_wrt_q2() : 0;

                // Collinear case -> lines join, continue
                if (side_pk_q2 == 0)
                {
                    both(ti, operation_continue);
                    return;
                }
                if (side_pk_q2 == side_qk_p1)
                {
                    ui_else_iu(right_to_left, ti);
                    ti.touch_only = true;
                    return;
                }
            }
            // otherwise (3)
            ui_else_iu(! right_to_left, ti);
            return;
        }
    }
};


template
<
    typename TurnInfo
>
struct equal : public base_turn_handler
{
    template
    <
        typename UniqueSubRange1,
        typename UniqueSubRange2,
        typename IntersectionInfo,
        typename DirInfo,
        typename SideCalculator,
        typename UmbrellaStrategy
    >
    static inline void apply(UniqueSubRange1 const& range_p,
                UniqueSubRange2 const& range_q,
                TurnInfo& ti,
                IntersectionInfo const& info,
                DirInfo const&  ,
                SideCalculator const& side,
                UmbrellaStrategy const& umbrella_strategy)
    {
        // Copy the intersection point in TO direction
        assign_point(ti, method_equal, info, non_opposite_to_index(info));

        bool const has_pk = ! range_p.is_last_segment();
        bool const has_qk = ! range_q.is_last_segment();

        int const side_pk_q2 = has_pk && has_qk ? side.pk_wrt_q2() : 0;
        int const side_pk_p = has_pk ? side.pk_wrt_p1() : 0;
        int const side_qk_p = has_qk ? side.qk_wrt_p1() : 0;

#if ! defined(BOOST_GEOMETRY_USE_RESCALING)

        if (has_pk && has_qk && side_pk_p == side_qk_p)
        {
            // They turn to the same side, or continue both collinearly
            // Without rescaling, to check for union/intersection,
            // try to check side values (without any thresholds)
            typedef typename select_coordinate_type
                    <
                        typename UniqueSubRange1::point_type,
                        typename UniqueSubRange2::point_type
                        >::type coordinate_type;

            typedef detail::distance_measure<coordinate_type> dm_type;

            dm_type const dm_qk_p
               = get_distance_measure<typename UmbrellaStrategy::cs_tag>(range_q.at(1), range_q.at(2), range_p.at(2));
            dm_type const dm_pk_q
               = get_distance_measure<typename UmbrellaStrategy::cs_tag>(range_p.at(1), range_p.at(2), range_q.at(2));

            if (dm_pk_q.measure != dm_qk_p.measure)
            {
                // A (possibly very small) difference is detected, which
                // can be used to distinguish between union/intersection
                ui_else_iu(dm_pk_q.measure < dm_qk_p.measure, ti);
                return;
            }
        }
#endif

        // If pk is collinear with qj-qk, they continue collinearly.
        // This can be on either side of p1 (== q1), or collinear
        // The second condition checks if they do not continue
        // oppositely
        if (side_pk_q2 == 0 && side_pk_p == side_qk_p)
        {
            both_collinear<0, 1>(range_p, range_q, umbrella_strategy, 2, 2, ti);
            return;
        }


        // If they turn to same side (not opposite sides)
        if (! opposite(side_pk_p, side_qk_p))
        {
            // If pk is left of q2 or collinear: p: union, q: intersection
            ui_else_iu(side_pk_q2 != -1, ti);
        }
        else
        {
            // They turn opposite sides. If p turns left (or collinear),
            // p: union, q: intersection
            ui_else_iu(side_pk_p != -1, ti);
        }
    }
};

template
<
    typename TurnInfo,
    typename AssignPolicy
>
struct equal_opposite : public base_turn_handler
{
    template
    <
        typename UniqueSubRange1,
        typename UniqueSubRange2,
        typename OutputIterator,
        typename IntersectionInfo
    >
    static inline void apply(
                UniqueSubRange1 const& /*range_p*/,
                UniqueSubRange2 const& /*range_q*/,
                /* by value: */ TurnInfo tp,
                OutputIterator& out,
                IntersectionInfo const& intersection_info)
    {
        // For equal-opposite segments, normally don't do anything.
        if (AssignPolicy::include_opposite)
        {
            tp.method = method_equal;
            for (unsigned int i = 0; i < 2; i++)
            {
                tp.operations[i].operation = operation_opposite;
            }
            for (unsigned int i = 0; i < intersection_info.i_info().count; i++)
            {
                assign_point(tp, method_none, intersection_info.i_info(), i);
                *out++ = tp;
            }
        }
    }
};

template
<
    typename TurnInfo
>
struct collinear : public base_turn_handler
{
    /*
        arrival P   pk//p1  qk//q1   product*  case    result
         1           1                1        CLL1    ui
        -1                   1       -1        CLL2    iu
         1           1                1        CLR1    ui
        -1                  -1        1        CLR2    ui

         1          -1               -1        CRL1    iu
        -1                   1       -1        CRL2    iu
         1          -1               -1        CRR1    iu
        -1                  -1        1        CRR2    ui

         1           0                0        CC1     cc
        -1                   0        0        CC2     cc

         *product = arrival * (pk//p1 or qk//q1)

         Stated otherwise:
         - if P arrives: look at turn P
         - if Q arrives: look at turn Q
         - if P arrives and P turns left: union for P
         - if P arrives and P turns right: intersection for P
         - if Q arrives and Q turns left: union for Q (=intersection for P)
         - if Q arrives and Q turns right: intersection for Q (=union for P)

         ROBUSTNESS: p and q are collinear, so you would expect
         that side qk//p1 == pk//q1. But that is not always the case
         in near-epsilon ranges. Then decision logic is different.
         If p arrives, q is further, so the angle qk//p1 is (normally)
         more precise than pk//p1

    */
    template
    <
        typename UniqueSubRange1,
        typename UniqueSubRange2,
        typename IntersectionInfo,
        typename DirInfo,
        typename SidePolicy
    >
    static inline void apply(
                UniqueSubRange1 const& range_p,
                UniqueSubRange2 const& range_q,
                TurnInfo& ti,
                IntersectionInfo const& info,
                DirInfo const& dir_info,
                SidePolicy const& side)
    {
        // Copy the intersection point in TO direction
        assign_point(ti, method_collinear, info, non_opposite_to_index(info));

        int const arrival = dir_info.arrival[0];
        // Should not be 0, this is checked before
        BOOST_GEOMETRY_ASSERT(arrival != 0);

        bool const has_pk = ! range_p.is_last_segment();
        bool const has_qk = ! range_q.is_last_segment();
        int const side_p = has_pk ? side.pk_wrt_p1() : 0;
        int const side_q = has_qk ? side.qk_wrt_q1() : 0;

        // If p arrives, use p, else use q
        int const side_p_or_q = arrival == 1
            ? side_p
            : side_q
            ;

        // See comments above,
        // resulting in a strange sort of mathematic rule here:
        // The arrival-info multiplied by the relevant side
        // delivers a consistent result.

        int const product = arrival * side_p_or_q;

        if(product == 0)
        {
            both(ti, operation_continue);
        }
        else
        {
            ui_else_iu(product == 1, ti);
        }

        // Calculate remaining distance. If it continues collinearly it is
        // measured until the end of the next segment
        ti.operations[0].remaining_distance
                = side_p == 0 && has_pk
                ? distance_measure(ti.point, range_p.at(2))
                : distance_measure(ti.point, range_p.at(1));
        ti.operations[1].remaining_distance
                = side_q == 0 && has_qk
                ? distance_measure(ti.point, range_q.at(2))
                : distance_measure(ti.point, range_q.at(1));
    }
};

template
<
    typename TurnInfo,
    typename AssignPolicy
>
struct collinear_opposite : public base_turn_handler
{
private :
    /*
        arrival P  arrival Q  pk//p1   qk//q1  case  result2  result
        --------------------------------------------------------------
         1          1          1       -1      CLO1    ix      xu
         1          1          1        0      CLO2    ix      (xx)
         1          1          1        1      CLO3    ix      xi

         1          1          0       -1      CCO1    (xx)    xu
         1          1          0        0      CCO2    (xx)    (xx)
         1          1          0        1      CCO3    (xx)    xi

         1          1         -1       -1      CRO1    ux      xu
         1          1         -1        0      CRO2    ux      (xx)
         1          1         -1        1      CRO3    ux      xi

        -1          1                  -1      CXO1    xu
        -1          1                   0      CXO2    (xx)
        -1          1                   1      CXO3    xi

         1         -1          1               CXO1    ix
         1         -1          0               CXO2    (xx)
         1         -1         -1               CXO3    ux
    */

    template
    <
        unsigned int Index,
        typename IntersectionInfo
    >
    static inline bool set_tp(int side_rk_r, bool handle_robustness,
                int side_rk_s,
                TurnInfo& tp, IntersectionInfo const& intersection_info)
    {
        BOOST_STATIC_ASSERT(Index <= 1);

        boost::ignore_unused(handle_robustness, side_rk_s);

        operation_type blocked = operation_blocked;
        switch(side_rk_r)
        {

            case 1 :
                // Turning left on opposite collinear: intersection
                tp.operations[Index].operation = operation_intersection;
                break;
            case -1 :
                // Turning right on opposite collinear: union
                tp.operations[Index].operation = operation_union;
                break;
            case 0 :
                // No turn on opposite collinear: block, do not traverse
                // But this "xx" is usually ignored, it is useless to include
                // two operations blocked, so the whole point does not need
                // to be generated.
                // So return false to indicate nothing is to be done.
                if (AssignPolicy::include_opposite)
                {
                    tp.operations[Index].operation = operation_opposite;
                    blocked = operation_opposite;
                }
                else
                {
                    return false;
                }
                break;
        }

        // The other direction is always blocked when collinear opposite
        tp.operations[1 - Index].operation = blocked;

        // If P arrives within Q, set info on P (which is done above, index=0),
        // this turn-info belongs to the second intersection point, index=1
        // (see e.g. figure CLO1)
        assign_point(tp, method_collinear, intersection_info, 1 - Index);
        return true;
    }

public:
    static inline void empty_transformer(TurnInfo &) {}

    template
    <
        typename UniqueSubRange1,
        typename UniqueSubRange2,
        typename OutputIterator,
        typename IntersectionInfo,
        typename SidePolicy
    >
    static inline void apply(
                UniqueSubRange1 const& range_p,
                UniqueSubRange2 const& range_q,

                // Opposite collinear can deliver 2 intersection points,
                TurnInfo const& tp_model,
                OutputIterator& out,

                IntersectionInfo const& intersection_info,
                SidePolicy const& side)
    {
        apply(range_p, range_q,
              tp_model, out, intersection_info, side, empty_transformer);
    }

public:

    template
    <
        typename UniqueSubRange1,
        typename UniqueSubRange2,
        typename OutputIterator,
        typename IntersectionInfo,
        typename SidePolicy,
        typename TurnTransformer
    >
    static inline void apply(
                UniqueSubRange1 const& range_p,
                UniqueSubRange2 const& range_q,

                // Opposite collinear can deliver 2 intersection points,
                TurnInfo const& tp_model,
                OutputIterator& out,

                IntersectionInfo const& info,
                SidePolicy const& side,
                TurnTransformer turn_transformer)
    {
        TurnInfo tp = tp_model;

        int const p_arrival = info.d_info().arrival[0];
        int const q_arrival = info.d_info().arrival[1];

        // If P arrives within Q, there is a turn dependent on P
        if ( p_arrival == 1
          && ! range_p.is_last_segment()
          && set_tp<0>(side.pk_wrt_p1(), true, side.pk_wrt_q1(), tp, info.i_info()) )
        {
            turn_transformer(tp);

            *out++ = tp;
        }

        // If Q arrives within P, there is a turn dependent on Q
        if ( q_arrival == 1
          && ! range_q.is_last_segment()
          && set_tp<1>(side.qk_wrt_q1(), false, side.qk_wrt_p1(), tp, info.i_info()) )
        {
            turn_transformer(tp);

            *out++ = tp;
        }

        if (AssignPolicy::include_opposite)
        {
            // Handle cases not yet handled above
            if ((q_arrival == -1 && p_arrival == 0)
                || (p_arrival == -1 && q_arrival == 0))
            {
                for (unsigned int i = 0; i < 2; i++)
                {
                    tp.operations[i].operation = operation_opposite;
                }
                for (unsigned int i = 0; i < info.i_info().count; i++)
                {
                    assign_point(tp, method_collinear, info.i_info(), i);
                    *out++ = tp;
                }
            }
        }

    }
};


template
<
    typename TurnInfo
>
struct crosses : public base_turn_handler
{
    template <typename IntersectionInfo, typename DirInfo>
    static inline void apply(TurnInfo& ti,
                IntersectionInfo const& intersection_info,
                DirInfo const& dir_info)
    {
        assign_point(ti, method_crosses, intersection_info, 0);

        // In all cases:
        // If Q crosses P from left to right
        // Union: take P
        // Intersection: take Q
        // Otherwise: vice versa
        int const side_qi_p1 = dir_info.sides.template get<1, 0>();
        unsigned int const index = side_qi_p1 == 1 ? 0 : 1;
        ti.operations[index].operation = operation_union;
        ti.operations[1 - index].operation = operation_intersection;
    }
};

struct only_convert : public base_turn_handler
{
    template<typename TurnInfo, typename IntersectionInfo>
    static inline void apply(TurnInfo& ti, IntersectionInfo const& intersection_info)
    {
        assign_point(ti, method_none, intersection_info, 0); // was collinear
        ti.operations[0].operation = operation_continue;
        ti.operations[1].operation = operation_continue;
    }
};

/*!
\brief Policy doing nothing
\details get_turn_info can have an optional policy include extra
    truns. By default it does not, and this class is that default.
 */
struct assign_null_policy
{
    static bool const include_no_turn = false;
    static bool const include_degenerate = false;
    static bool const include_opposite = false;
};

/*!
    \brief Turn information: intersection point, method, and turn information
    \details Information necessary for traversal phase (a phase
        of the overlay process). The information is gathered during the
        get_turns (segment intersection) phase.
    \tparam AssignPolicy policy to assign extra info,
        e.g. to calculate distance from segment's first points
        to intersection points.
        It also defines if a certain class of points
        (degenerate, non-turns) should be included.
 */
template<typename AssignPolicy>
struct get_turn_info
{
    // Intersect a segment p with a segment q
    // Both p and q are modelled as sub_ranges to provide more points
    // to be able to give more information about the turn (left/right)
    template
    <
        typename UniqueSubRange1,
        typename UniqueSubRange2,
        typename TurnInfo,
        typename UmbrellaStrategy,
        typename RobustPolicy,
        typename OutputIterator
    >
    static inline OutputIterator apply(
                UniqueSubRange1 const& range_p,
                UniqueSubRange2 const& range_q,
                TurnInfo const& tp_model,
                UmbrellaStrategy const& umbrella_strategy,
                RobustPolicy const& robust_policy,
                OutputIterator out)
    {
        typedef intersection_info
            <
                UniqueSubRange1, UniqueSubRange2,
                typename TurnInfo::point_type,
                UmbrellaStrategy,
                RobustPolicy
            > inters_info;

        inters_info inters(range_p, range_q, umbrella_strategy, robust_policy);

        char const method = inters.d_info().how;

        // Copy, to copy possibly extended fields
        TurnInfo tp = tp_model;

        bool do_only_convert = false;

        // Select method and apply
        switch(method)
        {
            case 'a' : // "angle"
            case 'f' : // "from"
            case 's' : // "start"
                do_only_convert = true;
                break;

            case 'd' : // disjoint: never do anything
                break;

            case 'm' :
            {
                typedef touch_interior
                    <
                        TurnInfo
                    > handler;

                // If Q (1) arrives (1)
                if ( inters.d_info().arrival[1] == 1 )
                {
                    handler::template apply<0>(range_p, range_q, tp, inters.i_info(), inters.d_info(),
                                inters.sides(), umbrella_strategy);
                }
                else
                {
                    // Swap p/q
                    handler::template apply<1>(range_q, range_p, tp, inters.i_info(), inters.d_info(),
                                inters.get_swapped_sides(), umbrella_strategy);
                }
                *out++ = tp;
            }
            break;
            case 'i' :
            {
                crosses<TurnInfo>::apply(tp, inters.i_info(), inters.d_info());
                *out++ = tp;
            }
            break;
            case 't' :
            {
                // Both touch (both arrive there)
                touch<TurnInfo>::apply(range_p, range_q, tp, inters.i_info(), inters.d_info(), inters.sides(), umbrella_strategy);
                *out++ = tp;
            }
            break;
            case 'e':
            {
                if ( ! inters.d_info().opposite )
                {
                    // Both equal
                    // or collinear-and-ending at intersection point
                    equal<TurnInfo>::apply(range_p, range_q, tp, inters.i_info(), inters.d_info(), inters.sides(), umbrella_strategy);
                    *out++ = tp;
                }
                else
                {
                    equal_opposite
                        <
                            TurnInfo,
                            AssignPolicy
                        >::apply(range_p, range_q, tp, out, inters);
                }
            }
            break;
            case 'c' :
            {
                // Collinear
                if ( ! inters.d_info().opposite )
                {

                    if ( inters.d_info().arrival[0] == 0 )
                    {
                        // Collinear, but similar thus handled as equal
                        equal<TurnInfo>::apply(range_p, range_q, tp,
                                inters.i_info(), inters.d_info(), inters.sides(), umbrella_strategy);

                        // override assigned method
                        tp.method = method_collinear;
                    }
                    else
                    {
                        collinear<TurnInfo>::apply(range_p, range_q, tp,
                                inters.i_info(), inters.d_info(), inters.sides());
                    }

                    *out++ = tp;
                }
                else
                {
                    collinear_opposite
                        <
                            TurnInfo,
                            AssignPolicy
                        >::apply(range_p, range_q,
                            tp, out, inters, inters.sides());
                }
            }
            break;
            case '0' :
            {
                // degenerate points
                if (AssignPolicy::include_degenerate)
                {
                    only_convert::apply(tp, inters.i_info());
                    *out++ = tp;
                }
            }
            break;
            default :
            {
#if defined(BOOST_GEOMETRY_DEBUG_ROBUSTNESS)
                std::cout << "TURN: Unknown method: " << method << std::endl;
#endif
#if ! defined(BOOST_GEOMETRY_OVERLAY_NO_THROW)
                BOOST_THROW_EXCEPTION(turn_info_exception(method));
#endif
            }
            break;
        }

        if (do_only_convert
            && AssignPolicy::include_no_turn
            && inters.i_info().count > 0)
        {
            only_convert::apply(tp, inters.i_info());
            *out++ = tp;
        }

        return out;
    }
};


}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_TURN_INFO_HPP

/* get_turn_info.hpp
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
*/