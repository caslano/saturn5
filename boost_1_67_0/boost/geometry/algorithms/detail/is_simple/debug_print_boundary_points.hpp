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
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
*/