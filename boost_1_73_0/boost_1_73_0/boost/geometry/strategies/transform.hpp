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
YXN0ZXIvbGliL3NwbGF5LmNVVAUAAbZIJGDNWW1v2zgS/u5fMekCtR0odtr9cGjdBptr07ugi3SRpBsEKGDIEh0zkUmvSMX2NvnvNzMk9WbnZYsF9lTEtqjhvM8zQ3W4+/ddHdiFJ68x/43xwm/e8Vuur0Vit1OPx3fg/uGub/j9lJAhVFvuxn14essd9HjL2Et5R7/H46cEfSPd6GNIO7+N6Seu4Dba+UEv1rm8mlnofejDqzdv/gV78Hr/9X4EH2MlRQZnVqiJyK8ieJfyyi+zeLUaGHEQgbAQZwPP6nwmDRg9tcs4F4C/M5kIZUQKsYFUmCSXE7yRCuxMwFRmAj58+e3y+OQ/ESxnMpkRk7UuwMx0kaUwi28F5CIR8tbxWMS5BT3F7cg8lcYiw8JKrQYoW4AV+dwQDxIfZ0ZDfBvLLJ6goNjCzNqFeTscJkWeofbDVCdmmATzBzM7Ly25RCXm8Rr0woLVUBgRAVFGMNepnNI3OgQXF8Ukk2YWVdqgKJUOdQ5GZBnxwn1SGKe2gDPvnojIYIEaS0tfRitDopYzPW8Qoh+Jy7TIFQpCPyBRqtHNERQqFTkTs+VBhPcpO/jB0FT6pqAVKgMvDs/g+OwFTGIjTQQXx+f//fL1HC4OT08PT84v4csnODy5
*/