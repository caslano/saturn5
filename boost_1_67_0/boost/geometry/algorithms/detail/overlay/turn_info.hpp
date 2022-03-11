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