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
tYAT+ew+esjC9AD/Q5Q72CNpCv00E18LUwrZKdWieStZjANceORCWKTCGs2TIMom5b69mZzFyaP7Ap6N5e3iTg0AuexaJpM4mYnB4AL6CrLAD4N/+ijtAp4LXKWB4PUWYiAzEhP67aVp6Km5A3urb1jxFoRtOZURPANelZmEqqfA+7eSJNUPQyg/W4RZAG9FFsxkitx8sJNm0PNIIJ+MYhgw6RLmNt1TEwRqAdbhFOco/fRR7I39zG/D4DMQvdF9AOL6ubXzm81CMLkdIVRN1RDWEnv4Q3wn8Mf+9/jjBAqa/oEFYJTwHp/0vKsP+Pas9+bmXXcw6PWHTayx/70lE/TfDDhUfMe1SAyI2QctrB1MmrtcC6iUdioo+ZOZxS8t8dsOGbE9VF6r1iljzTO6B1MBhMRKevA7bJ+IYFZHHnDzbUhd3TWZhPimnROxvbPS4PHn5eaTOaH2gAA8spZqHibniwlYEJeJYD4zP7mHhzi/URinC9CpoJZBET5IWOzmrT9uwSz3wW6AeOSDTYMZmKNE00FQq9iAbPIMG8OLAZi9aJxO/Xup+m7Q+J52kHAZmAFFvxNQM2EKjCuaD3EAHSKpTvKfZn4neU3mlsuroffm5vxi6J1fnmhl9bSzY7jrlOX3Wcy9BTcDwbdj
*/