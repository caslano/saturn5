// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_BOX_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_BOX_HPP

// Adapts Geometries from Boost.Polygon for usage in Boost.Geometry
// boost::polygon::rectangle_data -> boost::geometry::box


#include <boost/polygon/polygon.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{


template <typename CoordinateType>
struct tag<boost::polygon::rectangle_data<CoordinateType> >
{
    typedef box_tag type;
};


template <typename CoordinateType>
struct point_type<boost::polygon::rectangle_data<CoordinateType> >
{
    // Not sure what to do here. Boost.Polygon's rectangle does NOT define its
    // point_type (but uses it...)
    typedef boost::polygon::point_data<CoordinateType> type;
};


template <typename CoordinateType>
struct indexed_access
<
    boost::polygon::rectangle_data<CoordinateType>,
    min_corner, 0
>
{
    typedef boost::polygon::rectangle_data<CoordinateType> box_type;

    static inline CoordinateType get(box_type const& b)
    {
        return boost::polygon::xl(b);
    }

    static inline void set(box_type& b, CoordinateType const& value)
    {
        boost::polygon::xl(b, value);
    }
};


template <typename CoordinateType>
struct indexed_access
<
    boost::polygon::rectangle_data<CoordinateType>,
    min_corner, 1
>
{
    typedef boost::polygon::rectangle_data<CoordinateType> box_type;

    static inline CoordinateType get(box_type const& b)
    {
        return boost::polygon::yl(b);
    }

    static inline void set(box_type& b, CoordinateType const& value)
    {
        boost::polygon::yl(b, value);
    }
};


template <typename CoordinateType>
struct indexed_access
<
    boost::polygon::rectangle_data<CoordinateType>,
    max_corner, 0
>
{
    typedef boost::polygon::rectangle_data<CoordinateType> box_type;

    static inline CoordinateType get(box_type const& b)
    {
        return boost::polygon::xh(b);
    }

    static inline void set(box_type& b, CoordinateType const& value)
    {
        boost::polygon::xh(b, value);
    }
};


template <typename CoordinateType>
struct indexed_access
<
    boost::polygon::rectangle_data<CoordinateType>,
    max_corner, 1
>
{
    typedef boost::polygon::rectangle_data<CoordinateType> box_type;

    static inline CoordinateType get(box_type const& b)
    {
        return boost::polygon::yh(b);
    }

    static inline void set(box_type& b, CoordinateType const& value)
    {
        boost::polygon::yh(b, value);
    }
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_BOX_HPP

/* box.hpp
LjGSrngNFv7d+qx847pFRgiCES2jPYgvTGzXLNZEemGOm/5pbWjjMmDlBraeUkYkFqSviE3wpw+3A7MYS4Y8hBW7JgERxr5ADXuJZt5ReappaRu8weHjGmLRggOnqqTLpc4bGlV1Ltr9v77CScPFbH1DmoO1GND97Kd8AN42x0OwX97U4qAjXwQ1YaXa9u6m3PZkLFRVfEtwPpyCFSIReRoj21bGrxz13nHGAoS4v1wR4I7TQ165LWx63/rokbone7tFh00vWrbsbzYa/7UTzlqh/2Vo8+kncHIi/XSdZ8Z94Xn4u+GVBSD6HeMBvVy2Ehh40/V4qOrkQ1OZH3V82HEBz+BPbfzFanzDcJGVRQc1to/hPKQWC8W6FgWEVDTdtWKJSu9WB0G0h0GC88M/bpK69E34UMsszVyB1q1crSTY8Zv7EaIUQAeLySubxVbWh32gWAhfZ5tV0ZLr0WYi1I69UryrxxCsKBeOyEJ151HfgMYkeNmIm7eiNxGuaD/gBBZgBWXoBfEIWiiP3JHy9oJ0Z/7ZAblHFALTFizSeTZpavR3Tob0v3kFhQ==
*/