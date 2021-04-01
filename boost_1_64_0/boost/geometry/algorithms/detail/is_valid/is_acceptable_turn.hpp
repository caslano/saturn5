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
hTlI7qFx0w7z7AlSznXUJRsBLE+YuD6/veWdNu3yOiPeeZLHE4tbvb7hSiJVoM/K5ciwBH11vQaLz3/7QeJoFe1Fv82Nnd6iWzwj568YRWysgAcAiu/yb7OvYJeFU4TJYNM3rX17HlQSFETYq5mL2kyl3Xz/Z0REyv6x0DYv7wngKY4+BzyHmZd4MM17zg9jLEGtQR9Ee9GUCFEP8+aYccebyo0erbrE3SmJpEfgRT11Dpkz6xBoCMGdTyoEbB0MV+KCT1WWK4gDFtVXFCMbNYL1Uh9xg+aErUeMuk9Zw8pB0ZEds7Pymi6y9lE2O/+Bcem1BGo7xOlBlAwitSh3zEpEcBrcaDAO4CkTV49Fa6NLcNZj/F7TumZ35KPDnyMl5hGaxkfEN9yR2QaLHGrrQ5nMQvQ8ZJYUb5CXgtTywn30N6QBWu2I1ENHNEk+6hvUjelDlKcuMJWpyjyTSuk+0jAHk6I6oRqXbuTg75vzy5BPNGIT+NW4TDq5PcVgeVJyicIblBJ/PXzTP1WmWfEZnAOup9GPI5uFgw3vTGdLzRpdhvxCtZQRdRsSzA==
*/