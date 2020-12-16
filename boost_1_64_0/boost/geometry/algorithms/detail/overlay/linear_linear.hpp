// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle


#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_LINEAR_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_LINEAR_LINEAR_HPP

#include <algorithm>
#include <vector>

#include <boost/range.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/relate/turns.hpp>

#include <boost/geometry/algorithms/detail/turns/compare_turns.hpp>
#include <boost/geometry/algorithms/detail/turns/filter_continue_turns.hpp>
#include <boost/geometry/algorithms/detail/turns/remove_duplicate_turns.hpp>

#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>
#include <boost/geometry/algorithms/detail/overlay/follow_linear_linear.hpp>

#include <boost/geometry/algorithms/convert.hpp>



namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


template
<
    typename LineStringOut,
    overlay_type OverlayType,
    typename Geometry,
    typename GeometryTag
>
struct linear_linear_no_intersections;


template <typename LineStringOut, typename LineString>
struct linear_linear_no_intersections
    <
        LineStringOut, overlay_difference, LineString, linestring_tag
    >
{
    template <typename OutputIterator>
    static inline OutputIterator apply(LineString const& linestring,
                                       OutputIterator oit)
    {
        LineStringOut ls_out;
        geometry::convert(linestring, ls_out);
        *oit++ = ls_out;
        return oit;
    }
};


template <typename LineStringOut, typename MultiLineString>
struct linear_linear_no_intersections
    <
        LineStringOut,
        overlay_difference,
        MultiLineString,
        multi_linestring_tag
    >
{
    template <typename OutputIterator>
    static inline OutputIterator apply(MultiLineString const& multilinestring,
                                       OutputIterator oit)
    {
        for (typename boost::range_iterator<MultiLineString const>::type
                 it = boost::begin(multilinestring);
             it != boost::end(multilinestring); ++it)
        {
            LineStringOut ls_out;
            geometry::convert(*it, ls_out);
            *oit++ = ls_out;
        }
        return oit;
    }
};


template <typename LineStringOut, typename Geometry, typename GeometryTag>
struct linear_linear_no_intersections
    <
        LineStringOut, overlay_intersection, Geometry, GeometryTag
    >
{
    template <typename OutputIterator>
    static inline OutputIterator apply(Geometry const&,
                                       OutputIterator oit)
    {
        return oit;
    }
};







template
<
    typename Linear1,
    typename Linear2,
    typename LinestringOut,
    overlay_type OverlayType,
    bool EnableFilterContinueTurns = false,
    bool EnableRemoveDuplicateTurns = false,
    bool EnableDegenerateTurns = true,
#ifdef BOOST_GEOMETRY_INTERSECTION_DO_NOT_INCLUDE_ISOLATED_POINTS
    bool EnableFollowIsolatedPoints = false
#else
    bool EnableFollowIsolatedPoints = true
#endif
>
class linear_linear_linestring
{
protected:
    struct assign_policy
    {
        static bool const include_no_turn = false;
        static bool const include_degenerate = EnableDegenerateTurns;
        static bool const include_opposite = false;
    };


    template
    <
        typename Turns,
        typename LinearGeometry1,
        typename LinearGeometry2,
        typename IntersectionStrategy,
        typename RobustPolicy
    >
    static inline void compute_turns(Turns& turns,
                                     LinearGeometry1 const& linear1,
                                     LinearGeometry2 const& linear2,
                                     IntersectionStrategy const& strategy,
                                     RobustPolicy const& robust_policy)
    {
        turns.clear();

        detail::get_turns::no_interrupt_policy interrupt_policy;

        geometry::detail::relate::turns::get_turns
            <
                LinearGeometry1,
                LinearGeometry2,
                detail::get_turns::get_turn_info_type
                <
                    LinearGeometry1,
                    LinearGeometry2,
                    assign_policy
                >
            >::apply(turns, linear1, linear2, interrupt_policy, strategy, robust_policy);
    }


    template
    <
        overlay_type OverlayTypeForFollow,
        bool FollowIsolatedPoints,
        typename Turns,
        typename LinearGeometry1,
        typename LinearGeometry2,
        typename OutputIterator,
        typename IntersectionStrategy
    >
    static inline OutputIterator
    sort_and_follow_turns(Turns& turns,
                          LinearGeometry1 const& linear1,
                          LinearGeometry2 const& linear2,
                          OutputIterator oit,
                          IntersectionStrategy const& strategy)
    {
        // remove turns that have no added value
        turns::filter_continue_turns
            <
                Turns,
                EnableFilterContinueTurns && OverlayType != overlay_intersection
            >::apply(turns);

        // sort by seg_id, distance, and operation
        std::sort(boost::begin(turns), boost::end(turns),
                  detail::turns::less_seg_fraction_other_op<>());

        // remove duplicate turns
        turns::remove_duplicate_turns
            <
                Turns, EnableRemoveDuplicateTurns
            >::apply(turns);

        return detail::overlay::following::linear::follow
            <
                LinestringOut,
                LinearGeometry1,
                LinearGeometry2,
                OverlayTypeForFollow,
                FollowIsolatedPoints,
                !EnableFilterContinueTurns || OverlayType == overlay_intersection
            >::apply(linear1, linear2, boost::begin(turns), boost::end(turns),
                     oit, strategy.get_side_strategy());
    }

public:
    template
    <
        typename RobustPolicy, typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(Linear1 const& linear1,
                                       Linear2 const& linear2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator oit,
                                       Strategy const& strategy)
    {
        typedef typename detail::relate::turns::get_turns
            <
                Linear1,
                Linear2,
                detail::get_turns::get_turn_info_type
                    <
                        Linear1,
                        Linear2,
                        assign_policy
                    >
            >::template turn_info_type<Strategy, RobustPolicy>::type turn_info;

        typedef std::vector<turn_info> turns_container;

        turns_container turns;
        compute_turns(turns, linear1, linear2, strategy, robust_policy);

        if ( turns.empty() )
        {
            // the two linear geometries are disjoint
            return linear_linear_no_intersections
                <
                    LinestringOut,
                    OverlayType,
                    Linear1,
                    typename tag<Linear1>::type
                >::apply(linear1, oit);
        }

        return sort_and_follow_turns
            <
                OverlayType,
                EnableFollowIsolatedPoints
                && OverlayType == overlay_intersection
            >(turns, linear1, linear2, oit, strategy);
    }
};




template
<
    typename Linear1,
    typename Linear2,
    typename LinestringOut,
    bool EnableFilterContinueTurns,
    bool EnableRemoveDuplicateTurns,
    bool EnableDegenerateTurns,
    bool EnableFollowIsolatedPoints
>
struct linear_linear_linestring
    <
        Linear1, Linear2, LinestringOut, overlay_union,
        EnableFilterContinueTurns, EnableRemoveDuplicateTurns,
        EnableDegenerateTurns, EnableFollowIsolatedPoints
    >
{
    template
    <
        typename RobustPolicy, typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(Linear1 const& linear1,
                                       Linear2 const& linear2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator oit,
                                       Strategy const& strategy)
    {
        oit = linear_linear_no_intersections
            <
                LinestringOut,
                overlay_difference,
                Linear1,
                typename tag<Linear1>::type
            >::apply(linear1, oit);

        return linear_linear_linestring
            <
                Linear2, Linear1, LinestringOut, overlay_difference,
                EnableFilterContinueTurns, EnableRemoveDuplicateTurns,
                EnableDegenerateTurns, EnableFollowIsolatedPoints
            >::apply(linear2, linear1, robust_policy, oit, strategy);
    }
};




}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry



#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_LINEAR_LINEAR_HPP

/* linear_linear.hpp
L7Eo4uO8/xzqlfaxujmmBuVa6B+mf83dKX9wBffq8F89WPovv9cmg93JYF/qlswanckUqWTq6X9GKhmCigm66Z5MULsG0HSA2D1VWmZxr5OpjVSptTLcnrsycwtI/9OU/276N6T9YVenvpOwd9eptMttMu1Wm4xbIOOOQVwoUTJYHaO2hOjNX3OozXaM2/a/+ZeyP11IO6JqkknYTJP9VdXtoabDfvEhuaGHQwdvdi5hiXzVTRDU/PadLorjrE8MtlrEHbV98YIKW+INk+8g6u08189+yoBwGZbwcCbcQsicDEh5bAZdkA6VkLq4LJdbh7GKlPr9uSDEX0htMN/5qSQ0vmRTG/ENclrrTNInjyAwU7gCKSBSmj5ZqaJpiMaBfT5QBHSHNM7MUZ9jUUb1Kg5wwNd8AUldYSZ1dUZSev33SBlVIzGmMuxumeijyvJFpXz5HUaexL+QdEfmOWLkc6S2F7NyZa3sZq24vTjDOF6V7ioENCN6IjMLlWhgolW2jJLDLMwFZC/mEdb9baIPbX7Spw4+qOnNsY3St9Vogi+VrskY2ExY9Pvh1MXSFL3YWBAEMH6FERCLkQBH2LqfmwZXFM5e+mXi7A+QuPHij6XIhx7PWJNGq1bK0M2V5WcE+1OfqvZwen+5Qe4vxQYSF7yL5pwu+M0dDZP6uTJtC9JmPdaxOSMhJszqTGN17lPV8cQOmsZp7pY4cS4x5x0T9AsJqiRoJ0A+GM9BEvGTxdrhfBd6Io/Lj95oU9LX/ohVFly0dOcz0k7pesRmmPirCDyVH9sBkR+bAZmhosNyEyENaB9CqI9+Dtunje3z5J2sxuP0QM4y4LIyXh6KZgWnPZhj7Ad2xUPGXuBs7CYI3zJ9extnfgYwlcaMh23okKn4SmKRcPhAiKEAsUpAU7i2y5iTQJwzAIP1LQ13vX+nHAymQzKimuvCRTbTcE4LwPv1Qo+8LDgRQ1ESciN9qIvo4pMMJgRJIa5Dod/2rlSGOjJ8pwsZPi1ha2dazYPI1yFeQDxZKAv1TAFf2z+Q6LGcIRkkjA/iB/QxB5XtwP84a1V0jq3xTUfubhol+kwutFkR+6PxHOeaeGFk4KO+xAaf64NZW2MBxK0S2yQCp1AXbWa8b0E7laZwmzDT17CzjfvBC4WWCkqfwJ2VrkuVaMa4ZxMOp0/8sPJRnAeCX2YfEK3SEdTQoWf7x4jzZNKTWJj0eYDR7oYPu6Ju0meptaVidak8hFD5WUa3Liu3qr3NSWitoOaP9DG9xEKJ1hcgIfr09kVryxUKyp5lgDFwx8rMnBbHDmaWlCUZOgD+J8DfK5olohmHO1Fqa0ZNxTazsgcPwuedQ5k+6Sq9Ss9N8Ox+7MfmXBxkphXAA1bsajjSaNeaRLuJABtjfoS5KFsh1MJDZuOcmRl7ZLfY7ZoZ+3jGXoXY3f1U2SLHxcqQWObFwG8coDvsoJvxd8Dtj/QSC+WSk4XQ4IE9DERthnWeMJ4r8B3EsxTPz/CcfpLVEsdzCE8WDFePxDMajwuPB8+FeBbguRvPRQOtllY8b+OxQrDRB08JHjeey/HchOdNPNogq6Ufns/jCeD5IZ438axDGjvxGHgeQ1k+QZ598W2xjrCNGDFCg37IiGP95YxwmF9QKMnLP855ZICCPsef0LcfPvoPGDGi8MSTTh54yqDBRSOGADJ02PBTk8E+t+X/v///0r9Q08HQQb9zyX0WSQeCcvn1q10JnYRgX1zgoYMSbB9qtfgVJVhbaG5sMUDVnpcfKUeRLcNRmHKEIk/gu0g64DHRdjTM1wNsqs1MSEsmhO30dSjMd/F8D8+P8NTjeQDPFjx78OzDY3H8VT9r6suW/NA=
*/