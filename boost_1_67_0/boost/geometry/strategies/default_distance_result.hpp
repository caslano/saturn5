// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_DEFAULT_DISTANCE_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_DEFAULT_DISTANCE_RESULT_HPP

#include <boost/geometry/strategies/distance_result.hpp>


namespace boost { namespace geometry
{

/*!
\brief Meta-function defining return type of distance function
\ingroup distance
\note The strategy defines the return-type (so this situation is different
    from length, where distance is sqr/sqrt, but length always squared)
 */
template <typename Geometry1, typename Geometry2 = Geometry1>
struct default_distance_result
    : distance_result<Geometry1, Geometry2, void>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_DEFAULT_DISTANCE_RESULT_HPP

/* default_distance_result.hpp
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
*/