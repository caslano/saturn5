// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_IS_ACCEPTABLE_TURN_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_IS_ACCEPTABLE_TURN_HPP

#include <boost/range.hpp>

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