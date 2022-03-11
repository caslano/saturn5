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
    
    template <typename Result, typename IntersectionStrategy>
    static inline void apply(Geometry1 const& geometry1, Geometry2 const& geometry2,
                             Result & result,
                             IntersectionStrategy const& intersection_strategy)
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
            >::template turn_info_type<IntersectionStrategy>::type turn_type;
        std::vector<turn_type> turns;

        interrupt_policy_areal_areal<Result> interrupt_policy(geometry1, geometry2, result);

        turns::get_turns<Geometry1, Geometry2>::apply(turns, geometry1, geometry2, interrupt_policy, intersection_strategy);
        if ( BOOST_GEOMETRY_CONDITION(result.interrupt) )
            return;

        typedef typename IntersectionStrategy::cs_tag cs_tag;

        typedef typename IntersectionStrategy::template point_in_geometry_strategy
            <
                Geometry1, Geometry2
            >::type point_in_areal_strategy12_type;
        point_in_areal_strategy12_type point_in_areal_strategy12
            = intersection_strategy.template get_point_in_geometry_strategy<Geometry1, Geometry2>();
        typedef typename IntersectionStrategy::template point_in_geometry_strategy
            <
                Geometry2, Geometry1
            >::type point_in_areal_strategy21_type;
        point_in_areal_strategy21_type point_in_areal_strategy21
            = intersection_strategy.template get_point_in_geometry_strategy<Geometry2, Geometry1>();

        no_turns_aa_pred<Geometry2, Result, point_in_areal_strategy12_type, false>
            pred1(geometry2, result, point_in_areal_strategy12);
        for_each_disjoint_geometry_if<0, Geometry1>::apply(turns.begin(), turns.end(), geometry1, pred1);
        if ( BOOST_GEOMETRY_CONDITION(result.interrupt) )
            return;

        no_turns_aa_pred<Geometry1, Result, point_in_areal_strategy21_type, true>
            pred2(geometry1, result, point_in_areal_strategy21);
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
                analyse_each_turn(result, analyser, turns.begin(), turns.end(),
                                  point_in_areal_strategy12.get_equals_point_point_strategy());

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
                uncertain_rings_analyser<0, Result, Geometry1, Geometry2, point_in_areal_strategy12_type>
                    rings_analyser(result, geometry1, geometry2, point_in_areal_strategy12);
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
                analyse_each_turn(result, analyser, turns.begin(), turns.end(),
                                  point_in_areal_strategy21.get_equals_point_point_strategy());

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
                uncertain_rings_analyser<1, Result, Geometry2, Geometry1, point_in_areal_strategy21_type>
                    rings_analyser(result, geometry2, geometry1, point_in_areal_strategy21);
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