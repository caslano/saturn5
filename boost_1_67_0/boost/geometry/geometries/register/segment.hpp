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