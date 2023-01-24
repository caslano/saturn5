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
w3GYZhx3tgx8j8Y6QvFhtBfXTanoQ8vbqcy8D52pgg056+XJvgP7lk6V4Fsf+ZSth9HJdJ7EDLzrxiOCLnCZvL9cSKNtAaIPT8O7Xr80mRzUS+N82O+/+rND54eY98SD3eA5uhB1VPMXrJxsozY9NBt1/cY/cZzNzt8ZrME3X3hIonHGvnoR5qSn/28LbWtkHXAkzDQ4aAa31z9/PfZRJUJ3D4di26zNj5BXtQA67nzrFuZaSgLwl+egnR5fHguHuS4bW4T+94c/RKMj1n42nrdgDtrqd41rQgk+mYJ3dC7e+e0KNo4cJTJNnP0/vxA+4twusZYZv781HE/g7H/jdbBVem5Q8R1Dw5i/GwK06wK5AA7PxRprW2hEsKmhbk4fr4FtN4a1tESAdSyxXm6aBaw96hYh3lm1Y8NIPMGe7WNVuAX2ImgX0e98XWkN9V0b6ltbOW7nQtiQq14L3Kr1La2NDeva2ltam0A7gJigb99bQGPotqa1XZ3A71mMOerbjQLf2NTZtLYTcxRoNXmgLagErbN5XUdXw/quTqKdnoE4yMpC0NZ3NnUA14xYkW/nYeDaWjobgNuHPuD7VR5wzV1trciDcGABbI8PP9Td2VXfeVd7R8u6jpaue0zzDKOd4t/82yfpm6OxMMJp2zjtEnxb39eru9o3NLesaea4I7AvfH++g+HWrutoq281hZwzrG4zfPf/ieFb1zEc
*/