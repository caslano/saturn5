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
rONsZx0nO+sY2VnHyM46VssOR3bWMbazjueyM9V1PqsBubG99zmlMdg+wq5lLLpH9yrG+IgH4VG8c9ON7HRRbg5UsE1NsMw4oWsmhrLMxKYUG1zDWHQH8bWMxfZhTLcP47F9OLwMG+mL+hXry1isL2Oxvow1TzPb7lQvo7NAjHHEcbyor1r9Y0zXF1hoI3/uF/NohNm4Hqjx2z6ynXl00lJ2z4wXzYkhujfwgP+veXU7c1/iJmV2IOY2NKd6GmY0vzgKd9Tg51f4+RTs+3TIms+WSKGu/3XSNT/zP0fRfN72VDtve8Zy9s9F84mwljBPG/OY9z/VRcQW+e+e07auiKUjj66GZ75JT0Rb+uHRdI70UW19k04odxJfEvtLWA+EgAomjCKfnKB1JyWMGaI1ObqrsJ+i+NkXJjGXhkNDTA4drMNVhPkuKAwju0v6vj8JtjwUzttl4Dw677mSxJZFHMGfxjKA5oN6lfjOiOYNPqStCAjfioNBuWU8NOFqxdnUMp65ekt9YPmWHFi6KQcT1NZ539zbOu+be1vnfXNv67xv7m2d9829rfO+ubdl3tGQW+YdnJZ5B6dl3sFpmXdwWuYdnJZ5txPp9LzK4bKld2m4nHwiDp3Dk9DsdLiVqzjy2hRHPuN5E+Pcu+jpy17G9DFr0MdseRD5H/vaWCMyfYzu476K+2zFj2FCbTDGzsSo69YxZD4zHDIW5dmmlVUmnJ5jKDgbXA+PdBnnObnFZXkYe/fC3o0H0fi4xfpxN1nZKxNZO2N+cfc4/u/FE7i16f0967o3KPsOrmtWHj4Gpe3EsdOcwec/wr0dKF+n2Xz9i/LF+9K1sP4LhPW4VuPR7J7XDTUOG53HbM+Lx3OOgwMa/c+A/ldCf8Ad/W3NZTAHjuZeN9lyuPMobS6DEKq/A3Lvz9Awai06Rn4MPS3TkjS5aUXSZqUmvgCnm9Zfed3itsE4d5e8d8dhKOU4jP5NfhVhXHhKOPktasp2B8r2dpTtYnAG2ur3ENs6rd/7UcvyLdPdtZp8HfUtOmYKoBlOFSQbt5WkKb6pSXgaW7NxGLcpTk4q2EvHk+xlhOX6reOJalkY1ErXq3VUscLxm+0QjvE6Rx/jr5Ic3XfB+Hw1sUiMsa26sjCZdsyRbVWLg+zZPA7ZxrT8cfb08FFbG0NbO+LBNOYN2jHvsZD1Q3aMkbXV/iqlsvpdc3fTcc6EonakY7ai6RjVfxWjuh+Ws0tL6xc5LYfGYWUBcB9HmF63CBOGz71XoZxc/6XZ85AVzeyJ/X/+7tglQg8ji3Unudc97xvJiX616fiOlUOb6cZ+jMnMtQsNY78GMM3XAHH2nDVrTAfSrN8lu6t4AmfVVW1crxcpX6Z9nY/2tc+2rzNtm3s8ZO9xsrbmM4g5KoNlahlIXdZ3Jy1OxVD/DabnAYAWhpqonm/TRBV5NJ+x8XP/FmJR/yjHD+DqvARy2WT5ngzCeO+TeQy3kFz7szf4ViCe2q8+wGIz41OVIk6a0CFPxq9xOMSAiZfqG8gO2fo1dP3oDjjUme/ZvnuozTqzPqoza4M6c0RUXuuVMjR3k3UEfQxk6hxQXiHm9J+A/vddSnsgz7LtoARZP2THGVneO+xcnsjjOVPaoPWZGzl/ynxKhk6PnRJLjxvXRjjPYTjvjN+zfrZe3BCV18NFfsh2u2G7vUtpH9I2a889pl+xNt7W1lhuHqHW7Pjopn2LCcVjuYaR30nDeCyPMW0sN/KssVyk5eA4rD6WE8blFIVL+2lmYOPvw8YPBmd7WzZeMNqXYt/6Nt3GPAYtsI1ZNyePfVCMpX0eF55E+5B7wBtuR/fkDQ6tfoyoutdPIt0HyibcFrM=
*/