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
Cxn0YW++AGf1vFx/Vvf34OKCpyCPvb+p5pKFNCe0z1uyZDjsEw9ZOBwmKd9PQzC6F913I2hv2GvolQh7Y8HwrIM+OVCY0KF4OCLwDoRnr25AIOwmXFUWZqO2q9YpB/SRM/8BPE1/dNKBAof07sDh4FybGO/+txA+iivSiRTpyju8zjbVOPcafbrSr+lM+rR9PL7Odr8xc2HZe/VOdVC350jGYXSNzdqhHIL8uKZpfZ/exQbFjScgNTcP9RCe1xuCjGXYJJfFMppT3Fb5qz2vYes3L8mIS/ptcXXqk5qhqRNImc1qpVF4+3wVgbYh6P25b+P1h85Cove5tTylEDdtZf+PzDabMVLC91R2uM/Z/PkcyNH6TZLvt85CZOSl/Is0HMr9tjEXfDMRGbe1/iL49C8MzHF/ceZn55/Q2rnQInKlmhn+pSWcgefNn/CWQnb49xb9MLSEn2gLjn2+sQot7RfR8pO6gQP+uYXzSgZJ5FdwedMRjFdwQsWq/SrjczYfIWfUyMiWH9Wbm1IOF6YfQjdfTORKRQ32niVITejasoufpYX1k2MDw8DnheZRY98b2ZgN9ifsm3Zuyp6LMvJFUP+Oq2EjcLvLRtk2D2AY1EZ1tPrb+jy10iAi8rTYVcmyCu9tc0G1cBtFRpPemdWUGvfuiGgdeX+MOTiLagEZt8uH2NzrelzS1Zi1fCxZUuXKBUwTUPBH4AQQpzBj
*/