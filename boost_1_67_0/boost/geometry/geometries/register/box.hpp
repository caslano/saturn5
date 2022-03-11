// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_REGISTER_BOX_HPP
#define BOOST_GEOMETRY_GEOMETRIES_REGISTER_BOX_HPP


#ifndef DOXYGEN_NO_SPECIALIZATIONS


#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_BOX_ACCESS(Box, Point, MinCorner, MaxCorner) \
template <size_t D> \
struct indexed_access<Box, min_corner, D> \
{ \
    typedef typename coordinate_type<Point>::type ct; \
    static inline ct get(Box const& b) \
    { return geometry::get<D>(b. MinCorner);  } \
    static inline void set(Box& b, ct const& value) \
    { geometry::set<D>(b. MinCorner, value);  } \
}; \
template <size_t D> \
struct indexed_access<Box, max_corner, D> \
{ \
    typedef typename coordinate_type<Point>::type ct; \
    static inline ct get(Box const& b) \
    { return geometry::get<D>(b. MaxCorner);  } \
    static inline void set(Box& b, ct const& value) \
    { geometry::set<D>(b. MaxCorner, value);  } \
};


#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_BOX_ACCESS_TEMPLATED(Box, MinCorner, MaxCorner) \
template <typename P, size_t D> \
struct indexed_access<Box<P>, min_corner, D> \
{ \
    typedef typename coordinate_type<P>::type ct; \
    static inline ct get(Box<P> const& b) \
    { return geometry::get<D>(b. MinCorner);  } \
    static inline void set(Box<P>& b, ct const& value) \
    { geometry::set<D>(b. MinCorner, value);  } \
}; \
template <typename P, size_t D> \
struct indexed_access<Box<P>, max_corner, D> \
{ \
    typedef typename coordinate_type<P>::type ct; \
    static inline ct get(Box<P> const& b) \
    { return geometry::get<D>(b. MaxCorner);  } \
    static inline void set(Box<P>& b, ct const& value) \
    { geometry::set<D>(b. MaxCorner, value);  } \
};


#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_BOX_ACCESS_4VALUES(Box, Point, Left, Bottom, Right, Top) \
template <> struct indexed_access<Box, min_corner, 0> \
{ \
    typedef coordinate_type<Point>::type ct; \
    static inline ct get(Box const& b) { return b. Left;  } \
    static inline void set(Box& b, ct const& value) { b. Left = value; } \
}; \
template <> struct indexed_access<Box, min_corner, 1> \
{ \
    typedef coordinate_type<Point>::type ct; \
    static inline ct get(Box const& b) { return b. Bottom;  } \
    static inline void set(Box& b, ct const& value) { b. Bottom = value; } \
}; \
template <> struct indexed_access<Box, max_corner, 0> \
{ \
    typedef coordinate_type<Point>::type ct; \
    static inline ct get(Box const& b) { return b. Right;  } \
    static inline void set(Box& b, ct const& value) { b. Right = value; } \
}; \
template <> struct indexed_access<Box, max_corner, 1> \
{ \
    typedef coordinate_type<Point>::type ct; \
    static inline ct get(Box const& b) { return b. Top; } \
    static inline void set(Box& b, ct const& value) { b. Top = value; } \
};




#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_BOX_TRAITS(Box, PointType) \
    template<> struct tag<Box > { typedef box_tag type; }; \
    template<> struct point_type<Box > { typedef PointType type; };

#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_BOX_TRAITS_TEMPLATED(Box) \
    template<typename P> struct tag<Box<P> > { typedef box_tag type; }; \
    template<typename P> struct point_type<Box<P> > { typedef P type; };

#endif // DOXYGEN_NO_SPECIALIZATIONS



/*!
\brief \brief_macro{box}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_BOX, box} The
    box may contain template parameters, which must be specified then.
\param Box \param_macro_type{Box}
\param Point Point type on which box is based. Might be two or three-dimensional
\param MinCorner minimum corner (should be public member or method)
\param MaxCorner maximum corner (should be public member or method)

\qbk{
[heading Example]
[register_box]
[register_box_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_BOX(Box, Point, MinCorner, MaxCorner) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_BOX_TRAITS(Box, Point) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_BOX_ACCESS(Box, Point, MinCorner, MaxCorner) \
}}}


/*!
\brief \brief_macro{box}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_BOX_TEMPLATED, box}
    \details_macro_templated{box, point}
\param Box \param_macro_type{Box}
\param MinCorner minimum corner (should be public member or method)
\param MaxCorner maximum corner (should be public member or method)

\qbk{
[heading Example]
[register_box_templated]
[register_box_templated_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_BOX_TEMPLATED(Box, MinCorner, MaxCorner) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_BOX_TRAITS_TEMPLATED(Box) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_BOX_ACCESS_TEMPLATED(Box, MinCorner, MaxCorner) \
}}}

/*!
\brief \brief_macro{box}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_BOX_2D_4VALUES, box}
\param Box \param_macro_type{Box}
\param Point Point type reported as point_type by box. Must be two dimensional.
    Note that these box tyeps do not contain points, but they must have a
    related point_type
\param Left Left side (must be public member or method)
\param Bottom Bottom side (must be public member or method)
\param Right Right side (must be public member or method)
\param Top Top side (must be public member or method)

\qbk{
[heading Example]
[register_box_2d_4values]
[register_box_2d_4values_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_BOX_2D_4VALUES(Box, Point, Left, Bottom, Right, Top) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_BOX_TRAITS(Box, Point) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_BOX_ACCESS_4VALUES(Box, Point, Left, Bottom, Right, Top) \
}}}



// CONST versions are for boxes probably not that common. Postponed.


#endif // BOOST_GEOMETRY_GEOMETRIES_REGISTER_BOX_HPP

/* box.hpp
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
*/