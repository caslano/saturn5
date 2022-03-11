// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014, 2015, 2017, 2018, 2019.
// Modifications copyright (c) 2013-2019 Oracle and/or its affiliates.

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

#include <boost/geometry/algorithms/num_interior_rings.hpp>
#include <boost/geometry/algorithms/detail/point_on_border.hpp>
#include <boost/geometry/algorithms/detail/sub_range.hpp>
#include <boost/geometry/algorithms/detail/single_geometry.hpp>

#include <boost/geometry/algorithms/detail/relate/point_geometry.hpp>
#include <boost/geometry/algorithms/detail/relate/turns.hpp>
#include <boost/geometry/algorithms/detail/relate/boundary_checker.hpp>
#include <boost/geometry/algorithms/detail/relate/follow_helpers.hpp>

#include <boost/geometry/views/detail/normalized_view.hpp>

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

    template <typename Geometry>
        struct is_multi
            : boost::is_base_of
                <
                    multi_tag,
                    typename tag<Geometry>::type
                >
        {};

    template <typename Geom1, typename Geom2, typename Strategy>
    struct multi_turn_info
        : turns::get_turns<Geom1, Geom2>::template turn_info_type<Strategy>::type
    {
        multi_turn_info() : priority(0) {}
        int priority; // single-geometry sorting priority
    };

    template <typename Geom1, typename Geom2, typename Strategy>
    struct turn_info_type
        : boost::mpl::if_c
            <
                is_multi<Geometry2>::value,
                multi_turn_info<Geom1, Geom2, Strategy>,
                typename turns::get_turns<Geom1, Geom2>::template turn_info_type<Strategy>::type
            >
    {};
    
    template <typename Result, typename IntersectionStrategy>
    static inline void apply(Geometry1 const& geometry1, Geometry2 const& geometry2,
                             Result & result,
                             IntersectionStrategy const& intersection_strategy)
    {
// TODO: If Areal geometry may have infinite size, change the following line:

        // The result should be FFFFFFFFF
        relate::set<exterior, exterior, result_dimension<Geometry2>::value, TransposeResult>(result);// FFFFFFFFd, d in [1,9] or T

        if ( BOOST_GEOMETRY_CONDITION( result.interrupt ) )
            return;

        // get and analyse turns
        typedef typename turn_info_type<Geometry1, Geometry2, IntersectionStrategy>::type turn_type;
        std::vector<turn_type> turns;

        interrupt_policy_linear_areal<Geometry2, Result> interrupt_policy(geometry2, result);

        turns::get_turns<Geometry1, Geometry2>::apply(turns, geometry1, geometry2, interrupt_policy, intersection_strategy);
        if ( BOOST_GEOMETRY_CONDITION( result.interrupt ) )
            return;

        typedef typename IntersectionStrategy::template point_in_geometry_strategy<Geometry1, Geometry2>::type within_strategy_type;
        within_strategy_type const within_strategy = intersection_strategy.template get_point_in_geometry_strategy<Geometry1, Geometry2>();

        typedef typename IntersectionStrategy::cs_tag cs_tag;
        typedef typename within_strategy_type::equals_point_point_strategy_type eq_pp_strategy_type;
        
        typedef boundary_checker
            <
                Geometry1,
                eq_pp_strategy_type
            > boundary_checker1_type;
        boundary_checker1_type boundary_checker1(geometry1);

        no_turns_la_linestring_pred
            <
                Geometry2,
                Result,
                within_strategy_type,
                boundary_checker1_type,
                TransposeResult
            > pred1(geometry2,
                    result,
                    within_strategy,
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
            sort_dispatch<cs_tag>(turns.begin(), turns.end(), is_multi<Geometry2>());

            turns_analyser<turn_type> analyser;
            analyse_each_turn(result, analyser,
                              turns.begin(), turns.end(),
                              geometry1, geometry2,
                              boundary_checker1,
                              intersection_strategy.get_side_strategy());

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

                    eq_pp_strategy_type const eq_pp_strategy = within_strategy.get_equals_point_point_strategy();

                    // analyse
                    areal_boundary_analyser<turn_type> analyser;
                    for ( turn_iterator rit = it ; rit != next ; ++rit )
                    {
                        // if the analyser requests, break the search
                        if ( !analyser.apply(it, rit, next, eq_pp_strategy) )
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
    static void sort_dispatch(TurnIt first, TurnIt last, boost::true_type const& /*is_multi*/)
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
    static void sort_dispatch(TurnIt first, TurnIt last, boost::false_type const& /*is_multi*/)
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
                  typename SideStrategy,
                  typename Pi = PointP, typename Pj = PointP, typename Pk = PointP,
                  typename Qi = PointQ, typename Qj = PointQ, typename Qk = PointQ
        >
        struct la_side_calculator
        {
            inline la_side_calculator(Pi const& pi, Pj const& pj, Pk const& pk,
                                   Qi const& qi, Qj const& qj, Qk const& qk,
                                   SideStrategy const& side_strategy)
                : m_pi(pi), m_pj(pj), m_pk(pk)
                , m_qi(qi), m_qj(qj), m_qk(qk)
                , m_side_strategy(side_strategy)
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

            SideStrategy m_side_strategy;
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
                  typename SideStrategy>
        void apply(Result & res, TurnIt it,
                   Geometry const& geometry,
                   OtherGeometry const& other_geometry,
                   BoundaryChecker const& boundary_checker,
                   SideStrategy const& side_strategy)
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
                                                  side_strategy.get_equals_point_point_strategy()) )
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
                                                side_strategy.get_equals_point_point_strategy()) )
                {
                    fake_enter_detected = true;
                }

                m_exit_watcher.reset_detected_exit();
            }

            if ( BOOST_GEOMETRY_CONDITION( is_multi<OtherGeometry>::value )
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
                                                    side_strategy.get_equals_point_point_strategy()) )
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
                                                  side_strategy.get_equals_point_point_strategy()) )
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
                                                                       side_strategy);

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

                if ( BOOST_GEOMETRY_CONDITION( is_multi<OtherGeometry>::value ) )
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
                                                                             side_strategy);
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
                            if ( BOOST_GEOMETRY_CONDITION( is_multi<OtherGeometry>::value )
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
                                    if ( BOOST_GEOMETRY_CONDITION( is_multi<OtherGeometry>::value )
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
            if ( BOOST_GEOMETRY_CONDITION( is_multi<OtherGeometry>::value )
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
        template <typename Turn, typename SideStrategy>
        static inline bool calculate_from_inside(Geometry1 const& geometry1,
                                                 Geometry2 const& geometry2,
                                                 Turn const& turn,
                                                 SideStrategy const& side_strategy)
        {
            typedef typename cs_tag<typename Turn::point_type>::type cs_tag;

            if ( turn.operations[op_id].position == overlay::position_front )
                return false;

            typename sub_range_return_type<Geometry1 const>::type
                range1 = sub_range(geometry1, turn.operations[op_id].seg_id);
            
            typedef detail::normalized_view<Geometry2 const> const range2_type;
            typedef typename boost::range_iterator<range2_type>::type range2_iterator;
            range2_type range2(sub_range(geometry2, turn.operations[other_op_id].seg_id));
            
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
            bool const is_ip_qj = equals::equals_point_point(turn.point, qj, side_strategy.get_equals_point_point_strategy());
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
                                                                 side_strategy.get_equals_point_point_strategy());

                // Will this sequence of points be always correct?
                la_side_calculator<cs_tag, point1_type, point2_type, SideStrategy>
                    side_calc(qi_conv, new_pj, pi, qi, qj, *qk_it, side_strategy);

                return calculate_from_inside_sides(side_calc);
            }
            else
            {
                point2_type new_qj;
                geometry::convert(turn.point, new_qj);

                la_side_calculator<cs_tag, point1_type, point2_type, SideStrategy>
                    side_calc(qi_conv, new_pj, pi, qi, new_qj, qj, side_strategy);

                return calculate_from_inside_sides(side_calc);
            }
        }

        template <typename It, typename EqPPStrategy>
        static inline It find_next_non_duplicated(It first, It current, It last,
                                                  EqPPStrategy const& strategy)
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
              typename SideStrategy>
    static inline void analyse_each_turn(Result & res,
                                         Analyser & analyser,
                                         TurnIt first, TurnIt last,
                                         Geometry const& geometry,
                                         OtherGeometry const& other_geometry,
                                         BoundaryChecker const& boundary_checker,
                                         SideStrategy const& side_strategy)
    {
        if ( first == last )
            return;

        for ( TurnIt it = first ; it != last ; ++it )
        {
            analyser.apply(res, it,
                           geometry, other_geometry,
                           boundary_checker,
                           side_strategy);

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

        template <typename TurnIt, typename EqPPStrategy>
        bool apply(TurnIt /*first*/, TurnIt it, TurnIt last,
                   EqPPStrategy const& strategy)
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

    template <typename Result, typename IntersectionStrategy>
    static inline void apply(Geometry1 const& geometry1, Geometry2 const& geometry2,
                             Result & result,
                             IntersectionStrategy const& intersection_strategy)
    {
        linear_areal_type::apply(geometry2, geometry1, result, intersection_strategy);
    }
};

}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_LINEAR_AREAL_HPP

/* linear_areal.hpp
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
*/