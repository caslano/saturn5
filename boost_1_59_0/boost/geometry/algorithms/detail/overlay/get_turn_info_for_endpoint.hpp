// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013-2020.
// Modifications copyright (c) 2013-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_TURN_INFO_FOR_ENDPOINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_TURN_INFO_FOR_ENDPOINT_HPP

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turn_info.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/policies/robustness/no_rescale_policy.hpp>

namespace boost { namespace geometry {

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay {

// SEGMENT_INTERSECTION RESULT

//                   C  H0  H1  A0  A1   O              IP1 IP2

// D0 and D1 == 0

// |-------->        2   0   0   0   0   F              i/i x/x
// |-------->
//
// |-------->        2   0   0   0   0   T              i/x x/i
// <--------|
//
// |----->           1   0   0   0   0   T              x/x
//       <-----|
//

// |--------->       2   0   0   0   1   T              i/x x/i
//      <----|
//
// |--------->       2   0   0   0   0   F              i/i x/x
//      |---->
//
// |--------->       2   0   0  -1   1   F              i/i u/x
// |---->
//
// |--------->       2   0   0  -1   0   T              i/x u/i
// <----|

// |------->         2   0   0   1  -1   F   and        i/i x/u
//     |------->     2   0   0  -1   1   F   symmetric  i/i u/x
// |------->
//
//     |------->     2   0   0  -1  -1   T              i/u u/i
// <-------|
//
// |------->         2   0   0   1   1   T              i/x x/i
//     <-------|
//
// |-------->        2   0   0  -1   1   F              i/i u/x
//   |---->
//
// |-------->        2   0   0  -1   1   T              i/x u/i
//   <----|

//       |----->     1  -1  -1  -1  -1   T              u/u
// <-----|
//
//       |----->     1  -1   0  -1   0   F   and        u/x
// |----->           1   0  -1   0  -1   F   symmetric  x/u
//       |----->

// D0 or D1 != 0

//          ^
//          |
//          +        1  -1   1  -1   1   F   and        u/x  (P is vertical)
// |-------->        1   1  -1   1  -1   F   symmetric  x/u  (P is horizontal)
// ^
// |
// +
//
//          +
//          |
//          v
// |-------->        1   1   1   1   1   F              x/x  (P is vertical)
//
// ^
// |
// +
// |-------->        1  -1  -1  -1  -1   F              u/u  (P is vertical)
//
//      ^
//      |
//      +
// |-------->        1   0  -1   0  -1   F              u/u  (P is vertical)
//
//      +
//      |
//      v
// |-------->        1   0   1   0   1   F              u/x  (P is vertical)
//

class linear_intersections
{
public:
    template
    <
        typename Point1, typename Point2, typename IntersectionResult,
        typename Strategy
    >
    linear_intersections(Point1 const& pi,
                         Point2 const& qi,
                         IntersectionResult const& result,
                         bool is_p_last, bool is_q_last,
                         Strategy const& strategy)
    {
        int arrival_a = result.direction.arrival[0];
        int arrival_b = result.direction.arrival[1];
        bool same_dirs = result.direction.dir_a == 0
                      && result.direction.dir_b == 0;

        if ( same_dirs )
        {
            if ( result.intersection_points.count == 2 )
            {
                if ( ! result.direction.opposite )
                {
                    ips[0].p_operation = operation_intersection;
                    ips[0].q_operation = operation_intersection;
                    ips[1].p_operation = union_or_blocked_same_dirs(arrival_a, is_p_last);
                    ips[1].q_operation = union_or_blocked_same_dirs(arrival_b, is_q_last);

                    ips[0].is_pi
                        = equals::equals_point_point(
                            pi, result.intersection_points.intersections[0], strategy);
                    ips[0].is_qi
                        = equals::equals_point_point(
                            qi, result.intersection_points.intersections[0], strategy);
                    ips[1].is_pj = arrival_a != -1;
                    ips[1].is_qj = arrival_b != -1;
                }
                else
                {
                    ips[0].p_operation = operation_intersection;
                    ips[0].q_operation = union_or_blocked_same_dirs(arrival_b, is_q_last);
                    ips[1].p_operation = union_or_blocked_same_dirs(arrival_a, is_p_last);
                    ips[1].q_operation = operation_intersection;

                    ips[0].is_pi = arrival_b != 1;
                    ips[0].is_qj = arrival_b != -1;
                    ips[1].is_pj = arrival_a != -1;
                    ips[1].is_qi = arrival_a != 1;
                }
            }
            else
            {
                BOOST_GEOMETRY_ASSERT(result.intersection_points.count == 1);
                ips[0].p_operation = union_or_blocked_same_dirs(arrival_a, is_p_last);
                ips[0].q_operation = union_or_blocked_same_dirs(arrival_b, is_q_last);

                ips[0].is_pi = arrival_a == -1;
                ips[0].is_qi = arrival_b == -1;
                ips[0].is_pj = arrival_a == 0;
                ips[0].is_qj = arrival_b == 0;
            }
        }
        else
        {
            ips[0].p_operation = union_or_blocked_different_dirs(arrival_a, is_p_last);
            ips[0].q_operation = union_or_blocked_different_dirs(arrival_b, is_q_last);

            ips[0].is_pi = arrival_a == -1;
            ips[0].is_qi = arrival_b == -1;
            ips[0].is_pj = arrival_a == 1;
            ips[0].is_qj = arrival_b == 1;
        }
    }

    struct ip_info
    {
        inline ip_info()
            : p_operation(operation_none), q_operation(operation_none)
            , is_pi(false), is_pj(false), is_qi(false), is_qj(false)
        {}

        operation_type p_operation, q_operation;
        bool is_pi, is_pj, is_qi, is_qj;
    };

    template <std::size_t I>
    ip_info const& get() const
    {
        BOOST_STATIC_ASSERT(I < 2);
        return ips[I];
    }
    
private:

    // only if collinear (same_dirs)
    static inline operation_type union_or_blocked_same_dirs(int arrival, bool is_last)
    {
        if ( arrival == 1 )
            return operation_blocked;
        else if ( arrival == -1 )
            return operation_union;
        else
            return is_last ? operation_blocked : operation_union;
            //return operation_blocked;
    }

    // only if not collinear (!same_dirs)
    static inline operation_type union_or_blocked_different_dirs(int arrival, bool is_last)
    {
        if ( arrival == 1 )
            //return operation_blocked;
            return is_last ? operation_blocked : operation_union;
        else
            return operation_union;
    }

    ip_info ips[2];
};

template <bool EnableFirst, bool EnableLast>
struct get_turn_info_for_endpoint
{
    typedef std::pair<operation_type, operation_type> operations_pair;

    BOOST_STATIC_ASSERT(EnableFirst || EnableLast);

    template<typename UniqueSubRange1,
             typename UniqueSubRange2,
             typename TurnInfo,
             typename IntersectionInfo,
             typename OutputIterator,
             typename Strategy
    >
    static inline bool apply(UniqueSubRange1 const& range_p,
                             UniqueSubRange2 const& range_q,
                             TurnInfo const& tp_model,
                             IntersectionInfo const& inters,
                             method_type /*method*/,
                             OutputIterator out,
                             Strategy const& strategy)
    {
        std::size_t ip_count = inters.i_info().count;
        // no intersection points
        if (ip_count == 0)
        {
            return false;
        }

        if (! range_p.is_first_segment()
            && ! range_q.is_first_segment()
            && ! range_p.is_last_segment()
            && ! range_q.is_last_segment())
        {
            // Not an end-point from segment p or q
            return false;
        }

        linear_intersections intersections(range_p.at(0),
                                           range_q.at(0),
                                           inters.result(),
                                           range_p.is_last_segment(),
                                           range_q.is_last_segment(),
                                           strategy);

        bool append0_last
            = analyse_segment_and_assign_ip(range_p, range_q,
                                            intersections.template get<0>(),
                                            tp_model, inters, 0, out);

        // NOTE: opposite && ip_count == 1 may be true!
        bool opposite = inters.d_info().opposite;

        // don't ignore only for collinear opposite
        bool result_ignore_ip0 = append0_last && ( ip_count == 1 || !opposite );

        if ( intersections.template get<1>().p_operation == operation_none )
            return result_ignore_ip0;
        
        bool append1_last
            = analyse_segment_and_assign_ip(range_p, range_q,
                                            intersections.template get<1>(),
                                            tp_model, inters, 1, out);

        // don't ignore only for collinear opposite
        bool result_ignore_ip1 = append1_last && !opposite /*&& ip_count == 2*/;

        return result_ignore_ip0 || result_ignore_ip1;
    }

    template <typename UniqueSubRange1,
              typename UniqueSubRange2,
              typename TurnInfo,
              typename IntersectionInfo,
              typename OutputIterator>
    static inline
    bool analyse_segment_and_assign_ip(UniqueSubRange1 const& range_p,
                                       UniqueSubRange2 const& range_q,
                                       linear_intersections::ip_info const& ip_info,
                                       TurnInfo const& tp_model,
                                       IntersectionInfo const& inters,
                                       unsigned int ip_index,
                                       OutputIterator out)
    {
        // TODO - calculate first/last only if needed
        bool is_p_first_ip = range_p.is_first_segment() && ip_info.is_pi;
        bool is_p_last_ip = range_p.is_last_segment() && ip_info.is_pj;
        bool is_q_first_ip = range_q.is_first_segment() && ip_info.is_qi;
        bool is_q_last_ip = range_q.is_last_segment() && ip_info.is_qj;
        bool append_first = EnableFirst && (is_p_first_ip || is_q_first_ip);
        bool append_last = EnableLast && (is_p_last_ip || is_q_last_ip);

        operation_type p_operation = ip_info.p_operation;
        operation_type q_operation = ip_info.q_operation;

        if ( append_first || append_last )
        {
            bool handled = handle_internal<0>(range_p, range_q,
                                              is_p_first_ip, is_p_last_ip,
                                              is_q_first_ip, is_q_last_ip,
                                              ip_info.is_qi, ip_info.is_qj,
                                              tp_model, inters, ip_index,
                                              p_operation, q_operation);
            if ( !handled )
            {
                // Reverse p/q
                handle_internal<1>(range_q, range_p,
                                   is_q_first_ip, is_q_last_ip,
                                   is_p_first_ip, is_p_last_ip,
                                   ip_info.is_pi, ip_info.is_pj,
                                   tp_model, inters, ip_index,
                                   q_operation, p_operation);
            }

            if ( p_operation != operation_none )
            {
                method_type method = endpoint_ip_method(ip_info.is_pi, ip_info.is_pj,
                                                        ip_info.is_qi, ip_info.is_qj);
                turn_position p_pos = ip_position(is_p_first_ip, is_p_last_ip);
                turn_position q_pos = ip_position(is_q_first_ip, is_q_last_ip);

                // handle spikes

                // P is spike and should be handled
                if (ip_info.is_pj // this check is redundant (also in is_spike_p) but faster
                  && inters.i_info().count == 2
                  && inters.is_spike_p() )
                {
                    assign(inters.result(), ip_index, method, operation_blocked, q_operation,
                           p_pos, q_pos, is_p_first_ip, is_q_first_ip, true, false, tp_model, out);
                    assign(inters.result(), ip_index, method, operation_intersection, q_operation,
                           p_pos, q_pos, is_p_first_ip, is_q_first_ip, true, false, tp_model, out);
                }
                // Q is spike and should be handled
                else if (ip_info.is_qj // this check is redundant (also in is_spike_q) but faster
                       && inters.i_info().count == 2
                       && inters.is_spike_q() )
                {
                    assign(inters.result(), ip_index, method, p_operation, operation_blocked,
                           p_pos, q_pos, is_p_first_ip, is_q_first_ip, false, true, tp_model, out);
                    assign(inters.result(), ip_index, method, p_operation, operation_intersection,
                           p_pos, q_pos, is_p_first_ip, is_q_first_ip, false, true, tp_model, out);
                }
                // no spikes
                else
                {
                    assign(inters.result(), ip_index, method, p_operation, q_operation,
                           p_pos, q_pos, is_p_first_ip, is_q_first_ip, false, false, tp_model, out);
                }
            }
        }

        return append_last;
    }

    // TODO: IT'S ALSO PROBABLE THAT ALL THIS FUNCTION COULD BE INTEGRATED WITH handle_segment
    //       however now it's lazily calculated and then it would be always calculated

    template<std::size_t G1Index,
             typename UniqueRange1,
             typename UniqueRange2,
             typename TurnInfo,
             typename IntersectionInfo
    >
    static inline bool handle_internal(UniqueRange1 const& range1,
                                       UniqueRange2 const& range2,
                                       bool first1, bool last1, bool first2, bool last2,
                                       bool ip_i2, bool ip_j2, TurnInfo const& tp_model,
                                       IntersectionInfo const& inters, unsigned int ip_index,
                                       operation_type & op1, operation_type & op2)
    {
        boost::ignore_unused(ip_index, tp_model);

        auto const strategy = inters.strategy();

        if ( !first2 && !last2 )
        {
            if ( first1 )
            {
#ifdef BOOST_GEOMETRY_DEBUG_GET_TURNS_LINEAR_LINEAR
                // may this give false positives for INTs?
                typename IntersectionResult::point_type const&
                    inters_pt = inters.i_info().intersections[ip_index];
                BOOST_GEOMETRY_ASSERT(ip_i2 == equals::equals_point_point(i2, inters_pt, strategy));
                BOOST_GEOMETRY_ASSERT(ip_j2 == equals::equals_point_point(j2, inters_pt, strategy));
#endif
                if ( ip_i2 )
                {
                    // don't output this IP - for the first point of other geometry segment
                    op1 = operation_none;
                    op2 = operation_none;
                    return true;
                }
                else if ( ip_j2 )
                {
                    auto const sides = strategy.side();
                    int const side_pj_q2 = sides.apply(range2.at(1), range2.at(2), range1.at(1));
                    int const side_pj_q1 = sides.apply(range2.at(0), range2.at(1), range1.at(1));
                    int const side_qk_q1 = sides.apply(range2.at(0), range2.at(1), range2.at(2));

                    operations_pair operations = operations_of_equal(side_pj_q2, side_pj_q1, side_qk_q1);

// TODO: must the above be calculated?
// wouldn't it be enough to check if segments are collinear?

                    if ( operations_both(operations, operation_continue) )
                    {
                        if ( op1 != operation_union 
                          || op2 != operation_union
                          || ! ( G1Index == 0 ? inters.is_spike_q() : inters.is_spike_p() ) )
                        {
                            // THIS IS WRT THE ORIGINAL SEGMENTS! NOT THE ONES ABOVE!
                            bool opposite = inters.d_info().opposite;

                            op1 = operation_intersection;
                            op2 = opposite ? operation_union : operation_intersection;
                        }
                    }
                    else
                    {
                        BOOST_GEOMETRY_ASSERT(operations_combination(operations, operation_intersection, operation_union));
                        //op1 = operation_union;
                        //op2 = operation_union;
                    }

                    return true;
                }
                // else do nothing - shouldn't be handled this way
            }
            else if ( last1 )
            {
#ifdef BOOST_GEOMETRY_DEBUG_GET_TURNS_LINEAR_LINEAR
                // may this give false positives for INTs?
                typename IntersectionResult::point_type const&
                    inters_pt = inters.i_info().intersections[ip_index];
                BOOST_GEOMETRY_ASSERT(ip_i2 == equals::equals_point_point(i2, inters_pt, strategy));
                BOOST_GEOMETRY_ASSERT(ip_j2 == equals::equals_point_point(j2, inters_pt, strategy));
#endif
                if ( ip_i2 )
                {
                    // don't output this IP - for the first point of other geometry segment
                    op1 = operation_none;
                    op2 = operation_none;
                    return true;
                }
                else if ( ip_j2 )
                {
                    auto const sides = strategy.side();
                    int const side_pi_q2 = sides.apply(range2.at(1), range2.at(2), range1.at(0));
                    int const side_pi_q1 = sides.apply(range2.at(0), range2.at(1), range1.at(0));
                    int const side_qk_q1 = sides.apply(range2.at(0), range2.at(1), range2.at(2));

                    operations_pair operations = operations_of_equal(side_pi_q2, side_pi_q1, side_qk_q1);

// TODO: must the above be calculated?
// wouldn't it be enough to check if segments are collinear?

                    if ( operations_both(operations, operation_continue) )
                    {
                        if ( op1 != operation_blocked
                          || op2 != operation_union
                          || ! ( G1Index == 0 ? inters.is_spike_q() : inters.is_spike_p() ) )
                        {
                            // THIS IS WRT THE ORIGINAL SEGMENTS! NOT THE ONES ABOVE!
                            bool second_going_out = inters.i_info().count > 1;

                            op1 = operation_blocked;
                            op2 = second_going_out ? operation_union : operation_intersection;
                        }
                    }
                    else
                    {
                        BOOST_GEOMETRY_ASSERT(operations_combination(operations, operation_intersection, operation_union));
                        //op1 = operation_blocked;
                        //op2 = operation_union;
                    }

                    return true;
                }
                // else do nothing - shouldn't be handled this way
            }
            // else do nothing - shouldn't be handled this way
        }

        return false;
    }

    static inline method_type endpoint_ip_method(bool ip_pi, bool ip_pj, bool ip_qi, bool ip_qj)
    {
        if ( (ip_pi || ip_pj) && (ip_qi || ip_qj) )
            return method_touch;
        else
            return method_touch_interior;
    }

    static inline turn_position ip_position(bool is_ip_first_i, bool is_ip_last_j)
    {
        return is_ip_first_i ? position_front :
               ( is_ip_last_j ? position_back : position_middle );
    }

    template <typename IntersectionResult,
              typename TurnInfo,
              typename OutputIterator>
    static inline void assign(IntersectionResult const& result,
                              unsigned int ip_index,
                              method_type method,
                              operation_type op0, operation_type op1,
                              turn_position pos0, turn_position pos1,
                              bool is_p_first_ip, bool is_q_first_ip,
                              bool is_p_spike, bool is_q_spike,
                              TurnInfo const& tp_model,
                              OutputIterator out)
    {
        TurnInfo tp = tp_model;
        
        //geometry::convert(ip, tp.point);
        //tp.method = method;
        base_turn_handler::assign_point(tp, method, result.intersection_points, ip_index);

        tp.operations[0].operation = op0;
        tp.operations[1].operation = op1;
        tp.operations[0].position = pos0;
        tp.operations[1].position = pos1;

        if ( result.intersection_points.count > 1 )
        {
            // NOTE: is_collinear is NOT set for the first endpoint
            // for which there is no preceding segment

            //BOOST_GEOMETRY_ASSERT( result.direction.dir_a == 0 && result.direction.dir_b == 0 );
            if ( ! is_p_first_ip )
            {
                tp.operations[0].is_collinear = op0 != operation_intersection
                                             || is_p_spike;
            }

            if ( ! is_q_first_ip )
            {
                tp.operations[1].is_collinear = op1 != operation_intersection
                                             || is_q_spike;
            }
        }
        else //if ( result.intersection_points.count == 1 )
        {
            if ( op0 == operation_blocked && op1 == operation_intersection )
            {
                tp.operations[0].is_collinear = true;
            }
            else if ( op0 == operation_intersection && op1 == operation_blocked )
            {
                tp.operations[1].is_collinear = true;
            }
        }

        *out++ = tp;
    }

    static inline operations_pair operations_of_equal(int side_px_q2,
                                                      int side_px_q1,
                                                      int side_qk_q1)
    {
        // If px (pi or pj) is collinear with qj-qk (q2), they continue collinearly.
        // This can be on either side of q1, or collinear
        // The second condition checks if they do not continue
        // oppositely
        if (side_px_q2 == 0 && side_px_q1 == side_qk_q1)
        {
            return std::make_pair(operation_continue, operation_continue);
        }

        // If they turn to same side (not opposite sides)
        if ( ! base_turn_handler::opposite(side_px_q1, side_qk_q1) )
        {
            // If px is left of q2 or collinear: p: union, q: intersection
            if (side_px_q2 != -1 )
            {
                return std::make_pair(operation_union, operation_intersection);
            }
            else
            {
               return std::make_pair(operation_intersection, operation_union);
            }
        }
        else
        {
            // They turn opposite sides. If p turns left (or collinear),
           // p: union, q: intersection
            if (side_px_q1 != -1 )
            {
                return std::make_pair(operation_union, operation_intersection);
            }
           else
            {
                return std::make_pair(operation_intersection, operation_union);
            }
        }
   }

    static inline bool operations_both(operations_pair const& operations,
                                       operation_type const op)
    {
        return operations.first == op && operations.second == op;
    }

    static inline bool operations_combination(operations_pair const& operations,
                                              operation_type const op1,
                                              operation_type const op2)
    {
        return ( operations.first == op1 && operations.second == op2 )
            || ( operations.first == op2 && operations.second == op1 );
    }
};

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_TURN_INFO_FOR_ENDPOINT_HPP

/* get_turn_info_for_endpoint.hpp
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
*/