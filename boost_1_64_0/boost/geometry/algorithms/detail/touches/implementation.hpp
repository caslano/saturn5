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
BZ18flHon+zTm3zRZEhDFgHBPLPpnyz2Vt3v8UU0fkPaAS2f4DHipXa8gjTC40WGAkhnW9sFmLV/xawVHkKI293mSmJrR3w7qYufYhGNIHXv5C9Lxb5U8e77N6jDZVT5rykPL8sX6v/nh2cMEQ4aQr2Vf4aAeZEf/N/KdgNlkgEXDvGZXlHV8tqmRYIAsIHiQ/IDLJ0FSlciWpvrdn0ONr7y/71MlG537YvisO8GXqUQWQogsfkYLMWQDGvRYqQ+ELdN9X8v4dFKPfiMB1vXjpdcZ48UvCtopozauRfSELQwun7TGeIWHASzcMH8cEcw2PsMiruH1kpFH35S77afWDQGpNkBtfEN/LoXTUD/NOZNl9HpKvoztYPTX4oYcHX93hSP1oKolWO6i7VQlo3a54NzRe/V1n4mVYrNSNm72A1XO7FvnHctBEkPtx7+8wGxJyP2UcSGS1zBo/08WNM6dQJEefxfa61GwemzB75b8pAk9JI8wxfJPE1gRcWGCDAWNTLsC81vcb5QdZ6+NGVO7zG3mMD1eegKFtTuSSRw7zu4cRnPXCV9jbImFmGIaodY+hsh1DYTDxfjwfSAU5Er+Dclm4P9TX8e9vk8nKzfrae+eeqX3PqQeJswGp54TjYBxDasZvQuzXpA0NcTHeA3ES2++4I1Rn1TRVUoLOrQf5ao6p/rwag3H5Heit413WeIRph8hmiDS8weJe8Gx6jVyhuboe0qneQB0QM87JJ3vUYg0T4QzSZs3rgSPHL7nq7dj3c+vW+nGpOoS8zoWc/GjBPrAqrzG9wwMH4SZEPi4WA88OBX6ivOCl4nLDjyawk1gFFTgUFyoXlIyc5gCdh1qU6MzLUhT8lOlGVt++G1HzJvswW5P++U48mSlSjD2rrV1XleMe6Em0vLGq2LoVcCMUV79N0Oikj9fGI97DrR7ygTu6Kzwa58qezYbOo4+ICmHv2hp/35p7/yn9AfgfJIvV+YGns0dQRDz8IZwkepIdzbzPRGXVG3WEP83kvF4D1umhq8906VbT6JVORSkouLICfriw4tM7d5Y9dovuIhxmxhc0LYuo9NEdvzBCFGq/iVZoYgBg4UZvrNH7+BO4azmYct/4KSLcHzOluExqJfskXs9cJ+pxFoay+QPbaM3Ww2G77nJHfX8DWJdCUrZcoxbVCuizwul2WWNN9H8YS14NT2sHY+JPfde7mh/djCd8j+HGQ/qkv2ywgrlF2yRaxqRqCp/UiZfT2yR57r7Mw3iQQlW4wxTUDS4Uj3RQId6QmdaY5O29XkDuYoe9m7S6FZrLtCx+5q0uCQanSF0NnLA13QY2Z44QKxvbfPPNZrbi+LXgHbn48TbHm4Ja+seGaHUfc4rc6ZProERANL67omW5g2myAdW79CENfzSW4u9Rm+Dq/ZKnS+ZW9+gYXhK/odIN918B+lkMVQynVF5fDYiRXw/JI9XFVGeGxcSiwrvb3YMRtE0+/BfF7XXiDXlgYxOloN35rahOyglUxZ0iTSYm6vq1tfPQAjw9m8OaXNp8ToeP5BQcs6FNP6QBEvnxm2eLzHMnC0JKgU9+aiMPPQ+l+7DkxuhtVAoP+IbsCp0UGFipTRgcT3dgOMQ+YIq/85HDJIsqCbJP8Kn4Pd4W8XLxbdpnxpb5a+tNcjkC5dTARG9ahwA4qyfRLyBXQIC1BObLjWrFamY+TKFDpMrdQrOfM53U/cB7OusP137UGDG5tjs1zAnfE2fSc+F5Ox2ywSq8N7yqaP9lc1gTlw06K9CYgYuHdcrbvM+bOexg20+8SrYiQ2158g/g4Wf08UfweJv5Xib4H4Wyj+nsS/C/+E72/H9RNcP8f1AK7f4VqBaxk=
*/