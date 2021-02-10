// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2016, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_LINEAR_HPP


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/envelope/range.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/envelope.hpp>
#include <boost/geometry/strategies/spherical/envelope.hpp>
#include <boost/geometry/strategies/geographic/envelope.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Linestring>
struct envelope<Linestring, linestring_tag>
    : detail::envelope::envelope_range
{};


template <typename MultiLinestring>
struct envelope<MultiLinestring, multi_linestring_tag>
    : detail::envelope::envelope_multi_range
        <
            detail::envelope::envelope_range
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_LINEAR_HPP

/* linear.hpp
VtgsrCjUqhq94pN6Elodt8pn7VBmwXpmmA976NQl6JlVNTUOBTYl+Zl+CpyiyKL4AIkgTH+kV4rAq6QgdLx18muYRm3PT00EtsTRM3yhTjINgXez+W3L5tCRM8XLMwvzK7GS2F92oKcTV7GrLD+mMMNnGwMl1Lk8y0CHOCfEkNMzSZAjZ2QjaWGeT0+5aGzfwAalFJGSsgeZwu7FivUzSUKiudAg6MB7FN1s0i2VEbuCf+hI9qTskXLC5pbbgLWqXSz7zY3j5ocvy5P1XThiEORewXRDdZyb1X6owWQdIreYnUSVDP8hwxGxl+1yjwgd32ZSL1+R7xnhe8Lc42NvLYprFxg5LWm+oPzFbtm0jKCF0I44J4pNLHdB3FpbOtLJyl9mGG6lg7+J7wgg8FejUXYDHetskfuneX9R8VKON7Q/vkalZdn/hOVMj/Nr+3JMPflWOrBlnlvMwzSmBzEyVbqfq6lXRrM0ZCBUFTZRm52TCbZRCclqAfS/s5RM8EMYuY2smNUfIizl6M/D2XLIH08KmpolQ+74dtZJrkWNQ4gjsOWCDloIiRlXFRvPuWMNUORybWAsIj5cEnmM/JCgBnm6knGpsNkK2C7NLC+rlxKByqvyqQylO4YiniW61nqbIFIGKoB0lm0lCVz1
*/