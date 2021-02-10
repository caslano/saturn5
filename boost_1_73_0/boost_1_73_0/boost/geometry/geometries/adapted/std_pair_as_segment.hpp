// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_STD_PAIR_AS_SEGMENT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_STD_PAIR_AS_SEGMENT_HPP

// Only possible if the std::pair is not used for iterator/pair
// (maybe it is possible to avoid that by detecting in the other file
//  if an iterator was used in the pair)

#ifdef BOOST_GEOMETRY_ADAPTED_STD_RANGE_TAG_DEFINED
#error Include only one headerfile to register tag for adapted std:: containers or iterator pair
#endif

#define BOOST_GEOMETRY_ADAPTED_STD_RANGE_TAG_DEFINED


#include <cstddef>


#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{


template <typename Point>
struct tag<std::pair<Point, Point> >
{
    typedef segment_tag type;
};

template <typename Point>
struct point_type<std::pair<Point, Point> >
{
    typedef Point type;
};

template <typename Point, std::size_t Dimension>
struct indexed_access<std::pair<Point, Point>, 0, Dimension>
{
    typedef typename geometry::coordinate_type<Point>::type coordinate_type;

    static inline coordinate_type get(std::pair<Point, Point> const& s)
    {
        return geometry::get<Dimension>(s.first);
    }

    static inline void set(std::pair<Point, Point>& s, coordinate_type const& value)
    {
        geometry::set<Dimension>(s.first, value);
    }
};


template <typename Point, std::size_t Dimension>
struct indexed_access<std::pair<Point, Point>, 1, Dimension>
{
    typedef typename geometry::coordinate_type<Point>::type coordinate_type;

    static inline coordinate_type get(std::pair<Point, Point> const& s)
    {
        return geometry::get<Dimension>(s.second);
    }

    static inline void set(std::pair<Point, Point>& s, coordinate_type const& value)
    {
        geometry::set<Dimension>(s.second, value);
    }
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_STD_PAIR_AS_SEGMENT_HPP

/* std_pair_as_segment.hpp
sQkFffWP8v5ZiHVfSUWSCVoH7Dv0k2/6pvKn2ZJZXoabDLju7+jKzKyVtoHX3yMC/Cvf9LGRKLgnL6tjEjEUO2samCPIXRFsjxsO9HK88BLopgtgYAuIawIRZXyXBdCw30UUBaT5iYDgULug1oIgGtLGByswugN6Lr3KEtL2UZZOs5R2j1FKJcNoMgXvxSs4PeQ5KtHg/grteDlSg90oCNz4DPaI4WWdT9EPAXhDzHcd3BVn5auQGME80KKIODdOB2e7B/sH/TrvB37zV2mdReu3OR/KUXyUsgDy3OrYZRvbAhHYptdaNcE8DhmLwXqv8AJjoO28t4YeeQ30y7aEptDDecE8NjaomIMXNplDk+BFIeB3ryhIHJMUPEj+lrkBKoH4KOLkrBte1fp4kiIBnxrbxXL/3+GTeQIyEg4n0zp0bLDVgxfPVxvsBW1H8lWvXlKVnJNAtX963uPYS18T5G7mp8OrOiHDpRn9wVqz9kZ821DfmPr2VH3brL1RfVqqtK2+PVffXqhvL40+36nSV+rb9+rbD+rba6PPlSoN1LdD9e0P9e13o8+6Kj2G0uVIztsfYHtOrgIpV5gMNrwxK/e6h2eC0PfoljxG2J2Cgm6SsDaFrnbAy6OIKQj9yLvlgTuKA6Euj8DJc4em
*/