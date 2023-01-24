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
mQ22rsqisw5pydDLuFMVlsCJatknqUE1KjS9uMWIBrV5BGnQG5NasbThoMfIHzOW/mkklG+siw7Ybju8j6eaG3L/7kc1YjNggO4jNVr54uwUTXMS2NaGSY7CbmjUFL0/TIn+TTf47PmEvBAweu2JSkYbaextIj+hdD9+R9Ev25P208ZluKimC6OlWXVpiqeNxzKBN7I+jYvpdQ8K3yoYU5y08Owct7BeQ9kj813h9QeH0JVrr+U90akyjZ82mHFvxqLS5OGryntn5fK72e225Hqmdnr/cDQ3q8GFzc0VVh14OlGsdHdPN9zoJshUVCPPo3NVB+K6luLT3RL/LTe4lT2u+rZgTeKk9TvLLqH/+Li1r4Xd3p9eqx1Yvqkb2Q2PTvnHR+OrICgs1IF8+duXP+025e8EPjTmMHj749X9LugDcL45O9WNS42ACjvVtcLlmR+AbFmZa+gwV526U1o7SH72evH2ftw+DdH+cSLZ8lWgIbvWhV8Ym6nfFZpoSwLKqfJm3/vNVty/q8WVTLP8e11LCzeK0TKsJSDrh3fG9r0DWxuha5qW0TKzbNKcq8v3Pi/vxXi2N3IlYMPDTs2jsOH1amquXLE1zz5TW919esnQWa0dpWxqJezTtStz/xX7Xd7IxCfzidRTwj6NwjwTV9Jv9qXcd/Kv6W5mmh2iTTcCEzVY88qefYYrB4bv3bAI+7RjLp78epdIuvWh
*/