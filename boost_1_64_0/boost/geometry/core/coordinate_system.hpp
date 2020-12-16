// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_COORDINATE_SYSTEM_HPP
#define BOOST_GEOMETRY_CORE_COORDINATE_SYSTEM_HPP


#include <boost/mpl/assert.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/util/bare_type.hpp>


namespace boost { namespace geometry
{


namespace traits
{

/*!
\brief Traits class defining the coordinate system of a point, important for strategy selection
\ingroup traits
\par Geometries:
    - point
\par Specializations should provide:
    - typedef CS type; (cs::cartesian, cs::spherical, etc)
*/
template <typename Point, typename Enable = void>
struct coordinate_system
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
    template <typename GeometryTag, typename G>
    struct coordinate_system
    {
        typedef typename point_type<GeometryTag, G>::type P;

        // Call its own specialization on point-tag
        typedef typename coordinate_system<point_tag, P>::type type;
    };


    template <typename Point>
    struct coordinate_system<point_tag, Point>
    {
        typedef typename traits::coordinate_system
            <
                typename geometry::util::bare_type<Point>::type
            >::type type;
    };


} // namespace core_dispatch
#endif


/*!
\brief \brief_meta{type, coordinate system (cartesian\, spherical\, etc), \meta_point_type}
\tparam Geometry \tparam_geometry
\ingroup core

\qbk{[include reference/core/coordinate_system.qbk]}
*/
template <typename Geometry>
struct coordinate_system
{
    typedef typename core_dispatch::coordinate_system
        <
            typename tag<Geometry>::type,
            typename geometry::util::bare_type<Geometry>::type
        >::type type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_COORDINATE_SYSTEM_HPP

/* coordinate_system.hpp
w8MUD9nnSJrykCYHKBOZ9NJG8ayWUatqqfwM2lG1OIoIF7yqffDSSsn2ZMmWjiFEKKINKQUrftiTyZyXcgXSxGrTXQ0fCQL28ILdztvr5dktP/rhYht/LTeY8joeRUP73je6154ZN6cXPECFtC1OySeDdXILihM0+BKrdClRD2C7KTGRZ8mT7P8eQJ725qdPtda0lXHySWxUnQV1yI/EOSI7MgtL25CC+aRgIu5ODaTfCs/Be1rOwe+E52D/zkCNnJl2WPBioEa2sJbI9Na6QQstH4VWiHuF622WSNsEq2dF1oz51+zy9wgsTHX4uxrutOqKXQfmvAf+9AVOCJ7N/QlF86gNaR/b4Q38yDUrpCptTBEmsXPqu1ohQs1t5IR1wO9woUW/KoJ03Dlvlf3tcHGQz51A2jd3Y9q3pB6e9rUnnXaw77dfR2UoBg/5Jtlx+zvapC4ZeiPKivOzcxBGBP3lUMpXzhbtLfQbpy/iPQKxFzGN2JuYTuxHHEAcRDyLOJSYQRxOHEE8l5hFHEkcRRxDzCXmET8jvkfcSdxCXE98hLiaeBsR7UzuTYiNxOHX816GuJeYRRxJHEUcQ8wlvr+odfcDdP+A+AqxEfgopC4f9oc6/jp6ZszETMzETMzETMzETMzETMzETMzETMzETMzETMzETMzETMzETMzETMzETMzETMzETMzETMzETMzEDE2r/OnBXc/FTMzETMzETMzETMzETMzETMzETMzEzP+Fyb1YcR6/v6wwl7IrmsrsB4OH+UGeNviXC7NUgIsQoEX0DAQB56WRTNZaUYoMPSwfPimSUApKjYshbqhwuvls+4PBlSKEuyUzqyShomdursgCr2ut83YoL/taOF5jJmZiJmZiJmZiJmZiJmZiJmZiJmZi5htqLDETMzETMzETMzETMzHz/2kSbMreNSCu3Ap7ZYaFdu5wbY8QO2JW6/fpI5WdnKPsbbSPNPPnz6E9dOhU/J9XWjwXLkOGDR02NGPWVDxOvWr2vGmwh85oPX8dO6t0O3VT9rQUZa/squz+2v5+J2Un6Xglg1R5nPq9/LB362kq/Is6/TahuLnqvVTsf+Pvn3GU338zDmCTCJZ/ycyYMxsKrdJmzZ47e35J8czI9ykuW1Bc1sL92N9r5rBpc2ZfNXTGCYS7Zv7V4XCTJk4umuYqmDRseNa0sYXTJrldw6ZlZcDjGP6Zw4/wd+VLoGkS6oKxhZaj+Q8/51zlf0LlmV/mKz1a+zu84vvpdpDcRdkjeyh7Q7KyO3RU9iTdHjK0XaT9L+ml7B36+5+h7YtPV/YD+n2B/p0JOv7yM5Rd1VPZh/Tv9ND+a3X6Xp2+P1XZu95U7e5zHX+/zu/Hut3a7eGiJf4vls9mV91HivTfWL7pxymfNVI+x39j+Xa9cYzyfYX+N+ybVr5T3P/+28p3sv3vm1a+U93/vmnlO1X9b1jHb+j4cor6339r+U60/31Ty3eq+t83tXzH63/BQy3Ll6vd1+l0tp7k/H73aa2Xb7ne1/h0ukk6f2k9v1r5Huym4w88dvn+cSjS//4by7f6OOULBiPj5/9k+U6yfQ77hpXvVLfPb1r5jvv9TrJ9/teV7wTb54nOD//u8h2vfVqs/9vlO9H+900t33Hb5wn2v//W8sVMzMTM/6456rl66ff9xf7i498TlBXPmFc2U6xpc668rrhs2sxh0WfxfWfq8/1J3rQr5xSX+dLm+q+5CjcW2v/K+fPhOHve3LRZV86eUzxzZNqc4rlpo0anIULmtImTpxW6pkwr8ro8E6Z5CyZcMNkdSvio8TPoXlZ85cy0EkBxWeT9qnkzr8Nz+H3mvLnF+t0/93tz5107l88=
*/