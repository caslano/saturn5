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
                            umbrella_strategy);
                break;

            case 'd' : // disjoint: never do anything
                break;

            case 'm' :
            {
                using handler = touch_interior<TurnInfo, verify_policy_ll>;

                if ( get_turn_info_for_endpoint<false, true>
                        ::apply(range_p, range_q,
                                tp_model, inters, method_touch_interior, out,
                                umbrella_strategy) )
                {
                    // do nothing
                }
                else
                {
                    // If Q (1) arrives (1)
                    if ( inters.d_info().arrival[1] == 1)
                    {
                        handler::template apply<0>(range_p, range_q, tp,
                                                  inters.i_info(), inters.d_info(),
                                                  inters.sides(),
                                                  umbrella_strategy);
                    }
                    else
                    {
                        // Swap p/q
                        handler::template apply<1>(range_q, range_p, tp,
                                                  inters.i_info(), inters.d_info(),
                                                  inters.swapped_sides(),
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
                using handler = touch<TurnInfo, verify_policy_ll>;

                // Both touch (both arrive there)
                if ( get_turn_info_for_endpoint<false, true>
                        ::apply(range_p, range_q,
                                tp_model, inters, method_touch, out,
                                umbrella_strategy) )
                {
                    // do nothing
                }
                else 
                {
                    handler::apply(range_p, range_q, tp,
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
                using handler = equal<TurnInfo, verify_policy_ll>;

                if ( get_turn_info_for_endpoint<true, true>
                        ::apply(range_p, range_q,
                                tp_model, inters, method_equal, out,
                                umbrella_strategy) )
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
                        handler::apply(range_p, range_q, tp,
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
                                umbrella_strategy) )
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
                            using handler = equal<TurnInfo, verify_policy_ll>;

                            handler::apply(range_p, range_q, tp,
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
                            using handler = collinear<TurnInfo, verify_policy_ll>;
                            handler::apply(range_p, range_q, tp,
                                           inters.i_info(), inters.d_info(),
                                           inters.sides());

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
                    only_convert::apply(tp, inters.i_info());

                    // if any, only one of those should be true
                    if ( range_p.is_first_segment()
                      && equals::equals_point_point(range_p.at(0), tp.point, umbrella_strategy) )
                    {
                        tp.operations[0].position = position_front;
                    }
                    else if ( range_p.is_last_segment()
                           && equals::equals_point_point(range_p.at(1), tp.point, umbrella_strategy) )
                    {
                        tp.operations[0].position = position_back;
                    }
                    else if ( range_q.is_first_segment()
                           && equals::equals_point_point(range_q.at(0), tp.point, umbrella_strategy) )
                    {
                        tp.operations[1].position = position_front;
                    }
                    else if ( range_q.is_last_segment()
                           && equals::equals_point_point(range_q.at(1), tp.point, umbrella_strategy) )
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