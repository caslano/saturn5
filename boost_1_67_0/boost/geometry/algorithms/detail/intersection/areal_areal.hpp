// Boost.Geometry

// Copyright (c) 2020, Oracle and/or its affiliates.
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
    typename OutTag = typename detail::intersection::tag
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
                detail::intersection::expect_output_pla
                    <
                        Areal1, Areal2, single_out
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
        typedef typename geometry::tuples::element
            <
                pointlike::index, TupledOut
            >::type pointlike_out_type;

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
                            strategy.template get_point_in_geometry_strategy
                                <
                                    pointlike_out_type,
                                    areal_out_boundary_type
                                >());
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