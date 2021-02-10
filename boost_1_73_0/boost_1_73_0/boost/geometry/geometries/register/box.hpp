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
WXGWzS8GyfcTevK/LtPPn7eq7OUgyeoknW5JV6eXeZVU5Xl9k86zBH6f5uOsqLJJklbJJKvG8/wM/siLpL7MkvN8miWvj979sn/4wyC5uczHl9jJbblIqstyMZ0kl+mnLJln4yz/xH3M0nmdlOfwOXQ+yasaOlzUeVlswdhZUmfz6wr7wOHTaVUm6ac0n6ZnMFBaJ5d1PaueP306XsynMPunk3JcPR3r8rcu62u3kl9gEtfpbVLO6qQuk0WVDRJsOUiuy0l+jv/ChsDD2eJsmleXAz8bGKqYPC3nSZVNp9gXfJdnFU87S05kewbYLJnBjPMa/6nKosKhbi7L66Ah7CP2cr6YFzAQ7AM0mpSwzYNkUUyyOTWmlesQsqe0wZ1H4+c7ScoCJpM83D1J9k8eJmdplVeD5MP+6Y9H70+TD7vHx7uHp78kR2+S3cNfsLOf9g/34OhzGGyeZJ9n86yCwedJfj2b5tlExvz9fp5ubPxTXoyni0mWPMTTG1VZvZhtXT40L77HF3y2ly/tB/BkktYptvYP63laVOfZPHxKH9sH47Io4MaHD2fz8gKXHD7N0uo2Pw+fVZew29HHVTTE9WJa540Ps2ISParz6+xTGn2MIB1/OW1MGM68mDYmXM2ybDK+zMZXzTWPU3jR
*/