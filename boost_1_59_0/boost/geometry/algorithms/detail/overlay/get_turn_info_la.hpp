// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2020.
// Modifications copyright (c) 2013-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_TURN_INFO_LA_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_TURN_INFO_LA_HPP

#include <boost/throw_exception.hpp>

#include <boost/geometry/core/assert.hpp>

#include <boost/geometry/util/condition.hpp>

#include <boost/geometry/algorithms/detail/overlay/get_turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turn_info_for_endpoint.hpp>

// TEMP, for spikes detector
//#include <boost/geometry/algorithms/detail/overlay/get_turn_info_ll.hpp>

namespace boost { namespace geometry {

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay {

template<typename AssignPolicy>
struct get_turn_info_linear_areal
{
    // Currently only Linear spikes are handled
    // Areal spikes are ignored
    static const bool handle_spikes = true;

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

        // Select method and apply
        switch(method)
        {
            case 'a' : // collinear, "at"
            case 'f' : // collinear, "from"
            case 's' : // starts from the middle
                get_turn_info_for_endpoint<true, true>(range_p, range_q,
                    tp_model, inters, method_none, out,
                    umbrella_strategy);
                break;

            case 'd' : // disjoint: never do anything
                break;

            case 'm' :
            {
                if ( get_turn_info_for_endpoint<false, true>(range_p, range_q,
                        tp_model, inters, method_touch_interior, out,
                        umbrella_strategy) )
                {
                    // do nothing
                }
                else
                {
                    using handler = touch_interior<TurnInfo, verify_policy_la>;

                    // If Q (1) arrives (1)
                    if ( inters.d_info().arrival[1] == 1 )
                    {
                        handler::template apply<0>(range_p, range_q, tp,
                                    inters.i_info(), inters.d_info(),
                                    inters.sides(), umbrella_strategy);
                    }
                    else
                    {
                        // Swap p/q
                        handler::template apply<1>(range_q, range_p,
                                    tp, inters.i_info(), inters.d_info(),
                                    inters.swapped_sides(), umbrella_strategy);
                    }

                    if ( tp.operations[1].operation == operation_blocked )
                    {
                        tp.operations[0].is_collinear = true;
                    }

                    replace_method_and_operations_tm(tp.method,
                                                     tp.operations[0].operation,
                                                     tp.operations[1].operation);
                    
                    // this function assumes that 'u' must be set for a spike
                    calculate_spike_operation(tp.operations[0].operation,
                                              inters,
                                              umbrella_strategy);
                    
                    *out++ = tp;
                }
            }
            break;
            case 'i' :
            {
                crosses<TurnInfo>::apply(tp, inters.i_info(), inters.d_info());

                replace_operations_i(tp.operations[0].operation, tp.operations[1].operation);

                *out++ = tp;
            }
            break;
            case 't' :
            {
                // Both touch (both arrive there)
                if ( get_turn_info_for_endpoint<false, true>(range_p, range_q,
                        tp_model, inters, method_touch, out,
                        umbrella_strategy) )
                {
                    // do nothing
                }
                else 
                {
                    using handler = touch<TurnInfo, verify_policy_la>;
                    handler::apply(range_p, range_q, tp,
                        inters.i_info(), inters.d_info(), inters.sides(),
                        umbrella_strategy);

                    if ( tp.operations[1].operation == operation_blocked )
                    {
                        tp.operations[0].is_collinear = true;
                    }

                    // workarounds for touch<> not taking spikes into account starts here
                    // those was discovered empirically
                    // touch<> is not symmetrical!
                    // P spikes and Q spikes may produce various operations!
                    // Only P spikes are valid for L/A
                    // TODO: this is not optimal solution - think about rewriting touch<>

                    if ( tp.operations[0].operation == operation_blocked )
                    {
                        // a spike on P on the same line with Q1
                        if ( inters.is_spike_p() )
                        {
                            if ( inters.sides().qk_wrt_p1() == 0 )
                            {
                                tp.operations[0].is_collinear = true;
                            }
                            else
                            {
                                tp.operations[0].operation = operation_union;                                
                            }
                        }
                    }
                    else if ( tp.operations[0].operation == operation_continue
                           && tp.operations[1].operation == operation_continue )
                    {
                        // P spike on the same line with Q2 (opposite)
                        if ( inters.sides().pk_wrt_q1() == -inters.sides().qk_wrt_q1()
                          && inters.is_spike_p() )
                        {
                            tp.operations[0].operation = operation_union;
                            tp.operations[1].operation = operation_union;
                        }
                    }
                    else if ( tp.operations[0].operation == operation_none
                           && tp.operations[1].operation == operation_none )
                    {
                        // spike not handled by touch<>
                        if ( inters.is_spike_p() )
                        {
                            tp.operations[0].operation = operation_intersection;
                            tp.operations[1].operation = operation_union;

                            if ( inters.sides().pk_wrt_q2() == 0 )
                            {
                                tp.operations[0].operation = operation_continue; // will be converted to i
                                tp.operations[0].is_collinear = true;
                            }
                        }
                    }

                    // workarounds for touch<> not taking spikes into account ends here

                    replace_method_and_operations_tm(tp.method,
                                                     tp.operations[0].operation,
                                                     tp.operations[1].operation);

                    bool ignore_spike
                        = calculate_spike_operation(tp.operations[0].operation,
                                                    inters,
                                                    umbrella_strategy);

                    if ( ! BOOST_GEOMETRY_CONDITION(handle_spikes)
                      || ignore_spike
                      || ! append_opposite_spikes<append_touches>( // for 'i' or 'c' i???
                                tp, inters, out) )
                    {
                        *out++ = tp;
                    }
                }
            }
            break;
            case 'e':
            {
                if ( get_turn_info_for_endpoint<true, true>(range_p, range_q,
                        tp_model, inters, method_equal, out,
                        umbrella_strategy) )
                {
                    // do nothing
                }
                else
                {
                    tp.operations[0].is_collinear = true;

                    if ( ! inters.d_info().opposite )
                    {
                        // Both equal
                        // or collinear-and-ending at intersection point
                        using handler = equal<TurnInfo, verify_policy_la>;
                        handler::apply(range_p, range_q, tp,
                            inters.i_info(), inters.d_info(), inters.sides(),
                            umbrella_strategy);

                        turn_transformer_ec<false> transformer(method_touch);
                        transformer(tp);

                        // conditionally handle spikes
                        if ( ! BOOST_GEOMETRY_CONDITION(handle_spikes)
                          || ! append_collinear_spikes(tp, inters,
                                                       method_touch, append_equal, out) )
                        {
                            *out++ = tp; // no spikes
                        }
                    }
                    else
                    {
                        equal_opposite
                            <
                                TurnInfo,
                                AssignPolicy
                            >::apply(range_p, range_q,
                                     tp, out, inters);
                    }
                }
            }
            break;
            case 'c' :
            {
                // Collinear
                if ( get_turn_info_for_endpoint<true, true>(
                        range_p, range_q,
                        tp_model, inters, method_collinear, out,
                        umbrella_strategy) )
                {
                    // do nothing
                }
                else
                {
                    tp.operations[0].is_collinear = true;

                    if ( ! inters.d_info().opposite )
                    {
                        method_type method_replace = method_touch_interior;
                        append_version_c version = append_collinear;

                        if ( inters.d_info().arrival[0] == 0 )
                        {
                            // Collinear, but similar thus handled as equal
                            using handler = equal<TurnInfo, verify_policy_la>;
                            handler::apply(range_p, range_q, tp,
                                inters.i_info(), inters.d_info(), inters.sides(),
                                umbrella_strategy);

                            method_replace = method_touch;
                            version = append_equal;
                        }
                        else
                        {
                            using handler = collinear<TurnInfo, verify_policy_la>;
                            handler::apply(range_p, range_q, tp, inters.i_info(),
                                           inters.d_info(), inters.sides());

                            //method_replace = method_touch_interior;
                            //version = append_collinear;
                        }

                        turn_transformer_ec<false> transformer(method_replace);
                        transformer(tp);

                        // conditionally handle spikes
                        if ( ! BOOST_GEOMETRY_CONDITION(handle_spikes)
                          || ! append_collinear_spikes(tp, inters,
                                                       method_replace, version, out) )
                        {
                            // no spikes
                            *out++ = tp;
                        }
                    }
                    else
                    {
                        // Is this always 'm' ?
                        turn_transformer_ec<false> transformer(method_touch_interior);

                        // conditionally handle spikes
                        if ( BOOST_GEOMETRY_CONDITION(handle_spikes) )
                        {
                            append_opposite_spikes<append_collinear_opposite>(
                                    tp, inters, out);
                        }

                        // TODO: ignore for spikes?
                        //       E.g. pass is_p_valid = !is_p_last && !is_pj_spike,
                        //       the same with is_q_valid

                        collinear_opposite
                            <
                                TurnInfo,
                                AssignPolicy
                            >::apply(range_p, range_q,
                                tp, out, inters,
                                inters.sides(), transformer);
                    }
                }
            }
            break;
            case '0' :
            {
                // degenerate points
                if ( BOOST_GEOMETRY_CONDITION(AssignPolicy::include_degenerate) )
                {
                    only_convert::apply(tp, inters.i_info());

                    if ( range_p.is_first_segment()
                      && equals::equals_point_point(range_p.at(0), tp.point,
                                                    umbrella_strategy) )
                    {
                        tp.operations[0].position = position_front;
                    }
                    else if ( range_p.is_last_segment()
                           && equals::equals_point_point(range_p.at(1), tp.point,
                                                         umbrella_strategy) )
                    {
                        tp.operations[0].position = position_back;
                    }
                    // tp.operations[1].position = position_middle;

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

        return out;
    }

    template <typename Operation,
              typename IntersectionInfo,
              typename Strategy>
    static inline bool calculate_spike_operation(Operation & op,
                                                 IntersectionInfo const& inters,
                                                 Strategy const& strategy)
    {
        bool is_p_spike = ( op == operation_union || op == operation_intersection )
                       && inters.is_spike_p();

        if ( is_p_spike )
        {
            int const pk_q1 = inters.sides().pk_wrt_q1();
            
            bool going_in = pk_q1 < 0; // Pk on the right
            bool going_out = pk_q1 > 0; // Pk on the left

            int const qk_q1 = inters.sides().qk_wrt_q1();

            // special cases
            if ( qk_q1 < 0 ) // Q turning R
            { 
                // spike on the edge point
                // if it's already known that the spike is going out this musn't be checked
                if ( ! going_out
                  && equals::equals_point_point(inters.rpj(), inters.rqj(), strategy) )
                {
                    int const pk_q2 = inters.sides().pk_wrt_q2();
                    going_in = pk_q1 < 0 && pk_q2 < 0; // Pk on the right of both
                    going_out = pk_q1 > 0 || pk_q2 > 0; // Pk on the left of one of them
                }
            }
            else if ( qk_q1 > 0 ) // Q turning L
            {
                // spike on the edge point
                // if it's already known that the spike is going in this musn't be checked
                if ( ! going_in
                  && equals::equals_point_point(inters.rpj(), inters.rqj(), strategy) )
                {
                    int const pk_q2 = inters.sides().pk_wrt_q2();
                    going_in = pk_q1 < 0 || pk_q2 < 0; // Pk on the right of one of them
                    going_out = pk_q1 > 0 && pk_q2 > 0; // Pk on the left of both
                }
            }

            if ( going_in )
            {
                op = operation_intersection;
                return true;
            }
            else if ( going_out )
            {
                op = operation_union;
                return true;
            }
        }

        return false;
    }

    enum append_version_c { append_equal, append_collinear };

    template <typename TurnInfo,
              typename IntersectionInfo,
              typename OutIt>
    static inline bool append_collinear_spikes(TurnInfo & tp,
                                               IntersectionInfo const& inters,
                                               method_type method, append_version_c version,
                                               OutIt out)
    {
        // method == touch || touch_interior
        // both position == middle

        bool is_p_spike = ( version == append_equal ?
                            ( tp.operations[0].operation == operation_union
                           || tp.operations[0].operation == operation_intersection ) :
                            tp.operations[0].operation == operation_continue )
                       && inters.is_spike_p();

        // TODO: throw an exception for spike in Areal?
        /*bool is_q_spike = tp.operations[1].operation == operation_continue
                       && inters.is_spike_q();

        // both are collinear spikes on the same IP, we can just follow both
        if ( is_p_spike && is_q_spike )
        {
            return false;
        }
        // spike on Linear - it's turning back on the boundary of Areal
        else*/
        if ( is_p_spike )
        {
            tp.method = method;
            tp.operations[0].operation = operation_blocked;
            tp.operations[1].operation = operation_union;
            *out++ = tp;
            tp.operations[0].operation = operation_continue; // boundary
            //tp.operations[1].operation = operation_union;
            *out++ = tp;

            return true;
        }
        // spike on Areal - Linear is going outside
        /*else if ( is_q_spike )
        {
            tp.method = method;
            tp.operations[0].operation = operation_union;
            tp.operations[1].operation = operation_continue;
            *out++ = tp;
            *out++ = tp;

            return true;
        }*/

        return false;
    }

    enum append_version_o { append_touches, append_collinear_opposite };

    template <append_version_o Version,
              typename TurnInfo,
              typename IntersectionInfo,
              typename OutIt>
    static inline bool append_opposite_spikes(TurnInfo & tp,
                                              IntersectionInfo const& inters,
                                              OutIt out)
    {
        static const bool is_version_touches = (Version == append_touches);

        bool is_p_spike = ( is_version_touches ?
                            ( tp.operations[0].operation == operation_continue
                           || tp.operations[0].operation == operation_intersection ) : // i ???
                            true )
                       && inters.is_spike_p();
        
        // TODO: throw an exception for spike in Areal?
        /*bool is_q_spike = ( ( Version == append_touches
                           && tp.operations[1].operation == operation_continue )
                         || ( Version == append_collinear_opposite
                           && tp.operations[1].operation == operation_none ) )
                       && inters.is_spike_q();

        if ( is_p_spike && is_q_spike )
        {
            // u/u or nothing?
            return false;
        }
        else*/
        if ( is_p_spike )
        {
            if ( BOOST_GEOMETRY_CONDITION(is_version_touches)
              || inters.d_info().arrival[0] == 1 )
            {
                if ( BOOST_GEOMETRY_CONDITION(is_version_touches) )
                {
                    tp.operations[0].is_collinear = true;
                    //tp.operations[1].is_collinear = false;
                    tp.method = method_touch;
                }
                else
                {
                    tp.operations[0].is_collinear = true;
                    //tp.operations[1].is_collinear = false;

                    BOOST_GEOMETRY_ASSERT(inters.i_info().count > 1);
                    base_turn_handler::assign_point(tp, method_touch_interior, inters.i_info(), 1);
                }

                tp.operations[0].operation = operation_blocked;
                tp.operations[1].operation = operation_continue; // boundary
                *out++ = tp;
                tp.operations[0].operation = operation_continue; // boundary
                //tp.operations[1].operation = operation_continue; // boundary
                *out++ = tp;

                return true;
            }
        }
        /*else if ( is_q_spike )
        {
            tp.operations[0].is_collinear = true;
            tp.method = is_version_touches ? method_touch : method_touch_interior;
            tp.operations[0].operation = operation_continue;
            tp.operations[1].operation = operation_continue; // boundary
            *out++ = tp;
            *out++ = tp;

            return true;
        }*/

        return false;
    }

    static inline void replace_method_and_operations_tm(method_type & method,
                                                        operation_type & op0,
                                                        operation_type & op1)
    {
        if ( op0 == operation_blocked && op1 == operation_blocked )
        {
            // NOTE: probably only if methods are WRT IPs, not segments!
            method = (method == method_touch ? method_equal : method_collinear);
        }

        // Assuming G1 is always Linear
        if ( op0 == operation_blocked )
        {
            op0 = operation_continue;
        }

        if ( op1 == operation_blocked )
        {
            op1 = operation_continue;
        }
        else if ( op1 == operation_intersection )
        {
            op1 = operation_union;
        }

        // spikes in 'm'
        if ( method == method_error )
        {
            method = method_touch_interior;
            op0 = operation_union;
            op1 = operation_union;
        }
    }

    template <bool IsFront>
    class turn_transformer_ec
    {
    public:
        explicit turn_transformer_ec(method_type method_t_or_m)
            : m_method(method_t_or_m)
        {}

        template <typename Turn>
        void operator()(Turn & turn) const
        {
            operation_type & op0 = turn.operations[0].operation;
            operation_type & op1 = turn.operations[1].operation;

            // NOTE: probably only if methods are WRT IPs, not segments!
            if ( BOOST_GEOMETRY_CONDITION(IsFront)
              || op0 == operation_intersection || op0 == operation_union
              || op1 == operation_intersection || op1 == operation_union )
            {
                turn.method = m_method;
            }

            turn.operations[0].is_collinear = op0 != operation_blocked;

            // Assuming G1 is always Linear
            if ( op0 == operation_blocked )
            {
                op0 = operation_continue;
            }

            if ( op1 == operation_blocked )
            {
                op1 = operation_continue;
            }
            else if ( op1 == operation_intersection )
            {
                op1 = operation_union;
            }
        }

    private:
        method_type m_method;
    };

    static inline void replace_operations_i(operation_type & /*op0*/, operation_type & op1)
    {
        // assuming Linear is always the first one
        op1 = operation_union;
    }

    // NOTE: Spikes may NOT be handled for Linear endpoints because it's not
    //       possible to define a spike on an endpoint. Areal geometries must
    //       NOT have spikes at all. One thing that could be done is to throw
    //       an exception when spike is detected in Areal geometry.
    
    template <bool EnableFirst,
              bool EnableLast,
              typename UniqueSubRange1,
              typename UniqueSubRange2,
              typename TurnInfo,
              typename IntersectionInfo,
              typename OutputIterator,
              typename Strategy>
    static inline bool get_turn_info_for_endpoint(
                            UniqueSubRange1 const& range_p,
                            UniqueSubRange2 const& range_q,
                            TurnInfo const& tp_model,
                            IntersectionInfo const& inters,
                            method_type /*method*/,
                            OutputIterator out,
                            Strategy const& strategy)
    {
        namespace ov = overlay;
        typedef ov::get_turn_info_for_endpoint<EnableFirst, EnableLast> get_info_e;

        const std::size_t ip_count = inters.i_info().count;
        // no intersection points
        if (ip_count == 0)
        {
            return false;
        }

        if (! range_p.is_first_segment() && ! range_p.is_last_segment())
        {
            // P sub-range has no end-points
            return false;
        }

        linear_intersections intersections(range_p.at(0),
                                           range_q.at(0),
                                           inters.result(),
                                           range_p.is_last_segment(),
                                           range_q.is_last_segment(),
                                           strategy);
        linear_intersections::ip_info const& ip0 = intersections.template get<0>();
        linear_intersections::ip_info const& ip1 = intersections.template get<1>();

        const bool opposite = inters.d_info().opposite;

        // ANALYSE AND ASSIGN FIRST

        // IP on the first point of Linear Geometry
        bool was_first_point_handled = false;
        if ( BOOST_GEOMETRY_CONDITION(EnableFirst)
          && range_p.is_first_segment() && ip0.is_pi && !ip0.is_qi ) // !q0i prevents duplication
        {
            TurnInfo tp = tp_model;
            tp.operations[0].position = position_front;
            tp.operations[1].position = position_middle;

            if ( opposite ) // opposite -> collinear
            {
                tp.operations[0].operation = operation_continue;
                tp.operations[1].operation = operation_union;
                tp.method = ip0.is_qj ? method_touch : method_touch_interior;
            }
            else
            {
                auto const sides = strategy.side();

                // pi is the intersection point at qj or in the middle of q1
                // so consider segments
                // 1. pi at qj: qi-qj-pj and qi-qj-qk
                //    x: qi-qj, y: qj-qk, qz: qk
                // 2. pi in the middle of q1: qi-pi-pj and qi-pi-qj
                //    x: qi-pi, y: pi-qj, qz: qj
                //    qi-pi, side the same as WRT q1
                //    pi-qj, side the same as WRT q1
                //    qj WRT q1 is 0
                method_type replaced_method = method_none;
                int side_pj_y = 0, side_pj_x = 0, side_qz_x = 0;
                // 1. ip0 or pi at qj
                if ( ip0.is_qj )
                {
                    replaced_method = method_touch;
                    side_pj_y = sides.apply(range_q.at(1), range_q.at(2), range_p.at(1)); // pj wrt q2
                    side_pj_x = sides.apply(range_q.at(0), range_q.at(1), range_p.at(1)); // pj wrt q1
                    side_qz_x = sides.apply(range_q.at(0), range_q.at(1), range_q.at(2)); // qk wrt q1
                }
                // 2. ip0 or pi in the middle of q1
                else
                {
                    replaced_method = method_touch_interior;
                    side_pj_y = sides.apply(range_q.at(0), range_q.at(1), range_p.at(1)); // pj wrt q1
                    side_pj_x = side_pj_y; // pj wrt q1
                    side_qz_x = 0; // qj wrt q1
                }

                std::pair<operation_type, operation_type> operations
                    = get_info_e::operations_of_equal(side_pj_y, side_pj_x, side_qz_x);

                tp.operations[0].operation = operations.first;
                tp.operations[1].operation = operations.second;

                turn_transformer_ec<true> transformer(replaced_method);
                transformer(tp);
            }

            // equals<> or collinear<> will assign the second point,
            // we'd like to assign the first one
            base_turn_handler::assign_point(tp, tp.method, inters.i_info(), 0);

            // NOTE: is_collinear is not set for the first endpoint of L
            // for which there is no preceding segment
            // here is_p_first_ip == true
            tp.operations[0].is_collinear = false;

            *out++ = tp;

            was_first_point_handled = true;
        }

        // ANALYSE AND ASSIGN LAST

        // IP on the last point of Linear Geometry
        if ( BOOST_GEOMETRY_CONDITION(EnableLast)
          && range_p.is_last_segment()
          && ( ip_count > 1 ? (ip1.is_pj && !ip1.is_qi) : (ip0.is_pj && !ip0.is_qi) ) ) // prevents duplication
        {
            TurnInfo tp = tp_model;
            
            if ( inters.i_info().count > 1 )
            {
                //BOOST_GEOMETRY_ASSERT( result.template get<1>().dir_a == 0 && result.template get<1>().dir_b == 0 );
                tp.operations[0].is_collinear = true;
                tp.operations[1].operation = opposite ? operation_continue : operation_union;
            }
            else //if ( result.template get<0>().count == 1 )
            {
                auto const sides = strategy.side();

                // pj is the intersection point at qj or in the middle of q1
                // so consider segments
                // 1. pj at qj: qi-qj-pi and qi-qj-qk
                //    x: qi-qj, y: qj-qk, qz: qk
                // 2. pj in the middle of q1: qi-pj-pi and qi-pj-qj
                //    x: qi-pj, y: pj-qj, qz: qj
                //    qi-pj, the side is the same as WRT q1
                //    pj-qj, the side is the same as WRT q1
                //    side of qj WRT q1 is 0
                int side_pi_y = 0, side_pi_x = 0, side_qz_x = 0;
                // 1. ip0 or pj at qj
                if ( ip0.is_qj )
                {
                    side_pi_y = sides.apply(range_q.at(1), range_q.at(2), range_p.at(0)); // pi wrt q2
                    side_pi_x = sides.apply(range_q.at(0), range_q.at(1), range_p.at(0)); // pi wrt q1
                    side_qz_x = sides.apply(range_q.at(0), range_q.at(1), range_q.at(2)); // qk wrt q1   
                }
                // 2. ip0 or pj in the middle of q1
                else
                {
                    side_pi_y = sides.apply(range_q.at(0), range_q.at(1), range_p.at(0)); // pi wrt q1
                    side_pi_x = side_pi_y; // pi wrt q1
                    side_qz_x = 0; // qj wrt q1
                }

                std::pair<operation_type, operation_type> operations
                    = get_info_e::operations_of_equal(side_pi_y, side_pi_x, side_qz_x);

                tp.operations[0].operation = operations.first;
                tp.operations[1].operation = operations.second;

                turn_transformer_ec<false> transformer(method_none);
                transformer(tp);

                tp.operations[0].is_collinear = tp.both(operation_continue);
            }

            tp.method = ( ip_count > 1 ? ip1.is_qj : ip0.is_qj ) ? method_touch : method_touch_interior;
            tp.operations[0].operation = operation_blocked;
            tp.operations[0].position = position_back;
            tp.operations[1].position = position_middle;
            
            // equals<> or collinear<> will assign the second point,
            // we'd like to assign the first one
            unsigned int ip_index = ip_count > 1 ? 1 : 0;
            base_turn_handler::assign_point(tp, tp.method, inters.i_info(), ip_index);

            *out++ = tp;

            // don't ignore the first IP if the segment is opposite
            return !( opposite && ip_count > 1 ) || was_first_point_handled;
        }

        // don't ignore anything for now
        return false;
    }
};

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_TURN_INFO_LA_HPP

/* get_turn_info_la.hpp
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
*/