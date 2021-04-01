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
fzMyk38M3oop0ECr8n4wBiTRPcKK5/DYN8+Ba7PXeorV8UirzoAx/AAzbCvRrEuRvloPv9sAIcfuSj1Ih7xtMYyisk8yiilFxn/qLXp0kkzKnZzVEDgExjhkfAOExGgIeJ+RkET8a2G/QegUnMirB2/Hang2XE9+PzRDm5PEGMGxYGI7sKVqc4IKG83TBj/SkSd7t+CUqMSxGO0ihYAecui8cccPBSVD5TRbyshGPz2eOcLblGdQYB/QFhUJLU046UTUGGzECbJKdDKjaCjE33p+6MwRU0wcj12htGsgd4OZlrXd5UztUl2L6nLmRgQT0+kdVDHf0yIQcK1KLVrDo5BhkqoCtxBqIEXVrq0MCKECF7E9qLgbncVPwQusISPsaxdHgKDVr/9tB0xU+Y3muNnE/TQdgcOovFT6Bzx9PmyrYbPKnHfcFHQLTAEZ7GYKGOdD6lv1YTERN21dcxqflMmoA5LdHRskVNpHXT4LTM+Y+uxfUDNtzTGVM/5z5kN47qm3QDYqxay8d5RlPudvgjzXHqXSbzEa7BonIzbC+BF3mRuidpyPERyG2Q==
*/