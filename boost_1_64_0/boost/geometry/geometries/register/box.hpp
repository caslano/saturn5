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
7H0r6/aZWJlwcnuyvM01fPaXaHAmViz6LL/nQf9xxlvabhWOttqf5Dwr7fZcz/I8zzLvdkf8wUZHVXQqAdus+PlBZ8H47sOUpTemg9I3Q41PjTc+ZbyvzrNfVJewQ6C9K1Oje2uq/zh7rHet6Hc5rH0/1pHf1yHXIz9H1iM3IDciNyWcTB/uBtS/vYSrZZPo/bvTxMl9+jrULKrOjGaIP8wOP2uZZYl+0NYHir7P1geIvtvW+4u+w9Yz9V4SOG/L9UXdZYjF02gza/YGy1sOw7ByVc7uClju6n+e48T71rkB/bRPHn1Ylx/9rTw6XGeWaZntrzPrY+Xb83v9820Pum++/RrdN98eRvfNt/tsPTNgnZys+Zaj+xZ21DqZjAwn37KfC5Zv5WWVVfbtTjMwcN4Rhv1MPVPsllZa97Q4qPb2eOKWk6qL1IEAe9jOFF3C97t3ryFhkk4u0BISL0lfeePpW/p31s4DMKoiDcD7djc9gXRCaJGOFEMPTXqRGno9alAiLZKgEVAJoOIJHBYUsaGCIiAGBUHFEwEPVNDYUVFRUfFsHAKiotz3/v3fZDfZxVyJDt/+09709ubNzJ4zPSBONbWfuFHctbe68e83qF9RyZZZZ1N/U8rFOV3i7JinWz1YrVnEaQ1eK1bPPeduuVcxo9bG0AelkiZe7N9CmswmJmvhLSkVO7fygumjZ+LUlWfRL6T45EtV7pUamH5L65p7qCT9btbykfFayPSbM1WSL/g9CS3E3TxXJzk1z6Sb+pdYNt00bdScUOSRbk5/8r32JQ//n9LFvz3po2fm7dR6AWXMdzREvMtXiaB1Qt2vDDXOM+bNiGM0+utSSHvUetSjqMdQG1CPozaiNqE2V6jexALK38HS9mniQdPutHSp3siD5dv1gaV6zR29ngfLt/UdjV47kVsi+7dhFyP7t2EXIfu3YWnI/m1YZSO3CpV/pu8vm38dNTGWuMk/ZXtMSg6Gyj+55EPOss4tyJ09K3j+4T6wr/1C5HB36f0eM4Ept2o/zn2tlS53r/SnXJ1D3U6exUYWjZDxkeonN1D9SkVH/cdNK9GblVDRcw5jAX69UZrPe1836djW5PMho5fp6BUbey2N3t+MXot2jt6UUr02jl7HUj1TbuYdKt+vDTgUWCbCS8Mh8mH1hxHfn9xdMhME5vk+Pcdxs0WeK/tVtzMhVJ7LQZ9+mR40z9U97Y6OfZNF7m/VtKJN35WbUPE6OPFN3Dvp9mb5dEss1TP54DJ6zU0eHioxeiYfnispP+ZYWFK+/s4qKV9/+5cE1s9uyP71MRM5RH0M3Bt2cfn7/abY7/7eknzwredVYG+Yz35kyL1hal7hNZOK7P9y1mLH6SJ6KipO1YfUw0xfHLjLeejQ/hO6X5bdp+cQ7q6c5cRjpa/sTEfUeKgbnf+uEPO8Av+7btTclCVPgqvC7wxWSvrL80ybuEL05BmB6+hB4vQJccoOEic5elXjdCSlfJyyy4Q56j8IM/5pmAPDV9KkfPiOYjcvWPjkGu3Q4cszaW7uhMwphOZO4jLhj/svw58YcD+fPCOgLsxoWj5OF1Ul3wLjNGhAtqS4hLdW1fLxWfk/pDf+BU3vLs3Kh60edovLh01TO3T4ii+Y3pj/D+ldq2rF0/tYkDhlV6dsmTiNap3ZbsLArgN6ynWViYT3M1nntC9EYhe5/56nMmE+l/jnYU7VMOMn4VM/y6xL7LukfBg/p0ydCBLGvNl5clWok/ZVE8qlvbpLlbg8Ke2L7eLyubOm+K0flonL2f8g/Xmmk/7mXgSeg57znMBytTqzfPy6pfHe5+0g8ZubPy103NSNlqvN5dtOzAPjFfNfxsspV5s=
*/