// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_DEBUG_PRINT_BOUNDARY_POINTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_DEBUG_PRINT_BOUNDARY_POINTS_HPP

#ifdef BOOST_GEOMETRY_TEST_DEBUG
#include <algorithm>
#include <iostream>
#include <vector>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>

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
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
*/