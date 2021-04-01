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
vWQC1EHMOZpByliyqO01Db6dQZTa4n9+qFFYZWTQm9vu6PGr3IIfVXqZIwXyX5EkRZcb9kQRnr6hj48mHhvRiuccbbNtp6S5xf7zngrB7HiocMnqT3f9KF+vX4/bsFJu3O6SvXFs5ZStSkj2XKylSi3RXGE3165JGyha67+N1viwU3jKBv5wFd05FgR+5lB7ID/Pw0K6zd/rTLibHxjEKXNKgEOGxjgldfZAsB/r6MEjujC3RySu1xFkNEKnfVCdDpG1DbNRs2GNjXkcJO324bS/LtF5jEjJoGVeOKcqcUBeDNrOq1/YNuaJnHaELQ6xJPD05+qs7BwPwrMmay9g2RkwjZC9EYicZNlbboJqi4axrs8pXSeQ0QpwVx1RU7hmC9SCMHgqE8h0zURJbO7GhNpilYjoxz3orRnqBs8XBL8krl7oER8YTR0F31PdMmPBy3x7ohG63abcysGZLMzdspvQtCTeRTsnIVqL5oKtBq+lNC4wOBVh+pxVE5oCotNipJhDcGJg7ejN1iZuakzVczyPcnFHJ+7X1cUzWpmCO77Qet5u1DXFohSzjQ==
*/