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
+9TEDFlH0LWk0jCHuQ5Z5dpRLUsNxE2joPNc8lv+YtSOzGe1nfy9luQbLfTNalf3mIrduID5bBfiunqpM845G3o+q2U1TfzIUtlSP+uJX7H4U4By2s5FVmyc8w7RMb8Tpfv1zpabx2p4zmHncQnP26XzWK8vvPdhdtjvGUXf2vNYzT81P4vapO5lHusNmMeatfCvtS1MRIDSfh73O0uqC+ob5K7wnzALfgud9hIZVmQu+Odr2rJPIEg7WBikHZxmvs0JqLf6bZne77fc5RLqWQCL4Jc8L6N2kHYw8NQb/7bQvMvsIe6mWLfRqn7iiuCk0D7aJjp+1tV2k5In8jDewHcN1U6qm4vE/yHIXUWeZN2J/2/wTXukdUn5tk/r/6ViN8/aYM4NUP/Iidp2HaZu7lqm4yDKTyzDoE5hnm52NUUr5FpVErxa/HnJNYK2bKm+601Cp7AO+uXXqMy8eIW4+6d911PQ+koY5W+y2Gsn9XWw1tehotfE6uL6Uu2KZX1mPVNfZUz/V+7LWab1Va6+i4opBLyCLP9+TfuKeeL/H84dQOg58ekg7eGuW3mXsqy0Tk2JjYuR8Y6a9Vjm1Fl5oKlHTnh2LtMxbiPZ0lkQk8tYJ8w31umP2dJSv73d7LFOnI511Hwbqljdx4Ylx0TJqmRMu5DzGvK37nLSPMWZZ6VVtcPNe/6yd5SWv+NUy3OmxL9P0DJb5h49/Kp4Pb/wnXn6nU5AnQ5ct9l1l8/D59y6bwHK+KVu0HrLCR7Bxy59xP5K92/mu2nHj4ah6qSaNzbrNv1EHuvuZiVaodZt8up7zHfu2caPde5+VivLLrdr8T/UGKan2L3Nfc7y6hjGcV9P6vFq8njGSq3HYUXhVONmUbERLWKjE+1V57gg9djMXS6rJ+Mc6ydXlPkm9UEJa4ugdXgYbq4WN42s3bwxvNBaQ0+xlxUwL80WvTT/eSnPKzcvVb2LzTy5sbh70rLju2EFfd/fzL67VhTsiLjwCE+i/UPXcVdjfhil9SmiqKu9Z903PnHMz6K2GD+oF/59rD5n2kpnb3xlMy9lGCTPcGHWEeWblxZdZI+QYpx5qZrnoIp97n3rEF6ZKHm8Zeur5uPC2513Bq/H1CP3vJew2f1P7kI9J2Whp8qWk3bl80/Xp6pIWi61Gllh+l5I3bBOEWouWl/cjFfZPCMgv88TDjkT3W+M5VF3ofK7r8lvXb/T/P5J/PraymKfmJ3WeaRjxu3OOsRxHX/FeELtlQiT566xOlkeHQ87Yc6S/mHZbaQbyqxd/EveJ0SatQu1U/12s3ZxvOw4zAnXgtud9wlv2yUwir5Gykdd9MehNorZETv3zbuEVDUvRG1y3GIYsMdUy0T/O526fV3MZXaNJoGC1mn9bne3pN2n1vVWhH7L68S9VdC1iEykw+LG7Q6V//8U844XzP9dYqd7QH3fL3qtK1zfnfx/WNxluQdzY5adVktIpyN3OPm/yX6vEWfrL0NvF8qXxjvl0w9JXzU7jNpi3HhL1xnVzz53OutON5Wr30dxWx1zXXdaHVC/1bwH5sU+9xWq33XvcsZbtWJiY3rYNbwvwQpZv6fb3xBLWiRaPjlE/da8XI20Quz3D5mX94v5gAvm5RViZ7joDdG8HC16raxQeTkkSF5mIg8Sd7e6b3Htl7qcbafZKs3L8U5V9o2DRqG/EuXUyyti2kq1lDxV880oX50cb+dprElj9TvjLs3TS+xpka4pRfj834bbE6X+e3v7rympeXXcF/vc431yTOQF8lXP2WUNKVB9h9J9QmZMlP0nY6KVZcZEq4OMidYGmftsCDJOOgXTPKQR7uOtHX+76o4my3Ze/lmV3zefbng=
*/