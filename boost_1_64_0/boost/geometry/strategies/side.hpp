// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SIDE_HPP
#define BOOST_GEOMETRY_STRATEGIES_SIDE_HPP


#include <boost/mpl/assert.hpp>

#include <boost/geometry/strategies/tags.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace side
{

namespace services
{

/*!
\brief Traits class binding a side determination strategy to a coordinate system
\ingroup util
\tparam CSTag tag of coordinate system of point-type
\tparam CalculationType \tparam_calculation
*/
template <typename CSTag, typename CalculationType = void>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_TYPE
            , (types<CSTag>)
        );
};


} // namespace services


}} // namespace strategy::side


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SIDE_HPP

/* side.hpp
KOEWknFhQqk6QTvAhVbA92txfeDCW0mQuS6wUczEXmWUTn6tRbpLf55+LLK76jHNPma+WtZNwoMJxHi13nqBumbGHxPSUzXxbAbi10XYX9iHF98nJrBcMolEwnJgj5zj4jFiQe/7URuPkqwbO1/GhKALjmyfQQMr6pGPIkB5xH9vEjHpnyblRyd8DSKaHixOfPEEHRRytS6Gj1ANT6Qi+D3+zonwYCKJlR9aOufRBDttlUJFA35MlU1UbUMVbbeuYuJHNx29iBbFm1fWuQwivDmmRQ2yuemRyniqgyeC/Ai+2086mR3EeqOrdCLAMUwVnCvIhpXGjOrUa5RAVKRWTmZH/lC7zpIHjABs5uk4NnpIhLOdjtJaRN4gEjAWmZ583NOnYBkowVHGLYBK5NwBSFGXqut2xS+gB3YAuTFAkuvwAqcYVKjtUYg9FMv2Li8nZDgCL2FTEwQKvgfFMlT+NA1zv5pjujQxNNqG1+gJqZDuhG/LkC5xOJver9OLkLn6PhhqBjJA7kK/iGidCRDOafhUgeWDzQBdDegvknAPPy+u34vAMmCsbYA5EQ==
*/