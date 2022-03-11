// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013, 2014, 2015, 2017, 2018.
// Modifications copyright (c) 2013-2018 Oracle and/or its affiliates.

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
                    umbrella_strategy.get_point_in_point_strategy());
                break;

            case 'd' : // disjoint: never do anything
                break;

            case 'm' :
            {
                if ( get_turn_info_for_endpoint<false, true>(range_p, range_q,
                        tp_model, inters, method_touch_interior, out,
                        umbrella_strategy.get_point_in_point_strategy()) )
                {
                    // do nothing
                }
                else
                {
                    typedef touch_interior<TurnInfo> handler;

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
                                    inters.get_swapped_sides(), umbrella_strategy);
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
                                              umbrella_strategy.get_point_in_point_strategy());
                    
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
                        umbrella_strategy.get_point_in_point_strategy()) )
                {
                    // do nothing
                }
                else 
                {
                    touch<TurnInfo>::apply(range_p, range_q, tp,
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
                                                    umbrella_strategy.get_point_in_point_strategy());

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
                        umbrella_strategy.get_point_in_point_strategy()) )
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
                        equal<TurnInfo>::apply(range_p, range_q, tp,
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
                        umbrella_strategy.get_point_in_point_strategy()) )
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
                            equal<TurnInfo>::apply(range_p, range_q, tp,
                                inters.i_info(), inters.d_info(), inters.sides(),
                                umbrella_strategy);

                            method_replace = method_touch;
                            version = append_equal;
                        }
                        else
                        {
                            collinear<TurnInfo>::apply(range_p, range_q, tp,
                                inters.i_info(), inters.d_info(), inters.sides());

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
                                                    umbrella_strategy.get_point_in_point_strategy()) )
                    {
                        tp.operations[0].position = position_front;
                    }
                    else if ( range_p.is_last_segment()
                           && equals::equals_point_point(range_p.at(1), tp.point,
                                                         umbrella_strategy.get_point_in_point_strategy()) )
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
              typename EqPPStrategy>
    static inline bool calculate_spike_operation(Operation & op,
                                                 IntersectionInfo const& inters,
                                                 EqPPStrategy const& strategy)
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
                  && detail::equals::equals_point_point(inters.rpj(), inters.rqj(), strategy) )
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
                  && detail::equals::equals_point_point(inters.rpj(), inters.rqj(), strategy) )
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
              typename EqPPStrategy>
    static inline bool get_turn_info_for_endpoint(
                            UniqueSubRange1 const& range_p,
                            UniqueSubRange2 const& range_q,
                            TurnInfo const& tp_model,
                            IntersectionInfo const& inters,
                            method_type /*method*/,
                            OutputIterator out,
                            EqPPStrategy const& strategy)
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

        typename IntersectionInfo::side_strategy_type const& sides
                = inters.get_side_strategy();

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

    template <typename Point1, typename Point2, typename IntersectionStrategy>
    static inline bool equals_point_point(Point1 const& point1, Point2 const& point2,
                                          IntersectionStrategy const& strategy)
    {
        return detail::equals::equals_point_point(point1, point2,
                                                  strategy.get_point_in_point_strategy());
    }
};

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_TURN_INFO_LA_HPP

/* get_turn_info_la.hpp
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
*/