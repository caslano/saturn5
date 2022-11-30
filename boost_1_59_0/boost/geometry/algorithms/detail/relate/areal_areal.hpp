// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014, 2015, 2017, 2018, 2019.
// Modifications copyright (c) 2013-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_AREAL_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_AREAL_AREAL_HPP

#include <boost/geometry/core/topological_dimension.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/range.hpp>

#include <boost/geometry/algorithms/num_interior_rings.hpp>
#include <boost/geometry/algorithms/detail/point_on_border.hpp>
#include <boost/geometry/algorithms/detail/sub_range.hpp>
#include <boost/geometry/algorithms/detail/single_geometry.hpp>

#include <boost/geometry/algorithms/detail/relate/point_geometry.hpp>
#include <boost/geometry/algorithms/detail/relate/turns.hpp>
#include <boost/geometry/algorithms/detail/relate/boundary_checker.hpp>
#include <boost/geometry/algorithms/detail/relate/follow_helpers.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate {
    
// WARNING!
// TODO: In the worst case calling this Pred in a loop for MultiPolygon/MultiPolygon may take O(NM)
// Use the rtree in this case!

// may be used to set EI and EB for an Areal geometry for which no turns were generated
template
<
    typename OtherAreal,
    typename Result,
    typename PointInArealStrategy,
    bool TransposeResult
>
class no_turns_aa_pred
{
public:
    no_turns_aa_pred(OtherAreal const& other_areal,
                     Result & res,
                     PointInArealStrategy const& point_in_areal_strategy)
        : m_result(res)
        , m_point_in_areal_strategy(point_in_areal_strategy)
        , m_other_areal(other_areal)
        , m_flags(0)
    {
        // check which relations must be analysed

        if ( ! may_update<interior, interior, '2', TransposeResult>(m_result)
          && ! may_update<boundary, interior, '1', TransposeResult>(m_result)
          && ! may_update<exterior, interior, '2', TransposeResult>(m_result) )
        {
            m_flags |= 1;
        }

        if ( ! may_update<interior, exterior, '2', TransposeResult>(m_result)
          && ! may_update<boundary, exterior, '1', TransposeResult>(m_result) )
        {
            m_flags |= 2;
        }
    }

    template <typename Areal>
    bool operator()(Areal const& areal)
    {
        using detail::within::point_in_geometry;

        // if those flags are set nothing will change
        if ( m_flags == 3 )
        {
            return false;
        }

        typedef typename geometry::point_type<Areal>::type point_type;
        point_type pt;
        bool const ok = boost::geometry::point_on_border(pt, areal);

        // TODO: for now ignore, later throw an exception?
        if ( !ok )
        {
            return true;
        }

        // check if the areal is inside the other_areal
        // TODO: This is O(N)
        // Run in a loop O(NM) - optimize!
        int const pig = point_in_geometry(pt,
                                          m_other_areal,
                                          m_point_in_areal_strategy);
        //BOOST_GEOMETRY_ASSERT( pig != 0 );
        
        // inside
        if ( pig > 0 )
        {
            update<interior, interior, '2', TransposeResult>(m_result);
            update<boundary, interior, '1', TransposeResult>(m_result);
            update<exterior, interior, '2', TransposeResult>(m_result);
            m_flags |= 1;

            // TODO: OPTIMIZE!
            // Only the interior rings of other ONE single geometry must be checked
            // NOT all geometries

            // Check if any interior ring is outside
            ring_identifier ring_id(0, -1, 0);
            std::size_t const irings_count = geometry::num_interior_rings(areal);
            for ( ; static_cast<std::size_t>(ring_id.ring_index) < irings_count ;
                    ++ring_id.ring_index )
            {
                typename detail::sub_range_return_type<Areal const>::type
                    range_ref = detail::sub_range(areal, ring_id);

                if ( boost::empty(range_ref) )
                {
                    // TODO: throw exception?
                    continue; // ignore
                }

                // TODO: O(N)
                // Optimize!
                int const hpig = point_in_geometry(range::front(range_ref),
                                                   m_other_areal,
                                                   m_point_in_areal_strategy);

                // hole outside
                if ( hpig < 0 )
                {
                    update<interior, exterior, '2', TransposeResult>(m_result);
                    update<boundary, exterior, '1', TransposeResult>(m_result);
                    m_flags |= 2;
                    break;
                }
            }
        }
        // outside
        else
        {
            update<interior, exterior, '2', TransposeResult>(m_result);
            update<boundary, exterior, '1', TransposeResult>(m_result);
            m_flags |= 2;

            // Check if any interior ring is inside
            ring_identifier ring_id(0, -1, 0);
            std::size_t const irings_count = geometry::num_interior_rings(areal);
            for ( ; static_cast<std::size_t>(ring_id.ring_index) < irings_count ;
                    ++ring_id.ring_index )
            {
                typename detail::sub_range_return_type<Areal const>::type
                    range_ref = detail::sub_range(areal, ring_id);

                if ( boost::empty(range_ref) )
                {
                    // TODO: throw exception?
                    continue; // ignore
                }

                // TODO: O(N)
                // Optimize!
                int const hpig = point_in_geometry(range::front(range_ref),
                                                   m_other_areal,
                                                   m_point_in_areal_strategy);

                // hole inside
                if ( hpig > 0 )
                {
                    update<interior, interior, '2', TransposeResult>(m_result);
                    update<boundary, interior, '1', TransposeResult>(m_result);
                    update<exterior, interior, '2', TransposeResult>(m_result);
                    m_flags |= 1;
                    break;
                }
            }
        }
                    
        return m_flags != 3 && !m_result.interrupt;
    }

private:
    Result & m_result;
    PointInArealStrategy const& m_point_in_areal_strategy;
    OtherAreal const& m_other_areal;
    int m_flags;
};

// The implementation of an algorithm calculating relate() for A/A
template <typename Geometry1, typename Geometry2>
struct areal_areal
{
    // check Linear / Areal
    BOOST_STATIC_ASSERT(topological_dimension<Geometry1>::value == 2
                     && topological_dimension<Geometry2>::value == 2);

    static const bool interruption_enabled = true;

    typedef typename geometry::point_type<Geometry1>::type point1_type;
    typedef typename geometry::point_type<Geometry2>::type point2_type;
    
    template <typename Result, typename Strategy>
    static inline void apply(Geometry1 const& geometry1, Geometry2 const& geometry2,
                             Result & result,
                             Strategy const& strategy)
    {
// TODO: If Areal geometry may have infinite size, change the following line:

        // The result should be FFFFFFFFF
        relate::set<exterior, exterior, result_dimension<Geometry2>::value>(result);// FFFFFFFFd, d in [1,9] or T

        if ( BOOST_GEOMETRY_CONDITION(result.interrupt) )
            return;

        // get and analyse turns
        typedef typename turns::get_turns
            <
                Geometry1, Geometry2
            >::template turn_info_type<Strategy>::type turn_type;
        std::vector<turn_type> turns;

        interrupt_policy_areal_areal<Result> interrupt_policy(geometry1, geometry2, result);

        turns::get_turns<Geometry1, Geometry2>::apply(turns, geometry1, geometry2, interrupt_policy, strategy);
        if ( BOOST_GEOMETRY_CONDITION(result.interrupt) )
            return;

        typedef typename Strategy::cs_tag cs_tag;

        no_turns_aa_pred<Geometry2, Result, Strategy, false>
            pred1(geometry2, result, strategy);
        for_each_disjoint_geometry_if<0, Geometry1>::apply(turns.begin(), turns.end(), geometry1, pred1);
        if ( BOOST_GEOMETRY_CONDITION(result.interrupt) )
            return;

        no_turns_aa_pred<Geometry1, Result, Strategy, true>
            pred2(geometry1, result, strategy);
        for_each_disjoint_geometry_if<1, Geometry2>::apply(turns.begin(), turns.end(), geometry2, pred2);
        if ( BOOST_GEOMETRY_CONDITION(result.interrupt) )
            return;
        
        if ( turns.empty() )
            return;

        if ( may_update<interior, interior, '2'>(result)
          || may_update<interior, exterior, '2'>(result)
          || may_update<boundary, interior, '1'>(result)
          || may_update<boundary, exterior, '1'>(result)
          || may_update<exterior, interior, '2'>(result) )
        {
            // sort turns
            typedef turns::less<0, turns::less_op_areal_areal<0>, cs_tag> less;
            std::sort(turns.begin(), turns.end(), less());

            /*if ( may_update<interior, exterior, '2'>(result)
              || may_update<boundary, exterior, '1'>(result)
              || may_update<boundary, interior, '1'>(result)
              || may_update<exterior, interior, '2'>(result) )*/
            {
                // analyse sorted turns
                turns_analyser<turn_type, 0> analyser;
                analyse_each_turn(result, analyser, turns.begin(), turns.end(), strategy);

                if ( BOOST_GEOMETRY_CONDITION(result.interrupt) )
                    return;
            }

            if ( may_update<interior, interior, '2'>(result)
              || may_update<interior, exterior, '2'>(result)
              || may_update<boundary, interior, '1'>(result)
              || may_update<boundary, exterior, '1'>(result)
              || may_update<exterior, interior, '2'>(result) )
            {
                // analyse rings for which turns were not generated
                // or only i/i or u/u was generated
                uncertain_rings_analyser<0, Result, Geometry1, Geometry2, Strategy>
                    rings_analyser(result, geometry1, geometry2, strategy);
                analyse_uncertain_rings<0>::apply(rings_analyser, turns.begin(), turns.end());

                if ( BOOST_GEOMETRY_CONDITION(result.interrupt) )
                    return;
            }
        }

        if ( may_update<interior, interior, '2', true>(result)
          || may_update<interior, exterior, '2', true>(result)
          || may_update<boundary, interior, '1', true>(result)
          || may_update<boundary, exterior, '1', true>(result)
          || may_update<exterior, interior, '2', true>(result) )
        {
            // sort turns
            typedef turns::less<1, turns::less_op_areal_areal<1>, cs_tag> less;
            std::sort(turns.begin(), turns.end(), less());

            /*if ( may_update<interior, exterior, '2', true>(result)
              || may_update<boundary, exterior, '1', true>(result)
              || may_update<boundary, interior, '1', true>(result)
              || may_update<exterior, interior, '2', true>(result) )*/
            {
                // analyse sorted turns
                turns_analyser<turn_type, 1> analyser;
                analyse_each_turn(result, analyser, turns.begin(), turns.end(), strategy);

                if ( BOOST_GEOMETRY_CONDITION(result.interrupt) )
                    return;
            }

            if ( may_update<interior, interior, '2', true>(result)
              || may_update<interior, exterior, '2', true>(result)
              || may_update<boundary, interior, '1', true>(result)
              || may_update<boundary, exterior, '1', true>(result)
              || may_update<exterior, interior, '2', true>(result) )
            {
                // analyse rings for which turns were not generated
                // or only i/i or u/u was generated
                uncertain_rings_analyser<1, Result, Geometry2, Geometry1, Strategy>
                    rings_analyser(result, geometry2, geometry1, strategy);
                analyse_uncertain_rings<1>::apply(rings_analyser, turns.begin(), turns.end());

                //if ( result.interrupt )
                //    return;
            }
        }
    }

    // interrupt policy which may be passed to get_turns to interrupt the analysis
    // based on the info in the passed result/mask
    template <typename Result>
    class interrupt_policy_areal_areal
    {
    public:
        static bool const enabled = true;

        interrupt_policy_areal_areal(Geometry1 const& geometry1,
                                     Geometry2 const& geometry2,
                                     Result & result)
            : m_result(result)
            , m_geometry1(geometry1)
            , m_geometry2(geometry2)
        {}

        template <typename Range>
        inline bool apply(Range const& turns)
        {
            typedef typename boost::range_iterator<Range const>::type iterator;
            
            for (iterator it = boost::begin(turns) ; it != boost::end(turns) ; ++it)
            {
                per_turn<0>(*it);
                per_turn<1>(*it);
            }

            return m_result.interrupt;
        }

    private:
        template <std::size_t OpId, typename Turn>
        inline void per_turn(Turn const& turn)
        {
            //static const std::size_t other_op_id = (OpId + 1) % 2;
            static const bool transpose_result = OpId != 0;

            overlay::operation_type const op = turn.operations[OpId].operation;

            if ( op == overlay::operation_union )
            {
                // ignore u/u
                /*if ( turn.operations[other_op_id].operation != overlay::operation_union )
                {
                    update<interior, exterior, '2', transpose_result>(m_result);
                    update<boundary, exterior, '1', transpose_result>(m_result);
                }*/

                update<boundary, boundary, '0', transpose_result>(m_result);
            }
            else if ( op == overlay::operation_intersection )
            {
                // ignore i/i
                /*if ( turn.operations[other_op_id].operation != overlay::operation_intersection )
                {
                    // not correct e.g. for G1 touching G2 in a point where a hole is touching the exterior ring
                    // in this case 2 turns i/... and u/u will be generated for this IP
                    //update<interior, interior, '2', transpose_result>(m_result);

                    //update<boundary, interior, '1', transpose_result>(m_result);
                }*/

                update<boundary, boundary, '0', transpose_result>(m_result);
            }
            else if ( op == overlay::operation_continue )
            {
                update<boundary, boundary, '1', transpose_result>(m_result);
                update<interior, interior, '2', transpose_result>(m_result);
            }
            else if ( op == overlay::operation_blocked )
            {
                update<boundary, boundary, '1', transpose_result>(m_result);
                update<interior, exterior, '2', transpose_result>(m_result);
            }
        }

        Result & m_result;
        Geometry1 const& m_geometry1;
        Geometry2 const& m_geometry2;
    };

    // This analyser should be used like Input or SinglePass Iterator
    // IMPORTANT! It should be called also for the end iterator - last
    template <typename TurnInfo, std::size_t OpId>
    class turns_analyser
    {
        typedef typename TurnInfo::point_type turn_point_type;

        static const std::size_t op_id = OpId;
        static const std::size_t other_op_id = (OpId + 1) % 2;
        static const bool transpose_result = OpId != 0;

    public:
        turns_analyser()
            : m_previous_turn_ptr(0)
            , m_previous_operation(overlay::operation_none)
            , m_enter_detected(false)
            , m_exit_detected(false)
        {}

        template <typename Result, typename TurnIt, typename EqPPStrategy>
        void apply(Result & result, TurnIt it, EqPPStrategy const& strategy)
        {
            //BOOST_GEOMETRY_ASSERT( it != last );

            overlay::operation_type const op = it->operations[op_id].operation;

            if ( op != overlay::operation_union
              && op != overlay::operation_intersection
              && op != overlay::operation_blocked
              && op != overlay::operation_continue )
            {
                return;
            }

            segment_identifier const& seg_id = it->operations[op_id].seg_id;
            //segment_identifier const& other_id = it->operations[other_op_id].seg_id;

            const bool first_in_range = m_seg_watcher.update(seg_id);

            if ( m_previous_turn_ptr )
            {
                if ( m_exit_detected /*m_previous_operation == overlay::operation_union*/ )
                {
                    // real exit point - may be multiple
                    if ( first_in_range
                      || ! turn_on_the_same_ip<op_id>(*m_previous_turn_ptr, *it, strategy) )
                    {
                        update_exit(result);
                        m_exit_detected = false;
                    }
                    // fake exit point, reset state
                    else if ( op != overlay::operation_union )
                    {
                        m_exit_detected = false;
                    }
                }                
                /*else*/
                if ( m_enter_detected /*m_previous_operation == overlay::operation_intersection*/ )
                {
                    // real entry point
                    if ( first_in_range
                      || ! turn_on_the_same_ip<op_id>(*m_previous_turn_ptr, *it, strategy) )
                    {
                        update_enter(result);
                        m_enter_detected = false;
                    }
                    // fake entry point, reset state
                    else if ( op != overlay::operation_intersection )
                    {
                        m_enter_detected = false;
                    }
                }
            }

            if ( op == overlay::operation_union )
            {
                // already set in interrupt policy
                //update<boundary, boundary, '0', transpose_result>(m_result);

                // ignore u/u
                //if ( it->operations[other_op_id].operation != overlay::operation_union )
                {
                    m_exit_detected = true;
                }
            }
            else if ( op == overlay::operation_intersection )
            {
                // ignore i/i
                if ( it->operations[other_op_id].operation != overlay::operation_intersection )
                {
                    // this was set in the interrupt policy but it was wrong
                    // also here it's wrong since it may be a fake entry point
                    //update<interior, interior, '2', transpose_result>(result);

                    // already set in interrupt policy
                    //update<boundary, boundary, '0', transpose_result>(result);
                    m_enter_detected = true;
                }
            }
            else if ( op == overlay::operation_blocked )
            {
                // already set in interrupt policy
            }
            else // if ( op == overlay::operation_continue )
            {
                // already set in interrupt policy
            }

            // store ref to previously analysed (valid) turn
            m_previous_turn_ptr = boost::addressof(*it);
            // and previously analysed (valid) operation
            m_previous_operation = op;
        }

        // it == last
        template <typename Result>
        void apply(Result & result)
        {
            //BOOST_GEOMETRY_ASSERT( first != last );

            if ( m_exit_detected /*m_previous_operation == overlay::operation_union*/ )
            {
                update_exit(result);
                m_exit_detected = false;
            }

            if ( m_enter_detected /*m_previous_operation == overlay::operation_intersection*/ )
            {
                update_enter(result);
                m_enter_detected = false;
            }
        }

        template <typename Result>
        static inline void update_exit(Result & result)
        {
            update<interior, exterior, '2', transpose_result>(result);
            update<boundary, exterior, '1', transpose_result>(result);
        }

        template <typename Result>
        static inline void update_enter(Result & result)
        {
            update<interior, interior, '2', transpose_result>(result);
            update<boundary, interior, '1', transpose_result>(result);
            update<exterior, interior, '2', transpose_result>(result);
        }

    private:
        segment_watcher<same_ring> m_seg_watcher;
        TurnInfo * m_previous_turn_ptr;
        overlay::operation_type m_previous_operation;
        bool m_enter_detected;
        bool m_exit_detected;
    };

    // call analyser.apply() for each turn in range
    // IMPORTANT! The analyser is also called for the end iterator - last
    template
    <
        typename Result,
        typename Analyser,
        typename TurnIt,
        typename EqPPStrategy
    >
    static inline void analyse_each_turn(Result & res,
                                         Analyser & analyser,
                                         TurnIt first, TurnIt last,
                                         EqPPStrategy const& strategy)
    {
        if ( first == last )
            return;

        for ( TurnIt it = first ; it != last ; ++it )
        {
            analyser.apply(res, it, strategy);

            if ( BOOST_GEOMETRY_CONDITION(res.interrupt) )
                return;
        }

        analyser.apply(res);
    }

    template
    <
        std::size_t OpId,
        typename Result,
        typename Geometry,
        typename OtherGeometry,
        typename PointInArealStrategy
    >
    class uncertain_rings_analyser
    {
        static const bool transpose_result = OpId != 0;
        static const int other_id = (OpId + 1) % 2;

    public:
        inline uncertain_rings_analyser(Result & result,
                                        Geometry const& geom,
                                        OtherGeometry const& other_geom,
                                        PointInArealStrategy const& point_in_areal_strategy)
            : geometry(geom)
            , other_geometry(other_geom)
            , interrupt(result.interrupt) // just in case, could be false as well
            , m_result(result)
            , m_point_in_areal_strategy(point_in_areal_strategy)
            , m_flags(0)
        {
            // check which relations must be analysed
            // NOTE: 1 and 4 could probably be connected

            if ( ! may_update<interior, interior, '2', transpose_result>(m_result) )
            {
                m_flags |= 1;
            }

            if ( ! may_update<interior, exterior, '2', transpose_result>(m_result)
              && ! may_update<boundary, exterior, '1', transpose_result>(m_result) )
            {
                m_flags |= 2;
            }

            if ( ! may_update<boundary, interior, '1', transpose_result>(m_result)
              && ! may_update<exterior, interior, '2', transpose_result>(m_result) )
            {
                m_flags |= 4;
            }
        }

        inline void no_turns(segment_identifier const& seg_id)
        {
            // if those flags are set nothing will change
            if ( m_flags == 7 )
            {
                return;
            }

            typename detail::sub_range_return_type<Geometry const>::type
                range_ref = detail::sub_range(geometry, seg_id);

            if ( boost::empty(range_ref) )
            {
                // TODO: throw an exception?
                return; // ignore
            }
                
            // TODO: possible optimization
            // if the range is an interior ring we may use other IPs generated for this single geometry
            // to know which other single geometries should be checked

            // TODO: optimize! e.g. use spatial index
            // O(N) - running it in a loop gives O(NM)
            using detail::within::point_in_geometry;
            int const pig = point_in_geometry(range::front(range_ref),
                                              other_geometry,
                                              m_point_in_areal_strategy);

            //BOOST_GEOMETRY_ASSERT(pig != 0);
            if ( pig > 0 )
            {
                update<interior, interior, '2', transpose_result>(m_result);
                m_flags |= 1;

                update<boundary, interior, '1', transpose_result>(m_result);
                update<exterior, interior, '2', transpose_result>(m_result);
                m_flags |= 4;
            }
            else
            {
                update<boundary, exterior, '1', transpose_result>(m_result);
                update<interior, exterior, '2', transpose_result>(m_result);
                m_flags |= 2;
            }

// TODO: break if all things are set
// also some of them could be checked outside, before the analysis
// In this case we shouldn't relay just on dummy flags
// Flags should be initialized with proper values
// or the result should be checked directly
// THIS IS ALSO TRUE FOR OTHER ANALYSERS! in L/L and L/A

            interrupt = m_flags == 7 || m_result.interrupt;
        }

        template <typename TurnIt>
        inline void turns(TurnIt first, TurnIt last)
        {
            // if those flags are set nothing will change
            if ( (m_flags & 6) == 6 )
            {
                return;
            }

            bool found_ii = false;
            bool found_uu = false;

            for ( TurnIt it = first ; it != last ; ++it )
            {
                if ( it->operations[0].operation == overlay::operation_intersection 
                  && it->operations[1].operation == overlay::operation_intersection )
                {
                    found_ii = true;
                }
                else if ( it->operations[0].operation == overlay::operation_union 
                       && it->operations[1].operation == overlay::operation_union )
                {
                    found_uu = true;
                }
                else // ignore
                {
                    return; // don't interrupt
                }
            }

            // only i/i was generated for this ring
            if ( found_ii )
            {
                update<interior, interior, '2', transpose_result>(m_result);
                m_flags |= 1;

                //update<boundary, boundary, '0', transpose_result>(m_result);                

                update<boundary, interior, '1', transpose_result>(m_result);
                update<exterior, interior, '2', transpose_result>(m_result);
                m_flags |= 4;
            }

            // only u/u was generated for this ring
            if ( found_uu )
            {
                update<boundary, exterior, '1', transpose_result>(m_result);
                update<interior, exterior, '2', transpose_result>(m_result);
                m_flags |= 2;
            }

            interrupt = m_flags == 7 || m_result.interrupt; // interrupt if the result won't be changed in the future
        }

        Geometry const& geometry;
        OtherGeometry const& other_geometry;
        bool interrupt;

    private:
        Result & m_result;
        PointInArealStrategy const& m_point_in_areal_strategy;
        int m_flags;
    };

    template <std::size_t OpId>
    class analyse_uncertain_rings
    {
    public:
        template <typename Analyser, typename TurnIt>
        static inline void apply(Analyser & analyser, TurnIt first, TurnIt last)
        {
            if ( first == last )
                return;

            for_preceding_rings(analyser, *first);
            //analyser.per_turn(*first);

            TurnIt prev = first;
            for ( ++first ; first != last ; ++first, ++prev )
            {
                // same multi
                if ( prev->operations[OpId].seg_id.multi_index
                  == first->operations[OpId].seg_id.multi_index )
                {
                    // same ring
                    if ( prev->operations[OpId].seg_id.ring_index
                      == first->operations[OpId].seg_id.ring_index )
                    {
                        //analyser.per_turn(*first);
                    }
                    // same multi, next ring
                    else
                    {
                        //analyser.end_ring(*prev);
                        analyser.turns(prev, first);

                        //if ( prev->operations[OpId].seg_id.ring_index + 1
                        //   < first->operations[OpId].seg_id.ring_index)
                        {
                            for_no_turns_rings(analyser,
                                               *first,
                                               prev->operations[OpId].seg_id.ring_index + 1,
                                               first->operations[OpId].seg_id.ring_index);
                        }

                        //analyser.per_turn(*first);
                    }
                }
                // next multi
                else
                {
                    //analyser.end_ring(*prev);
                    analyser.turns(prev, first);
                    for_following_rings(analyser, *prev);
                    for_preceding_rings(analyser, *first);
                    //analyser.per_turn(*first);
                }

                if ( analyser.interrupt )
                {
                    return;
                }
            }

            //analyser.end_ring(*prev);
            analyser.turns(prev, first); // first == last
            for_following_rings(analyser, *prev);
        }

    private:
        template <typename Analyser, typename Turn>
        static inline void for_preceding_rings(Analyser & analyser, Turn const& turn)
        {
            segment_identifier const& seg_id = turn.operations[OpId].seg_id;

            for_no_turns_rings(analyser, turn, -1, seg_id.ring_index);
        }

        template <typename Analyser, typename Turn>
        static inline void for_following_rings(Analyser & analyser, Turn const& turn)
        {
            segment_identifier const& seg_id = turn.operations[OpId].seg_id;

            signed_size_type
                count = boost::numeric_cast<signed_size_type>(
                            geometry::num_interior_rings(
                                detail::single_geometry(analyser.geometry, seg_id)));
            
            for_no_turns_rings(analyser, turn, seg_id.ring_index + 1, count);
        }

        template <typename Analyser, typename Turn>
        static inline void for_no_turns_rings(Analyser & analyser,
                                              Turn const& turn,
                                              signed_size_type first,
                                              signed_size_type last)
        {
            segment_identifier seg_id = turn.operations[OpId].seg_id;

            for ( seg_id.ring_index = first ; seg_id.ring_index < last ; ++seg_id.ring_index )
            {
                analyser.no_turns(seg_id);
            }
        }
    };
};

}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_AREAL_AREAL_HPP

/* areal_areal.hpp
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
*/