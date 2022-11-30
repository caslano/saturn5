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
                                        m_boundary_checker.strategy()) )
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

    template <typename Result, typename Strategy>
    static inline void apply(Geometry1 const& geometry1, Geometry2 const& geometry2,
                             Result & result,
                             Strategy const& strategy)
    {
        typedef typename Strategy::cs_tag cs_tag;

        // The result should be FFFFFFFFF
        relate::set<exterior, exterior, result_dimension<Geometry1>::value>(result);// FFFFFFFFd, d in [1,9] or T
        if ( BOOST_GEOMETRY_CONDITION( result.interrupt ) )
            return;

        // get and analyse turns
        typedef typename turns::get_turns
            <
                Geometry1, Geometry2
            >::template turn_info_type<Strategy>::type turn_type;
        std::vector<turn_type> turns;

        interrupt_policy_linear_linear<Result> interrupt_policy(result);

        turns::get_turns
            <
                Geometry1,
                Geometry2,
                detail::get_turns::get_turn_info_type<Geometry1, Geometry2, turns::assign_policy<true> >
            >::apply(turns, geometry1, geometry2, interrupt_policy, strategy);

        if ( BOOST_GEOMETRY_CONDITION( result.interrupt ) )
            return;

        typedef boundary_checker<Geometry1, Strategy> boundary_checker1_type;
        boundary_checker1_type boundary_checker1(geometry1, strategy);
        disjoint_linestring_pred<Result, boundary_checker1_type, false> pred1(result, boundary_checker1);
        for_each_disjoint_geometry_if<0, Geometry1>::apply(turns.begin(), turns.end(), geometry1, pred1);
        if ( BOOST_GEOMETRY_CONDITION( result.interrupt ) )
            return;

        typedef boundary_checker<Geometry2, Strategy> boundary_checker2_type;
        boundary_checker2_type boundary_checker2(geometry2, strategy);
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
                                                  boundary_checker.strategy()) )
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
                                                boundary_checker.strategy()) )
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
                                OtherBoundaryChecker const& other_boundary_checker,
                                bool first_in_range)
        {
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
                                                                  boundary_checker.strategy());
                bool const is_point2 = boost::size(ls2_ref) == 2
                                    && equals::equals_point_point(range::front(ls2_ref),
                                                                  range::back(ls2_ref),
                                                                  other_boundary_checker.strategy());

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