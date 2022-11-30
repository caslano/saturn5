// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_IS_ACCEPTABLE_TURN_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_IS_ACCEPTABLE_TURN_HPP

#include <boost/range/value_type.hpp>

#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_valid
{


template
<
    typename Geometry,
    order_selector Order = geometry::point_order<Geometry>::value,
    typename Tag = typename tag<Geometry>::type
>
struct acceptable_operation
{};

template <typename Polygon>
struct acceptable_operation<Polygon, counterclockwise, polygon_tag>
{
    static const detail::overlay::operation_type value =
        detail::overlay::operation_union;
};

template <typename Polygon>
struct acceptable_operation<Polygon, clockwise, polygon_tag>
{
    static const detail::overlay::operation_type value =
        detail::overlay::operation_intersection;
};

template <typename MultiPolygon>
struct acceptable_operation<MultiPolygon, counterclockwise, multi_polygon_tag>
{
    static const detail::overlay::operation_type value =
        detail::overlay::operation_intersection;
};

template <typename MultiPolygon>
struct acceptable_operation<MultiPolygon, clockwise, multi_polygon_tag>
{
    static const detail::overlay::operation_type value =
        detail::overlay::operation_union;
};




template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct is_acceptable_turn
{};

template <typename Ring>
struct is_acceptable_turn<Ring, ring_tag>
{
    template <typename Turn>
    static inline bool apply(Turn const&)
    {
        return false;
    }
};

template <typename Polygon>
class is_acceptable_turn<Polygon, polygon_tag>
{
protected:
    template <typename Turn, typename Method, typename Operation>
    static inline bool check_turn(Turn const& turn,
                                  Method method,
                                  Operation operation)
    {
        return turn.method == method
            && turn.operations[0].operation == operation
            && turn.operations[1].operation == operation;
    }


public:
    template <typename Turn>
    static inline bool apply(Turn const& turn)
    {
        using namespace detail::overlay;

        if ( turn.operations[0].seg_id.ring_index
             == turn.operations[1].seg_id.ring_index )
        {
            return false;
        }

        operation_type const op = acceptable_operation<Polygon>::value;

        return check_turn(turn, method_touch_interior, op)
            || check_turn(turn, method_touch, op)
            ;
    }
};

template <typename MultiPolygon>
class is_acceptable_turn<MultiPolygon, multi_polygon_tag>
    : is_acceptable_turn<typename boost::range_value<MultiPolygon>::type>
{
private:
    typedef typename boost::range_value<MultiPolygon>::type polygon;
    typedef is_acceptable_turn<polygon> base;

public:
    template <typename Turn>
    static inline bool apply(Turn const& turn)
    {
        using namespace detail::overlay;

        if ( turn.operations[0].seg_id.multi_index
             == turn.operations[1].seg_id.multi_index )
        {
            return base::apply(turn);
        }

        operation_type const op = acceptable_operation<MultiPolygon>::value;
        if ( base::check_turn(turn, method_touch_interior, op)
          || base::check_turn(turn, method_touch, op))
        {
            return true;
        }

        // Turn is acceptable only in case of a touch(interior) and both lines
        // (polygons) do not cross
        return (turn.method == method_touch
                || turn.method == method_touch_interior)
                && turn.touch_only;
    }
};   


}} // namespace detail::is_valid
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_IS_ACCEPTABLE_TURN_HPP

/* is_acceptable_turn.hpp
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
*/