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
YFs1wbZqgm3VBNuqCbZVE2yrJthWTbCtmmBbNcG2akIbUxPsrSbYW02wt5rQxtQEG6wJNlgTbLAm2GBNsMHanZivIKdeqdMurGW26NvPrGA/s4L9zAq+blbw7bPCt84K3zrbgG+Pxt04hqYBpPedG9qlMaQ8/oYFTZgrpndWDAdRZIawEA+Ly9l8Ttrj/Eiv7pCM6g7JqO6QjOoOyajukIzqDsga0JszRx1Wa+OhNEd+nmMfa915JBMyDZpIZ9xeBK3jS1x/pf3WxfJzeZd/xXaR7/bY1Tn1Rvi0ig7hjB344WASLZuuok+OZrrU4XH1JLpQl44IdemIUJeOeHWJZE/ajjIYS1vZU7TsEpKxOkcyqnMkozoHsgbma6I6p27hgKkuvx816NS1pqP/jv47+u/ov6P/jv47+u/ov6P/jv47+u8f3N2Jt4/lFgfw5/e+ooQyT4VkJmTKPJN5ODjGyDzPM4nmiYyhUMgUKcSNkAbqIqK6SiIZSxSVolL387vddddd90+41trrHL/fOzzPfvb+7u/e+3nf83/574ZbvDfybu9c/Vsi9BsQhQxd5fLpEmH7Fe94bReFzBfs0Vuu5/S995kN97faFshRMsfh532J8H3tKFT3JvR5FxIhJU6EYq6VnRQit5Gm5JXiUcg+PQpZs8Wh4Kw4bEuJw67ivt8VhaF62RffUxtyXBfSidxLupJ+pAlpQzqSnmQ+eZY8T6aTp//rs2XkA7Kb7CH7yWFynOxNHrswDm8WToR15RLheRtM7qzgfZBL7fkunQjNjOW1h+Ow4/YoFOsZh1Wa5pvelu99H4VPndvjVuMhR+Rmz3zqbx1OjkO9++PwlTn1lYj12OndvkPj0MUxM2d4D/zAKKSc0EMongj1M0XhkbFRmLIpEZ72/XPkBNlPDpMb8qlbkawkH7mJNCftSGfSjbxIHv7Z+8CNbUPeKPTp6vevo/DsR3HY/E4U1q1LhM6V/GV6WVz8XCJ0vRqH8jviUOi0LsJR6/JHIrwwOgrH7lRzuxKFztsTYeiJODSdE4VTKVG4OCkOPy1MhNVD1LguRuHLdrLCkYmQ1xrPca2/DfRERO1EWOFdwDXGRCHdHXEYsc01rX/uYlH4+kU198+9P/RIFNo+H4X1XaJwc0M75bJZpxqJ8O1+e3eqJcKPIRHu3haHAWui0HxHIhxcnAijqnhX4toobFocheKF7eOiu9RnotDi9jjkfSQKR6+Pw+zJifD5D97vXTYOrZ+3Tuyx6GU5+QRVjq8Toel1iXBv/hCakSakirEceT8OafLGYVCDRFhbJw6v/xqFNb0SoctncuX1ibC3WRx+XxCH7g/EYc6IOLz290R4/Iqk+p1EGJYtCjOT+1zzGc+iOGw6nAizXPdZcoCcIntJOX6z4LM4/GNPHA72ToRBh6PQzYsef1XYWbKN39wdhXNp3ePFKEy8FIUfxkfhJRvOWw2MQ4rrnroahfJrEmHIiSjcloEOlidC25xReLefdR7vKbGMiTB9qnuvsN8oQyLc7KXNN+SPw9YP47Dmc+t8PA7r8ibCNvWrsqPcp34iPPFKFMqm+KyVdWZ/F8zp9lx8kTx7LgqfNEqEdEW8n4DftSgYhxyKC638oc4/j0XhGbZyqHoU7r0nCrdcjsPDl417XBwq0FfJ/VH4rJD66WJ+ROdH2ybCb2xy0ifeCX0+ETKUisNa65dtt3ceu1fJ1mqqJ1yzcxQ+ft+adVffGBSFnJuNw0bVNIq6uaM4THg0Do3+jEMu9tY+kQh7xnk/7Hj/zxOFBzv6+2HGkt81a2+Ow9/p8+mScdgLg+qxtZbjonC2XhSWWqtG7HavOTy6gj1diEPFb+JQ7Jk=
*/