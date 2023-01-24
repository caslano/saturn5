// Boost.Geometry

// Copyright (c) 2016, 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_ECCENCRICITY_SQR_HPP
#define BOOST_GEOMETRY_FORMULAS_ECCENCRICITY_SQR_HPP

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace formula_dispatch
{

template <typename ResultType, typename Geometry, typename Tag = typename tag<Geometry>::type>
struct eccentricity_sqr
    : not_implemented<Tag>
{};

template <typename ResultType, typename Geometry>
struct eccentricity_sqr<ResultType, Geometry, srs_sphere_tag>
{
    static inline ResultType apply(Geometry const& /*geometry*/)
    {
        return ResultType(0);
    }
};

template <typename ResultType, typename Geometry>
struct eccentricity_sqr<ResultType, Geometry, srs_spheroid_tag>
{
    static inline ResultType apply(Geometry const& geometry)
    {
        // 1 - (b / a)^2
        return ResultType(1) - math::sqr(ResultType(get_radius<2>(geometry))
                                       / ResultType(get_radius<0>(geometry)));
    }
};

} // namespace formula_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace formula
{

template <typename ResultType, typename Geometry>
ResultType eccentricity_sqr(Geometry const& geometry)
{
    return formula_dispatch::eccentricity_sqr<ResultType, Geometry>::apply(geometry);
}

} // namespace formula
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_ECCENCRICITY_SQR_HPP

/* eccentricity_sqr.hpp
m0eyNk4nT1ePZ/kIHEQy5/clmb5OkJfvaB6kjUaGXaKwgyQKOZBOLlAs0DugN0BtgGyAmgLhPbuG8J4l0ErCZGO+A/5imLY8XkMNebxGGvJ4jTXk8ZpoyOM11ZDHa8bz91+TxzMXJ4p6vrA9KZj6Nx/qVzBtauCYv5qWH9JVUJk1lb9aNY1whVBNIxxeKD5cM30M8isKZy8UhYM/n8vM/a+G6/fnM34X+clMmYZf6Vddw8+Ci/wsuMjPJSgtgrjTI3rJ5PEyBKGaVMr/e9QAqAvQvHwqhCYDMqK5/E/L4/FUZCGEmKCUaUg1bL9KWYhpNfarqGYaFKLEcOoHvlE/E4vEX6hdQ36FwH7z87nU6vzq1Tnr8W1BpiC4UkE5VviFtxVBgiwoBP2J8DwRwtkv+oOCEo38ghJNgkISq1WvXiaPV3bOXXbOXXbOXdI5d2GhSa4iN+eNQsGeF+o4kzyqzQ3cAk9PfeEoQhU9JDotOM1sgZBbJTc3t3VF+KdKriqcEP9c0+jo6OA0T8HMw98MZeUWeAwvCjd9Y0vlu4IDhei0aLO0tLRAFIZThwfkKqh18rRAIY2aAEfprgVF4XkmQm5AtNmQaDMFFYyrmlsxzUwUn5jaCrYerXMhnAmimUGBFlQpCocMCgrFm2izNzQfWBYxPo7cb2C1F5uG6VetmFsxFxIQh5u2Bv4pok1zuaRatFm0vzjc39Y2N1dB
*/