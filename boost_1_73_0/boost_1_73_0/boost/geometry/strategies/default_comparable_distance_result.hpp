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
9HNJy04gXnocGb6M3wf8MhfNcohWdkzM3336D/VOJEv91z35407iw0Z5Mc6cU79EXu+Lz30RvEFqLPMb1djk/wFQSwMECgAAAAgALWdKUoM/RmIVBAAAjgsAABcACQBjdXJsLW1hc3Rlci9saWIvc29ja3MuaFVUBQABtkgkYN1WUW/bNhB+9684JC+2oVhtsQDtWgxzbK8xGthB5CwLEICgpZPFTSYFkkrsIj9+d7QSN4M9Z1j3MtmJKPL77nh3H08+VrnOMIfzUX84uhKD66sLkUwHXxJx3jqmBaVx51rc/X5XC7pw8BLhT9BF98C4tOZ3TP1utBCPsPkQ647uh5zEsKU8ig4cpjxCO1BE4+UTj4U45OiO98b/YmbeCR7SDNGYOTDV2qpF4aE96MDbDx/ewwm8e/PubQRDqRWWkHjUc7SLCD5lYebnQq5WPYc/RYAeZNlrTM0K5cCZ3D9Ii0DjUqWoHWYgHWToUqvm9KA0+AIhVyXCYHp5O558juChUGnBRtamBleYusygkPcIFlNU9xsblbQeTE50Mp4p58lg7ZXRPfKN4NEuHdtg97J0BuS9VKWckyPpofC+cj/GcVrbknYfZyZ1cfoUfq/wy+dIbmkTS7kGU3nwBmqHETAygqXJVM53SghNVvW8
*/