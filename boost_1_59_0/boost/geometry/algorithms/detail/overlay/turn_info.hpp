// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TURN_INFO_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TURN_INFO_HPP


#include <boost/array.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>
#include <boost/geometry/algorithms/detail/overlay/segment_identifier.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>
#include <boost/geometry/policies/robustness/segment_ratio.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

enum method_type
{
    method_none,
    method_disjoint,
    method_crosses,
    method_touch,
    method_touch_interior,
    method_collinear,
    method_equal,
    method_start,
    method_error
};


/*!
    \brief Turn operation: operation
    \details Information necessary for traversal phase (a phase
        of the overlay process). The information is gathered during the
        get_turns (segment intersection) phase.
        The class is to be included in the turn_info class, either direct
        or a derived or similar class with more (e.g. enrichment) information.
 */
template <typename Point, typename SegmentRatio>
struct turn_operation
{
    typedef SegmentRatio segment_ratio_type;

    operation_type operation;
    segment_identifier seg_id;
    SegmentRatio fraction;

    typedef typename coordinate_type<Point>::type comparable_distance_type;
    comparable_distance_type remaining_distance;

    inline turn_operation()
        : operation(operation_none)
        , remaining_distance(0)
    {}
};


/*!
    \brief Turn information: intersection point, method, and turn information
    \details Information necessary for traversal phase (a phase
        of the overlay process). The information is gathered during the
        get_turns (segment intersection) phase.
    \tparam Point point type of intersection point
    \tparam Operation gives classes opportunity to add additional info
    \tparam Container gives classes opportunity to define how operations are stored
 */
template
<
    typename Point,
    typename SegmentRatio = geometry::segment_ratio<typename coordinate_type<Point>::type>,
    typename Operation = turn_operation<Point, SegmentRatio>,
    typename Container = boost::array<Operation, 2>
>
struct turn_info
{
    typedef Point point_type;
    typedef SegmentRatio segment_ratio_type;
    typedef Operation turn_operation_type;
    typedef Container container_type;

    Point point;
    method_type method;
    bool touch_only; // True in case of method touch(interior) and lines do not cross
    signed_size_type cluster_id; // For multiple turns on same location, > 0. Else -1. 0 is unused.
    bool discarded;
    bool has_colocated_both; // Colocated with a uu turn (for union) or ii (other)

    Container operations;

    inline turn_info()
        : method(method_none)
        , touch_only(false)
        , cluster_id(-1)
        , discarded(false)
        , has_colocated_both(false)
    {}

    inline bool both(operation_type type) const
    {
        return has12(type, type);
    }

    inline bool has(operation_type type) const
    {
        return this->operations[0].operation == type
            || this->operations[1].operation == type;
    }

    inline bool combination(operation_type type1, operation_type type2) const
    {
        return has12(type1, type2) || has12(type2, type1);
    }

    inline bool blocked() const
    {
        return both(operation_blocked);
    }
    inline bool opposite() const
    {
        return both(operation_opposite);
    }
    inline bool any_blocked() const
    {
        return has(operation_blocked);
    }
    inline bool is_clustered() const
    {
        return cluster_id > 0;
    }
    inline bool is_self() const
    {
        return operations[0].seg_id.source_index
                == operations[1].seg_id.source_index;
    }

private :
    inline bool has12(operation_type type1, operation_type type2) const
    {
        return this->operations[0].operation == type1
            && this->operations[1].operation == type2
            ;
    }

};


}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TURN_INFO_HPP

/* turn_info.hpp
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
*/