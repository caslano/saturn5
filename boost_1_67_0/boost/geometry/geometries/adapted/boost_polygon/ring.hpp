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