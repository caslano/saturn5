// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013, 2014, 2015, 2017, 2018.
// Modifications copyright (c) 2013-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_TURN_INFO_LL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_TURN_INFO_LL_HPP

#include <boost/throw_exception.hpp>

#include <boost/geometry/core/assert.hpp>

#include <boost/geometry/algorithms/detail/overlay/get_turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turn_info_for_endpoint.hpp>

#include <boost/geometry/util/condition.hpp>

namespace boost { namespace geometry {

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay {

template<typename AssignPolicy>
struct get_turn_info_linear_linear
{
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
                get_turn_info_for_endpoint<true, true>
                    ::apply(range_p, range_q,
                            tp_model, inters, method_none, out,
                            umbrella_strategy.get_point_in_point_strategy());
                break;

            case 'd' : // disjoint: never do anything
                break;

            case 'm' :
            {
                if ( get_turn_info_for_endpoint<false, true>
                        ::apply(range_p, range_q,
                                tp_model, inters, method_touch_interior, out,
                                umbrella_strategy.get_point_in_point_strategy()) )
                {
                    // do nothing
                }
                else
                {
                    typedef touch_interior
                        <
                            TurnInfo
                        > policy;

                    // If Q (1) arrives (1)
                    if ( inters.d_info().arrival[1] == 1)
                    {
                        policy::template apply<0>(range_p, range_q, tp,
                                                  inters.i_info(), inters.d_info(),
                                                  inters.sides(),
                                                  umbrella_strategy);
                    }
                    else
                    {
                        // Swap p/q
                        policy::template apply<1>(range_q, range_p, tp,
                                                  inters.i_info(), inters.d_info(),
                                                  inters.get_swapped_sides(),
                                                  umbrella_strategy);
                    }
                    
                    if ( tp.operations[0].operation == operation_blocked )
                    {
                        tp.operations[1].is_collinear = true;
                    }
                    if ( tp.operations[1].operation == operation_blocked )
                    {
                        tp.operations[0].is_collinear = true;
                    }

                    replace_method_and_operations_tm(tp.method,
                                                     tp.operations[0].operation,
                                                     tp.operations[1].operation);
                    
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
                if ( get_turn_info_for_endpoint<false, true>
                        ::apply(range_p, range_q,
                                tp_model, inters, method_touch, out,
                                umbrella_strategy.get_point_in_point_strategy()) )
                {
                    // do nothing
                }
                else 
                {
                    touch<TurnInfo>::apply(range_p, range_q, tp,
                                           inters.i_info(), inters.d_info(),
                                           inters.sides(),
                                           umbrella_strategy);

                    // workarounds for touch<> not taking spikes into account starts here
                    // those was discovered empirically
                    // touch<> is not symmetrical!
                    // P spikes and Q spikes may produce various operations!
                    // TODO: this is not optimal solution - think about rewriting touch<>

                    if ( tp.operations[0].operation == operation_blocked
                      && tp.operations[1].operation == operation_blocked )
                    {
                        // two touching spikes on the same line
                        if ( inters.is_spike_p() && inters.is_spike_q() )
                        {
                            tp.operations[0].operation = operation_union;
                            tp.operations[1].operation = operation_union; 
                        }
                        else
                        {
                            tp.operations[0].is_collinear = true;
                            tp.operations[1].is_collinear = true;
                        }
                    }
                    else if ( tp.operations[0].operation == operation_blocked )
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
                        else
                        {
                            tp.operations[1].is_collinear = true;
                        }
                    }
                    else if ( tp.operations[1].operation == operation_blocked )
                    {
                        // a spike on Q on the same line with P1
                        if ( inters.is_spike_q() )
                        {
                            if ( inters.sides().pk_wrt_q1() == 0 )
                            {
                                tp.operations[1].is_collinear = true;
                            }
                            else
                            {
                                tp.operations[1].operation = operation_union;                                
                            }
                        }
                        else
                        {
                            tp.operations[0].is_collinear = true;
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
                        bool const is_p = inters.is_spike_p();
                        bool const is_q = inters.is_spike_q();

                        if ( is_p || is_q )
                        {
                            tp.operations[0].operation = operation_union;
                            tp.operations[1].operation = operation_union;

                            if ( inters.sides().pk_wrt_q2() == 0 )
                            {
                                tp.operations[0].operation = operation_continue; // will be converted to i
                                if ( is_p )
                                {
                                    tp.operations[0].is_collinear = true;
                                }
                            }

                            if ( inters.sides().qk_wrt_p2() == 0 )
                            {
                                tp.operations[1].operation = operation_continue; // will be converted to i
                                if ( is_q )
                                {
                                    tp.operations[1].is_collinear = true;
                                }
                            }
                        }
                    }

                    // workarounds for touch<> not taking spikes into account ends here

                    replace_method_and_operations_tm(tp.method,
                                                     tp.operations[0].operation,
                                                     tp.operations[1].operation);

                    if ( ! BOOST_GEOMETRY_CONDITION(handle_spikes)
                      || ! append_opposite_spikes<append_touches>(tp, inters, out) )
                    {
                        *out++ = tp;
                    }
                }
            }
            break;
            case 'e':
            {
                if ( get_turn_info_for_endpoint<true, true>
                        ::apply(range_p, range_q,
                                tp_model, inters, method_equal, out,
                                umbrella_strategy.get_point_in_point_strategy()) )
                {
                    // do nothing
                }
                else
                {
                    tp.operations[0].is_collinear = true;
                    tp.operations[1].is_collinear = true;

                    if ( ! inters.d_info().opposite )
                    {
                        // Both equal
                        // or collinear-and-ending at intersection point
                        equal<TurnInfo>::apply(range_p, range_q, tp,
                            inters.i_info(), inters.d_info(), inters.sides(),
                            umbrella_strategy);

                        operation_type spike_op
                            = ( tp.operations[0].operation != operation_continue
                             || tp.operations[1].operation != operation_continue ) ?
                                operation_union :
                                operation_continue;

                        // transform turn
                        turn_transformer_ec transformer(method_touch);
                        transformer(tp);

                        // conditionally handle spikes
                        if ( ! BOOST_GEOMETRY_CONDITION(handle_spikes)
                          || ! append_collinear_spikes(tp, inters,
                                                       method_touch, spike_op,
                                                       out) )
                        {
                            *out++ = tp; // no spikes
                        }
                    }
                    else
                    {
                        // TODO: ignore for spikes or generate something else than opposite?

                        equal_opposite
                            <
                                TurnInfo,
                                AssignPolicy
                            >::apply(range_p, range_q, tp, out, inters);
                    }
                }
            }
            break;
            case 'c' :
            {
                // Collinear
                if ( get_turn_info_for_endpoint<true, true>
                        ::apply(range_p, range_q,
                                tp_model, inters,  method_collinear, out,
                                umbrella_strategy.get_point_in_point_strategy()) )
                {
                    // do nothing
                }
                else
                {
                    // NOTE: this is for spikes since those are set in the turn_transformer_ec
                    tp.operations[0].is_collinear = true;
                    tp.operations[1].is_collinear = true;

                    if ( ! inters.d_info().opposite )
                    {
                        method_type method_replace = method_touch_interior;
                        operation_type spike_op = operation_continue;

                        if ( inters.d_info().arrival[0] == 0 )
                        {
                            // Collinear, but similar thus handled as equal
                            equal<TurnInfo>::apply(range_p, range_q, tp,
                                inters.i_info(), inters.d_info(), inters.sides(),
                                umbrella_strategy);

                            method_replace = method_touch;
                            if ( tp.operations[0].operation != operation_continue
                              || tp.operations[1].operation != operation_continue )
                            {
                                spike_op = operation_union;
                            }
                        }
                        else
                        {
                            collinear<TurnInfo>::apply(range_p, range_q,
                                    tp, inters.i_info(), inters.d_info(), inters.sides());

                            //method_replace = method_touch_interior;
                            //spike_op = operation_continue;
                        }

                        // transform turn
                        turn_transformer_ec transformer(method_replace);
                        transformer(tp);
                        
                        // conditionally handle spikes
                        if ( ! BOOST_GEOMETRY_CONDITION(handle_spikes)
                          || ! append_collinear_spikes(tp, inters,
                                                       method_replace, spike_op,
                                                       out) )
                        {
                            // no spikes
                            *out++ = tp;
                        }
                    }
                    else
                    {
                        // If this always 'm' ?
                        turn_transformer_ec transformer(method_touch_interior);

                        // conditionally handle spikes
                        if ( BOOST_GEOMETRY_CONDITION(handle_spikes) )
                        {
                            append_opposite_spikes<append_collinear_opposite>(tp, inters, out);
                        }

                        // TODO: ignore for spikes?
                        //       E.g. pass is_p_valid = !is_p_last && !is_pj_spike,
                        //       the same with is_q_valid

                        collinear_opposite
                            <
                                TurnInfo,
                                AssignPolicy
                            >::apply(range_p, range_q,
                                tp, out, inters, inters.sides(),
                                transformer);
                    }
                }
            }
            break;
            case '0' :
            {
                // degenerate points
                if ( BOOST_GEOMETRY_CONDITION(AssignPolicy::include_degenerate) )
                {
                    typedef typename UmbrellaStrategy::point_in_point_strategy_type
                        equals_strategy_type;

                    only_convert::apply(tp, inters.i_info());

                    // if any, only one of those should be true
                    if ( range_p.is_first_segment()
                      && equals::equals_point_point(range_p.at(0), tp.point, equals_strategy_type()) )
                    {
                        tp.operations[0].position = position_front;
                    }
                    else if ( range_p.is_last_segment()
                           && equals::equals_point_point(range_p.at(1), tp.point, equals_strategy_type()) )
                    {
                        tp.operations[0].position = position_back;
                    }
                    else if ( range_q.is_first_segment()
                           && equals::equals_point_point(range_q.at(0), tp.point, equals_strategy_type()) )
                    {
                        tp.operations[1].position = position_front;
                    }
                    else if ( range_q.is_last_segment()
                           && equals::equals_point_point(range_q.at(1), tp.point, equals_strategy_type()) )
                    {
                        tp.operations[1].position = position_back;
                    }

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

    template <typename TurnInfo,
              typename IntersectionInfo,
              typename OutIt>
    static inline bool append_collinear_spikes(TurnInfo & tp,
                                               IntersectionInfo const& inters_info,
                                               method_type method, operation_type spike_op,
                                               OutIt out)
    {
        // method == touch || touch_interior
        // both position == middle

        bool is_p_spike = tp.operations[0].operation == spike_op
                       && inters_info.is_spike_p();
        bool is_q_spike = tp.operations[1].operation == spike_op
                       && inters_info.is_spike_q();

        if ( is_p_spike && is_q_spike )
        {
            if ( tp.method == method_equal
              && tp.operations[0].operation == operation_continue
              && tp.operations[1].operation == operation_continue )
            {
                // treat both non-opposite collinear spikes as no-spikes
                return false;
            }

            tp.method = method;
            tp.operations[0].operation = operation_blocked;
            tp.operations[1].operation = operation_blocked;
            *out++ = tp;
            tp.operations[0].operation = operation_intersection;
            tp.operations[1].operation = operation_intersection;
            *out++ = tp;

            return true;
        }
        else if ( is_p_spike )
        {
            tp.method = method;
            tp.operations[0].operation = operation_blocked;
            tp.operations[1].operation = operation_union;
            *out++ = tp;
            tp.operations[0].operation = operation_intersection;
            //tp.operations[1].operation = operation_union;
            *out++ = tp;

            return true;
        }
        else if ( is_q_spike )
        {
            tp.method = method;
            tp.operations[0].operation = operation_union;
            tp.operations[1].operation = operation_blocked;
            *out++ = tp;
            //tp.operations[0].operation = operation_union;
            tp.operations[1].operation = operation_intersection;
            *out++ = tp;

            return true;
        }
        
        return false;
    }

    enum append_version { append_touches, append_collinear_opposite };

    template <append_version Version,
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
                           || tp.operations[0].operation == operation_intersection ) :
                            true )
                       && inters.is_spike_p();
        bool is_q_spike = ( is_version_touches ?
                            ( tp.operations[1].operation == operation_continue
                           || tp.operations[1].operation == operation_intersection ) :
                            true )
                       && inters.is_spike_q();

        bool res = false;

        if ( is_p_spike
          && ( BOOST_GEOMETRY_CONDITION(is_version_touches)
            || inters.d_info().arrival[0] == 1 ) )
        {
            if ( BOOST_GEOMETRY_CONDITION(is_version_touches) )
            {
                tp.operations[0].is_collinear = true;
                tp.operations[1].is_collinear = false;
                tp.method = method_touch;
            }
            else // Version == append_collinear_opposite
            {
                tp.operations[0].is_collinear = true;
                tp.operations[1].is_collinear = false;
                
                BOOST_GEOMETRY_ASSERT(inters.i_info().count > 1);
                
                base_turn_handler::assign_point(tp, method_touch_interior,
                                                inters.i_info(), 1);
            }

            tp.operations[0].operation = operation_blocked;
            tp.operations[1].operation = operation_intersection;
            *out++ = tp;
            tp.operations[0].operation = operation_intersection;
            //tp.operations[1].operation = operation_intersection;
            *out++ = tp;

            res = true;
        }

        if ( is_q_spike
          && ( BOOST_GEOMETRY_CONDITION(is_version_touches)
            || inters.d_info().arrival[1] == 1 ) )
        {
            if ( BOOST_GEOMETRY_CONDITION(is_version_touches) )
            {
                tp.operations[0].is_collinear = false;
                tp.operations[1].is_collinear = true;
                tp.method = method_touch;
            }
            else // Version == append_collinear_opposite
            {
                tp.operations[0].is_collinear = false;
                tp.operations[1].is_collinear = true;
                
                BOOST_GEOMETRY_ASSERT(inters.i_info().count > 0);

                base_turn_handler::assign_point(tp, method_touch_interior, inters.i_info(), 0);
            }

            tp.operations[0].operation = operation_intersection;
            tp.operations[1].operation = operation_blocked;
            *out++ = tp;
            //tp.operations[0].operation = operation_intersection;
            tp.operations[1].operation = operation_intersection;
            *out++ = tp;

            res = true;
        }
        
        return res;
    }

    static inline void replace_method_and_operations_tm(method_type & method,
                                                        operation_type & op0,
                                                        operation_type & op1)
    {
        if ( op0 == operation_blocked && op1 == operation_blocked )
        {
            // NOTE: probably only if methods are WRT IPs, not segments!
            method = (method == method_touch ? method_equal : method_collinear);
            op0 = operation_continue;
            op1 = operation_continue;
        }
        else
        {
            if ( op0 == operation_continue || op0 == operation_blocked )
            {
                op0 = operation_intersection;
            }
            else if ( op0 == operation_intersection )
            {
                op0 = operation_union;
            }

            if ( op1 == operation_continue || op1 == operation_blocked )
            {
                op1 = operation_intersection;
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
    }

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

            BOOST_GEOMETRY_ASSERT(op0 != operation_blocked || op1 != operation_blocked );

            if ( op0 == operation_blocked )
            {
                op0 = operation_intersection;
            }
            else if ( op0 == operation_intersection )
            {
                op0 = operation_union;
            }

            if ( op1 == operation_blocked )
            {
                op1 = operation_intersection;
            }
            else if ( op1 == operation_intersection )
            {
                op1 = operation_union;
            }

            if ( op0 == operation_intersection || op0 == operation_union
              || op1 == operation_intersection || op1 == operation_union )
            {
                turn.method = m_method;
            }

// TODO: is this correct?
//       it's equivalent to comparing to operation_blocked at the beginning of the function
            turn.operations[0].is_collinear = op0 != operation_intersection;
            turn.operations[1].is_collinear = op1 != operation_intersection;
        }

    private:
        method_type m_method;
    };

    static inline void replace_operations_i(operation_type & op0, operation_type & op1)
    {
        if ( op0 == operation_intersection )
        {
            op0 = operation_union;
        }

        if ( op1 == operation_intersection )
        {
            op1 = operation_union;
        }
    }
};

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_TURN_INFO_LL_HPP

/* get_turn_info_ll.hpp
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
*/