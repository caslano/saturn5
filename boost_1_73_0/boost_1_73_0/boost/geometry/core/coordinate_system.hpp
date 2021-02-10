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
o/vJ6D4hGSt7K8Lop50ulv11mNsefYu4riHuoXZKk7tLzG2LWZO0bkVa+xOI2+DM/WR5QiprilXjQTy9Im0tz1i0TtTTJW06hjJeoiCKI1YZC5aJpS1Yj1gon3PCDG9IMLn/sOH2bjjHZjYc2EY58ZLuMLfHrJCmA3rzmjZKjVygIoab3tKzDYwHSrIeQwyD63ZqweNCmnGF8Wupu1tOhjY9zm74yBtw0Ntjr/d6OP7yyKK0piy5Gg9PcUNtbSzIeeivmgcLV9U8qKrXpELVvs2GBV5tmOHvo0mhzVmPFKSGAomr2qwAVk01dNkpI4gx1rqHNjM2/El4Q6IeRRzjiDWI0+FNkzF6AL37yWL2KJTbv5a0370JMC0WlCqarQhvQgRuOXBLjRWMAR38JZxtm2NCTsjJONyA+wmdfIlqM7MHw9icrtBpWpK91/tt3PmrvWr/UrOwVG3OO2goyxnZk66l1Q6+vaY+JlV6bFpnBrkOuc2u13GG4+lg5JxevHw1HA0mG58h2pm4jgTaksXIxF6K+bm1otwLFB08HB9+9fUz1oDepvtjQgm3xoq2o36WRKVXeYeB2/VdGoTH+6rrTISQ36a82ylZw8NCD1W8p1XXEK5X7oaxHnZxd+vjhncZSzq3jSzrceNMUqth
*/