// Boost.Geometry

// Copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_QUARTER_MERIDIAN_HPP
#define BOOST_GEOMETRY_FORMULAS_QUARTER_MERIDIAN_HPP

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/formulas/flattening.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace formula_dispatch
{

template <typename ResultType, typename Geometry, typename Tag = typename tag<Geometry>::type>
struct quarter_meridian
    : not_implemented<Tag>
{};

template <typename ResultType, typename Geometry>
struct quarter_meridian<ResultType, Geometry, srs_spheroid_tag>
{
    //https://en.wikipedia.org/wiki/Meridian_arc#Generalized_series
    //http://www.wolframalpha.com/input/?i=(sum(((2*j-3)!!%2F(2*j)!!)%5E2*n%5E(2*j),j,0,8))
    static inline ResultType apply(Geometry const& geometry)
    {
        //order 8 expansion
        ResultType const C[] =
        {
            1073741824,
            268435456,
            16777216,
            4194304,
            1638400,
            802816,
            451584,
            278784,
            184041
        };

        ResultType const c2 = 2;
        ResultType const c4 = 4;
        ResultType const f = formula::flattening<ResultType>(geometry);
        ResultType const n = f / (c2 - f);
        ResultType const ab4 = (get_radius<0>(geometry)
                                + get_radius<2>(geometry)) / c4;
        return geometry::math::pi<ResultType>() * ab4 *
                 horner_evaluate(n*n, C, C+8) / C[0];
    }

private :
    //TODO: move the following to a more general space to be used by other
    //      classes as well
    /*
        Evaluate the polynomial in x using Horner's method.
    */
    template <typename NT, typename IteratorType>
    static inline NT horner_evaluate(NT x,
                                     IteratorType begin,
                                     IteratorType end)
    {
        NT result(0);
        if (begin == end)
        {
            return result;
        }
        IteratorType it = end;
        do
        {
            result = result * x + *--it;
        }
        while (it != begin);
        return result;
    }
};

} // namespace formula_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace formula
{

template <typename ResultType, typename Geometry>
ResultType quarter_meridian(Geometry const& geometry)
{
    return formula_dispatch::quarter_meridian<ResultType, Geometry>::apply(geometry);
}

} // namespace formula
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_QUARTER_MERIDIAN_HPP

/* quarter_meridian.hpp
+xgm1WWF9c26P5eLZut0KqclfRevxIXK8F3NDxnazZ4Ul2mJga1aQPgRj+WewWpr9+2ahtEwg/DkxN0HmPHlNEopWDoNMSElUd2pc2WQq7Ir1Dz1uNl+N7SixrU5gdf3a9S67V2bADb3hzS1XxOQHhK/e905nBcY0+yxOR2r1Nip6ueO0PeGRG9T54J74tFMm6SPrAJGzhQY9cZ9tfjPZApzAAfS9ur/tE84MME2JZb8rpMhQkNjDijsbVPcTKwgBbHa95hTZvfwWoQ2KcIY431FnBGmWLrYV3Br8B4KOyoIwk3WMeKa77uwtYnISDcPYeavuGdN5Ols1QtmLalNxPi8cu8LRhCPZj4sw480Vwg95e0CowFuc2WhFsp3j9oESczyfD2vjczvqBXIHgJ7bvwNcBc9kt3PDhx2HsOVS3BVsEUVI5/C7jyv5rRUJGYJBrkpDQjtAHQA+RjiHmUOOql11K/fqwEQmjghcXkJ/yzBZgI7pdCi02L2aaPvbWsgEqDKxQApfQhc8xV1W4Lyl4TcqUdRCQSHdlmMhvSCi13NqLqZEA/Cm6FtnA==
*/