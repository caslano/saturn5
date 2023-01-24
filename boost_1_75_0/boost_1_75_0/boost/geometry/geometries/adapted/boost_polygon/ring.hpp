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
l0eiME6Z5ToQ4Pgx1gZTCi4u79uELs5HEVdGsHN3rEDZK4ao7DCPOf70HdBF+5q6gNnQtHZ9m+A/g3nPN22fwHc0NazraAS+dSnw739K4NvWNa5vbQK+biX0xZfXCXzL2q6mjtX1DU1cVnMd4oCNAUFrbOlsr+9qaBbv6S1DHO62vwlaw7qG1vpOxOFAK67F/tePPypo9a0t9Z0cz2MdvjseEvj1a7GmBPyVOsTLHnqSylbfQ+22+zbksv/qNxKsOe9nlhpwl9jYzSh4W3HfaqaH4oLvJPuGSQXvjvexDhSnZ5FrP7tgvLOP2dwROmAD/F68q2Dzk6KuuzcniB85CnMKPvepvk31Eebk8pUT3jarIKc0uBUyROiC4ytvQh+s+e7WtsB9Q/DI1w4P8L5WD/zFKVuZckxYZzgbUBfuoLSlWltRm6rae48qtatW7ao9U3vEqFlbS1EjVK2asSMEpfbeKyRm7USsIBKf7/v1/Xnve+/z3ueOc557zzmpAcOScTnjyYpfQ2pqy+o75ZL8oPebMtCvGCUaGsWaPJxM+/YjbCS4DsdlBbH38sf8ObaqYgRe9l+7cGaTxqyFlOQ3OvMhtsICJdPMkRP6YRREd61DSNq9xwRGF6hXMaorfIxvTQA4O2vbH/nkyA7DJV6r7bCDQO7C+lBfqsx6l+Wg2SkieS9Gu7bKH0MF9X5/UmZ/ySkKs1flNJs8uoiD
*/