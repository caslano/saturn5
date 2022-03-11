// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_REGISTER_POINT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_REGISTER_POINT_HPP


#include <cstddef>

#ifndef DOXYGEN_NO_SPECIALIZATIONS

// Starting point, specialize basic traits necessary to register a point
#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, Dim, CoordinateType, CoordinateSystem) \
    template<> struct tag<Point> { typedef point_tag type; }; \
    template<> struct dimension<Point> : boost::mpl::int_<Dim> {}; \
    template<> struct coordinate_type<Point> { typedef CoordinateType type; }; \
    template<> struct coordinate_system<Point> { typedef CoordinateSystem type; };

// Specialize access class per dimension
#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS(Point, Dim, CoordinateType, Get, Set) \
    template<> struct access<Point, Dim> \
    { \
        static inline CoordinateType get(Point const& p) { return p. Get; } \
        static inline void set(Point& p, CoordinateType const& value) { p. Set = value; } \
    };

// Const version
#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_CONST(Point, Dim, CoordinateType, Get) \
    template<> struct access<Point, Dim> \
    { \
        static inline CoordinateType get(Point const& p) { return p. Get; } \
    };


// Getter/setter version
#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_GET_SET(Point, Dim, CoordinateType, Get, Set) \
    template<> struct access<Point, Dim> \
    { \
        static inline CoordinateType get(Point const& p) \
        { return  p. Get (); } \
        static inline void set(Point& p, CoordinateType const& value) \
        { p. Set ( value ); } \
    };

#endif // DOXYGEN_NO_SPECIALIZATIONS


/*!
\brief \brief_macro{2D point type}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_POINT_2D, two-dimensional point type}
\param Point \param_macro_type{Point}
\param CoordinateType \param_macro_coortype{point}
\param CoordinateSystem \param_macro_coorsystem
\param Field0 \param_macro_member{\macro_x}
\param Field1 \param_macro_member{\macro_y}

\qbk{[include reference/geometries/register/point.qbk]}
*/
#define BOOST_GEOMETRY_REGISTER_POINT_2D(Point, CoordinateType, CoordinateSystem, Field0, Field1) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, 2, CoordinateType, CoordinateSystem) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS(Point, 0, CoordinateType, Field0, Field0) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS(Point, 1, CoordinateType, Field1, Field1) \
}}}

/*!
\brief \brief_macro{3D point type}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_POINT_3D, three-dimensional point type}
\param Point \param_macro_type{Point}
\param CoordinateType \param_macro_coortype{point}
\param CoordinateSystem \param_macro_coorsystem
\param Field0 \param_macro_member{\macro_x}
\param Field1 \param_macro_member{\macro_y}
\param Field2 \param_macro_member{\macro_z}
*/
#define BOOST_GEOMETRY_REGISTER_POINT_3D(Point, CoordinateType, CoordinateSystem, Field0, Field1, Field2) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, 3, CoordinateType, CoordinateSystem) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS(Point, 0, CoordinateType, Field0, Field0) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS(Point, 1, CoordinateType, Field1, Field1) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS(Point, 2, CoordinateType, Field2, Field2) \
}}}

/*!
\brief \brief_macro{2D point type} \brief_macro_const
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_POINT_2D_CONST, two-dimensional point type}. \details_macro_const
\param Point \param_macro_type{Point}
\param CoordinateType \param_macro_coortype{point}
\param CoordinateSystem \param_macro_coorsystem
\param Field0 \param_macro_member{\macro_x}
\param Field1 \param_macro_member{\macro_y}
*/
#define BOOST_GEOMETRY_REGISTER_POINT_2D_CONST(Point, CoordinateType, CoordinateSystem, Field0, Field1) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, 2, CoordinateType, CoordinateSystem) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_CONST(Point, 0, CoordinateType, Field0) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_CONST(Point, 1, CoordinateType, Field1) \
}}}

/*!
\brief \brief_macro{3D point type} \brief_macro_const
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_POINT_3D_CONST, three-dimensional point type}. \details_macro_const
\param Point \param_macro_type{Point}
\param CoordinateType \param_macro_coortype{point}
\param CoordinateSystem \param_macro_coorsystem
\param Field0 \param_macro_member{\macro_x}
\param Field1 \param_macro_member{\macro_y}
\param Field2 \param_macro_member{\macro_z}
*/
#define BOOST_GEOMETRY_REGISTER_POINT_3D_CONST(Point, CoordinateType, CoordinateSystem, Field0, Field1, Field2) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, 3, CoordinateType, CoordinateSystem) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_CONST(Point, 0, CoordinateType, Field0) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_CONST(Point, 1, CoordinateType, Field1) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_CONST(Point, 2, CoordinateType, Field2) \
}}}

/*!
\brief \brief_macro{2D point type} \brief_macro_getset
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET, two-dimensional point type}. \details_macro_getset
\param Point \param_macro_type{Point}
\param CoordinateType \param_macro_coortype{point}
\param CoordinateSystem \param_macro_coorsystem
\param Get0 \param_macro_getset{get, \macro_x}
\param Get1 \param_macro_getset{get, \macro_y}
\param Set0 \param_macro_getset{set, \macro_x}
\param Set1 \param_macro_getset{set, \macro_y}
*/
#define BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET(Point, CoordinateType, CoordinateSystem, Get0, Get1, Set0, Set1) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, 2, CoordinateType, CoordinateSystem) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_GET_SET(Point, 0, CoordinateType, Get0, Set0) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_GET_SET(Point, 1, CoordinateType, Get1, Set1) \
}}}

/*!
\brief \brief_macro{3D point type} \brief_macro_getset
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_POINT_3D_GET_SET, three-dimensional point type}. \details_macro_getset
\param Point \param_macro_type{Point}
\param CoordinateType \param_macro_coortype{point}
\param CoordinateSystem \param_macro_coorsystem
\param Get0 \param_macro_getset{get, \macro_x}
\param Get1 \param_macro_getset{get, \macro_y}
\param Get2 \param_macro_getset{get, \macro_z}
\param Set0 \param_macro_getset{set, \macro_x}
\param Set1 \param_macro_getset{set, \macro_y}
\param Set2 \param_macro_getset{set, \macro_z}
*/
#define BOOST_GEOMETRY_REGISTER_POINT_3D_GET_SET(Point, CoordinateType, CoordinateSystem, Get0, Get1, Get2, Set0, Set1, Set2) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, 3, CoordinateType, CoordinateSystem) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_GET_SET(Point, 0, CoordinateType, Get0, Set0) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_GET_SET(Point, 1, CoordinateType, Get1, Set1) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_GET_SET(Point, 2, CoordinateType, Get2, Set2) \
}}}

#endif // BOOST_GEOMETRY_GEOMETRIES_REGISTER_POINT_HPP

/* point.hpp
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
*/