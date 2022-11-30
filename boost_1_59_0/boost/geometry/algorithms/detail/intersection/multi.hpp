// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014, 2020.
// Modifications copyright (c) 2014-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_MULTI_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_MULTI_HPP

#include <type_traits>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/geometry_id.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>

// TODO: those headers probably may be removed
#include <boost/geometry/algorithms/detail/overlay/get_ring.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turns.hpp>
#include <boost/geometry/algorithms/detail/overlay/copy_segments.hpp>
#include <boost/geometry/algorithms/detail/overlay/copy_segment_point.hpp>
#include <boost/geometry/algorithms/detail/overlay/select_rings.hpp>
#include <boost/geometry/algorithms/detail/sections/range_by_section.hpp>
#include <boost/geometry/algorithms/detail/sections/sectionalize.hpp>

#include <boost/geometry/algorithms/detail/intersection/interface.hpp>

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/algorithms/num_points.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace intersection
{


template <typename PointOut>
struct intersection_multi_linestring_multi_linestring_point
{
    template
    <
        typename MultiLinestring1, typename MultiLinestring2,
        typename RobustPolicy,
        typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(MultiLinestring1 const& ml1,
            MultiLinestring2 const& ml2,
            RobustPolicy const& robust_policy,
            OutputIterator out,
            Strategy const& strategy)
    {
        // Note, this loop is quadratic w.r.t. number of linestrings per input.
        // Future Enhancement: first do the sections of each, then intersect.
        for (typename boost::range_iterator
                <
                    MultiLinestring1 const
                >::type it1 = boost::begin(ml1);
            it1 != boost::end(ml1);
            ++it1)
        {
            for (typename boost::range_iterator
                    <
                        MultiLinestring2 const
                    >::type it2 = boost::begin(ml2);
                it2 != boost::end(ml2);
                ++it2)
            {
                out = intersection_linestring_linestring_point<PointOut>
                      ::apply(*it1, *it2, robust_policy, out, strategy);
            }
        }

        return out;
    }
};


template <typename PointOut>
struct intersection_linestring_multi_linestring_point
{
    template
    <
        typename Linestring, typename MultiLinestring,
        typename RobustPolicy,
        typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(Linestring const& linestring,
            MultiLinestring const& ml,
            RobustPolicy const& robust_policy,
            OutputIterator out,
            Strategy const& strategy)
    {
        for (typename boost::range_iterator
                <
                    MultiLinestring const
                >::type it = boost::begin(ml);
            it != boost::end(ml);
            ++it)
        {
            out = intersection_linestring_linestring_point<PointOut>
                  ::apply(linestring, *it, robust_policy, out, strategy);
        }

        return out;
    }
};


// This loop is quite similar to the loop above, but beacuse the iterator
// is second (above) or first (below) argument, it is not trivial to merge them.
template
<
    bool ReverseAreal,
    typename LineStringOut,
    overlay_type OverlayType,
    bool FollowIsolatedPoints
>
struct intersection_of_multi_linestring_with_areal
{
    template
    <
        typename MultiLinestring, typename Areal,
        typename RobustPolicy,
        typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(MultiLinestring const& ml, Areal const& areal,
            RobustPolicy const& robust_policy,
            OutputIterator out,
            Strategy const& strategy)
    {
        for (typename boost::range_iterator
                <
                    MultiLinestring const
                >::type it = boost::begin(ml);
            it != boost::end(ml);
            ++it)
        {
            out = intersection_of_linestring_with_areal
                <
                    ReverseAreal, LineStringOut, OverlayType, FollowIsolatedPoints
                >::apply(*it, areal, robust_policy, out, strategy);
        }

        return out;

    }
};

// This one calls the one above with reversed arguments
template
<
    bool ReverseAreal,
    typename LineStringOut,
    overlay_type OverlayType,
    bool FollowIsolatedPoints
>
struct intersection_of_areal_with_multi_linestring
{
    template
    <
        typename Areal, typename MultiLinestring,
        typename RobustPolicy,
        typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(Areal const& areal, MultiLinestring const& ml,
            RobustPolicy const& robust_policy,
            OutputIterator out,
            Strategy const& strategy)
    {
        return intersection_of_multi_linestring_with_areal
            <
                ReverseAreal, LineStringOut, OverlayType, FollowIsolatedPoints
            >::apply(ml, areal, robust_policy, out, strategy);
    }
};



template <typename LinestringOut>
struct clip_multi_linestring
{
    template
    <
        typename MultiLinestring, typename Box,
        typename RobustPolicy,
        typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(MultiLinestring const& multi_linestring,
            Box const& box,
            RobustPolicy const& robust_policy,
            OutputIterator out, Strategy const& )
    {
        typedef typename point_type<LinestringOut>::type point_type;
        strategy::intersection::liang_barsky<Box, point_type> lb_strategy;
        for (typename boost::range_iterator<MultiLinestring const>::type it
            = boost::begin(multi_linestring);
            it != boost::end(multi_linestring); ++it)
        {
            out = detail::intersection::clip_range_with_box
                <LinestringOut>(box, *it, robust_policy, out, lb_strategy);
        }
        return out;
    }
};


}} // namespace detail::intersection
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// Linear
template
<
    typename MultiLinestring1, typename MultiLinestring2,
    typename GeometryOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2
>
struct intersection_insert
    <
        MultiLinestring1, MultiLinestring2,
        GeometryOut,
        OverlayType,
        Reverse1, Reverse2,
        multi_linestring_tag, multi_linestring_tag, point_tag,
        linear_tag, linear_tag, pointlike_tag
    > : detail::intersection::intersection_multi_linestring_multi_linestring_point
            <
                GeometryOut
            >
{};


template
<
    typename Linestring, typename MultiLinestring,
    typename GeometryOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2
>
struct intersection_insert
    <
        Linestring, MultiLinestring,
        GeometryOut,
        OverlayType,
        Reverse1, Reverse2,
        linestring_tag, multi_linestring_tag, point_tag,
        linear_tag, linear_tag, pointlike_tag
    > : detail::intersection::intersection_linestring_multi_linestring_point
            <
                GeometryOut
            >
{};


template
<
    typename MultiLinestring, typename Box,
    typename GeometryOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2
>
struct intersection_insert
    <
        MultiLinestring, Box,
        GeometryOut,
        OverlayType,
        Reverse1, Reverse2,
        multi_linestring_tag, box_tag, linestring_tag,
        linear_tag, areal_tag, linear_tag
    > : detail::intersection::clip_multi_linestring
            <
                GeometryOut
            >
{};


template
<
    typename Linestring, typename MultiPolygon,
    typename GeometryOut,
    overlay_type OverlayType,
    bool ReverseLinestring, bool ReverseMultiPolygon
>
struct intersection_insert
    <
        Linestring, MultiPolygon,
        GeometryOut,
        OverlayType,
        ReverseLinestring, ReverseMultiPolygon,
        linestring_tag, multi_polygon_tag, linestring_tag,
        linear_tag, areal_tag, linear_tag
    > : detail::intersection::intersection_of_linestring_with_areal
            <
                ReverseMultiPolygon,
                GeometryOut,
                OverlayType,
                false
            >
{};


// Derives from areal/mls because runtime arguments are in that order.
// areal/mls reverses it itself to mls/areal
template
<
    typename Polygon, typename MultiLinestring,
    typename GeometryOut,
    overlay_type OverlayType,
    bool ReversePolygon, bool ReverseMultiLinestring
>
struct intersection_insert
    <
        Polygon, MultiLinestring,
        GeometryOut,
        OverlayType,
        ReversePolygon, ReverseMultiLinestring,
        polygon_tag, multi_linestring_tag, linestring_tag,
        areal_tag, linear_tag, linear_tag
    > : detail::intersection::intersection_of_areal_with_multi_linestring
            <
                ReversePolygon,
                GeometryOut,
                OverlayType,
                false
            >
{};


template
<
    typename MultiLinestring, typename Ring,
    typename GeometryOut,
    overlay_type OverlayType,
    bool ReverseMultiLinestring, bool ReverseRing
>
struct intersection_insert
    <
        MultiLinestring, Ring,
        GeometryOut,
        OverlayType,
        ReverseMultiLinestring, ReverseRing,
        multi_linestring_tag, ring_tag, linestring_tag,
        linear_tag, areal_tag, linear_tag
    > : detail::intersection::intersection_of_multi_linestring_with_areal
            <
                ReverseRing,
                GeometryOut,
                OverlayType,
                false
            >
{};

template
<
    typename MultiLinestring, typename Polygon,
    typename GeometryOut,
    overlay_type OverlayType,
    bool ReverseMultiLinestring, bool ReversePolygon
>
struct intersection_insert
    <
        MultiLinestring, Polygon,
        GeometryOut,
        OverlayType,
        ReverseMultiLinestring, ReversePolygon,
        multi_linestring_tag, polygon_tag, linestring_tag,
        linear_tag, areal_tag, linear_tag
    > : detail::intersection::intersection_of_multi_linestring_with_areal
            <
                ReversePolygon,
                GeometryOut,
                OverlayType,
                false
            >
{};



template
<
    typename MultiLinestring, typename MultiPolygon,
    typename GeometryOut,
    overlay_type OverlayType,
    bool ReverseMultiLinestring, bool ReverseMultiPolygon
>
struct intersection_insert
    <
        MultiLinestring, MultiPolygon,
        GeometryOut,
        OverlayType,
        ReverseMultiLinestring, ReverseMultiPolygon,
        multi_linestring_tag, multi_polygon_tag, linestring_tag,
        linear_tag, areal_tag, linear_tag
    > : detail::intersection::intersection_of_multi_linestring_with_areal
            <
                ReverseMultiPolygon,
                GeometryOut,
                OverlayType,
                false
            >
{};



template
<
    typename MultiLinestring, typename Ring,
    typename TupledOut,
    overlay_type OverlayType,
    bool ReverseMultiLinestring, bool ReverseRing
>
struct intersection_insert
    <
        MultiLinestring, Ring,
        TupledOut,
        OverlayType,
        ReverseMultiLinestring, ReverseRing,
        multi_linestring_tag, ring_tag, detail::tupled_output_tag,
        linear_tag, areal_tag, detail::tupled_output_tag
    > : detail::intersection::intersection_of_multi_linestring_with_areal
            <
                ReverseRing,
                TupledOut,
                OverlayType,
                true
            >
      , detail::expect_output
            <
                MultiLinestring, Ring, TupledOut,
                // NOTE: points can be the result only in case of intersection.
                // TODO: union should require L and A
                std::conditional_t
                    <
                        (OverlayType == overlay_intersection),
                        point_tag,
                        void
                    >,
                linestring_tag
            >
{};


template
<
    typename MultiLinestring, typename Polygon,
    typename TupledOut,
    overlay_type OverlayType,
    bool ReverseMultiLinestring, bool ReversePolygon
>
struct intersection_insert
    <
        MultiLinestring, Polygon,
        TupledOut,
        OverlayType,
        ReverseMultiLinestring, ReversePolygon,
        multi_linestring_tag, polygon_tag, detail::tupled_output_tag,
        linear_tag, areal_tag, detail::tupled_output_tag
    > : detail::intersection::intersection_of_multi_linestring_with_areal
            <
                ReversePolygon,
                TupledOut,
                OverlayType,
                true
            >
      , detail::expect_output
            <
                MultiLinestring, Polygon, TupledOut,
                // NOTE: points can be the result only in case of intersection.
                // TODO: union should require L and A
                std::conditional_t
                    <
                        (OverlayType == overlay_intersection),
                        point_tag,
                        void
                    >,
                linestring_tag
            >
{};

template
<
    typename Polygon, typename MultiLinestring,
    typename TupledOut,
    overlay_type OverlayType,
    bool ReversePolygon, bool ReverseMultiLinestring
>
struct intersection_insert
    <
        Polygon, MultiLinestring,
        TupledOut,
        OverlayType,
        ReversePolygon, ReverseMultiLinestring,
        polygon_tag, multi_linestring_tag, detail::tupled_output_tag,
        areal_tag, linear_tag, detail::tupled_output_tag
    > : detail::intersection::intersection_of_areal_with_multi_linestring
            <
                ReversePolygon,
                TupledOut,
                OverlayType,
                true
            >
      , detail::expect_output
            <
                Polygon, MultiLinestring, TupledOut,
                // NOTE: points can be the result only in case of intersection.
                // TODO: union should require L and A
                // TODO: in general the result of difference should depend on the first argument
                //       but this specialization calls L/A in reality so the first argument is linear.
                //       So expect only L for difference?
                std::conditional_t
                    <
                        (OverlayType == overlay_intersection),
                        point_tag,
                        void
                    >,
                linestring_tag
            >
{};

template
<
    typename MultiLinestring, typename MultiPolygon,
    typename TupledOut,
    overlay_type OverlayType,
    bool ReverseMultiLinestring, bool ReverseMultiPolygon
>
struct intersection_insert
    <
        MultiLinestring, MultiPolygon,
        TupledOut,
        OverlayType,
        ReverseMultiLinestring, ReverseMultiPolygon,
        multi_linestring_tag, multi_polygon_tag, detail::tupled_output_tag,
        linear_tag, areal_tag, detail::tupled_output_tag
    > : detail::intersection::intersection_of_multi_linestring_with_areal
            <
                ReverseMultiPolygon,
                TupledOut,
                OverlayType,
                true
            >
      , detail::expect_output
            <
                MultiLinestring, MultiPolygon, TupledOut,
                // NOTE: points can be the result only in case of intersection.
                // TODO: union should require L and A
                std::conditional_t
                    <
                        (OverlayType == overlay_intersection),
                        point_tag,
                        void
                    >,
                linestring_tag
            >
{};


} // namespace dispatch
#endif

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_MULTI_HPP


/* multi.hpp
EKjU65LurAFy+Dnh6+4ilgDPd/LsxdDYnvfRZXb4ADVuCjXOf6WvnB0/OzJrl/xujFmrbsVZG5rtZb5/w9R6BItBUQgU83aQikmCfeq3ophLoZjXYOMOT69afYgSPcMTpUGiQFRdrz0uzAkn+4xiH3Sqc1N7foDlY0AkyHorz/odyPq9qKzzHhpzcVFIt7zsns9xxF1DVEIGL6HCl8+GpkRKeHTsbZHkKHkZStMuusgVCAh5WRw7AgrnOAhy3oweDANXZf6Yanm9hmopg1ruiarlqbFrIdlgXvoXFK4QbBM0IJxV5b1mC1bxE16Fy5fBLouq4tY1YhRXPc0jYdjlIkQ4sI/hX2eOjR5ile40J3Czm48Cl1aZH6CuqHdSPedorcYWJ0idXn7tEvQSstoDnwjax/bwPP8S7cfzTe0BzJUucmUeBtaithMYiUyBaZUm0DjMawTiZYRtQPgU9vzDA2qeG/iRPeEWdvCziZrvlLltywXAFasPaiewQjMcv+DE6GVvdPerg3kWo388X5foxRIqtIdKHF5Wy2D9JoaKrQT4mMpPmcledjM85/wtnbhdcKvebgmVOFltN15CySnsNriEc1OJpZT4dEclj9c1dAe0YQi4H9UPH4ziGxbAR6XghgUZnBmaIxfAB6cohgVZaLZn99uVVbjLyxiWGI5YK85g5/yWHK64O9MsN4XkC35PWUWRFsx1xMLIHjsfoySl2K7IyBnJRS5vqGAG+/VDEY6mr2Zb+Fm2/tOJMb5PxRZlZlEFHVPNiDKKYoGzS6vYb6AX37mDc3Awm1YSUYIktWY1YEbDzTEjzu78cVQovzWm6FB+q00jQ/mtN0VUJVaaapCMIqkWWOTNhPUhv+hCjef6OFv95GT4ZC0udKFgD/46HkNBPOzaYKIQA0oRBqfDTU/JtUi71dBmSgfF4dGDmRkClqDRR1e961XN4XSBa4HM0Z3hMgXYqNaKRHIKwusWw3i4vo9qd991jGT6H4xDLku5C72p1axm/qUn/grHCJkwE+Zuo4iAn9nqB9BVtN6Fm4W3Uk1qxsjL9S5UKXt9yepm1zFebz78K1KT5p3FVdEvIxNd78rmMr5suJzBL2dAyzGSSNZ/tlVDv8k/72HX0/xnA//BvQOS4RpCCQk8eZG/aOc/CAIUWuDKhtHBonbW0/AZWc8HcDowZR4uQ/VKEf6rhMvN1HYeOw9aPkdveTs9xhYjZqXtWWwnD9+X+TZifrg7aydJHabsKbaGAUg6S+owu/fV9AFhq6LWL3AthX/L4J8f/tXA82rR3JW8nfX8p1lrrt9VJdoax76PbTWObmtLdFuX6G2t19uKgTK43gcGtRoR5zs5/VXKsRPlrmz3O7WInO6CtkvtccrHK19XL0b5ZvOZ0IOSQJ9oQ3xojqtaazT77b8G0OGzSh/MR+9xwNSU9qqVUP2LZE7AnvjDEEpvl2CVdyCrjlGLk3Pgw+H58ialq8dr1r+HaQcWjJVAomqWM7KCH0AF4sYM64F21c30wyZg2hb6uM18bbAzIXXPT8w014pyptkPH6/2Z1QZUsjyEHngBWTLnVQP8xMaTGwUj/no9DLv3+IxvHDyUZiGJvRLFwoBm/IXA81utEODga6ITOAMPPDXuyjWH1993GYBmoXmw+wfjfFa6xNEsbat9a7/4IdocXXzRVtvpK/E+N0+focL5sETJ0tLYaXvN1KJmO6o04V7BU/ajFVczOINFbhcROAYNWkOztXNLnOc3g4cf31EM5vj8QCTKmZnOvzLgH9ZZZBiM6RI5KJRL+H8X7bagT3vFz1XrsCek88UwsKn6oWugXQ955+i0RBxjV1wOSxCHMPHR87TvyxSFgw/miiSJ9Zm5ftFOGlFqknwzsFdlTPUv6G3VNiMp0qMBBOYElNvCtQr7VJ7TvFRo9C3m7UWOMOpvODMQcia7MdwnMljFer/E5mrwqCYdqJyIUtNKrdzx253ZyCJkjTjgYhn7vkVfHYYwjliCL3wrxz+zRPNshCMoT6KXtbTSg7VufCvnOrOh2IzqNjxkWIpBX09yDRHlJXIvr8KhjYRVeFieJxVKYY3DLQlZGNNFXS5TE1aYKeFn+y3RjqKHBFUhk/yefXhphH58besIlJEJOnIFmotmKB9ID7X0P+9RSNBDk53nhB0h138h3icQckED9F5YRLe4If3wp6Hv+xZeCauob4iqi9ZlPyia3UcAVdFhuNSGMuYKTANHxQiQtaSzN2o976/Q/mI5xdpxomNI4pasH1/H7V57A85DO5P/GkU3YGTZnfz0+Qidxxp7cr1cdwjFmO7wlYC7GXmYT1CBaettpY/DtEiINOq3TnzHHBNVkwrUbCMAuUFrlyNELe4iHuB+ty7bKHnEmnKpyi8WWxR7ykVUuJenzPPbmsIJtK+5sxZww2zfsrTOxUeJoF93AE1tyE6GFLkjMRvQpE//d+nyONZ5ftfgSIv+RKKXP2/QZHPYH967ytQ5Dmnpci/4xR5saDIrd+AIk+MociWIzEEczybqIymyGc9GqHIzaMosg8o8kJ4yu78cKL2UayxZPn3h0fUsv7XOlmeMIIsLz88amXdAal7fsfJ8uKxyLL/C8jytr1fmyynfQlZLlqhk2Xb/xBZvvfY1yLL49nDK7+YLNujyfKa5q9ClsczowwDP+10ZLnof4gsj2dyMyfLiXFjkOWir0WWi8Yiy/nfhCyfOZIsz20isiyInQjyfRrKnD+KMtvZ45C/x3x6yjzvq1BmG4zqGm6qj8S5fkQRo4hzdOqvTJ/zT0+ff/1IFH2+4JzR9Nl2TjR9XvzF9NnOWhtj6PN4Fmz8Mvp81hj0OeNvo3aRrEaizxgZIRd92Od8BvOaB2l317UTnc7BR/KLcdwObQ7QRkPDblvz+fDY3eylJJMxyco5lIRIuWLgxNxOxNypcIqLmd3N3P/8ASDp8Cp3FK0v4bT+YY6F41JhmFo4WUUzwZSeUyMoeqj7lKoU2Wkr3mOr/xu8drdQFr9NRVCQlkj+KEL/J43Qww7MrC9EU/lqTuX7Y6l8hP5YuYliFvzLjuyPsxJpWXo5aU+Fy3J+mf5NiWRqFJGcxBr/HkXQcRpnf8VjKxokIUFPjSboi6MI+iRjFEGvJ7MiwZEQwO/DrmT+4+Q/iEMBydCYT7Q+lb9I5z8IbE+t30xFiQ442GtHo6h8VAeQfdI78IS+Y6Ybo6j8Ym54CYNKVu2dIuZmOfas3JUqqPziL6Hy34LJnxLbeubcT2siqqWT2LlSFLlfycn9BWuI3Gdj3ZvGPIDLkQN4Eqf0vDYgYvjDnntndE3P36WT/Mk6YyC/wxkDbY2uhkQ9x800uLgsBLHPjBD7euIWv4De7+76EnoveNgoen8xp/fIqo5J7+fdrtP75Ch6X2D8UnqPjPBXovePH/xa9H4Se7qa6P0oYqXR+ynRlGr9Skc0pzOC3s/RCz2zDobfyen9MU5tFwtGCKlmNL0/8nXoffmY9D5S74MrOb2/nNP7bk7vRQvyT0Pvy8ek9/kYRo7T+3k6vS8aRe/LNXrPjzhiE3iDb0r7+M/+yCHjbMji1Ua0hdKxshVE/ougm4T2H8UBZMZQ1nLiAIoEB9BCFYpyp7C1UErPh6ciTMC5EQq+ADNX0M5BQBmj+YBynQ9I0ii71pqeaujeiLLgnx+4gejiRmYb2fLT8gRFp+cJlj8QxRPYJo/mCT5LivAEfKGPxRaMGCl/rcMQM2turNU4g+zTcAZTY846zr2xm80FtcQQBBSKEGprdn8SxRDsJ2qfio/kfTpDkMsZgjPhsbsoxRay4PtcJ2cFBLfQ/3GEW2Affwm3gNEjo1iFa07HKgyciMyQb8MFDlBtinIf1wC0EKFWjGXSK865IXiI3qSqd4bUQj1VNU3A7f54TEyqhCiNVgupGzLfYNfeFOu3ExUUhDALAlaElU4MtaaT4VuJvbQMdTPOwUKL2VaPilt0N9iBRN3gT8AgIIFzUK9UZFZyLXKJV9qtygXl7PfwIboKso084rG0xGU1CI8CVLvZWnFjJfvXYgtbsBEN9IXxhyNnDdqm2FonGLmncBmTG40GLw9QsXGxpkbiRk7Sy6gAM3CHMellFB/AzUs8RqgVv/gnPBiMu45/Ldp35DkcyajhsK0ZQdbd81y2EJag5KYo5jXUFqcIUrMME/1Zjy9jC/2eAN55pIs1XOUxdbFQC31PaSaIwJOq/zLEBHevQQYqeCvMDyPX35W77LI3vVSEmlHeZJvXxON8sWvBbVaj8wWaJ+ThYLj5YLR8coomjRVtd+e4rNpcegHxzPATJEJJg8/ERzBz2Fv/mBgLRURmUh8pBZbM3S77DDtF4kJ9ZqlcPFwWWkVQqah/nCHdCQXapOCwwT9OOCfnmdEa6no7xhRfRaCpY6RM5SnJUsk6EiZf+UjTme5ZSPrPyUqJZeVxe+bbK0/abfe9UteFzF54nqYlXcdTuaC9682Bacpk3mpoc10XDh25lb9Zqc6dEc7QjAh+yfOkjCz5UfLmmCtyeGcsGqmpC9oNyjU4Ff1TpG04h4wBu0J+AogmjfN6lll6xT6X/Xl9vCESe9PatgGNDh+tIZtqMqeeZwkFraEAY987KMJQH/5VPPP8fSI6i7sXWWrGh/KMygmWj5Pok58NWk23m9H5Ej6fZU+/qnh6KZZeH5rIehhqWXe83q8pXDfhZSdzBpMMMQ7zaAN3MPPtSve7wXh26OhEQyA3p8Lsz8g8nFNhqZ2SqaJC0JyNAKnLoIg8qcvqXmip6VGXm7mBL2ovrwVGusIqV1h6yPSjxOx+PVCCTvLXD7kPrjChc2lw6GeqtZIdPfmpWpmpVnqhqWoSc0D+V+3uf9hab0YG5vphyGva649nj8uwErqsavFwoJcDAdZaIdmqX3OFprszWKR8ljb0s3YrFjvX1OHlpSmdaQUW6VUrwtbaWgkOsMRi2vuz3VZTiRnKnQ3lUppC91BNd88gWTViFOy0TvmaIczzL6zhMyg10vHbd6MVnEX1DKV1QqNyPEM1/+zZTi2xu18JnAfvHpT+mWh6pWPIhCj/8T7zvPAZ2wzAp7o7auOUDlMXDIH7YI0JBiQnOGRruQd5KDEkrw99qkIjoYmlMKiyZ7jSyxpuIsACJTis7Enbhb2Et6YuxIXng4bzhXc1paG99lzsZPEw9hIH72bYYBH9CxPkeIZrjusf61q5FmbIkFxglRdaFs3f3Tm2V0/icg3DvI0CGk5tl46ZpfbvyYXJsX48mosmRX+y+WDn+JkRsRQQlr1TKSgSzjronI1scGBcTh2abAeMudE180o35w+o0pP42tDVaDFxXiFiOy5t6yWMtUnK3bswkOenplrLj2S67uyiUjG9KLauSgcw9cVFxynXfIDsiDTFTs2GfnocckENrBIOQA+LUW5E9XxXwn0b0TUoFl9CR65P/7mqanCjkJ3bm/ESyORsES9lLDSVaL8dssFUDoXykisxqLQz1nfHhER5kZ2cSHap92CsJ2WIjjEmlXU2mQ2KIZSfGMeDQZKHCB4ieIxTdE6ZjFGlJ7NpeglvcDeZkfFPFe7wIlxH1mGcyRmhfIsJBfPc1+fEQa83ynsEg1SjhdzkKjwUAtOUW6p7VowRjVTCoSAPQfKq9hORcuoxNOA35Ex8zPLP49U++0I4dVxQZYBiKyp8xra3ZuE5YqKXnbIl4ezPnbKl+nFKSQ6FFRXoxOJNA34TOpCRtvNB5Ydm9C4yoWckrICuNO5tZOrylvKjdc8zwm+x4QnRGL0haOUHDfNhiI1scp/JigTpyIJ2ZqdhGMm+NL8r3X2iJk45kbYzDZ2dHsIPL9xXeIUnTXNc6dSMDBHAA6N27EQFAsHj+PX+w4Q0rFNMPpV8WlAOCS/xMyh71qmrzRzzRHjmHJw/GjUTHeSmz/ki9zct8kDm8iQDd4ao6Ic9p+9aOSAiD/T5x3nhP3ZwWFXZ0HI9+kDRs1HRB6iMDwNQBrKD7CwoY8zoBW2R/Eui84c2Qv5nA1og5jcLjWh2cv1wV0I9JNuWfyOcxVrxUCCvJajctan010V/yZ+jNZ2uM+jvDPqbTX+zCIY/F92ON22tltfm01Mv/Z1DfzFuwMsEB9KKhoyVFGK5uL1fDbUuE/dm9n2694v7eHYJ3VeL+wQ2je5rxH0imwD3iM0vryWDxbVorSi1Wgne+U2GnsTKTvZUYFQQg/fjviSIAQ1VvV8MFQqKaNMSkH93Ad/6fzpuSS/Hjlv8y7HjNrAjdtze2xE7bn/dgXyJY+TQYQQBHDx2KQ//8At/hFnRBuUXt0UNihb+gEZlaeH/8aioL8WOyocvxY7KP16KHZW9L8WOyssv8dkEwxA1KATwqHicfGgUjx0Ii4mGxwtD8UryKIBHIMitdgrfcBg4rcIyeS1Z5a4tp4gAZJW7luxx1y6mJ2Qzt7aKrofwwL4W/YzkHSS3WruEmmAxGHyTr1U6SoFmdDWiQA2NjOW1K6mceh7uAonVmoka9maU/67SiJ0ETop/Gza9Hf01qvkzNoXu/OLuDLpbJu4+fxnvloq7D3Ga0Xdhqg3B/vEDslVtcGxvxC/N6uFSeXNhzwGYCiON6eKHjnxd+H5pe5V26AwF7P5v8Q06YIW92buONVepas8K40jvWoG274tfd120o60WaGIKPjx6KBx39OCRCSzuhWq241aY0fvC8PDoQfjOaa/kkhotLyUtL/lCKH7lr+KLpF2ncgMWPPXDv1SkGCEPgnCgY6fWKmiioKYuRBLv+Ymq6q6z/sTHvMePV4fPVCScRcgWJCgSzQv0gN+tZrYrH+VIC0iSk6NgmkD8jtdee82QE29FCet3EIN///YtiKngLEWpWylGYRfUsYKAoPAeWAEXe+qVITVcJWxj7R3MbtvS3tFjmWDA4+iW3R3HLGd02LbgK7zCPA72izqHQZTi8qq3A7/aAkyQdEr1T6yooKLhkHbFAyTisaPHbzmKbH760sBpAgL8uZxTSrE+fI62K/G8lfELDu5jyaFt2laPSlmZrmHHfnHmgIo4Uv5gl+cYIUgEu+VgnxzslYMsVHysVA4Oq8uLlF3MMXgK1ldOkNUWwLGk5UE841/PbKHVNHe6Q+Y1agaZ6zO3l0wau/zfcu/0T0ILUbvcTPVh/CIjeutcz2peQNvYkOcYO3QVfLaCbEhfnNO2DHrlT43CyuqrmGTwVg0dhXL/dbUo15LThuhr/unq8mx26W9OqtdWVvrslMk8FTFaWNy+iVGIBCz5FxHfTi1kV/LPaVz4CYCFP1E17CwrS93Wr+J5w7aldSIO2RbaiErhdgL+ejHI1sG7qHVZGG/AAQ+8oavN7LYX9dPnFXCJobV+9/Movztz24xboOrf3YLRGdAjEYUEHguGKEBnbwHltQpXP7u2DRoRdBgCFylNYjvwsl9t7xex+BxkZ+xxdHn6yBN8CpCFULGdPeGNNwjXTXgVR2FVV+Hmwg5A3kF45LfBlgqVf47NbN3OjZThhdF/BlAofIi1+C4S2TLnUrgwmTwdFE+yTG4OuD0/QvsreTqwLbdEdmbo5n8thW5uWap302PJ3A3s/f0d8qrFHPhG7yxug2zpVuyslTrr1zrb8oLWWSvvrDWqs1ZEKtt69Rid
*/