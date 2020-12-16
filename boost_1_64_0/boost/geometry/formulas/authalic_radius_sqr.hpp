// Boost.Geometry

// Copyright (c) 2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_AUTHALIC_RADIUS_SQR_HPP
#define BOOST_GEOMETRY_FORMULAS_AUTHALIC_RADIUS_SQR_HPP

#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/formulas/eccentricity_sqr.hpp>

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/math/special_functions/atanh.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace formula_dispatch
{

template <typename ResultType, typename Geometry, typename Tag = typename tag<Geometry>::type>
struct authalic_radius_sqr
    : not_implemented<Tag>
{};

template <typename ResultType, typename Geometry>
struct authalic_radius_sqr<ResultType, Geometry, srs_sphere_tag>
{
    static inline ResultType apply(Geometry const& geometry)
    {
        return math::sqr<ResultType>(get_radius<0>(geometry));
    }
};

template <typename ResultType, typename Geometry>
struct authalic_radius_sqr<ResultType, Geometry, srs_spheroid_tag>
{
    static inline ResultType apply(Geometry const& geometry)
    {
        ResultType const a2 = math::sqr<ResultType>(get_radius<0>(geometry));
        ResultType const e2 = formula::eccentricity_sqr<ResultType>(geometry);

        return apply(a2, e2);
    }

    static inline ResultType apply(ResultType const& a2, ResultType const& e2)
    {
        ResultType const c0 = 0;

        if (math::equals(e2, c0))
        {
            return a2;
        }

        ResultType const e = math::sqrt(e2);
        ResultType const c2 = 2;

        //ResultType const b2 = math::sqr(get_radius<2>(geometry));
        //return a2 / c2 + b2 * boost::math::atanh(e) / (c2 * e);

        ResultType const c1 = 1;
        return (a2 / c2) * ( c1 + (c1 - e2) * boost::math::atanh(e) / e );
    }
};

} // namespace formula_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace formula
{

template <typename ResultType, typename Geometry>
inline ResultType authalic_radius_sqr(Geometry const& geometry)
{
    return formula_dispatch::authalic_radius_sqr<ResultType, Geometry>::apply(geometry);
}

} // namespace formula
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_AUTHALIC_RADIUS_SQR_HPP

/* authalic_radius_sqr.hpp
SNPRjSEBxqhjQkTQggPTe3qPOrEqYsQ5C06IMrEiakHECohVJ9aJ6O87582SdsXHx8frY8+el9//vOc73/ku73c5JxtYEK35diyM9sNbsVEdD/DHWC55OoopwzpiD79TE6vTe064yZmhNqND8MxL6SN0OcwqoS46NmA1ptCaX8Ky0JoTmB1tX8+8isXI31GaofqwPfgT8LgNxBh+Owxiw+gw/DLWzLM0D2AtaM3Pb6TN0ZqnX0a7oTUXYi+iI7CrjPTkoy5nrsVK8TthCDtMe2r+DrPi11y4iXKiNc/BctF+eMqHmE8op+Zpm5lP0JoXYU3oOBzF6nScQMeHM1S2bmd4G/aUnlvgt7GD6DH4J+wQ2nZFhjoDewDtgKux/Wgn/CzmPy3T4AUu2gqteSXWgda8uZy2QtsrMtSF2LPcq7keexGteXIldSSN5mpsAVqzCMtFR+B2N+doRw3xiHnQMfgHbMROOWsz1B1YAh2H4x7qiM7zEktYOVrzMcyP1nz9lfQdWjMXi6BD8FVsGG2/inatY054B2WAa7cwr+o0cI6PuEE74CWYE10Ob62nL9FjsOZqnsW9CXh+I+Mdbd+aobxYLjoEM65hXKAdsKyJtkXH4J+wBHXUvHAbz0VrXodNojWjmI30E9C3nTkWHYbD13INbdtBv2FOnQb6rqMddBo4iJXptoIvfIT88fuvz1BHMOc7KWeIPsL8aM3Tb6D8aM33YhG05vnYA+gwfPeN5In2w4mbGGto5072sTfTF+gEfOUW4k+nb2b/g+15N+X8aIYqwLLeRRvCuzCFjsHfY9lo2272lpgN7Yd9t3IvWrNsD+VBa27FhtHqY4wXzI7WvBHLQWs2Y3noMXjSbcQ8WvNGbAytuRebROfdTvtgY7peYcr/cca/vveODPVnbAHlj3yCct3JGr2AdruLdvgkc40uJ3wY26zTw3M/xRhHO+EW7FTujcOMFr3P4154MzYffwxuu5s5X98L33YP9cGv2YLloTWfwTajNQ9jTWj/pzPU85iH8tj2Mn6xvfgdcDUWxu+ENVi/Tg93YXeiw7AL69BlgAewfegEPP5e6su9mrdgy9GaXVgpegy+jE3SVuo+xjU2gbbDZdgoOg/eiz2g6w4/30rM6zK0MV91MReh87rZa/USA+QZ7iOWsQT3xuC7+pkf8U98lv7fR1ug875AHl8kBtD+Yeb2B8gfnfgqMf8g96MjsPVr5IOOxYmFr+M/nfTwo9iEbquH8GOT6Dg8/E36kTSJA+xnv0V8ojW3PUJcoTVvx3LRmi1YETr8bWIGewBtO8i+C1NoP2zGxnW94PWPco7f8Rh7PGzhGdQlkaEGsCJ0AhZ+l7ZFOx7nnQhbgI4fylDv+D7tj/bDPVh1Dm0CLT8gPToEy0aJH53nD3nnxfbo9DD+JDGMtv+IORyrQ4/BlqcY4+gELP0pcYVWY8TI0+Svy/AM8YPNRzthDfaKrhfchVnxh2EXdiI6Bg9gp+o84XPYftJPwMyfsb6gbfAM7CDaAVdjz6KdsAY7rPOHu7AX0WHYhT2FjsFzfk5fUN8IXP0cffp+0sPHsDr8mqf/gnZGa+7EIugEvHac9O8hH/jnX1IetPN51lws/r5Mg90vELdoza9gE2j7i+T9K+rLs+Lw0peoI1qzHVuO1jzhN7QjWvNkrA6teQ4WQtt/m6Fe93vSkGcCLnmZ8YvW/Ai2B6159iTjUaeBL/2Rccq9eUd4d8AilHkCXvkqft0vf+EdKMOi4vhtFosKzrWohVpnWtQPsdwc9DyLehgrxK9ZlWVRZWjNBcdZlB+tWYk1o9XxFlX0Oouaj47A39osKqGf9SaL6jjZosbxx99iUcs=
*/