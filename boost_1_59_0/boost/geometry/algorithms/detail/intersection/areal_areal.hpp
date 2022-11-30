// Boost.Geometry

// Copyright (c) 2020-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_AREAL_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_AREAL_AREAL_HPP


#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/algorithms/detail/intersection/interface.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace intersection
{


template
<
    typename GeometryOut,
    typename OutTag = typename geometry::detail::setop_insert_output_tag
                        <
                            typename geometry::detail::output_geometry_value
                                <
                                    GeometryOut
                                >::type
                        >::type
>
struct intersection_areal_areal_
{
    template
    <
        typename Areal1,
        typename Areal2,
        typename RobustPolicy,
        typename Strategy
    >
    static inline void apply(Areal1 const& areal1,
                             Areal2 const& areal2,
                             RobustPolicy const& robust_policy,
                             GeometryOut& geometry_out,
                             Strategy const& strategy)
    {
        geometry::dispatch::intersection_insert
            <
                Areal1, Areal2,
                typename boost::range_value<GeometryOut>::type,
                overlay_intersection
            >::apply(areal1, areal2, robust_policy,
                     geometry::range::back_inserter(geometry_out),
                     strategy);
    }
};

// TODO: Ideally this should be done in one call of intersection_insert
//   just like it's done for all other combinations
template <typename TupledOut>
struct intersection_areal_areal_<TupledOut, tupled_output_tag>
{
    template
    <
        typename Areal1,
        typename Areal2,
        typename RobustPolicy,
        typename Strategy
    >
    static inline void apply(Areal1 const& areal1,
                             Areal2 const& areal2,
                             RobustPolicy const& robust_policy,
                             TupledOut& geometry_out,
                             Strategy const& strategy)
    {
        typedef typename geometry::detail::output_geometry_value
            <
                TupledOut
            >::type single_out;

        boost::ignore_unused
            <
                geometry::detail::expect_output
                    <
                        Areal1, Areal2, single_out,
                        point_tag, linestring_tag, polygon_tag
                    >
            >();

        typedef geometry::detail::output_geometry_access
            <
                single_out, polygon_tag, polygon_tag
            > areal;
        typedef geometry::detail::output_geometry_access
            <
                single_out, linestring_tag, linestring_tag
            > linear;
        typedef geometry::detail::output_geometry_access
            <
                single_out, point_tag, point_tag
            > pointlike;

        typedef typename geometry::tuples::element
            <
                areal::index, TupledOut
            >::type areal_out_type;

        // NOTE: The same robust_policy is used in each call of
        //   intersection_insert. Is that correct?

        // A * A -> A
        call_intersection(areal1, areal2, robust_policy,
                          areal::get(geometry_out),
                          strategy);

        bool const is_areal_empty = boost::empty(areal::get(geometry_out));
        TupledOut temp_out;

        // L * L -> (L, P)
        call_intersection(geometry::detail::boundary_view<Areal1 const>(areal1),
                          geometry::detail::boundary_view<Areal2 const>(areal2),
                          robust_policy,
                          ! is_areal_empty
                            ? temp_out
                            : geometry_out,
                          strategy);

        if (! is_areal_empty)
        {
            // NOTE: the original areal geometry could be used instead of boundary here
            //   however this results in static assert failure related to rescale policy
            typedef geometry::detail::boundary_view
                <
                    areal_out_type const
                > areal_out_boundary_type;

            areal_out_boundary_type areal_out_boundary(areal::get(geometry_out));

            // L - L -> L
            call_difference(linear::get(temp_out),
                            areal_out_boundary,
                            robust_policy,
                            linear::get(geometry_out),
                            strategy);

            // P - L -> P
            call_difference(pointlike::get(temp_out),
                            areal_out_boundary,
                            robust_policy,
                            pointlike::get(geometry_out),
                            strategy);
        }
        
        return;
    }

private:
    template
    <
        typename Geometry1,
        typename Geometry2,
        typename RobustPolicy,
        typename GeometryOut,
        typename Strategy
    >
    static inline void call_intersection(Geometry1 const& geometry1,
                                         Geometry2 const& geometry2,
                                         RobustPolicy const& robust_policy,
                                         GeometryOut& geometry_out,
                                         Strategy const& strategy)
    {
        geometry::dispatch::intersection_insert
            <
                Geometry1,
                Geometry2,
                typename geometry::detail::output_geometry_value
                    <
                        GeometryOut
                    >::type,
                overlay_intersection
            >::apply(geometry1,
                     geometry2,
                     robust_policy,
                     geometry::detail::output_geometry_back_inserter(geometry_out),
                     strategy);
    }

    template
    <
        typename Geometry1,
        typename Geometry2,
        typename RobustPolicy,
        typename GeometryOut,
        typename Strategy
    >
    static inline void call_difference(Geometry1 const& geometry1,
                                       Geometry2 const& geometry2,
                                       RobustPolicy const& robust_policy,
                                       GeometryOut& geometry_out,
                                       Strategy const& strategy)
    {
        geometry::dispatch::intersection_insert
            <
                Geometry1,
                Geometry2,
                typename boost::range_value<GeometryOut>::type,
                overlay_difference
            >::apply(geometry1,
                     geometry2,
                     robust_policy,
                     geometry::range::back_inserter(geometry_out),
                     strategy);
    }
};


struct intersection_areal_areal
{
    template
    <
        typename Areal1,
        typename Areal2,
        typename RobustPolicy,
        typename GeometryOut,
        typename Strategy
    >
    static inline bool apply(Areal1 const& areal1,
                             Areal2 const& areal2,
                             RobustPolicy const& robust_policy,
                             GeometryOut& geometry_out,
                             Strategy const& strategy)
    {
        intersection_areal_areal_
            <
                GeometryOut
            >::apply(areal1, areal2, robust_policy, geometry_out, strategy);

        return true;
    }
};


}} // namespace detail::intersection
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Polygon1, typename Polygon2
>
struct intersection
    <
        Polygon1, Polygon2,
        polygon_tag, polygon_tag,
        false
    >
    : detail::intersection::intersection_areal_areal
{};

template
<
    typename Polygon, typename Ring
>
struct intersection
    <
        Polygon, Ring,
        polygon_tag, ring_tag,
        false
    >
    : detail::intersection::intersection_areal_areal
{};

template
<
    typename Ring1, typename Ring2
>
struct intersection
    <
        Ring1, Ring2,
        ring_tag, ring_tag,
        false
    >
    : detail::intersection::intersection_areal_areal
{};

template
<
    typename Polygon, typename MultiPolygon
>
struct intersection
    <
        Polygon, MultiPolygon,
        polygon_tag, multi_polygon_tag,
        false
    >
    : detail::intersection::intersection_areal_areal
{};

template
<
    typename MultiPolygon, typename Ring
>
struct intersection
    <
        MultiPolygon, Ring,
        multi_polygon_tag, ring_tag,
        false
    >
    : detail::intersection::intersection_areal_areal
{};

template
<
    typename MultiPolygon1, typename MultiPolygon2
>
struct intersection
    <
        MultiPolygon1, MultiPolygon2,
        multi_polygon_tag, multi_polygon_tag,
        false
    >
    : detail::intersection::intersection_areal_areal
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_AREAL_AREAL_HPP

/* areal_areal.hpp
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
*/