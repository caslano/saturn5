// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2020.
// Modifications copyright (c) 2013-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_TOUCHES_IMPLEMENTATION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_TOUCHES_IMPLEMENTATION_HPP


#include <type_traits>

#include <boost/geometry/algorithms/detail/for_each_range.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay.hpp>
#include <boost/geometry/algorithms/detail/overlay/self_turn_points.hpp>
#include <boost/geometry/algorithms/detail/sub_range.hpp>
#include <boost/geometry/algorithms/detail/relate/relate_impl.hpp>
#include <boost/geometry/algorithms/detail/touches/interface.hpp>
#include <boost/geometry/algorithms/disjoint.hpp>
#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/algorithms/num_geometries.hpp>
#include <boost/geometry/algorithms/relate.hpp>

#include <boost/geometry/policies/robustness/no_rescale_policy.hpp>

#include <boost/geometry/strategies/relate/cartesian.hpp>
#include <boost/geometry/strategies/relate/geographic.hpp>
#include <boost/geometry/strategies/relate/spherical.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace touches
{

// Box/Box

template
<
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct box_box_loop
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& b1, Box2 const& b2, bool & touch)
    {
        typedef typename coordinate_type<Box1>::type coordinate_type1;
        typedef typename coordinate_type<Box2>::type coordinate_type2;

        coordinate_type1 const& min1 = get<min_corner, Dimension>(b1);
        coordinate_type1 const& max1 = get<max_corner, Dimension>(b1);
        coordinate_type2 const& min2 = get<min_corner, Dimension>(b2);
        coordinate_type2 const& max2 = get<max_corner, Dimension>(b2);

        // TODO assert or exception?
        //BOOST_GEOMETRY_ASSERT(min1 <= max1 && min2 <= max2);

        if (max1 < min2 || max2 < min1)
        {
            return false;
        }

        if (max1 == min2 || max2 == min1)
        {
            touch = true;
        }
        
        return box_box_loop
                <
                    Dimension + 1,
                    DimensionCount
                >::apply(b1, b2, touch);
    }
};

template
<
    std::size_t DimensionCount
>
struct box_box_loop<DimensionCount, DimensionCount>
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& , Box2 const&, bool &)
    {
        return true;
    }
};

struct box_box
{
    template <typename Box1, typename Box2, typename Strategy>
    static inline bool apply(Box1 const& b1, Box2 const& b2, Strategy const& /*strategy*/)
    {
        BOOST_STATIC_ASSERT((std::is_same
                                <
                                    typename geometry::coordinate_system<Box1>::type,
                                    typename geometry::coordinate_system<Box2>::type
                                >::value
                           ));
        assert_dimension_equal<Box1, Box2>();

        bool touches = false;
        bool ok = box_box_loop
                    <
                        0,
                        dimension<Box1>::type::value
                    >::apply(b1, b2, touches);

        return ok && touches;
    }
};

// Areal/Areal

struct areal_interrupt_policy
{
    static bool const enabled = true;
    bool found_touch;
    bool found_not_touch;

    // dummy variable required by self_get_turn_points::get_turns
    static bool const has_intersections = false;

    inline bool result()
    {
        return found_touch && !found_not_touch;
    }

    inline areal_interrupt_policy()
        : found_touch(false), found_not_touch(false)
    {}

    template <typename Range>
    inline bool apply(Range const& range)
    {
        // if already rejected (temp workaround?)
        if ( found_not_touch )
            return true;

        typedef typename boost::range_iterator<Range const>::type iterator;
        for ( iterator it = boost::begin(range) ; it != boost::end(range) ; ++it )
        {
            if ( it->has(overlay::operation_intersection) )
            {
                found_not_touch = true;
                return true;
            }

            switch(it->method)
            {
                case overlay::method_crosses:
                    found_not_touch = true;
                    return true;
                case overlay::method_equal:
                    // Segment spatially equal means: at the right side
                    // the polygon internally overlaps. So return false.
                    found_not_touch = true;
                    return true;
                case overlay::method_touch:
                case overlay::method_touch_interior:
                case overlay::method_collinear:
                    if ( ok_for_touch(*it) )
                    {
                        found_touch = true;
                    }
                    else
                    {
                        found_not_touch = true;
                        return true;
                    }
                    break;
                case overlay::method_start :
                case overlay::method_none :
                case overlay::method_disjoint :
                case overlay::method_error :
                    break;
            }
        }

        return false;
    }

    template <typename Turn>
    inline bool ok_for_touch(Turn const& turn)
    {
        return turn.both(overlay::operation_union)
            || turn.both(overlay::operation_blocked)
            || turn.combination(overlay::operation_union, overlay::operation_blocked)
            ;
    }
};

template <typename Geometry1, typename Geometry2, typename Strategy>
inline bool point_on_border_within(Geometry1 const& geometry1,
                                   Geometry2 const& geometry2,
                                   Strategy const& strategy)
{
    typename geometry::point_type<Geometry1>::type pt;
    return geometry::point_on_border(pt, geometry1)
        && geometry::within(pt, geometry2, strategy);
}

template <typename FirstGeometry, typename SecondGeometry, typename Strategy>
inline bool rings_containing(FirstGeometry const& geometry1,
                             SecondGeometry const& geometry2,
                             Strategy const& strategy)
{
    return geometry::detail::any_range_of(geometry2, [&](auto const& range)
    {
        return point_on_border_within(range, geometry1, strategy);
    });
}

template <typename Geometry1, typename Geometry2>
struct areal_areal
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        typedef typename geometry::point_type<Geometry1>::type point_type;
        typedef detail::overlay::turn_info<point_type> turn_info;

        std::deque<turn_info> turns;
        detail::touches::areal_interrupt_policy policy;
        geometry::get_turns
            <
                detail::overlay::do_reverse<geometry::point_order<Geometry1>::value>::value,
                detail::overlay::do_reverse<geometry::point_order<Geometry2>::value>::value,
                detail::overlay::assign_null_policy
            >(geometry1, geometry2, strategy, detail::no_rescale_policy(), turns, policy);

        return policy.result()
            && ! geometry::detail::touches::rings_containing(geometry1, geometry2, strategy)
            && ! geometry::detail::touches::rings_containing(geometry2, geometry1, strategy);
    }
};

// P/*

struct use_point_in_geometry
{
    template <typename Point, typename Geometry, typename Strategy>
    static inline bool apply(Point const& point, Geometry const& geometry, Strategy const& strategy)
    {
        return detail::within::point_in_geometry(point, geometry, strategy) == 0;
    }
};


}}
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch {

// P/P

template <typename Geometry1, typename Geometry2>
struct touches<Geometry1, Geometry2, point_tag, point_tag, pointlike_tag, pointlike_tag, false>
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& , Geometry2 const& , Strategy const&)
    {
        return false;
    }
};

template <typename Geometry1, typename Geometry2>
struct touches<Geometry1, Geometry2, point_tag, multi_point_tag, pointlike_tag, pointlike_tag, false>
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& , Geometry2 const& , Strategy const&)
    {
        return false;
    }
};

template <typename Geometry1, typename Geometry2>
struct touches<Geometry1, Geometry2, multi_point_tag, multi_point_tag, pointlike_tag, pointlike_tag, false>
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const&, Geometry2 const&, Strategy const&)
    {
        return false;
    }
};

// P/L P/A

template <typename Point, typename Geometry, typename Tag2, typename CastedTag2>
struct touches<Point, Geometry, point_tag, Tag2, pointlike_tag, CastedTag2, false>
    : detail::touches::use_point_in_geometry
{};

template <typename MultiPoint, typename MultiGeometry, typename Tag2, typename CastedTag2>
struct touches<MultiPoint, MultiGeometry, multi_point_tag, Tag2, pointlike_tag, CastedTag2, false>
    : detail::relate::relate_impl
        <
            detail::de9im::static_mask_touches_type,
            MultiPoint,
            MultiGeometry
        >
{};

// L/P A/P

template <typename Geometry, typename MultiPoint, typename Tag1, typename CastedTag1>
struct touches<Geometry, MultiPoint, Tag1, multi_point_tag, CastedTag1, pointlike_tag, false>
    : detail::relate::relate_impl
        <
            detail::de9im::static_mask_touches_type,
            Geometry,
            MultiPoint
        >
{};

// Box/Box

template <typename Box1, typename Box2, typename CastedTag1, typename CastedTag2>
struct touches<Box1, Box2, box_tag, box_tag, CastedTag1, CastedTag2, false>
    : detail::touches::box_box
{};

template <typename Box1, typename Box2>
struct touches<Box1, Box2, box_tag, box_tag, areal_tag, areal_tag, false>
    : detail::touches::box_box
{};

// L/L

template <typename Linear1, typename Linear2, typename Tag1, typename Tag2>
struct touches<Linear1, Linear2, Tag1, Tag2, linear_tag, linear_tag, false>
    : detail::relate::relate_impl
    <
        detail::de9im::static_mask_touches_type,
        Linear1,
        Linear2
    >
{};

// L/A

template <typename Linear, typename Areal, typename Tag1, typename Tag2>
struct touches<Linear, Areal, Tag1, Tag2, linear_tag, areal_tag, false>
    : detail::relate::relate_impl
    <
        detail::de9im::static_mask_touches_type,
        Linear,
        Areal
    >
{};

// A/L
template <typename Linear, typename Areal, typename Tag1, typename Tag2>
struct touches<Areal, Linear, Tag1, Tag2, areal_tag, linear_tag, false>
    : detail::relate::relate_impl
    <
        detail::de9im::static_mask_touches_type,
        Areal,
        Linear
    >
{};

// A/A

template <typename Areal1, typename Areal2, typename Tag1, typename Tag2>
struct touches<Areal1, Areal2, Tag1, Tag2, areal_tag, areal_tag, false>
    : detail::relate::relate_impl
        <
            detail::de9im::static_mask_touches_type,
            Areal1,
            Areal2
        >
{};

template <typename Areal1, typename Areal2>
struct touches<Areal1, Areal2, ring_tag, ring_tag, areal_tag, areal_tag, false>
    : detail::touches::areal_areal<Areal1, Areal2>
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_variant
{

template <typename Geometry>
struct self_touches
{
    static bool apply(Geometry const& geometry)
    {
        concepts::check<Geometry const>();

        typedef typename strategies::relate::services::default_strategy
            <
                Geometry, Geometry
            >::type strategy_type;
        typedef typename geometry::point_type<Geometry>::type point_type;
        typedef detail::overlay::turn_info<point_type> turn_info;

        typedef detail::overlay::get_turn_info
            <
                detail::overlay::assign_null_policy
            > policy_type;

        std::deque<turn_info> turns;
        detail::touches::areal_interrupt_policy policy;
        strategy_type strategy;
        // TODO: skip_adjacent should be set to false
        detail::self_get_turn_points::get_turns
            <
                false, policy_type
            >::apply(geometry, strategy, detail::no_rescale_policy(),
                     turns, policy, 0, true);

        return policy.result();
    }
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_TOUCHES_IMPLEMENTATION_HPP

/* implementation.hpp
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
*/