// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_TRANSFORM_HPP
#define BOOST_GEOMETRY_STRATEGIES_TRANSFORM_HPP

#include <cstddef>

#include <boost/mpl/assert.hpp>

#include <boost/geometry/strategies/tags.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace transform { namespace services
{

/*!
    \brief Traits class binding a transformation strategy to a coordinate system
    \ingroup transform
    \details Can be specialized
    - per coordinate system family (tag)
    - per coordinate system (or groups of them)
    - per dimension
    - per point type
    \tparam CoordinateSystemTag 1,2 coordinate system tags
    \tparam CoordinateSystem 1,2 coordinate system
    \tparam D 1, 2 dimension
    \tparam Point 1, 2 point type
 */
template
<
    typename CoordinateSystemTag1, typename CoordinateSystemTag2,
    typename CoordinateSystem1, typename CoordinateSystem2,
    std::size_t Dimension1, std::size_t Dimension2,
    typename Point1, typename Point2
>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_POINT_TYPES
            , (types<Point1, Point2>)
        );
};

}}} // namespace strategy::transform::services


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_TRANSFORM_HPP

/* transform.hpp
dEloFdH8E7qniYeStA4aVpMfB9y0pTN0j2249fXbOWzmYdUS8t9smWNf1YFCQlQAyyvGYpYU4biSeJQyxHxzybMxpKKjNBPsHyF6ERSNb1KGGOiK130UcLZz/JNiC5Hukg6tkaELqCv7lOt0JDommdulKipzGqR8cwLWrMiFdlepg5s0q9uczg51oyzz2eSMyk6mu2SefaYDvaWPVNrXTaa4gSzqiZMMR5vi9RSfcsM8GhGTa5XEwh+kX7s1ih1k/FsFIYAP3zIR6oxS1DZo5DkXbV2lGDXCVeN3Zrh9YQ6PjJiEiNo4mGm1QerOE9i7n8bI9AWHimzQ4BcfMXSjbl89DoRh3cgGNEnHmcnuZHJub5s1EMObjg7pLz9SPA6jh5Sre0/R71PE1Z+MBFXmlM9wIxweLNN3hGmDBc11gDPpNkN/D10QA6EEOb8Xc8aZMf7lZbP2mIgM64MqBVrghCgfluUR0EHa0isO+B0EdnAGZwSSILPJMbjRjT45NMwosAtAwv/K/4yF95BqbFIHUSzh+EKIX/dc6sYNnvYa+ZK8FeRPe/SiujQikw==
*/