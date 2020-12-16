// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_BOX_CONCEPT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_BOX_CONCEPT_HPP

#include <cstddef>

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/point_type.hpp>


namespace boost { namespace geometry { namespace concepts
{


/*!
\brief Box concept
\ingroup concepts
\par Formal definition:
The box concept is defined as following:
- there must be a specialization of traits::tag defining box_tag as type
- there must be a specialization of traits::point_type to define the
  underlying point type (even if it does not consist of points, it should define
  this type, to indicate the points it can work with)
- there must be a specialization of traits::indexed_access, per index
  (min_corner, max_corner) and per dimension, with two functions:
  - get to get a coordinate value
  - set to set a coordinate value (this one is not checked for ConstBox)
*/
template <typename Geometry>
class Box
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename point_type<Geometry>::type point_type;


    template
    <
        std::size_t Index,
        std::size_t Dimension,
        std::size_t DimensionCount
    >
    struct dimension_checker
    {
        static void apply()
        {
            Geometry* b = 0;
            geometry::set<Index, Dimension>(*b, geometry::get<Index, Dimension>(*b));
            dimension_checker<Index, Dimension + 1, DimensionCount>::apply();
        }
    };

    template <std::size_t Index, std::size_t DimensionCount>
    struct dimension_checker<Index, DimensionCount, DimensionCount>
    {
        static void apply() {}
    };

public :
    BOOST_CONCEPT_USAGE(Box)
    {
        static const std::size_t n = dimension<Geometry>::type::value;
        dimension_checker<min_corner, 0, n>::apply();
        dimension_checker<max_corner, 0, n>::apply();
    }
#endif
};


/*!
\brief Box concept (const version)
\ingroup const_concepts
\details The ConstBox concept apply the same as the Box concept,
but does not apply write access.
*/
template <typename Geometry>
class ConstBox
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename point_type<Geometry>::type point_type;
    typedef typename coordinate_type<Geometry>::type coordinate_type;

    template
    <
        std::size_t Index,
        std::size_t Dimension,
        std::size_t DimensionCount
    >
    struct dimension_checker
    {
        static void apply()
        {
            const Geometry* b = 0;
            coordinate_type coord(geometry::get<Index, Dimension>(*b));
            boost::ignore_unused(coord);
            dimension_checker<Index, Dimension + 1, DimensionCount>::apply();
        }
    };

    template <std::size_t Index, std::size_t DimensionCount>
    struct dimension_checker<Index, DimensionCount, DimensionCount>
    {
        static void apply() {}
    };

public :
    BOOST_CONCEPT_USAGE(ConstBox)
    {
        static const std::size_t n = dimension<Geometry>::type::value;
        dimension_checker<min_corner, 0, n>::apply();
        dimension_checker<max_corner, 0, n>::apply();
    }
#endif
};

}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_BOX_CONCEPT_HPP

/* box_concept.hpp
cI7mT3P+rtLx5ly3N3/OgW1Ub6f6NlgGv4FV0AxkCQyD58EEWA5T4GLYDp4LR8BlcLy6208/WMTgbh2yFzmG9BxOGSMO/p63FffIamQrsg85hiTdQ3+O5CJVyDpkO7IfqUWitxEOMhEpR9YgW5HUbMKAR5D4e+nzsxGYi1Qh65HtyF7kMBK6Hb/D8Yu4RxAmMhaZh6xA9iJHkdCR5CsyFFmGbER2IQeQI8gxJH4U9ypkLFKOrEY2IXuQw8gXSPxo3CBDkRpkHbIdOYgcR6JP5zpINpKDlCPrkS3IPqQWSRqDf2QOUoOsQTYi25EDyBeIeyxlj+QipcgKZB2yAzmEOMZxHWQUkousQFYjm5BdyAHkGBI/nvgiY5FZSA2yAdmJ7B1OvOERxDGBuCM9kWJkNbIV2YMcQI4hGROZo8DPWDgPqUE2ItuRvUj0JK6BFCPLkNXIVmQXcgxxTyYMJBcpQi5DtiJ7kaOIYwpxRbKRGmQNsgXZiRxEjiEpOdgj85ByZDWyFdmD1CIpUylrpCcyFJmDVCGrkPXIFmQnshc5ioROI4+QTkgmMhEpQmqQdcgOZD9SizimE9ZK6igchRQjq5EtyD7kCBKdSxqRHGQeUoWsQjYgO5H9yCEkcgZpRYYiOUgVsg7ZgexB9iNHEPcZXA/JQuYhK5BNyA5kL3IQqUUiZ5IGZBayAlmNbER2IHuQw0jkLNwgo5BiZB2yFdmNHEJqkegzuR6SieQgK5D1yFakFkmaTVyQWUgpUoNsQLYiu5DDyLHhtAWYdBbhIKOQXKQIWY1sQXYie5G3kONI/BzcIqOQecgKZAOyA9mDdNqOHVKE1CAbkF3IQeQY0uk+4ouUI2uQHch+pBZx3099QHKRKmQdsgt5CzmOxD/AtZFZSA2yCdmHHEWid5BepBRZj+xDHA9ihhQha5A9yDGk50PUH6QK2YDsQg4hkQ9T1shEpBxZg2xH9iNfIPE7qTNIDlKKXIZsQvYhx5DUX2GHrEC2Im8hoY/gB5mHrEZ2I0cQ96OYI7lIDbIJ2YscQ1J3Ec4uR9Ov6df0a/o1/Zp+Tb+mX9Ov6df0a/o1/Zp+Tb//8F8osshhxADHqMFzysrZn76suqLQ4/2zsrRXQXVJaVGvPr379M6Y32tJZd+MPgNtu2UDMntVFudXeIp6VXhKPfmVHssFtnMqqziLfaEir7SkoHdZwTlcZ7BjaIy56dd+RxxT6o/mO2xOKimsKKssm1+Vmj6tW+qU8qqShSXnlSxakDqSffZLSj0Vsgf/PSne+YsQh7ntuZ4fmVeVX1DqcaRhvw37/WJf1NABv3DHxJi/Jph7pLWUdK8y7LyQnxNZG8/cymTZWz1n+MgJo3Pz9HwW9oP21NvHfrxhuQ2VfZAD53TqeC4m+xxHQk+9fY4HaFzidW1EWF35yB7BNX5xqfAszC9ZRMYEi4+6D/sR8YmO0W/p5fclkoR8iAzGZo03PhRzv7yisrylFZyQgJXffvOJut/8TnH7LHFxOW5DNI4aRrq1zz9/Vy0v99jnsKt9OwmnFfo20fc4ehG/+xD/c/Trzgd4Xtw9gs4Z9oi1V/Ua4v1ezMnsVR14b2qugW7FcVDMpClcB7OQGP+9+rdrRfoYaYkcQRaZdXJKXZ6VVVeVV1flcZgz/xVTmI7Ae/W/J35edzzO/5pvGk6ipL9S3BeWn6tlP8G279vg7P1Y/krLMe2ckley3kj0mbh1cs0s+yyFv0oYT2BunztqX3+0+Emy83UTAa+PPplzEQKfg1ApuqZB3RBvzEoln5fI9XivlOLfVjZpI1mh+bwEWWRWnKl2PtPoz/XkLcwvxDTgWdetxW2BlTb86h7xuA3DLbE=
*/