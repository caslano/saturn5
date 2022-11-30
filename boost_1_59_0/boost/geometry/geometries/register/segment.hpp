// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_REGISTER_SEGMENT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_REGISTER_SEGMENT_HPP


#ifndef DOXYGEN_NO_SPECIALIZATIONS


#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_SEGMENT_ACCESS(Segment, Point, Index0, Index1) \
template <size_t D> \
struct indexed_access<Segment, min_corner, D> \
{ \
    typedef typename coordinate_type<Point>::type ct; \
    static inline ct get(Segment const& b) \
    { return geometry::get<D>(b. Index0);  } \
    static inline void set(Segment& b, ct const& value) \
    { geometry::set<D>(b. Index0, value);  } \
}; \
template <size_t D> \
struct indexed_access<Segment, max_corner, D> \
{ \
    typedef typename coordinate_type<Point>::type ct; \
    static inline ct get(Segment const& b) \
    { return geometry::get<D>(b. Index1);  } \
    static inline void set(Segment& b, ct const& value) \
    { geometry::set<D>(b. Index1, value);  } \
};


#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_SEGMENT_ACCESS_TEMPLATIZED(Segment, Index0, Index1) \
template <typename P, size_t D> \
struct indexed_access<Segment<P>, min_corner, D> \
{ \
    typedef typename coordinate_type<P>::type ct; \
    static inline ct get(Segment<P> const& b) \
    { return geometry::get<D>(b. Index0);  } \
    static inline void set(Segment<P>& b, ct const& value) \
    { geometry::set<D>(b. Index0, value);  } \
}; \
template <typename P, size_t D> \
struct indexed_access<Segment<P>, max_corner, D> \
{ \
    typedef typename coordinate_type<P>::type ct; \
    static inline ct get(Segment<P> const& b) \
    { return geometry::get<D>(b. Index1);  } \
    static inline void set(Segment<P>& b, ct const& value) \
    { geometry::set<D>(b. Index1, value);  } \
};


#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_SEGMENT_ACCESS_4VALUES(Segment, Point, Left, Bottom, Right, Top) \
template <> struct indexed_access<Segment, min_corner, 0> \
{ \
    typedef coordinate_type<Point>::type ct; \
    static inline ct get(Segment const& b) { return b. Left;  } \
    static inline void set(Segment& b, ct const& value) { b. Left = value; } \
}; \
template <> struct indexed_access<Segment, min_corner, 1> \
{ \
    typedef coordinate_type<Point>::type ct; \
    static inline ct get(Segment const& b) { return b. Bottom;  } \
    static inline void set(Segment& b, ct const& value) { b. Bottom = value; } \
}; \
template <> struct indexed_access<Segment, max_corner, 0> \
{ \
    typedef coordinate_type<Point>::type ct; \
    static inline ct get(Segment const& b) { return b. Right;  } \
    static inline void set(Segment& b, ct const& value) { b. Right = value; } \
}; \
template <> struct indexed_access<Segment, max_corner, 1> \
{ \
    typedef coordinate_type<Point>::type ct; \
    static inline ct get(Segment const& b) { return b. Top; } \
    static inline void set(Segment& b, ct const& value) { b. Top = value; } \
};




#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_SEGMENT_TRAITS(Segment, PointType) \
    template<> struct tag<Segment > { typedef segment_tag type; }; \
    template<> struct point_type<Segment > { typedef PointType type; };

#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_SEGMENT_TRAITS_TEMPLATIZED(Segment) \
    template<typename P> struct tag<Segment<P> > { typedef segment_tag type; }; \
    template<typename P> struct point_type<Segment<P> > { typedef P type; };

#endif // DOXYGEN_NO_SPECIALIZATIONS



#define BOOST_GEOMETRY_REGISTER_SEGMENT(Segment, PointType, Index0, Index1) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_SEGMENT_TRAITS(Segment, PointType) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_SEGMENT_ACCESS(Segment, PointType, Index0, Index1) \
}}}


#define BOOST_GEOMETRY_REGISTER_SEGMENT_TEMPLATIZED(Segment, Index0, Index1) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_SEGMENT_TRAITS_TEMPLATIZED(Segment) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_SEGMENT_ACCESS_TEMPLATIZED(Segment, Index0, Index1) \
}}}

#define BOOST_GEOMETRY_REGISTER_SEGMENT_2D_4VALUES(Segment, PointType, Left, Bottom, Right, Top) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_SEGMENT_TRAITS(Segment, PointType) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_SEGMENT_ACCESS_4VALUES(Segment, PointType, Left, Bottom, Right, Top) \
}}}



// CONST versions are for segments probably not that common. Postponed.


#endif // BOOST_GEOMETRY_GEOMETRIES_REGISTER_SEGMENT_HPP

/* segment.hpp
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
*/