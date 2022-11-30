// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_RING_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_RING_HPP

// Adapts Geometries from Boost.Polygon for usage in Boost.Geometry
// boost::polygon::polygon_data -> boost::geometry::ring

#include <cstddef>
#include <boost/polygon/polygon.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/tags.hpp>


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS

namespace boost { namespace geometry
{

namespace traits
{

template <typename CoordinateType>
struct tag<boost::polygon::polygon_data<CoordinateType> >
{
    typedef ring_tag type;
};

template <typename CoordinateType>
struct clear<boost::polygon::polygon_data<CoordinateType> >
{
    static inline void apply(boost::polygon::polygon_data<CoordinateType>& data)
    {
        // There is no "clear" function but we can assign
        // a newly (and therefore empty) constructed polygon
        boost::polygon::assign(data, boost::polygon::polygon_data<CoordinateType>());
    }
};

template <typename CoordinateType>
struct push_back<boost::polygon::polygon_data<CoordinateType> >
{
    typedef boost::polygon::point_data<CoordinateType> point_type;

    static inline void apply(boost::polygon::polygon_data<CoordinateType>& data,
         point_type const& point)
    {
        // Boost.Polygon's polygons are not appendable. So create a temporary vector,
        // add a record and set it to the original. Of course: this is not efficient.
        // But there seems no other way (without using a wrapper)
        std::vector<point_type> temporary_vector
            (
                boost::polygon::begin_points(data),
                boost::polygon::end_points(data)
            );
        temporary_vector.push_back(point);
        data.set(temporary_vector.begin(), temporary_vector.end());
    }
};

template <typename CoordinateType>
struct resize<boost::polygon::polygon_data<CoordinateType> >
{
    typedef boost::polygon::point_data<CoordinateType> point_type;

    static inline void apply(boost::polygon::polygon_data<CoordinateType>& data,
                             std::size_t new_size)
    {
        // Boost.Polygon's polygons are not resizable. So create a temporary vector,
        // resize it and set it to the original. Of course: this is not efficient.
        // But there seems no other way (without using a wrapper)
        std::vector<point_type> temporary_vector
            (
                boost::polygon::begin_points(data),
                boost::polygon::end_points(data)
            );
        temporary_vector.resize(new_size);
        data.set(temporary_vector.begin(), temporary_vector.end());
    }
};


} // namespace traits

}} // namespace boost::geometry


// Adapt Boost.Polygon's polygon_data to Boost.Range
// This just translates to
// polygon_data.begin() and polygon_data.end()
namespace boost
{
    template<typename CoordinateType>
    struct range_mutable_iterator<boost::polygon::polygon_data<CoordinateType> >
    {
        typedef typename boost::polygon::polygon_traits
            <
                boost::polygon::polygon_data<CoordinateType>
            >::iterator_type type;
    };

    template<typename CoordinateType>
    struct range_const_iterator<boost::polygon::polygon_data<CoordinateType> >
    {
        typedef typename boost::polygon::polygon_traits
            <
                boost::polygon::polygon_data<CoordinateType>
            >::iterator_type type;
    };

    template<typename CoordinateType>
    struct range_size<boost::polygon::polygon_data<CoordinateType> >
    {
        typedef std::size_t type;
    };

} // namespace boost


// Support Boost.Polygon's polygon_data for Boost.Range ADP
namespace boost { namespace polygon
{

template<typename CoordinateType>
inline typename polygon_traits
        <
            polygon_data<CoordinateType>
        >::iterator_type range_begin(polygon_data<CoordinateType>& polygon)
{
    return polygon.begin();
}

template<typename CoordinateType>
inline typename polygon_traits
        <
            polygon_data<CoordinateType>
        >::iterator_type range_begin(polygon_data<CoordinateType> const& polygon)
{
    return polygon.begin();
}

template<typename CoordinateType>
inline typename polygon_traits
        <
            polygon_data<CoordinateType>
        >::iterator_type range_end(polygon_data<CoordinateType>& polygon)
{
    return polygon.end();
}

template<typename CoordinateType>
inline typename polygon_traits
        <
            polygon_data<CoordinateType>
        >::iterator_type range_end(polygon_data<CoordinateType> const& polygon)
{
    return polygon.end();
}

template<typename CoordinateType>
inline std::size_t range_calculate_size(polygon_data<CoordinateType> const& polygon)
{
    return polygon.size();
}

}}

#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_RING_HPP

/* ring.hpp
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
*/