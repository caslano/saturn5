// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014, 2017, 2018.
// Modifications copyright (c) 2013-2018 Oracle and/or its affiliates.

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
    template <typename Point1, typename Point2, typename IntersectionResult, typename EqPPStrategy>
    linear_intersections(Point1 const& pi,
                         Point2 const& qi,
                         IntersectionResult const& result,
                         bool is_p_last, bool is_q_last,
                         EqPPStrategy const& strategy)
    {
        int arrival_a = result.template get<1>().arrival[0];
        int arrival_b = result.template get<1>().arrival[1];
        bool same_dirs = result.template get<1>().dir_a == 0
                      && result.template get<1>().dir_b == 0;

        if ( same_dirs )
        {
            if ( result.template get<0>().count == 2 )
            {
                if ( ! result.template get<1>().opposite )
                {
                    ips[0].p_operation = operation_intersection;
                    ips[0].q_operation = operation_intersection;
                    ips[1].p_operation = union_or_blocked_same_dirs(arrival_a, is_p_last);
                    ips[1].q_operation = union_or_blocked_same_dirs(arrival_b, is_q_last);

                    ips[0].is_pi
                        = equals::equals_point_point(
                            pi, result.template get<0>().intersections[0], strategy);
                    ips[0].is_qi
                        = equals::equals_point_point(
                            qi, result.template get<0>().intersections[0], strategy);
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
                BOOST_GEOMETRY_ASSERT(result.template get<0>().count == 1);
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
             typename EqPPStrategy
    >
    static inline bool apply(UniqueSubRange1 const& range_p,
                             UniqueSubRange2 const& range_q,
                             TurnInfo const& tp_model,
                             IntersectionInfo const& inters,
                             method_type /*method*/,
                             OutputIterator out,
                             EqPPStrategy const& strategy)
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

        typename IntersectionInfo::side_strategy_type const& sides
                = inters.get_side_strategy();

        if ( !first2 && !last2 )
        {
            if ( first1 )
            {
#ifdef BOOST_GEOMETRY_DEBUG_GET_TURNS_LINEAR_LINEAR
                // may this give false positives for INTs?
                typename IntersectionResult::point_type const&
                    inters_pt = inters.i_info().intersections[ip_index];
                BOOST_GEOMETRY_ASSERT(ip_i2 == equals::equals_point_point(i2, inters_pt));
                BOOST_GEOMETRY_ASSERT(ip_j2 == equals::equals_point_point(j2, inters_pt));
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
                BOOST_GEOMETRY_ASSERT(ip_i2 == equals::equals_point_point(i2, inters_pt));
                BOOST_GEOMETRY_ASSERT(ip_j2 == equals::equals_point_point(j2, inters_pt));
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
        base_turn_handler::assign_point(tp, method, result.template get<0>(), ip_index);

        tp.operations[0].operation = op0;
        tp.operations[1].operation = op1;
        tp.operations[0].position = pos0;
        tp.operations[1].position = pos1;

        if ( result.template get<0>().count > 1 )
        {
            // NOTE: is_collinear is NOT set for the first endpoint
            // for which there is no preceding segment

            //BOOST_GEOMETRY_ASSERT( result.template get<1>().dir_a == 0 && result.template get<1>().dir_b == 0 );
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
        else //if ( result.template get<0>().count == 1 )
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