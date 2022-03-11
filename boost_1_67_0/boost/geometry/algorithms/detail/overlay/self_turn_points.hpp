// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SELF_TURN_POINTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SELF_TURN_POINTS_HPP


#include <cstddef>

#include <boost/mpl/vector_c.hpp>
#include <boost/range.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/detail/partition.hpp>
#include <boost/geometry/algorithms/detail/overlay/do_reverse.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turns.hpp>
#include <boost/geometry/algorithms/detail/sections/section_box_policies.hpp>

#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/util/condition.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace self_get_turn_points
{

struct no_interrupt_policy
{
    static bool const enabled = false;
    static bool const has_intersections = false;


    template <typename Range>
    static inline bool apply(Range const&)
    {
        return false;
    }
};


template
<
    bool Reverse,
    typename Geometry,
    typename Turns,
    typename TurnPolicy,
    typename IntersectionStrategy,
    typename RobustPolicy,
    typename InterruptPolicy
>
struct self_section_visitor
{
    Geometry const& m_geometry;
    IntersectionStrategy const& m_intersection_strategy;
    RobustPolicy const& m_rescale_policy;
    Turns& m_turns;
    InterruptPolicy& m_interrupt_policy;
    int m_source_index;
    bool m_skip_adjacent;

    inline self_section_visitor(Geometry const& g,
                                IntersectionStrategy const& is,
                                RobustPolicy const& rp,
                                Turns& turns,
                                InterruptPolicy& ip,
                                int source_index,
                                bool skip_adjacent)
        : m_geometry(g)
        , m_intersection_strategy(is)
        , m_rescale_policy(rp)
        , m_turns(turns)
        , m_interrupt_policy(ip)
        , m_source_index(source_index)
        , m_skip_adjacent(skip_adjacent)
    {}

    template <typename Section>
    inline bool apply(Section const& sec1, Section const& sec2)
    {
        if (! detail::disjoint::disjoint_box_box(sec1.bounding_box,
                                                 sec2.bounding_box,
                                                 m_intersection_strategy.get_disjoint_box_box_strategy())
                && ! sec1.duplicate
                && ! sec2.duplicate)
        {
            // false if interrupted
            return detail::get_turns::get_turns_in_sections
                    <
                        Geometry, Geometry,
                        Reverse, Reverse,
                        Section, Section,
                        TurnPolicy
                    >::apply(m_source_index, m_geometry, sec1,
                             m_source_index, m_geometry, sec2,
                             false, m_skip_adjacent,
                             m_intersection_strategy,
                             m_rescale_policy,
                             m_turns, m_interrupt_policy);
        }

        return true;
    }

};



template <bool Reverse, typename TurnPolicy>
struct get_turns
{
    template <typename Geometry, typename IntersectionStrategy, typename RobustPolicy, typename Turns, typename InterruptPolicy>
    static inline bool apply(
            Geometry const& geometry,
            IntersectionStrategy const& intersection_strategy,
            RobustPolicy const& robust_policy,
            Turns& turns,
            InterruptPolicy& interrupt_policy,
            int source_index, bool skip_adjacent)
    {
        typedef model::box
            <
                typename geometry::robust_point_type
                <
                    typename geometry::point_type<Geometry>::type,
                    RobustPolicy
                >::type
            > box_type;

        // sectionalize in two dimensions to detect
        // all potential spikes correctly
        typedef geometry::sections<box_type, 2> sections_type;

        typedef boost::mpl::vector_c<std::size_t, 0, 1> dimensions;

        sections_type sec;
        geometry::sectionalize<Reverse, dimensions>(geometry, robust_policy, sec,
                                                    intersection_strategy.get_envelope_strategy(),
                                                    intersection_strategy.get_expand_strategy());

        self_section_visitor
            <
                Reverse, Geometry,
                Turns, TurnPolicy, IntersectionStrategy, RobustPolicy, InterruptPolicy
            > visitor(geometry, intersection_strategy, robust_policy, turns, interrupt_policy, source_index, skip_adjacent);

        typedef detail::section::get_section_box
            <
                typename IntersectionStrategy::expand_box_strategy_type
            > get_section_box_type;
        typedef detail::section::overlaps_section_box
            <
                typename IntersectionStrategy::disjoint_box_box_strategy_type
            > overlaps_section_box_type;

        // false if interrupted
        geometry::partition
            <
                box_type
            >::apply(sec, visitor,
                     get_section_box_type(),
                     overlaps_section_box_type());

        return ! interrupt_policy.has_intersections;
    }
};


}} // namespace detail::self_get_turn_points
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    bool Reverse,
    typename GeometryTag,
    typename Geometry,
    typename TurnPolicy
>
struct self_get_turn_points
{
};


template
<
    bool Reverse,
    typename Ring,
    typename TurnPolicy
>
struct self_get_turn_points
    <
        Reverse, ring_tag, Ring,
        TurnPolicy
    >
    : detail::self_get_turn_points::get_turns<Reverse, TurnPolicy>
{};


template
<
    bool Reverse,
    typename Box,
    typename TurnPolicy
>
struct self_get_turn_points
    <
        Reverse, box_tag, Box,
        TurnPolicy
    >
{
    template <typename Strategy, typename RobustPolicy, typename Turns, typename InterruptPolicy>
    static inline bool apply(
            Box const& ,
            Strategy const& ,
            RobustPolicy const& ,
            Turns& ,
            InterruptPolicy& ,
            int /*source_index*/,
            bool /*skip_adjacent*/)
    {
        return true;
    }
};


template
<
    bool Reverse,
    typename Polygon,
    typename TurnPolicy
>
struct self_get_turn_points
    <
        Reverse, polygon_tag, Polygon,
        TurnPolicy
    >
    : detail::self_get_turn_points::get_turns<Reverse, TurnPolicy>
{};


template
<
    bool Reverse,
    typename MultiPolygon,
    typename TurnPolicy
>
struct self_get_turn_points
    <
        Reverse, multi_polygon_tag, MultiPolygon,
        TurnPolicy
    >
    : detail::self_get_turn_points::get_turns<Reverse, TurnPolicy>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace self_get_turn_points
{

// Version where Reverse can be specified manually. TODO: 
// can most probably be merged with self_get_turn_points::get_turn
template
<
    bool Reverse,
    typename AssignPolicy,
    typename Geometry,
    typename IntersectionStrategy,
    typename RobustPolicy,
    typename Turns,
    typename InterruptPolicy
>
inline void self_turns(Geometry const& geometry,
                       IntersectionStrategy const& strategy,
                       RobustPolicy const& robust_policy,
                       Turns& turns,
                       InterruptPolicy& interrupt_policy,
                       int source_index = 0,
                       bool skip_adjacent = false)
{
    concepts::check<Geometry const>();

    typedef detail::overlay::get_turn_info<detail::overlay::assign_null_policy> turn_policy;

    dispatch::self_get_turn_points
            <
                Reverse,
                typename tag<Geometry>::type,
                Geometry,
                turn_policy
            >::apply(geometry, strategy, robust_policy, turns, interrupt_policy,
                     source_index, skip_adjacent);
}

}} // namespace detail::self_get_turn_points
#endif // DOXYGEN_NO_DETAIL

/*!
    \brief Calculate self intersections of a geometry
    \ingroup overlay
    \tparam Geometry geometry type
    \tparam Turns type of intersection container
                (e.g. vector of "intersection/turn point"'s)
    \param geometry geometry
    \param strategy strategy to be used
    \param robust_policy policy to handle robustness issues
    \param turns container which will contain intersection points
    \param interrupt_policy policy determining if process is stopped
        when intersection is found
    \param source_index source index for generated turns
    \param skip_adjacent indicates if adjacent turns should be skipped
 */
template
<
    typename AssignPolicy,
    typename Geometry,
    typename IntersectionStrategy,
    typename RobustPolicy,
    typename Turns,
    typename InterruptPolicy
>
inline void self_turns(Geometry const& geometry,
                       IntersectionStrategy const& strategy,
                       RobustPolicy const& robust_policy,
                       Turns& turns,
                       InterruptPolicy& interrupt_policy,
                       int source_index = 0,
                       bool skip_adjacent = false)
{
    concepts::check<Geometry const>();

    static bool const reverse =  detail::overlay::do_reverse
        <
            geometry::point_order<Geometry>::value
        >::value;

    detail::self_get_turn_points::self_turns
            <
                reverse,
                AssignPolicy
            >(geometry, strategy, robust_policy, turns, interrupt_policy,
              source_index, skip_adjacent);
}



}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SELF_TURN_POINTS_HPP

/* self_turn_points.hpp
0NatxD9pofhrybPt/3i3IWSBoSkUThAPThuOM5HOIVKGfVbzI8Jt4+PYPVa6pj8taccWXpFeeywOHFv4N/gL7n0LOpPV2mH4iVqjupM54tvGnMhekdoao7ry4lQOHFihnUMvBHf4XN1xLWn/Y3xVP0ee+0ua0tYbctaN/aM9rSPHYj+bNfLbRfyG7/tlrOY6IflDg3g3+IlcuS2EO9Dbxt1Mu6zm/0E5cCyc3OMfaPbqyr9/SnVwP+2X7lqxHou35g9tTp6wHtviO3CEN3hGrsUP6U6+sWwbp5hpNxPWOF7gczFsbnLqWfQfHVm8ANgtElfKQ61tH/MvFMin0bm8QPdEtdNfYo52S4OMCxNn1ohQXWEplQLCWC3s6m663ocD3eAO9ylXvPgbHLp1SslHCZtmXYMDeWdMUXvDv4CF419XWwwsBXwW8D7LLQ+meKBw1pxBDEG2GiapJMwFAx/v95sVuNRAeAOHDkbl59iFOiwXrItcvZ6r7yuA1+8ruYD1736GX8jAs3MZF61Lhu+YDDH6Ynr8Li1CDHzIJp36jiKH9DYnnRmPyD8krEv98vsWkT525H25i6WRHm9K05cKG+E91bkH9ufywzxd/cJeDtmNdzqzGaSJ3sqPgyp+GD4G7ZbWlEfg4RO+le/AnYR0n4ft6nSH/CIPuviTc/FvdzNDJU8U63aQ6CN397zrLxi4mNiVwe6mT/Yo3tETQ0kKnfLE7kmKMl2HN6nVB9cDda/hSOvQ74uXJW1D2j+GA6W5vpsVtJu1p+sk6Wh02o18l8OSViWM3GzZzvCLzbtGHaUvxWHhpQRFM+8+g+4h9scJ9xy0+yheLdsCa/sq7HlHllt0DnBPEjna63QsA2UaTngeJUgOhMl+9294yXkkEjdLC6Pzvz68x8FIoVfTtk1vqvt/yvFeXSKEENjJFZiD3F02YyhqMcfr3P0PFLYqiu2eXVKE3U/oSTks2peM2v9Czxfb96mc+soPTaSLu+DF8Pf1d4bk41rYwRxthXRb4c1pwFLhKYdn4/T5HKKSDqTBe/HJRiiDT2FxecDh8ijbSTyrNSPgVsnRy+BzmpP96E8YsUP1PWnXWmHwc/YaGUKIohD/MJ6C1DEe1VvFXTgZw+9uqFqY2EgtvD+fytd9tTBwqTx47nm7pCVG0Iytu8qt8EjVpu3ZclhZI/KXQ4hsXKhiVrAnpFCidn2hU/UuOLAWkT83pfrQMqLL2nadT/I+NvjZeaUXGz2ErU04TCH7ucTz+gxdvuXbPoO9be8uKiKOfnC8iJsBOPuWpK1inzG/sjDttZRrTNFz4c2/qFLh6crC+WeFC3Fa7D+QwjpDHDKbjqPkrjisFty0tKOdx/4dVR8aFO9/jka73shsMFkVu2xBNtR84fqtvpaJYyDHNcn7nt8Nr1gKZydBU8fSipSgperVkeZulAcnAe21nH/XKNexc2TS68kpulUtLwj1KgDoRn79IbBhEIdvKD1uOcrmToJiO5wpS7wr8f6DW343XJmH5lLP4NJK8BuWci7LUktlY+HANq6ctoPGfHqJ7CPI48ssug4o8ovtGpQwT+DH0jjNAs/b+pduMJwy3Y8r7DSuyb+3LeoWhM75QHU9s4ekF+hSzjymE65II9J8pu+Lhivype4/+A0HwPTSH5clNQbvkudzbqI3XFXTm7cjbKizXPzebT87ZF07/hPmAQYDFf4ui6t8xXU7+DsMn3YoTumB6hzdqtfyJdFi9veoxo/rZSHyqykQwrpEtSQHSLR1M7dLoc/aRmIaxlnuhCiV5n2aqSYitrxU/GEoxcKWW/qgsD7CSlZeiPDoydbX5SdYnOYwGeXncV/ElbZlxHPJalWSrAq0+39r3+N0eDqUGmw5FSdszcdsg2hdCybp+MVnzFsni3OTrsTWSjMQKtaiiuOKu5ZsexlY/8sZpeMcEeDMrE5CO6v+I8401N1KVDRhEDPf1cvQ3ofI3S5WT2EDd/+xe/KBsp87fHHxgWangcdrLUU+NA7xi7a2bDhT51AJk0Dyy7PgeNCL4Opu99oreLWYtXbOaM8AcbJL+uVhQHWpFugHkuPFSNpVTjKbeZkVjKxr0wjAac2fFZwL3QkvpN8La/rlNziQxo7wK6Ci1V4J7/pxdn0F0YQ6NmbPNdsK/ZaceeltxLnn/t6eusoNxpsQilRNUV+4e/SIP1cFHlUcSdU8oveGQnt8S0k2HbgQGr4M+UZu4v6s4iROmvJyXFgs0Zjqq2I4y8eR8srigazmN64TXlbXW8zNjh9uVNNZGq6Ze2NG63WwMjno/CSy0U5t62Bhz97kgS6OflA9ABF9quus5/0zoUrx7UsQEiZLdgWKQSMan7EBtcPVxAwAqgmjNKqtcqT727rB+Hab7MFYkSbJZFFiG2TC1FVE+fZKT7NCuPhUrAxhZQn6IVH0KU203PIoC1R3cZxm7Yre2JbSD3Fgi4XwzxNC7n3xYiFrk5iQ+xImcojaf+W3okNc3OATI7VjtDgvaE5DvAGmjrKMV33W+3EXjfPRn+k7uKRebhAWvrtzMNi3bDxey8OIZKEKWibxWxhVR4vJr6klEYv2ByvkQ1KHXfAFIc+CKD/ZjkL8VYfEivxKzFMWja/W1pcrOEv/RnBsgp09dkFT9HDiywfgxyt00/cM1hcKwsfZ1imA11cYPPlBFfGA7ihzh+uSvdLOgL83OLjDFRol2Phm36tK/8Jp/1IxXYdFCxzHLrXFtduUWK3LWz+HdTc0yLv+wcsSDLkgfbJ7RmlwzbAczJ/5cg5/msA/yWxhWWqldZWAAXP0nlcGfcgvXRNgqwuGEriNq/qOogEEr3adEHspLKJxb/FjTzRNBTR/t/RRYRcXgrZntiiZW6Kg3IgJS0UWgiRvJclC60ZEwbbFjCrHaUBCL/nibpNkTWHjkShr/oOiYLyhjU8a+pb+Vibvllqmb2btk/7Gnn5Oo3YxsThC5U0UpkZ0argq/lDwHEcrSFFgw8c45qc6IKc6AF+Wb55UTUX1c4ZP1hqRap7iEIMmEmUt2UnVnSY+SeBHsT9Lw38ptYqqa7bpTlxINgzJwtRm0jJrgmpuawll3lSApLISs3MxGXOlpcfiT1pO8SZQYUKPYJjD5tEvfhtbROJ0+x6PWwPhSn+j+IpVauhlWNyOmY5R3yTvlzz6NS7arHxAXfgFstPnbc0f76rSi5buHT8aSYlieo71dQx9g1aN608ninO0vL7sIVxcHSd31OjPOCjOpcxR2zjD0UWqn8VBl8xqojScOKYE6esp/2XNKBsklrFjp6PWV8tXIRcgllECMObVHLBkRkSqRxe/fj34QZ5a5hP0oGSSKa+QXDYR/ADcA990iA+wpEvWsgwMUnbFGcKdQYw948C873Bnj7PU/9WU2ot5K7gjzosWpnBGlnEewNfHcQd6U1HAnpfJ5m3Xe6Ov+LRR/PthkGeA8W5mnRIizG40pvpb7JNtCT+DXvgXUMMyzau6FmjkPYcgu2YQ+AZ4B6Sva/cfj7JkFfWiBL6h85Ht36pj3A7GnHxAPLOuNGch4RNgChPDS3W3o925Nmcst23aw/aluu7n1n5F5VUUZIzwM2SuvRkdAdxQVxh+2h9YRohdf1ALXwA/3wI2ZeppZqXH3enn4Q6xGWelkL+n/iukyU08pAZkd9KPccoYJJjm08TKcmol6NK0aSZM0BDRjznKwK+PrZZeQwiDcIL9SCl2UKAlPpw6fyWWTtGWc+Ppgxh9OeYgKRm6Lxd4hN9+1uQKJGUg36HIFskzFTMEdTKOTSQIMY+ZJGyyjlUl6NGP/ZQZluMM+s/7WYxzKXzUN25EVHpMKoBUqgyJUpR2PrGAISEAYbQ66Ry9XjjeCBfR8S/5yUzEf4A30wACLP3T6f0LN6nznB/yyexf3UjiEaFLV0FgrcWm8CfcMKPJ+hTd1bAePR6FFAXn7FoFUxJ/fAUu7LYsl+7PV5gzERf+wFftfKlRO9tfhG0/7fO1x2lXjH+a/Blt3nzbvhWCCAt3Ae+Fgfd+J1k7ryegm7leAmgJ+DC5jV9ekNR1RC8IQdrv38mLBrzG4bAGSdRqNusJhx+G1iRomV+/me4il0Xzwun8LiMlsuICXjyqqDLvhEXZak/1NgqRgvagTY4o8MaesBiaOEw3TqhKl1kbiNISl24M9yS+1KVC4ZLDW3YMBE2ElCBNrDWHX7rXD0FdVhbYk6+FQpuZuIwpojmWjyQqoDu6J4wOIyU1LCTa0gdGotrKNY/xflvpVRJZXYGORPWVf6ruNYapQWbhuKnsRYZh9k3bPDn4xxMeBzSn4K+8jZ9WFdf9nb5p8m9K7+hxgUFTpm7OlkR+y5OCRHd0nY3F8oT6MZdYBTBXC9akXrQgltleGN0Lk0o4GcuZ/e/uy5o+sYw9VYci9ZgZsUw7scw0XprV7+bhIR9nZHjZOULL0uEfMHzK7Oi4Q4Ff+WcpMNR873crtyUWy/SuRFDsvf77SAjfsGlc/Js9UMl6v2tLsvZILl9Nc+FzI5hrGxO+p6QQlu3EQrhHFR5o+u68d20q6LjHYwpo/dXaJ6lcowf7OCpJE/HgODTUb6FX6b4oSWNUyWp2JbVc7W5kURfJYUOXb4e/Ub/KE2hXaOmHaSRKoPUDakhAjSXLeArZOBfvq1dh7YgS7ro13np13VWWuHkycvqVFp+eIG51JHZoZL4yVWlJ+rczxyZ+ZBgFrdWAA9VMh13C0JFJRaMj67OauEOdc/cie9iSl6Pff2vQiz1Pfv89QSeXkWBwXwhchUMgb58bEEMg97fIs2Pe+Evq+UsRg1x4sjCc6EFZsk79L5pLrTZSSBfZpXljcCk3no7KXkd05pQPSc+Pec6byLNAtLoNHhEavdRoDpNfPiFNHdq62WgWJLYsWQ7U4b1SfdD96SFUJEphd67yHAnGEbiRTVjWGCQjpYXRvgO2hxuWe//8Gx1VL1hAWTKKIy6lw/0Gg3MSTaERsdo3HSvi5wo4Ti6bg+vQKP6pv25stG8EN954NwzP6Ibdo9n+9z8XV32vH5pDb+47rFzPyZucMD9/Ysb5YWFiYorhrPFOVR8n10dxDhbNFtC8/3o4SeH1YJ2gZbpXLdOKnI/TLfiz4ZGEiddlXdpzP5nOdZ+DA+KeeO6e6bSYzuLnuhc+8aNgVvunE6d+H9cUg72nrS34O6VVQrvP+UNQTkgRqW+f6ZwrdP1Ifu4GWP90Im+krV3c2hyIbZSatEWDxVLvrlH8TZhebfXduvi0gV+VR+br4Oi6zDw8UJ5jAg8eiURKZq0POz+88orBzjOJytrBAtGlsr6ZSQI1zdDsKpbI+DJpfL2LyJjQLr5piMj459HEehGRMbGv/vL0FKZNkLq2oLAEC0a/WZVh2C/GqNQmd6J9fvKvNj4NLJmcHaPrKUTGak68+osGSgQbCdba75mVwmw2PclN76ZXy65OvCtj60tnzh/MNg0LR29ay+b/Jh5rKqPlCZ6/Ki+3l0T67FHahH92c0rLIoxY6/8iyXYnf9Qh1cjhFBvK4zxpFiNRKxUjTcT8iwhsFVVYraVW+N5JpbD5yq3Kw66Aui4HVbDHsnZju+YYZMsnoKAn6Zhx6qZUxqNZHp1kDVPUtVUUf1UUH13WP5pZZixvIIOnAIpnymBQwnPZcYEydvBm0JiEVWpYH7qMYkjIZjfeh2SYka0SqfzzJAMxq36v+6axmZKqOjT4ENxzmv3LSsKyvFU+V32ubFr1yq/MnHrJexzlPKn8dcVuaN75SOwvvgpQ8+9x6a7OX/xfnXSSLoaQjgxzkQNRh73Lp4aNSmQ+LKOpP14hhfDuXLJqg1ebmV956nV/pVz9jVQbHDoq+ZOjChrUA3n/rf1Iyq0V5pYUgTDuc/7P8X9bC26x92BEOTDQZeLfDSNmJZebkxA9Eo/uc1lyAdrvuvWW/QbEr1W4q6kszz317vr1lnZNlfpUfWwvyLWvqpQSQUNj66OmHKBmGW4Pxt04FvhBx7XBTNUnGcYNKR4nUZnFZVokH/bx9XGaOVr6xEFW0j3mdu+epC0qLJ7RdW6Z/YjJxKbIxMGBdFobC3qkBcgVtXxsCnSfTL+rkragZnnV/5z9w6Ns2cBA2aSgNa9M9Uq2IO6DWkVP2aug9S8QR9ImOI3YJ/pSEVduBB27UpnHaUJ3kU0GN4U1qaqLRlcupWpIdlMYu0/6K5+cy3YqNA92i0WB/7VgFD967RwpQmUM5UjjxNeb7OMuPJRkf/Z59lxbBry3/6CLxIFyeeqnrEhJyHYyljHIH7bqDeqnbCpTqvkOUjxyodV/vivnI9AqM7m2wMqG2if/KJtFu01C9qPNUc1nPmDEe/MUKhJPHVZjeqigTUIWrghRzbdI+i4d6k83/yPUnSVf/dToU771P7lgkjLTQ7CxbGg1a7H6qctQErK+gXzZrPTfzELxmj/flPNRIj8R/U/C0tn7v4x4Am2t/EwPo3/My2b1qVHVT8U+L9iqSlPN18VTY3KVwCoSN2QsUD8d/yobKmKwSIonAKgPRO7K/6Oar/VZAT7Mf8r9mz45C7xPLuqTQ2cuULes+QTkaj/LZiUiMwrFmfc+9wlAdkhB/vDybFC3lPtsTi9vPk2O7cEzPYiifC6jKk413+R/oPUTbH2C9epPgEDAIx3aTWqeJ77TpMzUuCReNtuj++nRkFDV/J66z42SoxSJOzR++i3wU5KqzYDnnf8JLD51BKY/lffwZUOfmj+vLCySYXowzFdQy2cPIy6dzadmwFt3gS0Sf8dTZXL9QVUk3oH7aWkaiVs5/77+cxWCmar5J+afHlDlKRJXGvv0ZICtbKj7/8DJ53g74FPsMWWfgOxnr7qgfkoB1jScOvfIz5nqRcDs89hQoD6zsPo2Kh19jlLrwJR/5Yv7PDt6nEkk/wGQKIOVTVX9s1O7cmy9J9c+Zctp/FMUeQ4P8yhgNU5c5K+HOWZmcqITHUWrhtjPNiFExT/k5eNljIdVXd3cbotLwGvJ/dKKSAPjmPbzJ2Vp/SWf0sJqw+dPVNKsJq2PkfDJ+tUtqqyk/DovncCWI3MTrgi/QhIvc8g5C67Eb83x1VMSq3fcWCqA3/wFSSCeJpuwUhswzlmsnRbij//Wh6EEW4P5Njf2j8tnMKNfTZsuQXEyOAFPNjhR8h9PK7uqu1D+04Gq6Qbn9qqu8FKFuWjZzHem5dieEpRaPlHtnwFeaix/VX7CRa67GPgdkwOgcvGXVUIdb0qOEOJ9PRIcpO8wWDgNpe+48Y8xoO1Tk1Q4+s2Gf6eYKQbEklHZT5B8r7+UDhTQZmfHzAYjruT+9A3Mzi23g5qR55ZcS4N65Rzd+Y+mLtkdhR8Mt7v6Y36MOk8do0hC3GqpG2X1ZGZ4J6NpFLxjcPyPeC1woS/evjVAl0JPXYKwPAVlErwD7Qq0hiD10o/GapzCIvkRUtrRNPaEiHAqiK/gqZ5OET9cQHuT51VAbdHFCxl2CFvZxpwvfecZqan4RPX/Qy7MlrYxzCafzTjHdx5p5+/RU3VmFtQRU3VvnoVRU3Mif4aPX5jv/8513NoDHhQiPfCZ/JEOoZkKFW4JUyWqvzh/4IScXFvT2h3xFzo0wY6ShW1eeSaqFVVoTwlo9P/3zT97noQPrXeNXOnybVsaFtbxKR8KCl2Rw09NeQ+BgoxVI2Dtdr+YYHNoeScnpGe6p2JI9GEB4V3gdEhshiPHc0Ypltuv++0vBVFnQ14jtCyGBXaQ/ZDHbt8AxeSJSoZa/pVKhseMgkpGRZzfjlXWq84FT7wuJNt0xgXIQRYIQHqxscAWjYMiUlCVgtzQFn8coiTYM2twe9GdjTq1GwoPO15hSZLNXFJMiGoSRfCL/sxdkVMmbo0E2vEUPvwzWA9UletSD5u/yu50hS6a8C4jL6qKKd7jxtasDkgucprXElT8YxCp7nOOkkWi/Y5Xyx99lMvw24U4c1QAoFZCkd/0W9t9/HAqZvbX6oqN4UoZoXCeVl3GGVUNqjG22Cj5hw4EMR/hHbcg84lxEEHkH72LX6+vddX6Kn1MnANGCRKCDT11RpQQV0SBJ7QZtLJ/thjfZE1JegpWV6mqNIOZuNUV6h3rfEJTu43jZvOYZXYbvPSZtz+3x3qkFZ1O9sGvMRKcn/27kcMYbs3e1P7YN8LmiIbijsSmW3dUF+wvHeqbsRBhe5Cew0efDEwYHuGzISah2blCHZ0NYZR3m139b81lcsEaHHqUX6z3BLpOUd+df1HnuWFHN/6gVrRblEI2oLxOsT/Pd3lAKJ5HMWyXsJ9GMV1UEnJJj1Wu/NU9zgHXt4FYBW3Jr1ZVgqoj5yJvk8A/K4Bchb9YnF5OGvS1xF/ZDPnvJXqoFANIaOsUzdLMMxGmNJGACAVDeK+6pqr8o8/1HLSe+vZSfWb6xnMkbTkkZjPsWo95RVFd66Cac2xlkdOMvtI/BMYzd+YFp9BzmIn8EIWz7DgbTLzHMErbPK9quE8P3ve2SchJL7agu0j/IXyQb5H1MHnvbf4n56zCov0oU5Sr7TzwrDvberzAqkBpAriL6tDnB7ILSQcc/rfV8hIhyOIPJFvu2hAe5a6CUWYKIC2JuL7Kc/2YOjw/xRs9kqhe+L7vPsUh6fmkS6C5oP6PFGM9A0Z5PEAVX05P6SjMuibSekOneVCnd1w6mT9/ndGXiX0k1Lrkfi5/3crPstTdGzizgCTkhsw9ZCX4DSqXqUlrA63oyn3vyrzenTl5WGYduyawpEmoa3ChIVFerufnbsqXFqowTw4KIqdAO03br2yE4YkDsPNEEvl66EcfHIOlF4lNP8oI6DOhi7bdR46Lg5l6hMIq5Q58MgtawAjO6HFyf6guVE626RBIMikJEPhTCffVDiTn2HZIWZzppSAwssx5i0zDL98saP72+gJpsleyb+3QjAARtVDYXwt2q8y1eWw1R22bJ6dT11DTo1Gw2H70YPTMql9G5m6VQjB4O/sEypuH5WknkuYQjoKCPdLhEhTjGrNl23k4QNAdwAVP746SsgqcfF4Mb7S5QzJ+Tj0UsFkhSRmgdP/HFAny0ZTyNoUCcRd5MXez2xC/iUmL/i0c12GqdKIyecv96WGA5LUTYvPZP+Rh6UQSQYZfPgLedQ8Bd7DsLSjLOeWRhddEoiFjUIqwjt6SiVA6WP/guN8=
*/