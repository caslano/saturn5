// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014, 2015, 2017, 2018, 2019.
// Modifications copyright (c) 2013-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_LINEAR_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_LINEAR_LINEAR_HPP

#include <algorithm>

#include <boost/core/ignore_unused.hpp>
#include <boost/range/size.hpp>

#include <boost/geometry/core/assert.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/range.hpp>

#include <boost/geometry/algorithms/detail/sub_range.hpp>
#include <boost/geometry/algorithms/detail/single_geometry.hpp>

#include <boost/geometry/algorithms/detail/relate/point_geometry.hpp>
#include <boost/geometry/algorithms/detail/relate/result.hpp>
#include <boost/geometry/algorithms/detail/relate/turns.hpp>
#include <boost/geometry/algorithms/detail/relate/boundary_checker.hpp>
#include <boost/geometry/algorithms/detail/relate/follow_helpers.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate {

template <typename Result, typename BoundaryChecker, bool TransposeResult>
class disjoint_linestring_pred
{
    typedef typename BoundaryChecker::equals_strategy_type equals_strategy_type;

public:
    disjoint_linestring_pred(Result & res,
                             BoundaryChecker const& boundary_checker)
        : m_result(res)
        , m_boundary_checker(boundary_checker)
        , m_flags(0)
    {
        if ( ! may_update<interior, exterior, '1', TransposeResult>(m_result) )
        {
            m_flags |= 1;
        }
        if ( ! may_update<boundary, exterior, '0', TransposeResult>(m_result) )
        {
            m_flags |= 2;
        }
    }

    template <typename Linestring>
    bool operator()(Linestring const& linestring)
    {
        if ( m_flags == 3 )
        {
            return false;
        }

        std::size_t const count = boost::size(linestring);
        
        // invalid input
        if ( count < 2 )
        {
            // ignore
            // TODO: throw an exception?
            return true;
        }

        // point-like linestring
        if ( count == 2
          && equals::equals_point_point(range::front(linestring),
                                        range::back(linestring),
                                        equals_strategy_type()) )
        {
            update<interior, exterior, '0', TransposeResult>(m_result);
        }
        else
        {
            update<interior, exterior, '1', TransposeResult>(m_result);
            m_flags |= 1;

            // check if there is a boundary
            if ( m_flags < 2
              && ( m_boundary_checker.template
                    is_endpoint_boundary<boundary_front>(range::front(linestring))
                || m_boundary_checker.template
                    is_endpoint_boundary<boundary_back>(range::back(linestring)) ) )
            {
                update<boundary, exterior, '0', TransposeResult>(m_result);
                m_flags |= 2;
            }
        }

        return m_flags != 3
            && ! m_result.interrupt;
    }

private:
    Result & m_result;
    BoundaryChecker const& m_boundary_checker;
    unsigned m_flags;
};

template <typename Geometry1, typename Geometry2>
struct linear_linear
{
    static const bool interruption_enabled = true;

    typedef typename geometry::point_type<Geometry1>::type point1_type;
    typedef typename geometry::point_type<Geometry2>::type point2_type;

    template <typename Result, typename IntersectionStrategy>
    static inline void apply(Geometry1 const& geometry1, Geometry2 const& geometry2,
                             Result & result,
                             IntersectionStrategy const& intersection_strategy)
    {
        typedef typename IntersectionStrategy::cs_tag cs_tag;

        // The result should be FFFFFFFFF
        relate::set<exterior, exterior, result_dimension<Geometry1>::value>(result);// FFFFFFFFd, d in [1,9] or T
        if ( BOOST_GEOMETRY_CONDITION( result.interrupt ) )
            return;

        // get and analyse turns
        typedef typename turns::get_turns
            <
                Geometry1, Geometry2
            >::template turn_info_type<IntersectionStrategy>::type turn_type;
        std::vector<turn_type> turns;

        interrupt_policy_linear_linear<Result> interrupt_policy(result);

        turns::get_turns
            <
                Geometry1,
                Geometry2,
                detail::get_turns::get_turn_info_type<Geometry1, Geometry2, turns::assign_policy<true> >
            >::apply(turns, geometry1, geometry2, interrupt_policy, intersection_strategy);

        if ( BOOST_GEOMETRY_CONDITION( result.interrupt ) )
            return;

        typedef boundary_checker
            <
                Geometry1,
                typename IntersectionStrategy::point_in_point_strategy_type
            > boundary_checker1_type;
        boundary_checker1_type boundary_checker1(geometry1);
        disjoint_linestring_pred<Result, boundary_checker1_type, false> pred1(result, boundary_checker1);
        for_each_disjoint_geometry_if<0, Geometry1>::apply(turns.begin(), turns.end(), geometry1, pred1);
        if ( BOOST_GEOMETRY_CONDITION( result.interrupt ) )
            return;

        typedef boundary_checker
            <
                Geometry2,
                typename IntersectionStrategy::point_in_point_strategy_type
            > boundary_checker2_type;
        boundary_checker2_type boundary_checker2(geometry2);
        disjoint_linestring_pred<Result, boundary_checker2_type, true> pred2(result, boundary_checker2);
        for_each_disjoint_geometry_if<1, Geometry2>::apply(turns.begin(), turns.end(), geometry2, pred2);
        if ( BOOST_GEOMETRY_CONDITION( result.interrupt ) )
            return;
        
        if ( turns.empty() )
            return;

        // TODO: turns must be sorted and followed only if it's possible to go out and in on the same point
        // for linear geometries union operation must be detected which I guess would be quite often

        if ( may_update<interior, interior, '1'>(result)
          || may_update<interior, boundary, '0'>(result)
          || may_update<interior, exterior, '1'>(result)
          || may_update<boundary, interior, '0'>(result)
          || may_update<boundary, boundary, '0'>(result)
          || may_update<boundary, exterior, '0'>(result) )
        {
            typedef turns::less<0, turns::less_op_linear_linear<0>, cs_tag> less;
            std::sort(turns.begin(), turns.end(), less());

            turns_analyser<turn_type, 0> analyser;
            analyse_each_turn(result, analyser,
                              turns.begin(), turns.end(),
                              geometry1, geometry2,
                              boundary_checker1, boundary_checker2);
        }

        if ( BOOST_GEOMETRY_CONDITION( result.interrupt ) )
            return;
        
        if ( may_update<interior, interior, '1', true>(result)
          || may_update<interior, boundary, '0', true>(result)
          || may_update<interior, exterior, '1', true>(result)
          || may_update<boundary, interior, '0', true>(result)
          || may_update<boundary, boundary, '0', true>(result)
          || may_update<boundary, exterior, '0', true>(result) )
        {
            typedef turns::less<1, turns::less_op_linear_linear<1>, cs_tag> less;
            std::sort(turns.begin(), turns.end(), less());

            turns_analyser<turn_type, 1> analyser;
            analyse_each_turn(result, analyser,
                              turns.begin(), turns.end(),
                              geometry2, geometry1,
                              boundary_checker2, boundary_checker1);
        }
    }

    template <typename Result>
    class interrupt_policy_linear_linear
    {
    public:
        static bool const enabled = true;

        explicit interrupt_policy_linear_linear(Result & result)
            : m_result(result)
        {}

// TODO: since we update result for some operations here, we may not do it in the analyser!

        template <typename Range>
        inline bool apply(Range const& turns)
        {
            typedef typename boost::range_iterator<Range const>::type iterator;
            
            for (iterator it = boost::begin(turns) ; it != boost::end(turns) ; ++it)
            {
                if ( it->operations[0].operation == overlay::operation_intersection
                  || it->operations[1].operation == overlay::operation_intersection )
                {
                    update<interior, interior, '1'>(m_result);
                }
                else if ( ( it->operations[0].operation == overlay::operation_union
                         || it->operations[0].operation == overlay::operation_blocked
                         || it->operations[1].operation == overlay::operation_union
                         || it->operations[1].operation == overlay::operation_blocked )
                       && it->operations[0].position == overlay::position_middle
                       && it->operations[1].position == overlay::position_middle )
                {
// TODO: here we could also check the boundaries and set IB,BI,BB at this point
                    update<interior, interior, '0'>(m_result);
                }
            }

            return m_result.interrupt;
        }

    private:
        Result & m_result;
    };

    // This analyser should be used like Input or SinglePass Iterator
    template <typename TurnInfo, std::size_t OpId>
    class turns_analyser
    {
        typedef typename TurnInfo::point_type turn_point_type;

        static const std::size_t op_id = OpId;
        static const std::size_t other_op_id = (OpId + 1) % 2;
        static const bool transpose_result = OpId != 0;

    public:
        turns_analyser()
            : m_previous_turn_ptr(NULL)
            , m_previous_operation(overlay::operation_none)
            , m_degenerated_turn_ptr(NULL)
            , m_collinear_spike_exit(false)
        {}

        template <typename Result,
                  typename TurnIt,
                  typename Geometry,
                  typename OtherGeometry,
                  typename BoundaryChecker,
                  typename OtherBoundaryChecker>
        void apply(Result & res, TurnIt it,
                   Geometry const& geometry,
                   OtherGeometry const& other_geometry,
                   BoundaryChecker const& boundary_checker,
                   OtherBoundaryChecker const& other_boundary_checker)
        {
            typedef typename BoundaryChecker::equals_strategy_type equals_strategy_type;

            overlay::operation_type const op = it->operations[op_id].operation;

            segment_identifier const& seg_id = it->operations[op_id].seg_id;
            segment_identifier const& other_id = it->operations[other_op_id].seg_id;

            bool const first_in_range = m_seg_watcher.update(seg_id);

            if ( op != overlay::operation_union
              && op != overlay::operation_intersection
              && op != overlay::operation_blocked )
            {
                // degenerated turn
                if ( op == overlay::operation_continue
                  && it->method == overlay::method_none
                  && m_exit_watcher.is_outside(*it) 
                  /*&& ( m_exit_watcher.get_exit_operation() == overlay::operation_none 
                    || ! turn_on_the_same_ip<op_id>(m_exit_watcher.get_exit_turn(), *it) )*/ )
                {
                    // TODO: rewrite the above condition

                    // WARNING! For spikes the above condition may be TRUE
                    // When degenerated turns are be marked in a different way than c,c/c
                    // different condition will be checked

                    handle_degenerated(res, *it,
                                       geometry, other_geometry,
                                       boundary_checker, other_boundary_checker,
                                       first_in_range);

                    // TODO: not elegant solution! should be rewritten.
                    if ( it->operations[op_id].position == overlay::position_back )
                    {
                        m_previous_operation = overlay::operation_blocked;
                        m_exit_watcher.reset_detected_exit();
                    }
                }

                return;
            }

            // reset
            m_degenerated_turn_ptr = NULL;

            // handle possible exit
            bool fake_enter_detected = false;
            if ( m_exit_watcher.get_exit_operation() == overlay::operation_union )
            {
                // real exit point - may be multiple
                // we know that we entered and now we exit
                if ( ! turn_on_the_same_ip<op_id>(m_exit_watcher.get_exit_turn(),
                                                  *it,
                                                  equals_strategy_type()) )
                {
                    m_exit_watcher.reset_detected_exit();
                    
                    // not the last IP
                    update<interior, exterior, '1', transpose_result>(res);
                }
                // fake exit point, reset state
                else if ( op == overlay::operation_intersection )
                {
                    m_exit_watcher.reset_detected_exit();
                    fake_enter_detected = true;
                }
            }
            else if ( m_exit_watcher.get_exit_operation() == overlay::operation_blocked )
            {
                // ignore multiple BLOCKs
                if ( op == overlay::operation_blocked )
                    return;

                if ( op == overlay::operation_intersection
                  && turn_on_the_same_ip<op_id>(m_exit_watcher.get_exit_turn(),
                                                *it,
                                                equals_strategy_type()) )
                {
                    fake_enter_detected = true;
                }

                m_exit_watcher.reset_detected_exit();
            }

            // i/i, i/x, i/u
            if ( op == overlay::operation_intersection )
            {
                bool const was_outside = m_exit_watcher.is_outside();
                m_exit_watcher.enter(*it);

                // interiors overlaps
                update<interior, interior, '1', transpose_result>(res);

                bool const this_b = it->operations[op_id].position == overlay::position_front // ignore spikes!
                                 && is_ip_on_boundary<boundary_front>(it->point,
                                                                      it->operations[op_id],
                                                                      boundary_checker,
                                                                      seg_id);

                // going inside on boundary point
                // may be front only
                if ( this_b )
                {
                    // may be front and back
                    bool const other_b = is_ip_on_boundary<boundary_any>(it->point,
                                                                         it->operations[other_op_id],
                                                                         other_boundary_checker,
                                                                         other_id);

                    // it's also the boundary of the other geometry
                    if ( other_b )
                    {
                        update<boundary, boundary, '0', transpose_result>(res);
                    }
                    else
                    {
                        update<boundary, interior, '0', transpose_result>(res);
                    }
                }
                // going inside on non-boundary point
                else
                {
                    // if we didn't enter in the past, we were outside
                    if ( was_outside
                      && ! fake_enter_detected
                      && it->operations[op_id].position != overlay::position_front
                      && ! m_collinear_spike_exit )
                    {
                        update<interior, exterior, '1', transpose_result>(res);

                        // if it's the first IP then the first point is outside
                        if ( first_in_range )
                        {
                            bool const front_b = is_endpoint_on_boundary<boundary_front>(
                                                    range::front(sub_range(geometry, seg_id)),
                                                    boundary_checker);

                            // if there is a boundary on the first point
                            if ( front_b )
                            {
                                update<boundary, exterior, '0', transpose_result>(res);
                            }
                        }
                    }
                }

                m_collinear_spike_exit = false;
            }
            // u/i, u/u, u/x, x/i, x/u, x/x
            else if ( op == overlay::operation_union || op == overlay::operation_blocked )
            {
                // TODO: is exit watcher still needed?
                // couldn't is_collinear and some going inside counter be used instead?

                bool const is_collinear = it->operations[op_id].is_collinear;
                bool const was_outside = m_exit_watcher.is_outside()
                                      && m_exit_watcher.get_exit_operation() == overlay::operation_none;
// TODO: move the above condition into the exit_watcher?

                // to exit we must be currently inside and the current segment must be collinear
                if ( !was_outside && is_collinear )
                {
                    m_exit_watcher.exit(*it, false);
                    // if the position is not set to back it must be a spike
                    if ( it->operations[op_id].position != overlay::position_back )
                    {
                        m_collinear_spike_exit = true;
                    }
                }

                bool const op_blocked = op == overlay::operation_blocked;

                // we're inside and going out from inside
                // possibly going out right now
                if ( ! was_outside && is_collinear )
                {
                    if ( op_blocked
                      && it->operations[op_id].position == overlay::position_back ) // ignore spikes!
                    {
                        // check if this is indeed the boundary point
                        // NOTE: is_ip_on_boundary<>() should be called here but the result will be the same
                        if ( is_endpoint_on_boundary<boundary_back>(it->point, boundary_checker) )
                        {
                            // may be front and back
                            bool const other_b = is_ip_on_boundary<boundary_any>(it->point,
                                                                                 it->operations[other_op_id],
                                                                                 other_boundary_checker,
                                                                                 other_id);
                            // it's also the boundary of the other geometry
                            if ( other_b )
                            {
                                update<boundary, boundary, '0', transpose_result>(res);
                            }
                            else
                            {
                                update<boundary, interior, '0', transpose_result>(res);
                            }
                        }
                    }
                }
                // we're outside or intersects some segment from the outside
                else
                {
                    // if we are truly outside
                    if ( was_outside
                      && it->operations[op_id].position != overlay::position_front
                      && ! m_collinear_spike_exit
                      /*&& !is_collinear*/ )
                    {
                        update<interior, exterior, '1', transpose_result>(res);
                    }

                    // boundaries don't overlap - just an optimization
                    if ( it->method == overlay::method_crosses )
                    {
                        // the L1 is going from one side of the L2 to the other through the point
                        update<interior, interior, '0', transpose_result>(res);

                        // it's the first point in range
                        if ( first_in_range )
                        {
                            bool const front_b = is_endpoint_on_boundary<boundary_front>(
                                                    range::front(sub_range(geometry, seg_id)),
                                                    boundary_checker);

                            // if there is a boundary on the first point
                            if ( front_b )
                            {
                                update<boundary, exterior, '0', transpose_result>(res);
                            }
                        }
                    }
                    // method other than crosses, check more conditions
                    else
                    {
                        bool const this_b = is_ip_on_boundary<boundary_any>(it->point,
                                                                            it->operations[op_id],
                                                                            boundary_checker,
                                                                            seg_id);

                        bool const other_b = is_ip_on_boundary<boundary_any>(it->point,
                                                                             it->operations[other_op_id],
                                                                             other_boundary_checker,
                                                                             other_id);
                        
                        // if current IP is on boundary of the geometry
                        if ( this_b )
                        {
                            // it's also the boundary of the other geometry
                            if ( other_b )
                            {
                                update<boundary, boundary, '0', transpose_result>(res);
                            }
                            else
                            {
                                update<boundary, interior, '0', transpose_result>(res);
                            }
                        }
                        // if current IP is not on boundary of the geometry
                        else
                        {
                            // it's also the boundary of the other geometry
                            if ( other_b )
                            {
                                update<interior, boundary, '0', transpose_result>(res);
                            }
                            else
                            {
                                update<interior, interior, '0', transpose_result>(res);
                            }
                        }

                        // first IP on the last segment point - this means that the first point is outside
                        if ( first_in_range
                          && ( !this_b || op_blocked )
                          && was_outside
                          && it->operations[op_id].position != overlay::position_front
                          && ! m_collinear_spike_exit
                          /*&& !is_collinear*/ )
                        {
                            bool const front_b = is_endpoint_on_boundary<boundary_front>(
                                                    range::front(sub_range(geometry, seg_id)),
                                                    boundary_checker);

                            // if there is a boundary on the first point
                            if ( front_b )
                            {
                                update<boundary, exterior, '0', transpose_result>(res);
                            }
                        }
                            
                    }
                }
            }

            // store ref to previously analysed (valid) turn
            m_previous_turn_ptr = boost::addressof(*it);
            // and previously analysed (valid) operation
            m_previous_operation = op;
        }

        // Called for last
        template <typename Result,
                  typename TurnIt,
                  typename Geometry,
                  typename OtherGeometry,
                  typename BoundaryChecker,
                  typename OtherBoundaryChecker>
        void apply(Result & res,
                   TurnIt first, TurnIt last,
                   Geometry const& geometry,
                   OtherGeometry const& /*other_geometry*/,
                   BoundaryChecker const& boundary_checker,
                   OtherBoundaryChecker const& /*other_boundary_checker*/)
        {
            boost::ignore_unused(first, last);
            //BOOST_GEOMETRY_ASSERT( first != last );

            // here, the possible exit is the real one
            // we know that we entered and now we exit
            if ( /*m_exit_watcher.get_exit_operation() == overlay::operation_union // THIS CHECK IS REDUNDANT
                ||*/ m_previous_operation == overlay::operation_union
                || m_degenerated_turn_ptr )
            {
                update<interior, exterior, '1', transpose_result>(res);

                BOOST_GEOMETRY_ASSERT(first != last);

                const TurnInfo * turn_ptr = NULL;
                if ( m_degenerated_turn_ptr )
                    turn_ptr = m_degenerated_turn_ptr;
                else if ( m_previous_turn_ptr )
                    turn_ptr = m_previous_turn_ptr;
                
                if ( turn_ptr )
                {
                    segment_identifier const& prev_seg_id = turn_ptr->operations[op_id].seg_id;

                    //BOOST_GEOMETRY_ASSERT(!boost::empty(sub_range(geometry, prev_seg_id)));
                    bool const prev_back_b = is_endpoint_on_boundary<boundary_back>(
                                                range::back(sub_range(geometry, prev_seg_id)),
                                                boundary_checker);

                    // if there is a boundary on the last point
                    if ( prev_back_b )
                    {
                        update<boundary, exterior, '0', transpose_result>(res);
                    }
                }
            }

            // Just in case,
            // reset exit watcher before the analysis of the next Linestring
            // note that if there are some enters stored there may be some error above
            m_exit_watcher.reset();

            m_previous_turn_ptr = NULL;
            m_previous_operation = overlay::operation_none;
            m_degenerated_turn_ptr = NULL;

            // actually if this is set to true here there is some error
            // in get_turns_ll or relate_ll, an assert could be checked here
            m_collinear_spike_exit = false;
        }

        template <typename Result,
                  typename Turn,
                  typename Geometry,
                  typename OtherGeometry,
                  typename BoundaryChecker,
                  typename OtherBoundaryChecker>
        void handle_degenerated(Result & res,
                                Turn const& turn,
                                Geometry const& geometry,
                                OtherGeometry const& other_geometry,
                                BoundaryChecker const& boundary_checker,
                                OtherBoundaryChecker const& /*other_boundary_checker*/,
                                bool first_in_range)
        {
            typedef typename BoundaryChecker::equals_strategy_type
                equals_strategy1_type;
            typedef typename OtherBoundaryChecker::equals_strategy_type
                equals_strategy2_type;

            typename detail::single_geometry_return_type<Geometry const>::type
                ls1_ref = detail::single_geometry(geometry, turn.operations[op_id].seg_id);
            typename detail::single_geometry_return_type<OtherGeometry const>::type
                ls2_ref = detail::single_geometry(other_geometry, turn.operations[other_op_id].seg_id);

            // only one of those should be true:

            if ( turn.operations[op_id].position == overlay::position_front )
            {
                // valid, point-sized
                if ( boost::size(ls2_ref) == 2 )
                {
                    bool const front_b = is_endpoint_on_boundary<boundary_front>(turn.point, boundary_checker);

                    if ( front_b )
                    {
                        update<boundary, interior, '0', transpose_result>(res);
                    }
                    else
                    {
                        update<interior, interior, '0', transpose_result>(res);
                    }

                    // operation 'c' should be last for the same IP so we know that the next point won't be the same
                    update<interior, exterior, '1', transpose_result>(res);

                    m_degenerated_turn_ptr = boost::addressof(turn);
                }
            }
            else if ( turn.operations[op_id].position == overlay::position_back )
            {
                // valid, point-sized
                if ( boost::size(ls2_ref) == 2 )
                {
                    update<interior, exterior, '1', transpose_result>(res);

                    bool const back_b = is_endpoint_on_boundary<boundary_back>(turn.point, boundary_checker);

                    if ( back_b )
                    {
                        update<boundary, interior, '0', transpose_result>(res);
                    }
                    else
                    {
                        update<interior, interior, '0', transpose_result>(res);
                    }

                    if ( first_in_range )
                    {
                        //BOOST_GEOMETRY_ASSERT(!boost::empty(ls1_ref));
                        bool const front_b = is_endpoint_on_boundary<boundary_front>(
                                                range::front(ls1_ref), boundary_checker);
                        if ( front_b )
                        {
                            update<boundary, exterior, '0', transpose_result>(res);
                        }
                    }
                }
            }
            else if ( turn.operations[op_id].position == overlay::position_middle
                   && turn.operations[other_op_id].position == overlay::position_middle )
            {
                update<interior, interior, '0', transpose_result>(res);

                // here we don't know which one is degenerated

                bool const is_point1 = boost::size(ls1_ref) == 2
                                    && equals::equals_point_point(range::front(ls1_ref),
                                                                  range::back(ls1_ref),
                                                                  equals_strategy1_type());
                bool const is_point2 = boost::size(ls2_ref) == 2
                                    && equals::equals_point_point(range::front(ls2_ref),
                                                                  range::back(ls2_ref),
                                                                  equals_strategy2_type());

                // if the second one is degenerated
                if ( !is_point1 && is_point2 )
                {
                    update<interior, exterior, '1', transpose_result>(res);

                    if ( first_in_range )
                    {
                        //BOOST_GEOMETRY_ASSERT(!boost::empty(ls1_ref));
                        bool const front_b = is_endpoint_on_boundary<boundary_front>(
                                                range::front(ls1_ref), boundary_checker);
                        if ( front_b )
                        {
                            update<boundary, exterior, '0', transpose_result>(res);
                        }
                    }

                    m_degenerated_turn_ptr = boost::addressof(turn);
                }
            }

            // NOTE: other.position == front and other.position == back
            //       will be handled later, for the other geometry
        }

    private:
        exit_watcher<TurnInfo, OpId> m_exit_watcher;
        segment_watcher<same_single> m_seg_watcher;
        const TurnInfo * m_previous_turn_ptr;
        overlay::operation_type m_previous_operation;
        const TurnInfo * m_degenerated_turn_ptr;
        bool m_collinear_spike_exit;
    };

    template <typename Result,
              typename TurnIt,
              typename Analyser,
              typename Geometry,
              typename OtherGeometry,
              typename BoundaryChecker,
              typename OtherBoundaryChecker>
    static inline void analyse_each_turn(Result & res,
                                         Analyser & analyser,
                                         TurnIt first, TurnIt last,
                                         Geometry const& geometry,
                                         OtherGeometry const& other_geometry,
                                         BoundaryChecker const& boundary_checker,
                                         OtherBoundaryChecker const& other_boundary_checker)
    {
        if ( first == last )
            return;

        for ( TurnIt it = first ; it != last ; ++it )
        {
            analyser.apply(res, it,
                           geometry, other_geometry,
                           boundary_checker, other_boundary_checker);

            if ( BOOST_GEOMETRY_CONDITION( res.interrupt ) )
                return;
        }

        analyser.apply(res, first, last,
                       geometry, other_geometry,
                       boundary_checker, other_boundary_checker);
    }
};

}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_LINEAR_LINEAR_HPP

/* linear_linear.hpp
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
*/