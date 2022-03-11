// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014, 2018.
// Modifications copyright (c) 2013-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_FOLLOW_HELPERS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_FOLLOW_HELPERS_HPP

#include <vector>

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/algorithms/detail/overlay/get_turn_info_helpers.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>
#include <boost/geometry/algorithms/detail/overlay/segment_identifier.hpp>
#include <boost/geometry/algorithms/detail/relate/boundary_checker.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/core/assert.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/range.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate {

// NOTE: This iterates through single geometries for which turns were not generated.
//       It doesn't mean that the geometry is disjoint, only that no turns were detected.

template <std::size_t OpId,
          typename Geometry,
          typename Tag = typename geometry::tag<Geometry>::type,
          bool IsMulti = boost::is_base_of<multi_tag, Tag>::value
>
struct for_each_disjoint_geometry_if
    : public not_implemented<Tag>
{};

template <std::size_t OpId, typename Geometry, typename Tag>
struct for_each_disjoint_geometry_if<OpId, Geometry, Tag, false>
{
    template <typename TurnIt, typename Pred>
    static inline bool apply(TurnIt first, TurnIt last,
                             Geometry const& geometry,
                             Pred & pred)
    {
        if ( first != last )
            return false;
        pred(geometry);
        return true;
    }
};

template <std::size_t OpId, typename Geometry, typename Tag>
struct for_each_disjoint_geometry_if<OpId, Geometry, Tag, true>
{
    template <typename TurnIt, typename Pred>
    static inline bool apply(TurnIt first, TurnIt last,
                             Geometry const& geometry,
                             Pred & pred)
    {
        if ( first != last )
            return for_turns(first, last, geometry, pred);
        else
            return for_empty(geometry, pred);
    }

    template <typename Pred>
    static inline bool for_empty(Geometry const& geometry,
                                 Pred & pred)
    {
        typedef typename boost::range_iterator<Geometry const>::type iterator;

        // O(N)
        // check predicate for each contained geometry without generated turn
        for ( iterator it = boost::begin(geometry) ;
              it != boost::end(geometry) ; ++it )
        {
            bool cont = pred(*it);
            if ( !cont )
                break;
        }
        
        return !boost::empty(geometry);
    }

    template <typename TurnIt, typename Pred>
    static inline bool for_turns(TurnIt first, TurnIt last,
                                 Geometry const& geometry,
                                 Pred & pred)
    {
        BOOST_GEOMETRY_ASSERT(first != last);

        const std::size_t count = boost::size(geometry);
        boost::ignore_unused(count);

        // O(I)
        // gather info about turns generated for contained geometries
        std::vector<bool> detected_intersections(count, false);
        for ( TurnIt it = first ; it != last ; ++it )
        {
            signed_size_type multi_index = it->operations[OpId].seg_id.multi_index;
            BOOST_GEOMETRY_ASSERT(multi_index >= 0);
            std::size_t const index = static_cast<std::size_t>(multi_index);
            BOOST_GEOMETRY_ASSERT(index < count);
            detected_intersections[index] = true;
        }

        bool found = false;

        // O(N)
        // check predicate for each contained geometry without generated turn
        for ( std::vector<bool>::iterator it = detected_intersections.begin() ;
              it != detected_intersections.end() ; ++it )
        {
            // if there were no intersections for this multi_index
            if ( *it == false )
            {
                found = true;
                std::size_t const index = std::size_t(std::distance(detected_intersections.begin(), it));
                bool cont = pred(range::at(geometry, index));
                if ( !cont )
                    break;
            }
        }
        
        return found;
    }
};

// WARNING! This class stores pointers!
// Passing a reference to local variable will result in undefined behavior!
template <typename Point>
class point_info
{
public:
    point_info() : sid_ptr(NULL), pt_ptr(NULL) {}
    point_info(Point const& pt, segment_identifier const& sid)
        : sid_ptr(boost::addressof(sid))
        , pt_ptr(boost::addressof(pt))
    {}
    segment_identifier const& seg_id() const
    {
        BOOST_GEOMETRY_ASSERT(sid_ptr);
        return *sid_ptr;
    }
    Point const& point() const
    {
        BOOST_GEOMETRY_ASSERT(pt_ptr);
        return *pt_ptr;
    }

    //friend bool operator==(point_identifier const& l, point_identifier const& r)
    //{
    //    return l.seg_id() == r.seg_id()
    //        && detail::equals::equals_point_point(l.point(), r.point());
    //}

private:
    const segment_identifier * sid_ptr;
    const Point * pt_ptr;
};

// WARNING! This class stores pointers!
// Passing a reference to local variable will result in undefined behavior!
class same_single
{
public:
    same_single(segment_identifier const& sid)
        : sid_ptr(boost::addressof(sid))
    {}

    bool operator()(segment_identifier const& sid) const
    {
        return sid.multi_index == sid_ptr->multi_index;                
    }

    template <typename Point>
    bool operator()(point_info<Point> const& pid) const
    {
        return operator()(pid.seg_id());
    }

private:
    const segment_identifier * sid_ptr;
};

class same_ring
{
public:
    same_ring(segment_identifier const& sid)
        : sid_ptr(boost::addressof(sid))
    {}

    bool operator()(segment_identifier const& sid) const
    {
        return sid.multi_index == sid_ptr->multi_index
            && sid.ring_index == sid_ptr->ring_index;
    }

private:
    const segment_identifier * sid_ptr;
};

// WARNING! This class stores pointers!
// Passing a reference to local variable will result in undefined behavior!
template <typename SameRange = same_single>
class segment_watcher
{
public:
    segment_watcher()
        : m_seg_id_ptr(NULL)
    {}

    bool update(segment_identifier const& seg_id)
    {
        bool result = m_seg_id_ptr == 0 || !SameRange(*m_seg_id_ptr)(seg_id);
        m_seg_id_ptr = boost::addressof(seg_id);
        return result;
    }

private:
    const segment_identifier * m_seg_id_ptr;
};

// WARNING! This class stores pointers!
// Passing a reference to local variable will result in undefined behavior!
template <typename TurnInfo, std::size_t OpId>
class exit_watcher
{
    static const std::size_t op_id = OpId;
    static const std::size_t other_op_id = (OpId + 1) % 2;

    typedef typename TurnInfo::point_type point_type;
    typedef detail::relate::point_info<point_type> point_info;

public:
    exit_watcher()
        : m_exit_operation(overlay::operation_none)
        , m_exit_turn_ptr(NULL)
    {}

    void enter(TurnInfo const& turn)
    {
        m_other_entry_points.push_back(
            point_info(turn.point, turn.operations[other_op_id].seg_id) );
    }

    // TODO: exit_per_geometry parameter looks not very safe
    //       wrong value may be easily passed

    void exit(TurnInfo const& turn, bool exit_per_geometry = true)
    {
        //segment_identifier const& seg_id = turn.operations[op_id].seg_id;
        segment_identifier const& other_id = turn.operations[other_op_id].seg_id;
        overlay::operation_type exit_op = turn.operations[op_id].operation;

        typedef typename std::vector<point_info>::iterator point_iterator;
        // search for the entry point in the same range of other geometry
        point_iterator entry_it = std::find_if(m_other_entry_points.begin(),
                                               m_other_entry_points.end(),
                                               same_single(other_id));

        // this end point has corresponding entry point
        if ( entry_it != m_other_entry_points.end() )
        {
            // erase the corresponding entry point
            m_other_entry_points.erase(entry_it);

            if ( exit_per_geometry || m_other_entry_points.empty() )
            {
                // here we know that we possibly left LS
                // we must still check if we didn't get back on the same point
                m_exit_operation = exit_op;
                m_exit_turn_ptr = boost::addressof(turn);
            }
        }
    }

    bool is_outside() const
    {
        // if we didn't entered anything in the past, we're outside
        return m_other_entry_points.empty();
    }

    bool is_outside(TurnInfo const& turn) const
    {
        return m_other_entry_points.empty()
            || std::find_if(m_other_entry_points.begin(),
                            m_other_entry_points.end(),
                            same_single(
                                turn.operations[other_op_id].seg_id))
                    == m_other_entry_points.end();
    }

    overlay::operation_type get_exit_operation() const
    {
        return m_exit_operation;
    }

    point_type const& get_exit_point() const
    {
        BOOST_GEOMETRY_ASSERT(m_exit_operation != overlay::operation_none);
        BOOST_GEOMETRY_ASSERT(m_exit_turn_ptr);
        return m_exit_turn_ptr->point;
    }

    TurnInfo const& get_exit_turn() const
    {
        BOOST_GEOMETRY_ASSERT(m_exit_operation != overlay::operation_none);
        BOOST_GEOMETRY_ASSERT(m_exit_turn_ptr);
        return *m_exit_turn_ptr;
    }

    void reset_detected_exit()
    {
        m_exit_operation = overlay::operation_none;
    }

    void reset()
    {
        m_exit_operation = overlay::operation_none;
        m_other_entry_points.clear();
    }

private:
    overlay::operation_type m_exit_operation;
    const TurnInfo * m_exit_turn_ptr;
    std::vector<point_info> m_other_entry_points; // TODO: use map here or sorted vector?
};

template <std::size_t OpId, typename Turn, typename EqPPStrategy>
inline bool turn_on_the_same_ip(Turn const& prev_turn, Turn const& curr_turn,
                                EqPPStrategy const& strategy)
{
    segment_identifier const& prev_seg_id = prev_turn.operations[OpId].seg_id;
    segment_identifier const& curr_seg_id = curr_turn.operations[OpId].seg_id;

    if ( prev_seg_id.multi_index != curr_seg_id.multi_index
      || prev_seg_id.ring_index != curr_seg_id.ring_index )
    {
        return false;
    }

    // TODO: will this work if between segments there will be some number of degenerated ones?

    if ( prev_seg_id.segment_index != curr_seg_id.segment_index
      && ( ! curr_turn.operations[OpId].fraction.is_zero()
        || prev_seg_id.segment_index + 1 != curr_seg_id.segment_index ) )
    {
        return false;
    }

    return detail::equals::equals_point_point(prev_turn.point, curr_turn.point, strategy);
}

template <boundary_query BoundaryQuery,
          typename Point,
          typename BoundaryChecker>
static inline bool is_endpoint_on_boundary(Point const& pt,
                                           BoundaryChecker & boundary_checker)
{
    return boundary_checker.template is_endpoint_boundary<BoundaryQuery>(pt);
}

template <boundary_query BoundaryQuery,
          typename IntersectionPoint,
          typename OperationInfo,
          typename BoundaryChecker>
static inline bool is_ip_on_boundary(IntersectionPoint const& ip,
                                     OperationInfo const& operation_info,
                                     BoundaryChecker & boundary_checker,
                                     segment_identifier const& seg_id)
{
    boost::ignore_unused(seg_id);

    bool res = false;

    // IP on the last point of the linestring
    if ( BOOST_GEOMETRY_CONDITION(BoundaryQuery == boundary_back || BoundaryQuery == boundary_any)
      && operation_info.position == overlay::position_back )
    {
        // check if this point is a boundary
        res = boundary_checker.template is_endpoint_boundary<boundary_back>(ip);
    }
    // IP on the last point of the linestring
    else if ( BOOST_GEOMETRY_CONDITION(BoundaryQuery == boundary_front || BoundaryQuery == boundary_any)
           && operation_info.position == overlay::position_front )
    {
        // check if this point is a boundary
        res = boundary_checker.template is_endpoint_boundary<boundary_front>(ip);
    }
            
    return res;
}


}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_FOLLOW_HELPERS_HPP

/* follow_helpers.hpp
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
*/