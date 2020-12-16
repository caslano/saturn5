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
Zl6/8ulQOf36lQun03TpAzj+HVv/HQAuz3n5cO4XpA1cwji3a9GmL2U8bI9CxmWS41XGdv9pxjXb9zZ7BfMCu5X5/bznsO3JOr4yxoez+1KuijicaafPa+j7GOnzqxyu6vNaxlV9Xsd4U31+gzmqPm9gXNXnAq0MuU1rB9axnd/IWFNd38QcVdffYbyprr9HHFXXc925NPw2X9sC1jJkWK2EIKQlwxIT1v53vF5XfZXBhdoY5pZubt/j5OKXxtIdH3BX0rczuC5+KLk9jjte2o7zfXKsc6vkOZp5XBwjf3LSxfurGjeZgtxCXp5v/4nnwS9mgtf97Q5H3qdwNayjtOPrkf7GK/obMSeqvt7P1D7b6I99jZ8rZWxglnihitPJU6ZxGe/0PPiGhit078/PeI5ZulxbLFTGgzXB3wQ47dBx2G8DbDB45+t3AbY1nW6RdX6PxylP6P4rU1yIRObx956Lg5O+EIz/Uda1oq8/S9ydbM8jpQTZQnn8PWQBr1Ko4zf54bBpVVZz3f+F7UvmifZpxRwlLV6PfsDx+LovUqjQwYOeYxoMCml2txZ5nPgP4KE1sU3+q9vuFYRJh9ngMdHD4ITaZRv5DzCKbC6UrpWCu896LOZny2vp1mWH7+3xYtnYHsHi3ApwzFnG7lpjis+b6Bw7/cn63od4svlxYvJ8iMbjBPl8SA/Pp5pRy+DqLaMD5N94zn4qJ5zz3V/lhHehPEXlwG5EOvM1TjtnTV2fpt5RUZf9GZ9D6VF8aZr9mdzOeYONKDxkX+p9QU/cN3Ji3B4OUnmhLjodxy/rlSZKhXCt7eCQU5NrT10BVisWSlWsoPKc1yE67vbl8xqW5HH75XfwIrwYzJkd7nGUgXpJy8oF7Wgx8+yHE/6x8LOPZBwvabFdPduHQ88yZaHLpZ6TuGkz6l2EvnokJwdtAJZ66JO4y6OIv1zi4ju1gMvHODkFHlvJWB3zlEFbPkrvG6h1Cd7RTdp8u+uK1H6mmrwh9ia1DR0D2dHecS6N19HzwBvZOLhxQJxwljo+xuHyNCPXI3Dpb0KOldDO2iOVL7EFzJbvbepc07G2fvw3QGCrHeZnldlm13psIvU7XDnXSZvttkYr1t/We9xA4uxiEC4bHOdng+fQEpHU7+30DbXWDSXAXdRwsl6P81157ltHl3cVZ/CQMpwLy2993nYl/W4yx3hBa3OMK90UI93hsxl522b2Fu6F+4XtPsIX2LCndCCs1X2ElcndPX3dy/0/ou/IRaqNvNDo3UbJkZvpsZzEjJsp13ckRhvB+Q6DIwSGCQHU9ulFMWa66ECs5/X1jm5exWOrr5qwVaObEc73nkGGKw49HJvweqDEilNB3ooSK5Vbfku4Bt/01KnxnPmrvIWi6q/Ug3yace5mJIlJdLJLrvvxSppczuSe8sK2MU/DcxVkLGfH/NSyDcG9oefCd/ZQOB1qk++fULj2rt7p+1tsxy705sUgvYsPZAyv8/K99E5+uVJNig1klwRGeIByum+yOAmUb5NSOF0g1Np8e1o/aaTi9vHIvq/i+mmnvs0v9d7aa/bcnk3Ft3lvLcvUfL2vsUyhq9OsjXkbYN1TOCnd57Hu+OimybpwVmVHhe+ZE3Gb1VvDpkH1xuV/w0IX7tLGHvpSOZjTnOG4kXyuf+Lwnca6/aJNtLxHh3WLRawZrY++6f+wkempJKqv74j0qO9+Ocr+EvTlz3oU5plsf/5KhJ2L/vyIvRHW4j1tLHdXSXnbRbWTVzu949kvaC3WNTrFScGf5+sAy8zY78fhtP/ezCrV2tXTRGmyGOX3NrXvfJfLr4lD15HxG1MWo4YGgsAWuHyTuwWwtXFWrdBrfjA=
*/