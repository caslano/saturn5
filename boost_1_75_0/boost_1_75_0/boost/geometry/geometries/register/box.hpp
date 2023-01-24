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
lY7Jjg/cNeEBqNB7sR1WulT2nU+J13JIGFifBaYri+9RW5L5CdHbfj5nEhUl754KYmAl+EbdXjOCVv49ZzgRmh9YEYqsJxMxJTHr/MARuUyWLCI19vOz7+/FlxidFjyy57LVfYqjaQEQAL823WkCf27m6X0iI/wJYH8oca+UnnDF2frM9V03k1tH/Vy/C7Xt3Ws2wkNp2w3zP4/o9ejQWFd0Ss3Wu8qts9KEHwy75Pg2a6Du6evDdsM9aRjJ2d17BVe0F7mozG0FsrX+Fn62q1QZguTuxJk4K5BlQ3cSf9MNscym8Ba2nG/GxdJdK+spOdpNtlaLgCLQ/A5yjdN64+p+7+QLLd5L/n0678z6zo1lsgLhL7vLZlBGYipQQa6hC1pFiY4eFVbK8kDzxVPlEgh+umVTmUWxhMhrkanUi/JeooNvH9Nr4zt47CPO3jQGbHkiDMfQWb/13PI3GsyNrI3QVJk89y1Tl0xmcKp6MeOR9HO/FCvaXywK/3XpexODSL4818cby0lePO0D7f5dgw67Mim2KOake+DaCxkucT5htLCmlKDgVEKy2kj+8uhgmu1XjYqd24ddvVChhSqq3FCPjLVWFcjH/dyhr/ZT+KVKHziPguopOejlYPUldFzfoLIuSbZ9oQJULnZN12TfznYtm87Wy+12K5F//p4XIdO+CzeuQC9D3zRZ/dltnqy8fbtY2k7RVkrBdJrF
*/