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
            || std::none_of(m_other_entry_points.begin(),
                            m_other_entry_points.end(),
                            same_single(
                                turn.operations[other_op_id].seg_id));
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

template <std::size_t OpId, typename Turn, typename Strategy>
inline bool turn_on_the_same_ip(Turn const& prev_turn, Turn const& curr_turn,
                                Strategy const& strategy)
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