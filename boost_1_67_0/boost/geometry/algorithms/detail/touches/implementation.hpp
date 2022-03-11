// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013, 2014, 2015, 2017, 2019.
// Modifications copyright (c) 2013-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_TOUCHES_IMPLEMENTATION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_TOUCHES_IMPLEMENTATION_HPP


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
        BOOST_STATIC_ASSERT((boost::is_same
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

template<typename Geometry, typename PointInRingStrategy>
struct check_each_ring_for_within
{
    bool has_within;
    Geometry const& m_geometry;
    PointInRingStrategy const& m_strategy;

    inline check_each_ring_for_within(Geometry const& g, PointInRingStrategy const& strategy)
        : has_within(false)
        , m_geometry(g)
        , m_strategy(strategy)
    {}

    template <typename Range>
    inline void apply(Range const& range)
    {
        typename geometry::point_type<Range>::type p;
        geometry::point_on_border(p, range);
        if ( !has_within && geometry::within(p, m_geometry, m_strategy) )
        {
            has_within = true;
        }
    }
};

template <typename FirstGeometry, typename SecondGeometry, typename IntersectionStrategy>
inline bool rings_containing(FirstGeometry const& geometry1,
                             SecondGeometry const& geometry2,
                             IntersectionStrategy const& strategy)
{
    // NOTE: This strategy could be defined inside IntersectionStrategy
    typedef typename IntersectionStrategy::template point_in_geometry_strategy
        <
            FirstGeometry, SecondGeometry
        >::type point_in_ring_strategy_type;

    point_in_ring_strategy_type point_in_ring_strategy
        = strategy.template get_point_in_geometry_strategy<FirstGeometry, SecondGeometry>();

    check_each_ring_for_within
        <
            FirstGeometry, point_in_ring_strategy_type
        > checker(geometry1, point_in_ring_strategy);
    geometry::detail::for_each_range(geometry2, checker);
    return checker.has_within;
}

template <typename Geometry1, typename Geometry2>
struct areal_areal
{
    template <typename IntersectionStrategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             IntersectionStrategy const& strategy)
    {
        typedef typename geometry::point_type<Geometry1>::type point_type;
        typedef detail::overlay::turn_info<point_type> turn_info;

        std::deque<turn_info> turns;
        detail::touches::areal_interrupt_policy policy;
        boost::geometry::get_turns
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

        typedef typename strategy::relate::services::default_strategy
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
        >::apply(geometry, strategy, detail::no_rescale_policy(), turns, policy, 0, true);

        return policy.result();
    }
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_TOUCHES_IMPLEMENTATION_HPP

/* implementation.hpp
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
*/