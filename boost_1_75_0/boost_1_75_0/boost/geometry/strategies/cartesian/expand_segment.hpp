// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_SEGMENT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_SEGMENT_HPP


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/expand/indexed.hpp>

#include <boost/geometry/strategies/expand.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace expand
{

class cartesian_segment
{
public:
    template <typename Box, typename Segment>
    static void apply(Box & box, Segment const& segment)
    {
        geometry::detail::expand::expand_indexed
            <
                0, dimension<Segment>::value
            >::apply(box, segment);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<segment_tag, cartesian_tag, CalculationType>
{
    typedef cartesian_segment type;
};


} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::expand

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_SEGMENT_HPP

/* expand_segment.hpp
uAtFFH1uMorTcaT3dWtAC2AoFfhB1FyqPvQuVGDwXaipUMGne56NX+n1J303y+VCfHRrv1oabaqejPX9AltnB3q8qG6rRKv6inU0a4KiJal1qoGF5asQNbA8oAn7aVhDMeBDKLwx76WoNIK8HVv8VeJRXo2WOKH2y9IqORnhALJpMbsE4f6HdiocsdTez2JxOQ7XfKESx67bwtfqonJ3hWC2+c9htsjUgaxd24DmR+NQpLutD1cw4WKL/N3c0yEitRDyk+/6bW6x8yNn1Y18U2UJ4bRLUbH4CVAWLHPAqkb3ulzhsOia59G4ia6Wuf5PrTDiOtid+QHdtGVdVQjyDz/8Q51rYQC99s21vb92auBiUI0CEPRyDYkpNqYj7IWM4yqwwrm0okJgOQShBSdmHSSOy5t9B/8EhzbPZjt+XGX0hAY/UD2uoaMCPy/YF4JxUBhB4T14I6ZFIOlNmuup65fuYHVqGQR+UAoyrUcOUnIxDS74GY2kKeoz7MHSwD/8XLBm7U9w8GcZvcOAa7rr/OugRzSEHi2tP5qEfage6Y+z6kQP7qbg7yah1dwYbn9+cn5M9RkX21fym/SftJlbFXERxcdLaLZKlkRnwPGNPLj0RLpM6AtyKokNw4Wdf6QOqPn9Zt/B0YbF6noCXUYcW346Dgm3SJ+ovsooZfIwSpMxFGANmcjLAdQQ6595xtbZ8saRqdtOQe9YP4mR
*/