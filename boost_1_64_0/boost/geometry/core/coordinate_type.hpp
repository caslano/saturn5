// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_COORDINATE_TYPE_HPP
#define BOOST_GEOMETRY_CORE_COORDINATE_TYPE_HPP


#include <boost/mpl/assert.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/util/bare_type.hpp>
#include <boost/geometry/util/promote_floating_point.hpp>


namespace boost { namespace geometry
{

namespace traits
{

/*!
\brief Traits class which indicate the coordinate type (double,float,...) of a point
\ingroup traits
\par Geometries:
    - point
\par Specializations should provide:
    - typedef T type; (double,float,int,etc)
*/
template <typename Point, typename Enable = void>
struct coordinate_type
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_POINT_TYPE, (types<Point>)
        );
};

} // namespace traits

#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename GeometryTag, typename Geometry>
struct coordinate_type
{
    typedef typename point_type<GeometryTag, Geometry>::type point_type;

    // Call its own specialization on point-tag
    typedef typename coordinate_type<point_tag, point_type>::type type;
};

template <typename Point>
struct coordinate_type<point_tag, Point>
{
    typedef typename traits::coordinate_type
        <
            typename geometry::util::bare_type<Point>::type
        >::type type;
};


} // namespace core_dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief \brief_meta{type, coordinate type (int\, float\, double\, etc), \meta_point_type}
\tparam Geometry \tparam_geometry
\ingroup core

\qbk{[include reference/core/coordinate_type.qbk]}
*/
template <typename Geometry>
struct coordinate_type
{
    typedef typename core_dispatch::coordinate_type
                <
                    typename tag<Geometry>::type,
                    typename geometry::util::bare_type<Geometry>::type
                >::type type;
};

template <typename Geometry>
struct fp_coordinate_type
{
    typedef typename promote_floating_point
        <
            typename coordinate_type<Geometry>::type
        >::type type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_COORDINATE_TYPE_HPP

/* coordinate_type.hpp
E934y8Nf/smUe37m0BknUK8qnjxmTrvKP2tWcVmLq4tzT9JMPUlz0u0gOr/quUV+LyiYzE9ZdOEkPrhxhZMm7xcr97EXTphQ0Op3uubKGdPmz15ULB+74JIifujC/GmTPJcVHPP7zk0bMxof+aj+vuP4oxBDxswrm331NLQ0CXvNTObjOO0KwU4gu0evx/mZ02ZcNWPojOO235lX+q6cVjrHP3+a1BAfSq+cOXP23Kv176cNyxg+Im0QLYvluOmxnotnlBX7pMBX+0qkBJLSvFkDSuApqQ9smcgx2uPh/t89zIibC395efj2Y8cesz6K56I+jp5vunvyC1xDxuaNHYIbRY4jBQX5fNYm310wJH/SpCGtuf+TveuAjiIow7N3l3CkQIAACUUXFQUUDAEVCwqEKCglhtjL5ZK7kJMkd95dMFh59i62Z3kW7D71+dBnr7H3Z1TsLfp49hIVe/3mn393Znfn9i4Ey/OxL5Pd/f/5//nnn3/+6XuDpw5G4AcPHwnA+o6dGFLrj/cdpHX0jarfM8H9oDtyf6qvS93fzP2xcY53C+Y7e48mek/x+6dD79nNZj+QLsK9gPtnt9vUWH/rxH2OHdt5/PDtzPdA/mgJliAB/VjgpJ8gnPQTgTFfLMpa+BLcypfgJl8TFpYfiKD8DNE0uFnyoynt+dJ4m9y16e14yoeFN8GtNBwXi9lhOMVl+J59e+3ya7oQvjY95S+OnvB2espHTVrG22mD+e3rO27mk94t+bPCOX6Y374Qv30WfjZ4MP7AqXtF0ma4ETdoDxYagttognH31eC/L4a/lt9G098nMfgf1aENb8oWQ7+vDr0dr31PHH+KEcPfhh+McGe4navG27jSdVBGsEhMcAtPghu84vOHSHH5ozpSKx9EHZsPorbzt9fTYLzY+srpxXPT8epwIzsPaFlShWB0gZMNbtYfbvUj9ceEE387jcbXomU5YugJH0sPXIzmCB+rMZYv1l/X5kHyxdATPpY+mPdY+QlPtNbyJkobnCniyiuY37g0CR9M0wYnCnv5xuoHeKt+zfSscKKgehJvkYS3W1Qcvb0+2iW3x7P5U2vOrPggZ+ovD8iUd4aySHDoxopjPPU/YvCEoyxZ+RIuhq8d73mvviMH8dfbs3Pg5LEH7N7Tczs/v7VjWNu3OjGhuTi81m+d9OrFgsSx+L6Dx/uPHTt6UDc1wX5gHB68a+GpH2jHBdMFMCZdwselS3h7uoSrly4gNdO12Ycdb083ql+C1dRvbHoaX1O/Ufuz679mvEh3guLVKelgvDrcyO5jOBE+lgPbe6xdxvGAhDH0hI+j1/WyIX3E5oaue2BerLenZ/dO+bDvjnyL4snNEvaOFvrdvUxoPATxmn53b6PzUQ3tA0c8vQ+cdiEFrvSD1TzHlXel6E54Y96ji/HfILxBx/dtjP9DCO/yvacGvovvB0L4p3l8+T4Qwj8X8sl7D+MfzPifGfgE7vsYPx7GIyRluoyvMv5vGk95P8L485b0m6RcjH8x479n0Dcj3J/xbwzSE34ZQonxs1E86XaG8d+wpL8c92HG/4TxCwZ9i8y3V04PifJvNcygy4Jvk/n2yiGMB2E77k9l/D7C6/Rp75d8v7+CrxHB6wLfDzykqaH5sv/UhUMYFcxemudmMiZstFAaz5cBz1ckLFPgdZHJbKWKxYMzeV6YwEMmWz6tbKswmcfNfy5OV+m5lAcnukx+mdHiVDU/U/XlKYydw4x9ZXpCgqoTFeAy48VKdSrLbIlX5QxocbSkUD2XGS9MVS1woemrhdEz8BtjeSmPHz+IV/ktTpbAQOujXMpMY4rXS3xsInu6otaFMqf6T506evJE5uA=
*/