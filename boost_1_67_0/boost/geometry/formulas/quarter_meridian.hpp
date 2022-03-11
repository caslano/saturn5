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