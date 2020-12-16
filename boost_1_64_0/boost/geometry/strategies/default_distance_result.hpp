// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_DEFAULT_DISTANCE_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_DEFAULT_DISTANCE_RESULT_HPP

#include <boost/geometry/strategies/distance_result.hpp>


namespace boost { namespace geometry
{

/*!
\brief Meta-function defining return type of distance function
\ingroup distance
\note The strategy defines the return-type (so this situation is different
    from length, where distance is sqr/sqrt, but length always squared)
 */
template <typename Geometry1, typename Geometry2 = Geometry1>
struct default_distance_result
    : distance_result<Geometry1, Geometry2, void>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_DEFAULT_DISTANCE_RESULT_HPP

/* default_distance_result.hpp
Y/9+jvrdR/5E3UzTnTCSU0bjpj73bH9Eqr4qD4WFpofC5DvGQXJW6G/BvZR5axpceVhtqGYLWqdWOBcf7vBEfHjCJ8Xm0hWchuFVYkCuYxRac2mY8yHKFjlCRf3X5HRn2+mKKd0YdLWYnO4rdrpxNNqOgyGZix5EE0MHbjFp+Gu3sCg93G2Hj9PDfSJ874+C/bRnRvekTn+EGlnaoY/e/Hh3XM4i8YYsvn3yjsdoHpZ0YQth67FJls/ctFG6HpKByiFu7Y5XG6VJ81nJCqCocn4B08u0FRZuii+ytPAXr+ZRlLXqQOoY3VCmzqHPEkNXY0sjSN+/LkRqYrHSGD16DKUkfNI8hI+H8LnSxOeOqwifgRKa9AodLIS9qwdAkAhV1RjFYd4pQgjyK7dGCopo2Tm04RiVVqcOmEVg4vgZmblPIjLzTWQGMzLNeP7/7UTIBT1CTmPIgxlyoRPkp65ki9UIGVE/CF+GO9aY6/a5JUyXUK9mmpbBcMyaHLQWV706RP1Y+aeWX0FWjS6D8PqzHVE37vgH/U9kZ4H47jBVcaeklp7UDX7/rgKmtAtqOLsHGrkbChJra1FtmXaHMO22P+7AsouuYCEOvDsAz7ai7z4AdKHTtXZL+LwAlmS7TAy3jeDWmXAPRrisZEC50HH8YGindrZUhAGZ0SuvoKUXlSf1FlCiV9kBK9AN63JcaaJx/rCKjq1Iu3oKl5rnVJtHGrFUXsw2iklVlgZiwk7J0/96x8L/pb+e/e8Pe0AtV0Lsep3mSdVPimXPKCaGlV/VfEOwDMLrv1OFMesGiGYNRp/OpGmnyrAsEiC1KPZwZTg8V12n11Rdl4o+E6JkbJFjr60kbNLYPtTj9zFlhOf2GFjI8xYROl7hVq7MW1Q/ioiEbvrJP3Z+Z4PfDqns9MJWcjNNQqm4ce8Vn0v3BJ9TOr0NA+0gbydcItk8eUNfyLQp/ui+l0rFE5Vgy06rISe6roFaFy9HF/ufwPY+UhpBCtn+xXOo9fD+0Gl3046ptM/yqJbtdnkBcQW7WtbYJ33jY8VbdmbWT4EX4Jzc0LKcix62cJ6zshGlAIyzQ+y4GRDHdl2g9k/1XXsdn+7VNj5ccrwTnuC7/wOInjc9dJ63CIq4f1l33P/EYmv95engAbZ5JTxCno3x7Xz5pDjipjtWEQ8+9o948bFfJI0uT0fS8ZFmM4l/uOs7kL8O/ubB30L4a4W/pfB3Pfy5LHf6/8vP40178cv46f7dVf+/W42MgYT1BjMAtATI9OjFDYYm4AXjwu7YCdQdgStGPICX4n3U3uQ5XUb4RIQbI16mQ6u0j++3yAY9b2PbLY58lHPRBFpcFiptCEmEpDYtXVuepIcSBHjHKABkRjXVoBzwnNhZCXBCPcMJOcKpRjhDYvmyTqX3c52wr/bdw77Yz3Eqm3GXEj1W8yA0j2Vh4ctQIpLporOnjffRwWfWrnhcWpGIU+Jj2brK6ffSBqIIt0kcMVGfx3AdBwNrW76l5i0VWqRC+zsv6fIfWBMp/9xz5iLm6Yz5CYx5dXc8ToKN/s73M8n+swAvb8KGlIROib1ihckb3YD84jUYmRjztyALkChhXbaY/GuiG1k07Y6t4320piVAy4jkTbW5yGAjg2Jfjfoh5ioiaQlezOtqf+tafQ+elNYy0i4TFQ6K5UWQXfqG5xqF1ZLIghYjFTkaaDOG7zZDDXzShS+JSGqR8qEqxIOlarx4gQY8YQQWznlySVcbtgR/3g371MXw7z/ianLCeBgiAdPtxDkGhWpoL3Hkznhcv7bLPl5w7j/jVsgjpvHpBgU55w2Qs2Und7NDbFE15a/s8Iln0Gtf23xoxZ7IrKk+upE=
*/