// Boost.Geometry

// Copyright (c) 2014-2016 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_FLATTENING_HPP
#define BOOST_GEOMETRY_FORMULAS_FLATTENING_HPP

#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace formula_dispatch
{

template <typename ResultType, typename Geometry, typename Tag = typename tag<Geometry>::type>
struct flattening
    : not_implemented<Tag>
{};

template <typename ResultType, typename Geometry>
struct flattening<ResultType, Geometry, srs_sphere_tag>
{
    static inline ResultType apply(Geometry const& /*geometry*/)
    {
        return ResultType(0);
    }
};

template <typename ResultType, typename Geometry>
struct flattening<ResultType, Geometry, srs_spheroid_tag>
{
    static inline ResultType apply(Geometry const& geometry)
    {
        // (a - b) / a
        return ResultType(get_radius<0>(geometry) - get_radius<2>(geometry))
                    / ResultType(get_radius<0>(geometry));
    }
};

} // namespace formula_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace formula
{

template <typename ResultType, typename Geometry>
ResultType flattening(Geometry const& geometry)
{
    return formula_dispatch::flattening<ResultType, Geometry>::apply(geometry);
}

} // namespace formula
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_FLATTENING_HPP

/* flattening.hpp
TQEiVQQGmTD9nZ+/4RYSHWoMSzw97BGaIJ0LsA4H+g5GELfEnzRevLb4M6XAobXnZySbSrYszQCeeh5PRvlj854DvcDTpReXbobylDf7qYuuWauB1ygPOreQXNIjTLkqVvS8AHZgGi4+SqdqkaJZ21qmDmQP9KwK3u6J+8/9HPsAQGEMKpRHOs5dDYT4RtjJWqtsG21yt/3m49vWCXD+6SJe1m/uQtq114xLLcR5kdKuDLr3I81xLayKbbYFdlunLXOQIdOHbjSVYOVeJJpQCxzjYV+Wt2ni5rmaJly0e7EJnFIVzWhwbkEIzlAtNtetoxcf79+hp+0MuwY9+ySh0DC3DYmd3S80TG8AJnRgp3Vw8Ka182s9nTrds0If9E4WfjWq22Q3BxU1ypyuadYP/dUFu9cgWjhgwdoVnvHHw/n0foq+96Y7SPCpHSMRwL67GNv9jyDPg+6FSq5iEKYX0cigrQ+1lRYVjxooDpEUVgY6kmH+a1HUtM6Uo1m7aQbk42nnaK/zvv3+6PiTu/fVzQRT1yKCdgs2sugv25ZuniEzjwjhzSdbioLly3YM2N5et4Jej0SGlS2uW73XFaKlB0NW1xsnrkoB/3woKKaLw+nQy6Z5PRG5POkCQrbHkoHfAHejHXS6f3TYaR2/
*/