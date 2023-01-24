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
+pW/lHHCot65uo+P1ExsVhFrUTBHMsGY24pjWW6iaeMGuvzcB4a1Pw9rUF5mbmXwSZxCG1VDkJQI+xnW6NwaXybH1/ZppdjaPkfxhkC2Vv1AGR4H4xkZAT7neHDvibguvxM4EN+jN1iN7nzP4XNRQTS3ZSnJlipUCBq4wTYJJA6u6HVBIjlwAoGHsPoBEC0xHlXUeRTmEEFT2los3SpDsUrkBRSykLse4fYcIcTQLoyFhZWcCFNVvlVKth/fwDzwXFuV2/ENUTjPFNytrks5FWii5SPkB6y9gFKIqsCFU6jXoblMFW/wE4ipc0uT11FZJyWoFVILv/7w/BnxLL2d2QRhkYJ8NC1QKBLqMzl9d7pytkloDEsH5Sm3Riyi1iQUjVKhUuI3P8fex6E6/TLIsxpj93sGzF8QDW7OcBBHvjJZQ5xtnVst5Qa/v/ZBIWGGDLt0U/hb+l3/ePh4X1Y0Cqn1C2dFrG81n6/Dax5dXhk8Z3UEk9uyyEXhvBP1aWpHg6p9xIKUswI1tga2zqbDVe1m/aZY1+E2FNfQZ2udrYZsp9a1FyAofRkBZWklWfpjDWMND4DkiMKL+vOWCmWtp6+H2LRC1WFHLRd5ic7XCbuOwvf1EjKAbX65HvvKORfzEsk49/0lMmsPZS6RLeo9igrSWU9Sj8ivKV4JTySQGMkWBorYmy2r4awFDX1tvJ2SUJsQ1B7xrTeu7/hR
*/