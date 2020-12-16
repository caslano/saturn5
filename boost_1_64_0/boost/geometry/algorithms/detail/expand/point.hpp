// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015-2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_POINT_HPP


#include <boost/geometry/algorithms/dispatch/expand.hpp>

#include <boost/geometry/core/tags.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/expand_point.hpp>
#include <boost/geometry/strategies/spherical/expand_point.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// Box + point -> new box containing also point
template
<
    typename BoxOut, typename Point
>
struct expand
    <
        BoxOut, Point,
        box_tag, point_tag
    >
{
    template <typename Strategy>
    static inline void apply(BoxOut& box,
                             Point const& point,
                             Strategy const& )
    {
        Strategy::apply(box, point);
    }
};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_POINT_HPP

/* point.hpp
uYz0Cnsn/d2qsvzN7aXuGyVjXuwSTBpvPK92MN8zeAEwm5rnX4e0XDzFyuxuOMi4fBlznbnHPsSYve2d3wx7G2OkqHFipc60TEOXOYSyiZpjnA0Vp8gjvOrw+vrC+m4bS/A9reA+FygfJR4iye8QxlIR+PAfO9Jxio7k6+RVAqOeH0YQaT/d4bj/p8cMc+P8TX1RgCGw6J+fIjE0L4yewXf655YxXpiRbSiQu8y025fN6m/4HNjJdZz9+LWw/5DVIRhvVzfjz08EdBf3bMhNqvB0pWxGFgwSzOd6GfjcovOXKocPmfm69f6Qk07Y61cXc4c8eQ/5et43ujlfzM00wD2Y09dL9fFqKdon9ABZxpnf6xTYdEvU/+6FrocvwY/5Nrd97ZOsrFPInmplXUbWvn8l8VfF/rajVJ2fFtQdCmtnkJ7zdGHjNMe/18z97WyFVlp9e7s4he0eD32fL2Cc4uY3K/iMS5pTqo1LP8SLU7j/AhbzrZcxR14dy28pp/H5qo/Fn+lMzdmKE6SJ7HdeZzklknsbXUpyipxmg95GbyRMJImoRTm9Bfj0bjcP2zm0bZDTde3x7RkcK/F3+r0zm8eSgR1927aJuwaiMOF363sj3M9Rea9txAm/wa6McJQinA7lvfyt8aFgPloqk2+D7fRhBS/Mkl9M93djvBFzy4/K8NavlNznDfkZYLwenFXttcm5CXPYaEZ7r6q7U/NDfyJsk2acoeNKZjVQjCnXNOPZzy3Zr36qKR9joNDh0824Yp33YvZPMceYlOLzui7W/VhRxKSr6suKuGuZq/irsnX+rOzPFJ6L9xaOl5tlRGeb8fdgmkRtpTcaJzhe3RrcpyxAZ3MnP8ya9Ayuvl4f1Ff4XdtbI0HdpMlaXDcf3antXbshqBfxfPMaDee6yHc6ajxRRl9gXFrIE7uy64nnuLS+JMpbSUuvPzFPrw+ehnbWsnyJm/sOZ19GJaXv2Nqp+UlvDO2KpxbFGUiBcT6J05ltT0NAHM3LBRy+L0Pam3XItjVzsu0MSjLWtbTxwJltzvNgX/q4im18ttoGvhrakQLrbYBxpQ3cpPFytAEiNm0DntO8jnua1+lmWXYOb9kGiJavDRD3HrSBxng0D3+i2gZuSbWB0b6Olm0AnOZtAISWbQAcp8M3QjsaqGUbkBzdzoaSqw2M9rU9DpSL+vfsBaqNvxnacbC/dT9jOM1sDELrfgYcr8O3AxsDat3PDPa37GcG+/P1M4P97fczs3v0d0vn1G+z7yhzMBOe9dPngHL65+/ryeBxm820uSQ3XWuUvNU55mZEFfcFifKMdGw9JyMqfQuo8zGeimGO17J8OUj75UxOg9j/+XS1Ld0als1I3/BAR4u2xBy9LBIC0m85lhCPdfmhLIPsdBqKLtnlQ5Qcbcrwcp65Y1sr48Ilqp1vS9k5x7iQcDqb2TnHuDAixoXbU/bNMS6MtB4XRnKOC4ZHPqbfQI8vH4B9HuD3LMp5n029vkt/3/CVqr3/cCLtmRgd6xtL71e7i7Bk4Q5x1uqpuyj+HOF76Z1qkUfgtA+aGB3+rmkKS1K3bUG+D6TghSrb+B+EJ37DgCTv3LXpo7LY1Dn+uyk8Y4VplAXH/x8VJwNQGfJ+E7sQxcSJ+nid/e5wRjCPVrr/GOUDgSJb6Pta8BeiNKS9DljFHMZjW+CK/z3WGMIWjEljrGRbKDgZg3RQ0sCqnbP6Sk5HwxFZ6AP5j87jRH0Zs23MouhcDTvF63t8/TtwlcXmbQyK3evl8UatGpre38tMcdv1OSo6WS5LDw/wud2IrEQ0H8dBVgd0FrINRfoDJ+WVMp2vBqUa+LLNXtxSYfS8UQPb3JixOLU=
*/