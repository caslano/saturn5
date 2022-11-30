// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013-2021.
// Modifications copyright (c) 2013-2021 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_LINEAR_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_LINEAR_AREAL_HPP

#include <boost/core/ignore_unused.hpp>
#include <boost/range/size.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/topological_dimension.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/range.hpp>
#include <boost/geometry/util/type_traits.hpp>

#include <boost/geometry/algorithms/num_interior_rings.hpp>
#include <boost/geometry/algorithms/detail/point_on_border.hpp>
#include <boost/geometry/algorithms/detail/sub_range.hpp>
#include <boost/geometry/algorithms/detail/single_geometry.hpp>

#include <boost/geometry/algorithms/detail/relate/point_geometry.hpp>
#include <boost/geometry/algorithms/detail/relate/turns.hpp>
#include <boost/geometry/algorithms/detail/relate/boundary_checker.hpp>
#include <boost/geometry/algorithms/detail/relate/follow_helpers.hpp>

#include <boost/geometry/views/detail/closed_clockwise_view.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate {

// WARNING!
// TODO: In the worst case calling this Pred in a loop for MultiLinestring/MultiPolygon may take O(NM)
// Use the rtree in this case!

// may be used to set IE and BE for a Linear geometry for which no turns were generated
template
<
    typename Geometry2,
    typename Result,
    typename PointInArealStrategy,
    typename BoundaryChecker,
    bool TransposeResult
>
class no_turns_la_linestring_pred
{
public:
    no_turns_la_linestring_pred(Geometry2 const& geometry2,
                                Result & res,
                                PointInArealStrategy const& point_in_areal_strategy,
                                BoundaryChecker const& boundary_checker)
        : m_geometry2(geometry2)
        , m_result(res)
        , m_point_in_areal_strategy(point_in_areal_strategy)
        , m_boundary_checker(boundary_checker)
        , m_interrupt_flags(0)
    {
        if ( ! may_update<interior, interior, '1', TransposeResult>(m_result) )
        {
            m_interrupt_flags |= 1;
        }

        if ( ! may_update<interior, exterior, '1', TransposeResult>(m_result) )
        {
            m_interrupt_flags |= 2;
        }

        if ( ! may_update<boundary, interior, '0', TransposeResult>(m_result) )
        {
            m_interrupt_flags |= 4;
        }

        if ( ! may_update<boundary, exterior, '0', TransposeResult>(m_result) )
        {
            m_interrupt_flags |= 8;
        }
    }

    template <typename Linestring>
    bool operator()(Linestring const& linestring)
    {
        std::size_t const count = boost::size(linestring);
        
        // invalid input
        if ( count < 2 )
        {
            // ignore
            // TODO: throw an exception?
            return true;
        }

        // if those flags are set nothing will change
        if ( m_interrupt_flags == 0xF )
        {
            return false;
        }

        int const pig = detail::within::point_in_geometry(range::front(linestring),
                                                          m_geometry2,
                                                          m_point_in_areal_strategy);
        //BOOST_GEOMETRY_ASSERT_MSG(pig != 0, "There should be no IPs");

        if ( pig > 0 )
        {
            update<interior, interior, '1', TransposeResult>(m_result);
            m_interrupt_flags |= 1;
        }
        else
        {
            update<interior, exterior, '1', TransposeResult>(m_result);
            m_interrupt_flags |= 2;
        }

        // check if there is a boundary
        if ( ( m_interrupt_flags & 0xC ) != 0xC // if wasn't already set
          && ( m_boundary_checker.template
                is_endpoint_boundary<boundary_front>(range::front(linestring))
            || m_boundary_checker.template
                is_endpoint_boundary<boundary_back>(range::back(linestring)) ) )
        {
            if ( pig > 0 )
            {
                update<boundary, interior, '0', TransposeResult>(m_result);
                m_interrupt_flags |= 4;
            }
            else
            {
                update<boundary, exterior, '0', TransposeResult>(m_result);
                m_interrupt_flags |= 8;
            }
        }

        return m_interrupt_flags != 0xF
            && ! m_result.interrupt;
    }

private:
    Geometry2 const& m_geometry2;
    Result & m_result;
    PointInArealStrategy const& m_point_in_areal_strategy;
    BoundaryChecker const& m_boundary_checker;
    unsigned m_interrupt_flags;
};

// may be used to set EI and EB for an Areal geometry for which no turns were generated
template <typename Result, bool TransposeResult>
class no_turns_la_areal_pred
{
public:
    no_turns_la_areal_pred(Result & res)
        : m_result(res)
        , interrupt(! may_update<interior, exterior, '2', TransposeResult>(m_result)
                 && ! may_update<boundary, exterior, '1', TransposeResult>(m_result) )
    {}

    template <typename Areal>
    bool operator()(Areal const& areal)
    {
        if ( interrupt )
        {
            return false;
        }

        // TODO:
        // handle empty/invalid geometries in a different way than below?

        typedef typename geometry::point_type<Areal>::type point_type;
        point_type dummy;
        bool const ok = boost::geometry::point_on_border(dummy, areal);

        // TODO: for now ignore, later throw an exception?
        if ( !ok )
        {
            return true;
        }

        update<interior, exterior, '2', TransposeResult>(m_result);
        update<boundary, exterior, '1', TransposeResult>(m_result);
                    
        return false;
    }

private:
    Result & m_result;
    bool const interrupt;
};

// The implementation of an algorithm calculating relate() for L/A
template <typename Geometry1, typename Geometry2, bool TransposeResult = false>
struct linear_areal
{
    // check Linear / Areal
    BOOST_STATIC_ASSERT(topological_dimension<Geometry1>::value == 1
                     && topological_dimension<Geometry2>::value == 2);

    static const bool interruption_enabled = true;

    typedef typename geometry::point_type<Geometry1>::type point1_type;
    typedef typename geometry::point_type<Geometry2>::type point2_type;

    template <typename Geom1, typename Geom2, typename Strategy>
    struct multi_turn_info
        : turns::get_turns<Geom1, Geom2>::template turn_info_type<Strategy>::type
    {
        multi_turn_info() : priority(0) {}
        int priority; // single-geometry sorting priority
    };

    template <typename Geom1, typename Geom2, typename Strategy>
    struct turn_info_type
        : std::conditional
            <
                util::is_multi<Geometry2>::value,
                multi_turn_info<Geom1, Geom2, Strategy>,
                typename turns::get_turns<Geom1, Geom2>::template turn_info_type<Strategy>::type
            >
    {};
    
    template <typename Result, typename Strategy>
    static inline void apply(Geometry1 const& geometry1, Geometry2 const& geometry2,
                             Result & result,
                             Strategy const& strategy)
    {
// TODO: If Areal geometry may have infinite size, change the following line:

        // The result should be FFFFFFFFF
        relate::set<exterior, exterior, result_dimension<Geometry2>::value, TransposeResult>(result);// FFFFFFFFd, d in [1,9] or T

        if ( BOOST_GEOMETRY_CONDITION( result.interrupt ) )
            return;

        // get and analyse turns
        typedef typename turn_info_type<Geometry1, Geometry2, Strategy>::type turn_type;
        std::vector<turn_type> turns;

        interrupt_policy_linear_areal<Geometry2, Result> interrupt_policy(geometry2, result);

        turns::get_turns<Geometry1, Geometry2>::apply(turns, geometry1, geometry2, interrupt_policy, strategy);
        if ( BOOST_GEOMETRY_CONDITION( result.interrupt ) )
            return;

        typedef typename Strategy::cs_tag cs_tag;
        
        typedef boundary_checker
            <
                Geometry1,
                Strategy
            > boundary_checker1_type;
        boundary_checker1_type boundary_checker1(geometry1, strategy);

        no_turns_la_linestring_pred
            <
                Geometry2,
                Result,
                Strategy,
                boundary_checker1_type,
                TransposeResult
            > pred1(geometry2,
                    result,
                    strategy,
                    boundary_checker1);
        for_each_disjoint_geometry_if<0, Geometry1>::apply(turns.begin(), turns.end(), geometry1, pred1);
        if ( BOOST_GEOMETRY_CONDITION( result.interrupt ) )
            return;

        no_turns_la_areal_pred<Result, !TransposeResult> pred2(result);
        for_each_disjoint_geometry_if<1, Geometry2>::apply(turns.begin(), turns.end(), geometry2, pred2);
        if ( BOOST_GEOMETRY_CONDITION( result.interrupt ) )
            return;
        
        if ( turns.empty() )
            return;

        // This is set here because in the case if empty Areal geometry were passed
        // those shouldn't be set
        relate::set<exterior, interior, '2', TransposeResult>(result);// FFFFFF2Fd
        if ( BOOST_GEOMETRY_CONDITION( result.interrupt ) )
            return;

        {
            sort_dispatch<cs_tag>(turns.begin(), turns.end(), util::is_multi<Geometry2>());

            turns_analyser<turn_type> analyser;
            analyse_each_turn(result, analyser,
                              turns.begin(), turns.end(),
                              geometry1, geometry2,
                              boundary_checker1,
                              strategy);

            if ( BOOST_GEOMETRY_CONDITION( result.interrupt ) )
                return;
        }

        // If 'c' (insersection_boundary) was not found we know that any Ls isn't equal to one of the Rings
        if ( !interrupt_policy.is_boundary_found )
        {
            relate::set<exterior, boundary, '1', TransposeResult>(result);
        }
        // Don't calculate it if it's required
        else if ( may_update<exterior, boundary, '1', TransposeResult>(result) )
        {
// TODO: REVISE THIS CODE AND PROBABLY REWRITE SOME PARTS TO BE MORE HUMAN-READABLE
//       IN GENERAL IT ANALYSES THE RINGS OF AREAL GEOMETRY AND DETECTS THE ONES THAT
//       MAY OVERLAP THE INTERIOR OF LINEAR GEOMETRY (NO IPs OR NON-FAKE 'u' OPERATION)
// NOTE: For one case std::sort may be called again to sort data by operations for data already sorted by ring index
//       In the worst case scenario the complexity will be O( NlogN + R*(N/R)log(N/R) )
//       So always should remain O(NlogN) -> for R==1 <-> 1(N/1)log(N/1), for R==N <-> N(N/N)log(N/N)
//       Some benchmarking should probably be done to check if only one std::sort should be used

            // sort by multi_index and rind_index
            std::sort(turns.begin(), turns.end(), less_ring());

            typedef typename std::vector<turn_type>::iterator turn_iterator;

            turn_iterator it = turns.begin();
            segment_identifier * prev_seg_id_ptr = NULL;
            // for each ring
            for ( ; it != turns.end() ; )
            {
                // it's the next single geometry
                if ( prev_seg_id_ptr == NULL
                  || prev_seg_id_ptr->multi_index != it->operations[1].seg_id.multi_index )
                {
                    // if the first ring has no IPs
                    if ( it->operations[1].seg_id.ring_index > -1 )
                    {
                        // we can be sure that the exterior overlaps the boundary
                        relate::set<exterior, boundary, '1', TransposeResult>(result);                    
                        break;
                    }
                    // if there was some previous ring
                    if ( prev_seg_id_ptr != NULL )
                    {
                        signed_size_type const next_ring_index = prev_seg_id_ptr->ring_index + 1;
                        BOOST_GEOMETRY_ASSERT(next_ring_index >= 0);
                        
                        // if one of the last rings of previous single geometry was ommited
                        if ( static_cast<std::size_t>(next_ring_index)
                                < geometry::num_interior_rings(
                                    single_geometry(geometry2, *prev_seg_id_ptr)) )
                        {
                            // we can be sure that the exterior overlaps the boundary
                            relate::set<exterior, boundary, '1', TransposeResult>(result);
                            break;
                        }
                    }
                }
                // if it's the same single geometry
                else /*if ( previous_multi_index == it->operations[1].seg_id.multi_index )*/
                {
                    // and we jumped over one of the rings
                    if ( prev_seg_id_ptr != NULL // just in case
                      && prev_seg_id_ptr->ring_index + 1 < it->operations[1].seg_id.ring_index )
                    {
                        // we can be sure that the exterior overlaps the boundary
                        relate::set<exterior, boundary, '1', TransposeResult>(result);                    
                        break;
                    }
                }

                prev_seg_id_ptr = boost::addressof(it->operations[1].seg_id);

                // find the next ring first iterator and check if the analysis should be performed
                has_boundary_intersection has_boundary_inters;
                turn_iterator next = find_next_ring(it, turns.end(), has_boundary_inters);

                // if there is no 1d overlap with the boundary
                if ( !has_boundary_inters.result )
                {
                    // we can be sure that the exterior overlaps the boundary
                    relate::set<exterior, boundary, '1', TransposeResult>(result);                    
                    break;
                }
                // else there is 1d overlap with the boundary so we must analyse the boundary
                else
                {
                    // u, c
                    typedef turns::less<1, turns::less_op_areal_linear<1>, cs_tag> less;
                    std::sort(it, next, less());

                    // analyse
                    areal_boundary_analyser<turn_type> analyser;
                    for ( turn_iterator rit = it ; rit != next ; ++rit )
                    {
                        // if the analyser requests, break the search
                        if ( !analyser.apply(it, rit, next, strategy) )
                            break;
                    }

                    // if the boundary of Areal goes out of the Linear
                    if ( analyser.is_union_detected )
                    {
                        // we can be sure that the boundary of Areal overlaps the exterior of Linear
                        relate::set<exterior, boundary, '1', TransposeResult>(result);
                        break;
                    }
                }

                it = next;
            }

            // if there was some previous ring
            if ( prev_seg_id_ptr != NULL )
            {
                signed_size_type const next_ring_index = prev_seg_id_ptr->ring_index + 1;
                BOOST_GEOMETRY_ASSERT(next_ring_index >= 0);

                // if one of the last rings of previous single geometry was ommited
                if ( static_cast<std::size_t>(next_ring_index)
                        < geometry::num_interior_rings(
                            single_geometry(geometry2, *prev_seg_id_ptr)) )
                {
                    // we can be sure that the exterior overlaps the boundary
                    relate::set<exterior, boundary, '1', TransposeResult>(result);
                }
            }
        }
    }

    template <typename It, typename Pred, typename Comp>
    static void for_each_equal_range(It first, It last, Pred pred, Comp comp)
    {
        if ( first == last )
            return;

        It first_equal = first;
        It prev = first;
        for ( ++first ; ; ++first, ++prev )
        {
            if ( first == last || !comp(*prev, *first) )
            {
                pred(first_equal, first);
                first_equal = first;
            }
            
            if ( first == last )
                break;
        }
    }

    struct same_ip
    {
        template <typename Turn>
        bool operator()(Turn const& left, Turn const& right) const
        {
            return left.operations[0].seg_id == right.operations[0].seg_id
                && left.operations[0].fraction == right.operations[0].fraction;
        }
    };

    struct same_ip_and_multi_index
    {
        template <typename Turn>
        bool operator()(Turn const& left, Turn const& right) const
        {
            return same_ip()(left, right)
                && left.operations[1].seg_id.multi_index == right.operations[1].seg_id.multi_index;
        }
    };

    template <typename OpToPriority>
    struct set_turns_group_priority
    {
        template <typename TurnIt>
        void operator()(TurnIt first, TurnIt last) const
        {
            BOOST_GEOMETRY_ASSERT(first != last);
            static OpToPriority op_to_priority;
            // find the operation with the least priority
            int least_priority = op_to_priority(first->operations[0]);
            for ( TurnIt it = first + 1 ; it != last ; ++it )
            {
                int priority = op_to_priority(it->operations[0]);
                if ( priority < least_priority )
                    least_priority = priority;
            }
            // set the least priority for all turns of the group
            for ( TurnIt it = first ; it != last ; ++it )
            {
                it->priority = least_priority;
            }
        }
    };

    template <typename SingleLess>
    struct sort_turns_group
    {
        struct less
        {
            template <typename Turn>
            bool operator()(Turn const& left, Turn const& right) const
            {
                return left.operations[1].seg_id.multi_index == right.operations[1].seg_id.multi_index ?
                    SingleLess()(left, right) :
                    left.priority < right.priority;
            }
        };

        template <typename TurnIt>
        void operator()(TurnIt first, TurnIt last) const
        {
            std::sort(first, last, less());
        }
    };

    template <typename CSTag, typename TurnIt>
    static void sort_dispatch(TurnIt first, TurnIt last, std::true_type const& /*is_multi*/)
    {
        // sort turns by Linear seg_id, then by fraction, then by other multi_index
        typedef turns::less<0, turns::less_other_multi_index<0>, CSTag> less;
        std::sort(first, last, less());

        // For the same IP and multi_index - the same other's single geometry
        // set priorities as the least operation found for the whole single geometry
        // so e.g. single geometries containing 'u' will always be before those only containing 'i'
        typedef turns::op_to_int<0,2,3,1,4,0> op_to_int_xuic;
        for_each_equal_range(first, last,
                             set_turns_group_priority<op_to_int_xuic>(), // least operation in xuic order
                             same_ip_and_multi_index()); // other's multi_index

        // When priorities for single geometries are set now sort turns for the same IP
        // if multi_index is the same sort them according to the single-less
        // else use priority of the whole single-geometry set earlier
        typedef turns::less<0, turns::less_op_linear_areal_single<0>, CSTag> single_less;
        for_each_equal_range(first, last,
                             sort_turns_group<single_less>(),
                             same_ip());
    }

    template <typename CSTag, typename TurnIt>
    static void sort_dispatch(TurnIt first, TurnIt last, std::false_type const& /*is_multi*/)
    {
        // sort turns by Linear seg_id, then by fraction, then
        // for same ring id: x, u, i, c
        // for different ring id: c, i, u, x
        typedef turns::less<0, turns::less_op_linear_areal_single<0>, CSTag> less;
        std::sort(first, last, less());
    }
    

    // interrupt policy which may be passed to get_turns to interrupt the analysis
    // based on the info in the passed result/mask
    template <typename Areal, typename Result>
    class interrupt_policy_linear_areal
    {
    public:
        static bool const enabled = true;

        interrupt_policy_linear_areal(Areal const& areal, Result & result)
            : m_result(result), m_areal(areal)
            , is_boundary_found(false)
        {}

// TODO: since we update result for some operations here, we may not do it in the analyser!

        template <typename Range>
        inline bool apply(Range const& turns)
        {
            typedef typename boost::range_iterator<Range const>::type iterator;
            
            for (iterator it = boost::begin(turns) ; it != boost::end(turns) ; ++it)
            {
                if ( it->operations[0].operation == overlay::operation_intersection )
                {
                    bool const no_interior_rings
                        = geometry::num_interior_rings(
                                single_geometry(m_areal, it->operations[1].seg_id)) == 0;

                    // WARNING! THIS IS TRUE ONLY IF THE POLYGON IS SIMPLE!
                    // OR WITHOUT INTERIOR RINGS (AND OF COURSE VALID)
                    if ( no_interior_rings )
                        update<interior, interior, '1', TransposeResult>(m_result);
                }
                else if ( it->operations[0].operation == overlay::operation_continue )
                {
                    update<interior, boundary, '1', TransposeResult>(m_result);
                    is_boundary_found = true;
                }
                else if ( ( it->operations[0].operation == overlay::operation_union
                         || it->operations[0].operation == overlay::operation_blocked )
                       && it->operations[0].position == overlay::position_middle )
                {
// TODO: here we could also check the boundaries and set BB at this point
                    update<interior, boundary, '0', TransposeResult>(m_result);
                }
            }

            return m_result.interrupt;
        }

    private:
        Result & m_result;
        Areal const& m_areal;

    public:
        bool is_boundary_found;
    };

    // This analyser should be used like Input or SinglePass Iterator
    // IMPORTANT! It should be called also for the end iterator - last
    template <typename TurnInfo>
    class turns_analyser
    {
        typedef typename TurnInfo::point_type turn_point_type;

        static const std::size_t op_id = 0;
        static const std::size_t other_op_id = 1;

        template <typename TurnPointCSTag, typename PointP, typename PointQ,
                  typename Strategy,
                  typename Pi = PointP, typename Pj = PointP, typename Pk = PointP,
                  typename Qi = PointQ, typename Qj = PointQ, typename Qk = PointQ
        >
        struct la_side_calculator
        {
            typedef decltype(std::declval<Strategy>().side()) side_strategy_type;

            inline la_side_calculator(Pi const& pi, Pj const& pj, Pk const& pk,
                                      Qi const& qi, Qj const& qj, Qk const& qk,
                                      Strategy const& strategy)
                : m_pi(pi), m_pj(pj), m_pk(pk)
                , m_qi(qi), m_qj(qj), m_qk(qk)
                , m_side_strategy(strategy.side())
            {}

            inline int pk_wrt_p1() const { return m_side_strategy.apply(m_pi, m_pj, m_pk); }
            inline int qk_wrt_p1() const { return m_side_strategy.apply(m_pi, m_pj, m_qk); }
            inline int pk_wrt_q2() const { return m_side_strategy.apply(m_qj, m_qk, m_pk); }

         private :
            Pi const& m_pi;
            Pj const& m_pj;
            Pk const& m_pk;
            Qi const& m_qi;
            Qj const& m_qj;
            Qk const& m_qk;

            side_strategy_type m_side_strategy;
        };


    public:
        turns_analyser()
            : m_previous_turn_ptr(NULL)
            , m_previous_operation(overlay::operation_none)
            , m_boundary_counter(0)
            , m_interior_detected(false)
            , m_first_interior_other_id_ptr(NULL)
            , m_first_from_unknown(false)
            , m_first_from_unknown_boundary_detected(false)
        {}

        template <typename Result,
                  typename TurnIt,
                  typename Geometry,
                  typename OtherGeometry,
                  typename BoundaryChecker,
                  typename Strategy>
        void apply(Result & res, TurnIt it,
                   Geometry const& geometry,
                   OtherGeometry const& other_geometry,
                   BoundaryChecker const& boundary_checker,
                   Strategy const& strategy)
        {
            overlay::operation_type op = it->operations[op_id].operation;

            if ( op != overlay::operation_union
              && op != overlay::operation_intersection
              && op != overlay::operation_blocked
              && op != overlay::operation_continue ) // operation_boundary / operation_boundary_intersection
            {
                return;
            }

            segment_identifier const& seg_id = it->operations[op_id].seg_id;
            segment_identifier const& other_id = it->operations[other_op_id].seg_id;

            const bool first_in_range = m_seg_watcher.update(seg_id);

            // TODO: should apply() for the post-last ip be called if first_in_range ?
            // this would unify how last points in ranges are handled
            // possibly replacing parts of the code below
            // e.g. for is_multi and m_interior_detected

            // handle possible exit
            bool fake_enter_detected = false;
            if ( m_exit_watcher.get_exit_operation() == overlay::operation_union )
            {
                // real exit point - may be multiple
                // we know that we entered and now we exit
                if ( ! turn_on_the_same_ip<op_id>(m_exit_watcher.get_exit_turn(), *it,
                                                  strategy) )
                {
                    m_exit_watcher.reset_detected_exit();
                    
                    update<interior, exterior, '1', TransposeResult>(res);

                    // next single geometry
                    if ( first_in_range && m_previous_turn_ptr )
                    {
                        // NOTE: similar code is in the post-last-ip-apply()
                        segment_identifier const& prev_seg_id = m_previous_turn_ptr->operations[op_id].seg_id;

                        bool const prev_back_b = is_endpoint_on_boundary<boundary_back>(
                                                    range::back(sub_range(geometry, prev_seg_id)),
                                                    boundary_checker);

                        // if there is a boundary on the last point
                        if ( prev_back_b )
                        {
                            update<boundary, exterior, '0', TransposeResult>(res);
                        }
                    }
                }
                // fake exit point, reset state
                else if ( op == overlay::operation_intersection
                        || op == overlay::operation_continue ) // operation_boundary
                {
                    m_exit_watcher.reset_detected_exit();
                    fake_enter_detected = true;
                }
            }
            else if ( m_exit_watcher.get_exit_operation() == overlay::operation_blocked )
            {
                // ignore multiple BLOCKs for this same single geometry1
                if ( op == overlay::operation_blocked
                  && seg_id.multi_index == m_previous_turn_ptr->operations[op_id].seg_id.multi_index )
                {
                    return;
                }

                if ( ( op == overlay::operation_intersection
                    || op == overlay::operation_continue )
                  && turn_on_the_same_ip<op_id>(m_exit_watcher.get_exit_turn(), *it,
                                                strategy) )
                {
                    fake_enter_detected = true;
                }

                m_exit_watcher.reset_detected_exit();
            }

            if ( BOOST_GEOMETRY_CONDITION( util::is_multi<OtherGeometry>::value )
              && m_first_from_unknown )
            {
                // For MultiPolygon many x/u operations may be generated as a first IP
                // if for all turns x/u was generated and any of the Polygons doesn't contain the LineString
                // then we know that the LineString is outside
                // Similar with the u/u turns, if it was the first one it doesn't mean that the
                // Linestring came from the exterior
                if ( ( m_previous_operation == overlay::operation_blocked
                    && ( op != overlay::operation_blocked // operation different than block
                        || seg_id.multi_index != m_previous_turn_ptr->operations[op_id].seg_id.multi_index ) ) // or the next single-geometry
                  || ( m_previous_operation == overlay::operation_union
                    && ! turn_on_the_same_ip<op_id>(*m_previous_turn_ptr, *it,
                                                    strategy) )
                   )
                {
                    update<interior, exterior, '1', TransposeResult>(res);
                    if ( m_first_from_unknown_boundary_detected )
                    {
                        update<boundary, exterior, '0', TransposeResult>(res);
                    }

                    m_first_from_unknown = false;
                    m_first_from_unknown_boundary_detected = false;
                }
            }

// NOTE: THE WHOLE m_interior_detected HANDLING IS HERE BECAUSE WE CAN'T EFFICIENTLY SORT TURNS (CORRECTLY)
// BECAUSE THE SAME IP MAY BE REPRESENTED BY TWO SEGMENTS WITH DIFFERENT DISTANCES
// IT WOULD REQUIRE THE CALCULATION OF MAX DISTANCE
// TODO: WE COULD GET RID OF THE TEST IF THE DISTANCES WERE NORMALIZED

// UPDATE: THEY SHOULD BE NORMALIZED NOW

// TODO: THIS IS POTENTIALLY ERROREOUS!
// THIS ALGORITHM DEPENDS ON SOME SPECIFIC SEQUENCE OF OPERATIONS
// IT WOULD GIVE WRONG RESULTS E.G.
// IN THE CASE OF SELF-TOUCHING POINT WHEN 'i' WOULD BE BEFORE 'u' 

            // handle the interior overlap
            if ( m_interior_detected )
            {
                BOOST_GEOMETRY_ASSERT_MSG(m_previous_turn_ptr, "non-NULL ptr expected");

                // real interior overlap
                if ( ! turn_on_the_same_ip<op_id>(*m_previous_turn_ptr, *it,
                                                  strategy) )
                {
                    update<interior, interior, '1', TransposeResult>(res);
                    m_interior_detected = false;

                    // new range detected - reset previous state and check the boundary
                    if ( first_in_range )
                    {
                        segment_identifier const& prev_seg_id = m_previous_turn_ptr->operations[op_id].seg_id;

                        bool const prev_back_b = is_endpoint_on_boundary<boundary_back>(
                                                    range::back(sub_range(geometry, prev_seg_id)),
                                                    boundary_checker);

                        // if there is a boundary on the last point
                        if ( prev_back_b )
                        {
                            update<boundary, interior, '0', TransposeResult>(res);
                        }

                        // The exit_watcher is reset below
                        // m_exit_watcher.reset();
                    }
                }
                // fake interior overlap
                else if ( op == overlay::operation_continue )
                {
                    m_interior_detected = false;
                }
                else if ( op == overlay::operation_union )
                {
// TODO: this probably is not a good way of handling the interiors/enters
//       the solution similar to exit_watcher would be more robust
//       all enters should be kept and handled.
//       maybe integrate it with the exit_watcher -> enter_exit_watcher
                    if ( m_first_interior_other_id_ptr
                      && m_first_interior_other_id_ptr->multi_index == other_id.multi_index )
                    {
                        m_interior_detected = false;
                    }
                }
            }

            // NOTE: If post-last-ip apply() was called this wouldn't be needed
            if ( first_in_range )
            {
                m_exit_watcher.reset();
                m_boundary_counter = 0;
                m_first_from_unknown = false;
                m_first_from_unknown_boundary_detected = false;
            }

            // i/u, c/u
            if ( op == overlay::operation_intersection
              || op == overlay::operation_continue ) // operation_boundary/operation_boundary_intersection
            {
                bool const first_point = first_in_range || m_first_from_unknown;
                bool no_enters_detected = m_exit_watcher.is_outside();
                m_exit_watcher.enter(*it);

                if ( op == overlay::operation_intersection )
                {
                    if ( m_boundary_counter > 0 && it->operations[op_id].is_collinear )
                        --m_boundary_counter;

                    if ( m_boundary_counter == 0 )
                    {
                        // interiors overlaps
                        //update<interior, interior, '1', TransposeResult>(res);

// TODO: think about the implementation of the more robust version
//       this way only the first enter will be handled
                        if ( !m_interior_detected )
                        {
                            // don't update now
                            // we might enter a boundary of some other ring on the same IP
                            m_interior_detected = true;
                            m_first_interior_other_id_ptr = boost::addressof(other_id);
                        }
                    }
                }
                else // operation_boundary
                {
                    // don't add to the count for all met boundaries
                    // only if this is the "new" boundary
                    if ( first_point || !it->operations[op_id].is_collinear )
                        ++m_boundary_counter;

                    update<interior, boundary, '1', TransposeResult>(res);
                }

                bool const this_b
                    = is_ip_on_boundary<boundary_front>(it->point,
                                                        it->operations[op_id],
                                                        boundary_checker,
                                                        seg_id);
                // going inside on boundary point
                if ( this_b )
                {
                    update<boundary, boundary, '0', TransposeResult>(res);
                }
                // going inside on non-boundary point
                else
                {
                    update<interior, boundary, '0', TransposeResult>(res);

                    // if we didn't enter in the past, we were outside
                    if ( no_enters_detected
                      && ! fake_enter_detected
                      && it->operations[op_id].position != overlay::position_front )
                    {
// TODO: calculate_from_inside() is only needed if the current Linestring is not closed
                        bool const from_inside = first_point
                                              && calculate_from_inside(geometry,
                                                                       other_geometry,
                                                                       *it,
                                                                       strategy);

                        if ( from_inside )
                            update<interior, interior, '1', TransposeResult>(res);
                        else
                            update<interior, exterior, '1', TransposeResult>(res);

                        // if it's the first IP then the first point is outside
                        if ( first_point )
                        {
                            bool const front_b = is_endpoint_on_boundary<boundary_front>(
                                                    range::front(sub_range(geometry, seg_id)),
                                                    boundary_checker);

                            // if there is a boundary on the first point
                            if ( front_b )
                            {
                                if ( from_inside )
                                    update<boundary, interior, '0', TransposeResult>(res);
                                else
                                    update<boundary, exterior, '0', TransposeResult>(res);
                            }
                        }
                    }
                }

                if ( BOOST_GEOMETRY_CONDITION( util::is_multi<OtherGeometry>::value ) )
                {
                    m_first_from_unknown = false;
                    m_first_from_unknown_boundary_detected = false;
                }
            }
            // u/u, x/u
            else if ( op == overlay::operation_union || op == overlay::operation_blocked )
            {
                bool const op_blocked = op == overlay::operation_blocked;
                bool const no_enters_detected = m_exit_watcher.is_outside()
// TODO: is this condition ok?
// TODO: move it into the exit_watcher?
                    && m_exit_watcher.get_exit_operation() == overlay::operation_none;
                    
                if ( op == overlay::operation_union )
                {
                    if ( m_boundary_counter > 0 && it->operations[op_id].is_collinear )
                        --m_boundary_counter;
                }
                else // overlay::operation_blocked
                {
                    m_boundary_counter = 0;
                }

                // we're inside, possibly going out right now
                if ( ! no_enters_detected )
                {
                    if ( op_blocked
                      && it->operations[op_id].position == overlay::position_back ) // ignore spikes!
                    {
                        // check if this is indeed the boundary point
                        // NOTE: is_ip_on_boundary<>() should be called here but the result will be the same
                        if ( is_endpoint_on_boundary<boundary_back>(it->point, boundary_checker) )
                        {
                            update<boundary, boundary, '0', TransposeResult>(res);
                        }
                    }
                    // union, inside, but no exit -> collinear on self-intersection point
                    // not needed since we're already inside the boundary
                    /*else if ( !exit_detected )
                    {
                        update<interior, boundary, '0', TransposeResult>(res);
                    }*/
                }
                // we're outside or inside and this is the first turn
                else
                {
                    bool const this_b = is_ip_on_boundary<boundary_any>(it->point,
                                                                        it->operations[op_id],
                                                                        boundary_checker,
                                                                        seg_id);
                    // if current IP is on boundary of the geometry
                    if ( this_b )
                    {
                        update<boundary, boundary, '0', TransposeResult>(res);
                    }
                    // if current IP is not on boundary of the geometry
                    else
                    {
                        update<interior, boundary, '0', TransposeResult>(res);
                    }

                    // TODO: very similar code is used in the handling of intersection
                    if ( it->operations[op_id].position != overlay::position_front )
                    {
// TODO: calculate_from_inside() is only needed if the current Linestring is not closed
                        // NOTE: this is not enough for MultiPolygon and operation_blocked
                        // For LS/MultiPolygon multiple x/u turns may be generated
                        // the first checked Polygon may be the one which LS is outside for.
                        bool const first_point = first_in_range || m_first_from_unknown;
                        bool const first_from_inside = first_point
                                                    && calculate_from_inside(geometry,
                                                                             other_geometry,
                                                                             *it,
                                                                             strategy);
                        if ( first_from_inside )
                        {
                            update<interior, interior, '1', TransposeResult>(res);

                            // notify the exit_watcher that we started inside
                            m_exit_watcher.enter(*it);
                            // and reset unknown flags since we know that we started inside
                            m_first_from_unknown = false;
                            m_first_from_unknown_boundary_detected = false;
                        }
                        else
                        {
                            if ( BOOST_GEOMETRY_CONDITION( util::is_multi<OtherGeometry>::value )
                              /*&& ( op == overlay::operation_blocked
                                || op == overlay::operation_union )*/ ) // if we're here it's u or x
                            {
                                m_first_from_unknown = true;
                            }
                            else
                            {
                                update<interior, exterior, '1', TransposeResult>(res);
                            }
                        }

                        // first IP on the last segment point - this means that the first point is outside or inside
                        if ( first_point && ( !this_b || op_blocked ) )
                        {
                            bool const front_b = is_endpoint_on_boundary<boundary_front>(
                                                    range::front(sub_range(geometry, seg_id)),
                                                    boundary_checker);

                            // if there is a boundary on the first point
                            if ( front_b )
                            {
                                if ( first_from_inside )
                                {
                                    update<boundary, interior, '0', TransposeResult>(res);
                                }
                                else
                                {
                                    if ( BOOST_GEOMETRY_CONDITION( util::is_multi<OtherGeometry>::value )
                                      /*&& ( op == overlay::operation_blocked
                                        || op == overlay::operation_union )*/ ) // if we're here it's u or x
                                    {
                                        BOOST_GEOMETRY_ASSERT(m_first_from_unknown);
                                        m_first_from_unknown_boundary_detected = true;
                                    }
                                    else
                                    {
                                        update<boundary, exterior, '0', TransposeResult>(res);
                                    }
                                }
                            }
                        }
                    }
                }

                // if we're going along a boundary, we exit only if the linestring was collinear
                if ( m_boundary_counter == 0
                  || it->operations[op_id].is_collinear )
                {
                    // notify the exit watcher about the possible exit
                    m_exit_watcher.exit(*it);
                }
            }

            // store ref to previously analysed (valid) turn
            m_previous_turn_ptr = boost::addressof(*it);
            // and previously analysed (valid) operation
            m_previous_operation = op;
        }

        // it == last
        template <typename Result,
                  typename TurnIt,
                  typename Geometry,
                  typename OtherGeometry,
                  typename BoundaryChecker>
        void apply(Result & res,
                   TurnIt first, TurnIt last,
                   Geometry const& geometry,
                   OtherGeometry const& /*other_geometry*/,
                   BoundaryChecker const& boundary_checker)
        {
            boost::ignore_unused(first, last);
            //BOOST_GEOMETRY_ASSERT( first != last );

            // For MultiPolygon many x/u operations may be generated as a first IP
            // if for all turns x/u was generated and any of the Polygons doesn't contain the LineString
            // then we know that the LineString is outside
            if ( BOOST_GEOMETRY_CONDITION( util::is_multi<OtherGeometry>::value )
              && m_first_from_unknown )
            {
                update<interior, exterior, '1', TransposeResult>(res);
                if ( m_first_from_unknown_boundary_detected )
                {
                    update<boundary, exterior, '0', TransposeResult>(res);
                }

                // done below
                //m_first_from_unknown = false;
                //m_first_from_unknown_boundary_detected = false;
            }

            // here, the possible exit is the real one
            // we know that we entered and now we exit
            if ( /*m_exit_watcher.get_exit_operation() == overlay::operation_union // THIS CHECK IS REDUNDANT
                ||*/ m_previous_operation == overlay::operation_union
                && !m_interior_detected )
            {
                // for sure
                update<interior, exterior, '1', TransposeResult>(res);

                BOOST_GEOMETRY_ASSERT(first != last);
                BOOST_GEOMETRY_ASSERT(m_previous_turn_ptr);

                segment_identifier const& prev_seg_id = m_previous_turn_ptr->operations[op_id].seg_id;

                bool const prev_back_b = is_endpoint_on_boundary<boundary_back>(
                                            range::back(sub_range(geometry, prev_seg_id)),
                                            boundary_checker);

                // if there is a boundary on the last point
                if ( prev_back_b )
                {
                    update<boundary, exterior, '0', TransposeResult>(res);
                }
            }
            // we might enter some Areal and didn't go out,
            else if ( m_previous_operation == overlay::operation_intersection
                   || m_interior_detected )
            {
                // just in case
                update<interior, interior, '1', TransposeResult>(res);
                m_interior_detected = false;

                BOOST_GEOMETRY_ASSERT(first != last);
                BOOST_GEOMETRY_ASSERT(m_previous_turn_ptr);

                segment_identifier const& prev_seg_id = m_previous_turn_ptr->operations[op_id].seg_id;

                bool const prev_back_b = is_endpoint_on_boundary<boundary_back>(
                                            range::back(sub_range(geometry, prev_seg_id)),
                                            boundary_checker);

                // if there is a boundary on the last point
                if ( prev_back_b )
                {
                    update<boundary, interior, '0', TransposeResult>(res);
                }
            }

            // This condition may be false if the Linestring is lying on the Polygon's collinear spike
            // if Polygon's spikes are not handled in get_turns() or relate() (they currently aren't)
            //BOOST_GEOMETRY_ASSERT_MSG(m_previous_operation != overlay::operation_continue,
            //                    "Unexpected operation! Probably the error in get_turns(L,A) or relate(L,A)");
            // Currently one c/c turn is generated for the exit
            //   when a Linestring is going out on a collinear spike
            // When a Linestring is going in on a collinear spike
            //   the turn is not generated for the entry
            // So assume it's the former
            if ( m_previous_operation == overlay::operation_continue )
            {
                update<interior, exterior, '1', TransposeResult>(res);

                segment_identifier const& prev_seg_id = m_previous_turn_ptr->operations[op_id].seg_id;

                bool const prev_back_b = is_endpoint_on_boundary<boundary_back>(
                                            range::back(sub_range(geometry, prev_seg_id)),
                                            boundary_checker);

                // if there is a boundary on the last point
                if ( prev_back_b )
                {
                    update<boundary, exterior, '0', TransposeResult>(res);
                }
            }

            // Reset exit watcher before the analysis of the next Linestring
            m_exit_watcher.reset();
            m_boundary_counter = 0;
            m_first_from_unknown = false;
            m_first_from_unknown_boundary_detected = false;
        }

        // check if the passed turn's segment of Linear geometry arrived
        // from the inside or the outside of the Areal geometry
        template <typename Turn, typename Strategy>
        static inline bool calculate_from_inside(Geometry1 const& geometry1,
                                                 Geometry2 const& geometry2,
                                                 Turn const& turn,
                                                 Strategy const& strategy)
        {
            typedef typename cs_tag<typename Turn::point_type>::type cs_tag;

            if ( turn.operations[op_id].position == overlay::position_front )
                return false;

            typename sub_range_return_type<Geometry1 const>::type
                range1 = sub_range(geometry1, turn.operations[op_id].seg_id);
            
            using range2_view = detail::closed_clockwise_view<typename ring_type<Geometry2>::type const>;
            using range2_iterator = typename boost::range_iterator<range2_view const>::type;
            range2_view const range2(sub_range(geometry2, turn.operations[other_op_id].seg_id));
            
            BOOST_GEOMETRY_ASSERT(boost::size(range1));
            std::size_t const s2 = boost::size(range2);
            BOOST_GEOMETRY_ASSERT(s2 > 2);
            std::size_t const seg_count2 = s2 - 1;

            std::size_t const p_seg_ij = static_cast<std::size_t>(turn.operations[op_id].seg_id.segment_index);
            std::size_t const q_seg_ij = static_cast<std::size_t>(turn.operations[other_op_id].seg_id.segment_index);

            BOOST_GEOMETRY_ASSERT(p_seg_ij + 1 < boost::size(range1));
            BOOST_GEOMETRY_ASSERT(q_seg_ij + 1 < s2);

            point1_type const& pi = range::at(range1, p_seg_ij);
            point2_type const& qi = range::at(range2, q_seg_ij);
            point2_type const& qj = range::at(range2, q_seg_ij + 1);
            point1_type qi_conv;
            geometry::convert(qi, qi_conv);
            bool const is_ip_qj = equals::equals_point_point(turn.point, qj, strategy);
// TODO: test this!
//            BOOST_GEOMETRY_ASSERT(!equals::equals_point_point(turn.point, pi));
//            BOOST_GEOMETRY_ASSERT(!equals::equals_point_point(turn.point, qi));
            point1_type new_pj;
            geometry::convert(turn.point, new_pj);

            if ( is_ip_qj )
            {
                std::size_t const q_seg_jk = (q_seg_ij + 1) % seg_count2;
// TODO: the following function should return immediately, however the worst case complexity is O(N)
// It would be good to replace it with some O(1) mechanism
                range2_iterator qk_it = find_next_non_duplicated(boost::begin(range2),
                                                                 range::pos(range2, q_seg_jk),
                                                                 boost::end(range2),
                                                                 strategy);

                // Will this sequence of points be always correct?
                la_side_calculator<cs_tag, point1_type, point2_type, Strategy>
                    side_calc(qi_conv, new_pj, pi, qi, qj, *qk_it, strategy);

                return calculate_from_inside_sides(side_calc);
            }
            else
            {
                point2_type new_qj;
                geometry::convert(turn.point, new_qj);

                la_side_calculator<cs_tag, point1_type, point2_type, Strategy>
                    side_calc(qi_conv, new_pj, pi, qi, new_qj, qj, strategy);

                return calculate_from_inside_sides(side_calc);
            }
        }

        template <typename It, typename Strategy>
        static inline It find_next_non_duplicated(It first, It current, It last,
                                                  Strategy const& strategy)
        {
            BOOST_GEOMETRY_ASSERT( current != last );

            It it = current;

            for ( ++it ; it != last ; ++it )
            {
                if ( !equals::equals_point_point(*current, *it, strategy) )
                    return it;
            }

            // if not found start from the beginning
            for ( it = first ; it != current ; ++it )
            {
                if ( !equals::equals_point_point(*current, *it, strategy) )
                    return it;
            }

            return current;
        }

        // calculate inside or outside based on side_calc
        // this is simplified version of a check from equal<>
        template <typename SideCalc>
        static inline bool calculate_from_inside_sides(SideCalc const& side_calc)
        {
            int const side_pk_p = side_calc.pk_wrt_p1();
            int const side_qk_p = side_calc.qk_wrt_p1();
            // If they turn to same side (not opposite sides)
            if (! overlay::base_turn_handler::opposite(side_pk_p, side_qk_p))
            {
                int const side_pk_q2 = side_calc.pk_wrt_q2();
                return side_pk_q2 == -1;
            }
            else
            {
                return side_pk_p == -1;
            }
        }

    private:
        exit_watcher<TurnInfo, op_id> m_exit_watcher;
        segment_watcher<same_single> m_seg_watcher;
        TurnInfo * m_previous_turn_ptr;
        overlay::operation_type m_previous_operation;
        unsigned m_boundary_counter;
        bool m_interior_detected;
        const segment_identifier * m_first_interior_other_id_ptr;
        bool m_first_from_unknown;
        bool m_first_from_unknown_boundary_detected;
    };

    // call analyser.apply() for each turn in range
    // IMPORTANT! The analyser is also called for the end iterator - last
    template <typename Result,
              typename TurnIt,
              typename Analyser,
              typename Geometry,
              typename OtherGeometry,
              typename BoundaryChecker,
              typename Strategy>
    static inline void analyse_each_turn(Result & res,
                                         Analyser & analyser,
                                         TurnIt first, TurnIt last,
                                         Geometry const& geometry,
                                         OtherGeometry const& other_geometry,
                                         BoundaryChecker const& boundary_checker,
                                         Strategy const& strategy)
    {
        if ( first == last )
            return;

        for ( TurnIt it = first ; it != last ; ++it )
        {
            analyser.apply(res, it,
                           geometry, other_geometry,
                           boundary_checker,
                           strategy);

            if ( BOOST_GEOMETRY_CONDITION( res.interrupt ) )
                return;
        }

        analyser.apply(res, first, last,
                       geometry, other_geometry,
                       boundary_checker);
    }

    // less comparator comparing multi_index then ring_index
    // may be used to sort turns by ring
    struct less_ring
    {
        template <typename Turn>
        inline bool operator()(Turn const& left, Turn const& right) const
        {
            return left.operations[1].seg_id.multi_index < right.operations[1].seg_id.multi_index
                || ( left.operations[1].seg_id.multi_index == right.operations[1].seg_id.multi_index
                  && left.operations[1].seg_id.ring_index < right.operations[1].seg_id.ring_index );
        }
    };

    // policy/functor checking if a turn's operation is operation_continue
    struct has_boundary_intersection
    {
        has_boundary_intersection()
            : result(false) {}

        template <typename Turn>
        inline void operator()(Turn const& turn)
        {
            if ( turn.operations[1].operation == overlay::operation_continue )
                result = true;
        }

        bool result;
    };

    // iterate through the range and search for the different multi_index or ring_index
    // also call fun for each turn in the current range
    template <typename It, typename Fun>
    static inline It find_next_ring(It first, It last, Fun & fun)
    {
        if ( first == last )
            return last;

        signed_size_type const multi_index = first->operations[1].seg_id.multi_index;
        signed_size_type const ring_index = first->operations[1].seg_id.ring_index;

        fun(*first);
        ++first;

        for ( ; first != last ; ++first )
        {
            if ( multi_index != first->operations[1].seg_id.multi_index
              || ring_index != first->operations[1].seg_id.ring_index )
            {
                return first;
            }

            fun(*first);
        }

        return last;
    }

    // analyser which called for turns sorted by seg/distance/operation
    // checks if the boundary of Areal geometry really got out
    // into the exterior of Linear geometry
    template <typename TurnInfo>
    class areal_boundary_analyser
    {
    public:
        areal_boundary_analyser()
            : is_union_detected(false)
            , m_previous_turn_ptr(NULL)
        {}

        template <typename TurnIt, typename Strategy>
        bool apply(TurnIt /*first*/, TurnIt it, TurnIt last,
                   Strategy const& strategy)
        {
            overlay::operation_type op = it->operations[1].operation;

            if ( it != last )
            {
                if ( op != overlay::operation_union
                  && op != overlay::operation_continue )
                {
                    return true;
                }

                if ( is_union_detected )
                {
                    BOOST_GEOMETRY_ASSERT(m_previous_turn_ptr != NULL);
                    if ( !detail::equals::equals_point_point(it->point, m_previous_turn_ptr->point, strategy) )
                    {
                        // break
                        return false;
                    }
                    else if ( op == overlay::operation_continue ) // operation_boundary
                    {
                        is_union_detected = false;
                    }
                }

                if ( op == overlay::operation_union )
                {
                    is_union_detected = true;
                    m_previous_turn_ptr = boost::addressof(*it);
                }

                return true;
            }
            else
            {
                return false;
            }            
        }

        bool is_union_detected;

    private:
        const TurnInfo * m_previous_turn_ptr;
    };
};

template <typename Geometry1, typename Geometry2>
struct areal_linear
{
    typedef linear_areal<Geometry2, Geometry1, true> linear_areal_type;

    static const bool interruption_enabled = linear_areal_type::interruption_enabled;

    template <typename Result, typename Strategy>
    static inline void apply(Geometry1 const& geometry1, Geometry2 const& geometry2,
                             Result & result,
                             Strategy const& strategy)
    {
        linear_areal_type::apply(geometry2, geometry1, result, strategy);
    }
};

}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_LINEAR_AREAL_HPP

/* linear_areal.hpp
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
*/