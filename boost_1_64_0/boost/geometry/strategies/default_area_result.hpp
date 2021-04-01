// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_DEFAULT_AREA_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_DEFAULT_AREA_RESULT_HPP


#include <boost/geometry/strategies/area_result.hpp>


namespace boost { namespace geometry
{

/*!
\brief Meta-function defining return type of area function, using the default strategy
\ingroup area
\note The strategy defines the return-type (so this situation is different
    from length, where distance is sqr/sqrt, but length always squared)
 */

template <typename Geometry>
struct default_area_result
    : area_result<Geometry>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_DEFAULT_AREA_RESULT_HPP

/* default_area_result.hpp
VhBg+VOVrfxSgP8kPfNvtuCedaH+sPYrFh+7yWhhFh7IvFT5XdksMiLwJzDd5wnH4TtJil4BP7nrkup+xkxHHqeuFrrz0+ZOcWt3z7FTyLO51oS1z0AQsBuJIqtYk5b+v3vtMijIjpyek3u0Tsv8m7e76L5UZI6fjXblZXonqY56Y23xrC0Mz2idT0vkNrDciuIYlnLOf4IMbUAoJ/V2BtpWsyw+ghMX/Rm4pTN1zcmO7KqRBbmf8kg3IbYnSE62eCYuNyNswjvRaIUfQOPUSvyqFgPjJ4u2Vr4ZX4uvbrQ0THpyXi8HCq1cdVBtUlNgPlsr4UfnV8fYVUOovAEm/6BCrU0gBZbyqgN7UwHLylwqvy5uZ6AGtM3CErqipJ0XtvE5SWdTr7WGwXRQh5n3fz8UBC4Uex6x1zT01VYnCbpaz+oPhhRvzgwkPBRwjzZMej6gnlJMu+rmIUSibpH5RbV/yc8FTOJqgS3K1JOGFPQEge37TThUSZMQACOkO/TK/wvPLoMqdavK3h7H6AlpsaYbFOUq6TweFhOJ7TzQTrn0Rr7NQqPHkyHjZw==
*/