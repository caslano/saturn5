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
JuPsbO/a0NnS1t7aZAra5RlYY2iME00+vKGzqaGrZd1aE+dj96FO/X/7U0tTLIYY0BasxTJ8+lTY5N1N9cEgp3BfchrG2qvXROMPoNzcogb+3HWoq7qSKJsGQtGWwc1D4jtx7326kT8DcQHwRTNgix2+sa+vX363JSNzDvyVt7xHiLZInLavFHH1LdVRx4P1fQi9Cp7GWWiXJXdER+LReFTs0eidgn7R/4noSCAmxx/wB7hdEjweVT4a5Y1cD/7wE533h6NdQ02DmD/Qjtuxpmkc2CDbVzSWkFUGG8y4q0o2IM4WX70Oc+r3f+lqX2Ybgo67iScZS3r58oFci54HOZMXyaICV415yyg5GH+gNTzIrT4xb0PGsfmgrRrlMjofqI+vYj2EZF2cj7r4YW/8AfHV4K8shjoZXb+KeRqDtr7h5hWeObEA46LklvgDdr37KlDvJ34ZjSb7EsHTNRt1dnNXNMhU8ND94RCV7/wC2EWr3slq0fE2e+9KpjHtK/IxXm88tjT2/dXMluinuo8WYGz9y1UxhsTL8ezVKrx37oeU4nD+xush4xtNXBdRfRxZABmv+7Gqn4Dfzvvt00tWBfru38IMdjQ4znq3L4C9UfUn6KZu2BEBfY8ReHqvQ/1ffgfTp6pqM6EfEvMg94MpKoE/Mx9lewqxXb7rDrhmHvf7w4rOxFAUv49ORzv8Zh/zW/sQoAPuIO/bsYOd
*/