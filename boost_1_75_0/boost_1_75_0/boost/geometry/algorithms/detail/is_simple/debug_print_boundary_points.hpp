// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_DEBUG_PRINT_BOUNDARY_POINTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_DEBUG_PRINT_BOUNDARY_POINTS_HPP

#ifdef BOOST_GEOMETRY_TEST_DEBUG
#include <algorithm>
#include <iostream>
#include <vector>

#include <boost/range.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/range.hpp>

#include <boost/geometry/io/dsv/write.hpp>

#include <boost/geometry/policies/compare.hpp>

#include <boost/geometry/algorithms/equals.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#endif // BOOST_GEOMETRY_TEST_DEBUG


namespace boost { namespace geometry
{

namespace detail { namespace is_simple
{


#ifdef BOOST_GEOMETRY_TEST_DEBUG
template <typename Linear, typename Tag = typename tag<Linear>::type>
struct debug_boundary_points_printer
    : not_implemented<Linear>
{};

template <typename Linestring>
struct debug_boundary_points_printer<Linestring, linestring_tag>
{
    static inline void apply(Linestring const& linestring)
    {
        std::cout << "boundary points: ";
        std::cout << " " << geometry::dsv(range::front(linestring));
        std::cout << " " << geometry::dsv(range::back(linestring));
        std::cout << std::endl << std::endl;
    }
};

template <typename MultiLinestring>
struct debug_boundary_points_printer<MultiLinestring, multi_linestring_tag>
{
    static inline void apply(MultiLinestring const& multilinestring)
    {
        typedef typename point_type<MultiLinestring>::type point_type;
        typedef std::vector<point_type> point_vector;

        point_vector boundary_points;
        for (typename boost::range_iterator<MultiLinestring const>::type it
                 = boost::begin(multilinestring);
             it != boost::end(multilinestring); ++it)
        {
            if ( boost::size(*it) > 1
                 && !geometry::equals(range::front(*it), range::back(*it)) )
            {
                boundary_points.push_back( range::front(*it) );
                boundary_points.push_back( range::back(*it) );
            }
        }

        std::sort(boundary_points.begin(), boundary_points.end(),
                  geometry::less<point_type>());

        std::cout << "boundary points: ";
        for (typename point_vector::const_iterator
                 pit = boundary_points.begin();
             pit != boundary_points.end(); ++pit)
        {
            std::cout << " " << geometry::dsv(*pit);
        }
        std::cout << std::endl << std::endl;
    }
};


template <typename Linear>
inline void debug_print_boundary_points(Linear const& linear)
{
    debug_boundary_points_printer<Linear>::apply(linear);
}
#else
template <typename Linear>
inline void debug_print_boundary_points(Linear const&)
{
}
#endif // BOOST_GEOMETRY_TEST_DEBUG


}} // namespace detail::is_simple

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_DEBUG_PRINT_BOUNDARY_POINTS_HPP

/* debug_print_boundary_points.hpp
T+wN9LKxUDbyM/4eiGRDuGOjrhPV9bPRWDtRh962kapDJ200uMgZe60GIPMF7TjIX3lSObW+KCL7pn47UkBWsveY8G83cllpPUT+E8K7G/V597AJqrslN3Z2mBXK0epDhJ40isYw8F3/vTEhGrW/DrnaJGU9j9cKUbFVbldWqW1azLHIuVCplcpQlcCPHDh8Tk1J+JHIA/k3yYHSLg7tST3M8hnexPXF4yHyCwgrNyX8ftSbDghftCASsfWTTUBV3wxDLdSYu7iDuv24Z5PVGvdcSrhHqJOmyrlavSMNq3VynjNHLpXyxKBQj51oBc6G1quTqfVSH92eSf56YxO3tz0NEd/mTJS7Wa/T/jAxLe4kLKA21DJrE13FQpuN3btRD0OlDgm9it/mOJjl2k7sPCUvoTCYtczShlkhyb39lbWQ7EDewoshcgiCl/ogLc5fCURztpPLP5PL8+TyGrmcJZcvyUX+J7iMJJcouXz/n/gJgwqpFG3FrjneMt6v8xxo6EGokxaJ+T/czHUZlyCC7oe6gMBdnrCxuHEOEfml+61mladtWhoW49gnRoUKvAVVkz5M/NtC/0iD/kF373mdx+/X9z8h0gJh1f0JfxP6CRrjJFQ73bddZHyv+84WDxprd87H4h65UCwU/Hgmehq7RBfZYxtAf/3c/Sb70Jch8b/3M97ptV4FOWJXPb28PQ62N+7cYqIbgMStWxjd
*/