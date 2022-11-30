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
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
*/