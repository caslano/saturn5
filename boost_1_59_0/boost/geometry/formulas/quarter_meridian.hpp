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
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
*/