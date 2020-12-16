// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014, 2015, 2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAPS_IMPLEMENTATION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAPS_IMPLEMENTATION_HPP


#include <cstddef>

#include <boost/geometry/core/access.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/relate.hpp>
#include <boost/geometry/algorithms/detail/overlaps/interface.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlaps
{

template
<
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct box_box_loop
{
    template <typename Box1, typename Box2>
    static inline void apply(Box1 const& b1, Box2 const& b2,
            bool& overlaps, bool& one_in_two, bool& two_in_one)
    {
        assert_dimension_equal<Box1, Box2>();

        typedef typename coordinate_type<Box1>::type coordinate_type1;
        typedef typename coordinate_type<Box2>::type coordinate_type2;

        coordinate_type1 const& min1 = get<min_corner, Dimension>(b1);
        coordinate_type1 const& max1 = get<max_corner, Dimension>(b1);
        coordinate_type2 const& min2 = get<min_corner, Dimension>(b2);
        coordinate_type2 const& max2 = get<max_corner, Dimension>(b2);

        // We might use the (not yet accepted) Boost.Interval
        // submission in the future

        // If:
        // B1: |-------|
        // B2:           |------|
        // in any dimension -> no overlap
        if (max1 <= min2 || min1 >= max2)
        {
            overlaps = false;
            return;
        }

        // If:
        // B1: |--------------------|
        // B2:   |-------------|
        // in all dimensions -> within, then no overlap
        // B1: |--------------------|
        // B2: |-------------|
        // this is "within-touch" -> then no overlap. So use < and >
        if (min1 < min2 || max1 > max2)
        {
            one_in_two = false;
        }

        // Same other way round
        if (min2 < min1 || max2 > max1)
        {
            two_in_one = false;
        }

        box_box_loop
            <
                Dimension + 1,
                DimensionCount
            >::apply(b1, b2, overlaps, one_in_two, two_in_one);
    }
};

template
<
    std::size_t DimensionCount
>
struct box_box_loop<DimensionCount, DimensionCount>
{
    template <typename Box1, typename Box2>
    static inline void apply(Box1 const& , Box2 const&, bool&, bool&, bool&)
    {
    }
};

struct box_box
{
    template <typename Box1, typename Box2, typename Strategy>
    static inline bool apply(Box1 const& b1, Box2 const& b2, Strategy const& /*strategy*/)
    {
        bool overlaps = true;
        bool within1 = true;
        bool within2 = true;
        box_box_loop
            <
                0,
                dimension<Box1>::type::value
            >::apply(b1, b2, overlaps, within1, within2);

        /*
        \see http://docs.codehaus.org/display/GEOTDOC/02+Geometry+Relationships#02GeometryRelationships-Overlaps
        where is stated that "inside" is not an "overlap",
        this is true and is implemented as such.
        */
        return overlaps && ! within1 && ! within2;
    }
};

}} // namespace detail::overlaps
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Box1, typename Box2>
struct overlaps<Box1, Box2, box_tag, box_tag>
    : detail::overlaps::box_box
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAPS_IMPLEMENTATION_HPP

/* implementation.hpp
01WZqTBRTlDyOvNQm8v6rvPtPemHCx6yJg81ge8H2c5N7LSa/rrzwlU5XCV2lYqb2iNf751kPRpm1JfrJ/cIwbQ2I+Xxr9KJmseNp8QMcaZBsp4AE88bT9qhYsBOHM75A1epYbzKn/n8tUtyDnhXWbwc5Xm2rL3U7LPQd3Z7C9jux/KZwjnUbl4Tb2B1zob23MC+9dnENL2KlG/luzeykS1yNDykwE3y/TqOg2O99IO+fUCdA+87vZu/XweDs8FA+W6VM47ze93m/MJ8ihpjAz34H3OIl/j/iK76q4fFaf7R+Dv6dOxDxr+WL7Q4bl3SJveO8p3X5ZD4/Pv85VE1ihJ0+LRjV1iPiXTbtJU+qvl1vFstbjxfTfaqn+Kn9+p3i62zHdvuY/sKisO7FPWBH2HtPBy0vHqH7+rnlL91VTNpzaZaym2a8Ck9htHiRA571AZant3Gsekb1/mN7bfGJ+uqMzn3PnO85TO1iqO4b33xeCzcYd+X6DCX2HvBdVawzQebGjce33sKW2ZTj9ZK/l0gWCXuD5eT3gD3j7WV23yC91aXq3XU8ypj/YbCpNfp70n4PZCtf6Svh9f2SvZ5esC/2vaDFNcPzAbjySFyjHxJTpLTJEN255Ic5BZSgHRhR7N66qWosW29T14sJ+qWBubQZftd4kgJcXct3e9wfmt5YjP+IOe7MF5sS4VVOFgim5h8MInRbFbNrrA4WH2leLIcB22kTtOP/q/Zw9lSvzoFN86CM6jlpM+oVs/e6x1yLT3RbHLx7lnVKsrir+J9o4bGXxCmq+UUY6cF7B0aqQZfpIUeVHrxp6NcyNoMtM89Eie/vwTzyomFWT1bIS8rgetm/55LlYfRbOCzj/7aF1JJz6k+7O1bHU6Osg/QuU324LVf4rf446g7YVxaNvW7a/Zia/jCRGvbtDsfzSOXno6zTnWO6zy5wfcwazEfuIk+625Rq0ruqVazqJQifovNcVM148fdn2/saWDfdU+xf6jequN/XSpWboSZTdVK2Xa/a7CqH6x4Tg+XLZyrIya1sW8Khs74Rgyrq4Zdyz7N1/l5F1wEzt3IFp56lP+Ko4fUS5I5ajr4mkd8TdYWMzRnj+JnU/X74n7e+YBxy8mSz288Dnuu9tfHfAUGzrNearpD5ff5YXqfB3A4vjIcH+qV+pfNFCQHS7PNefygoj7YbjrLAh99nhlmFNuurmYct7CZu/D7lj7Pk50v8Pnmc2D87ea1Vb/oHbxIPKjyrN6q3v79H8iD1a9a8r272Fqvi7BdLabxfnaYPflst3rMw+JphHvvwtn64s94RSFxpmgFPUd16fKD5fzH8LhK1lysrHUHv7oBPsyzZqPlzuxxWyPzxq1vvx8PfI1d55ED5cKp9FBGsPccOEZX9+tGer0nTqqd5ejIBxLOZZPDuuEmdfAXmNifzXw7yrp1ltPqAYfN4vIguahaY0c93jTGXEPPpSs8GG09n7KfechVdo5j1vyV/bVXU8eZ0jSAafTdyz17k+T7un/bpu7/Bv5sXd7y+xG1lPv3ilcf4wG4ZbNk76kVm2zqp7rd1w+LqbGxuOaKijDDuvd1rYlPyG8Pi+HXYI9YlOFrdWp5aDPftSDfNJaT74ej8LrHGzDldzmm+F+Fbe2DKSmOaUOqm9/ds3GUc+J8R2v1tO/1rftfpQs6q8vWd+KY3flqO8d/Ij6svEPvowA+D/sOVIPLPs/UBk9fI04Z5yMpf/X/S25kU935Iv7x4cPiTR/rCs8b3Sanf0qcTdZ6trLjTnBP0bQOPHmY/7XCJQeyw9ruk07vrjus/5APnWZL9dvKG/+QO69XmxqpPyb2l71JHaCYGJZPvlKa3rc=
*/