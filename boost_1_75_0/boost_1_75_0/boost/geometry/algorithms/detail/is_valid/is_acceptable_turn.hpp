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
5O4jffXsHWZt7RnSEwM0Tl1gOV1Ot0lr9eVUzYxaREnTziWLKGlYuojy873xgF+Mi2vj7OBrnFd1BDyWMxnIeyZid7DSYH+n31Dcug36Kt9rKG6PcSsI0a0g9DA1O2g/ozPjXoWmv1WuXIdzxBLJJx9QwpZU9Tn77TjLnmsrsXpUv8VGOdp+3GyvsK1zbHc9arNZ/SqQPpKNPs+3ZbMreMnBn93lsPK7jSkfwDaEl7L5DOel7ABP/xlNbkiz30wrtpWuqM/Rf/WosFTMhba8W9pKLARJw/CtL5zh/M1vwON5Hejz1zU+TWWOHNt2dVQUav1lck1e5uvR7TERKBpoDb+8XZkjTRezhSUoV0hltt2IXCGs2+dGImcXwMZE5AzAWleVcoGsWSFIKf9W+Lsd3LbXKR+LIhuUj3W3nk9wn8WJZpulFdgrJGAm/0nHxhXcTlzqUPt3r3Ma8i3wzHgjA9W9Qe2aczKY6V9QE269O9lYYI8Wco4CJ/roOrLQQD3WR13tVWfYTKOEg3ZQ4+bXvRGpQjH+3qNOdO/4OS34LBZX4/XSPnmpslauslSr2dal6lxLvuwR8nGLbY69zvFoOtA2HwD5R692oy8u2fMgNA7bq/iDZqFFYqbePEwnO12n+5ApHt13Dorz1xHE/hF4xr4FiDW4OcZ7TTn3JY0zYQQue0911c07DYSwKUpghPNVVomaiicT8WACJ1Gm
*/