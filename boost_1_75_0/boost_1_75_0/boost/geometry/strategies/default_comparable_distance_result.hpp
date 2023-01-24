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

#ifndef BOOST_GEOMETRY_STRATEGIES_DEFAULT_COMPARABLE_DISTANCE_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_DEFAULT_COMPARABLE_DISTANCE_RESULT_HPP

#include <boost/geometry/strategies/comparable_distance_result.hpp>


namespace boost { namespace geometry
{

/*!
\brief Meta-function defining return type of comparable_distance function
\ingroup distance
\note The strategy defines the return-type (so this situation is different
    from length, where distance is sqr/sqrt, but length always squared)
 */
template <typename Geometry1, typename Geometry2 = Geometry1>
struct default_comparable_distance_result
    : comparable_distance_result<Geometry1, Geometry2, void>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_DEFAULT_COMPARABLE_DISTANCE_RESULT_HPP

/* default_comparable_distance_result.hpp
mhZ/BSbsWQW2tdQu5whfiRPGpOiHwasdeXpndHFFrH0Gcdk9FrnMFJEwHUktbv9ss0K2WcXrDXtUcJDbcWHbOy7XeN/BLkujQBUTUsFBNdgN1UWvvedPm7qK4pbm2NaZ1ObkwFn16LeKkBlsEVmuqXjrL++Vct6g5r86V6KNZagMfN9AyXhJ48f8+ssuVm+XoSzBFAnQ6xttmcS2Bjp6vwqfeqZmV47ADH1OdSK+VgjdiEJoHWqNfpRj04JkkyUqwMSgYg3PK622FHNJigDqsqRi5lCqflg44JWrPi3cqTjAp4zdeCA5xGqkQTDN6R+XM6qhoS14PcPtnwQqx+GTo+eT/3TosdjuVWUEVyA6YZdQDoQPO2ELt/pEKvaiQFx+cEFxgXLBKFUDQbqUL8/eOLT8vKtnChQ2M950dhl1LBedT9u7jrjh1dXJEdORxnTOvAlK71WvgwoWTH2FUatBvTuVdo7q5nhhI8TfFC6JPXzlXUR4TLO4P5i1m2V9P3XvKrh9vu4lfbiUx1uW2P35CMQyAXC5qLox4b3U3R6HN2ZXKpQ7vLtUtjdGzbu2r1Pw4DKDmHFZmMsg73/A4qGLn5p7Sp1G+pIQHNpxuw9sPqnLC+m2L4TRZxMlcjxOV4ecy18s7DzA1OAod0B4iss0/8JGF0zC9BebojXOlASdL1gxSN9sEak2ZQwTeOK8K2D2578U8zfY7hwLcNFX
*/