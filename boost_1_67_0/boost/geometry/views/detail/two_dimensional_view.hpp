// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_VIEWS_DETAIL_TWO_DIMENSIONAL_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_DETAIL_TWO_DIMENSIONAL_VIEW_HPP

#include <cstddef>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/int.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template
<
    typename Geometry,
    std::size_t Dimension1 = 0,
    std::size_t Dimension2 = 1,
    typename Tag = typename tag<Geometry>::type
>
struct two_dimensional_view
    : not_implemented<Tag>
{};


// View that enables to choose two dimensions of a point and see it as
// a two-dimensional point
template <typename Point, std::size_t Dimension1, std::size_t Dimension2>
struct two_dimensional_view<Point, Dimension1, Dimension2, point_tag>
{
    BOOST_MPL_ASSERT_MSG(
        (Dimension1 < static_cast<std::size_t>(dimension<Point>::value)),
        COORDINATE_DIMENSION1_IS_LARGER_THAN_POINT_DIMENSION,
        (boost::mpl::int_<Dimension1>));

    BOOST_MPL_ASSERT_MSG(
        (Dimension2 < static_cast<std::size_t>(dimension<Point>::value)),
        COORDINATE_DIMENSION2_IS_LARGER_THAN_POINT_DIMENSION,
        (boost::mpl::int_<Dimension2>));

    two_dimensional_view(Point& point)
        : m_point(point)
    {}

    Point& m_point;
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{


template <typename Point, std::size_t Dimension1, std::size_t Dimension2>
struct tag
    <
        geometry::detail::two_dimensional_view
            <
                Point, Dimension1, Dimension2, point_tag
            >
    >
{
    typedef point_tag type;
};

template <typename Point, std::size_t Dimension1, std::size_t Dimension2>
struct coordinate_system
    <
        geometry::detail::two_dimensional_view
            <
                Point, Dimension1, Dimension2, point_tag
            >
    > : coordinate_system<typename geometry::point_type<Point>::type>
{};

template <typename Point, std::size_t Dimension1, std::size_t Dimension2>
struct coordinate_type
    <
        geometry::detail::two_dimensional_view
            <
                Point, Dimension1, Dimension2, point_tag
            >
    > : coordinate_type<typename geometry::point_type<Point>::type>
{};

template <typename Point, std::size_t Dimension1, std::size_t Dimension2>
struct dimension
    <
        geometry::detail::two_dimensional_view
            <
                Point, Dimension1, Dimension2, point_tag
            >
    > : boost::mpl::int_<2>
{};

template <typename Point, std::size_t Dimension1, std::size_t Dimension2>
struct point_type
    <
        geometry::detail::two_dimensional_view
            <
                Point, Dimension1, Dimension2, point_tag
            >
    >
{
    typedef typename geometry::point_type<Point>::type type;
};


template <typename Point, std::size_t Dimension1, std::size_t Dimension2>
struct access
    <
        geometry::detail::two_dimensional_view
            <
                Point, Dimension1, Dimension2, point_tag
            >,
        0
    >
{
    typedef typename geometry::coordinate_type<Point>::type coordinate_type;
    typedef geometry::detail::two_dimensional_view
        <
            Point, Dimension1, Dimension2, point_tag
        > view_type;

    static inline coordinate_type get(view_type const& view)
    {
        return geometry::get<Dimension1>(view.m_point);
    }

    static inline void set(view_type& view, coordinate_type const& value)
    {
        geometry::set<Dimension1>(view.m_point, value);
    }
};

template <typename Point, std::size_t Dimension1, std::size_t Dimension2>
struct access
    <
        geometry::detail::two_dimensional_view
            <
                Point, Dimension1, Dimension2, point_tag
            >,
        1
    >
{
    typedef typename geometry::coordinate_type<Point>::type coordinate_type;
    typedef geometry::detail::two_dimensional_view
        <
            Point, Dimension1, Dimension2, point_tag
        > view_type;

    static inline coordinate_type get(view_type const& view)
    {
        return geometry::get<Dimension2>(view.m_point);
    }

    static inline void set(view_type& view, coordinate_type const& value)
    {
        geometry::set<Dimension2>(view.m_point, value);
    }
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_DETAIL_TWO_DIMENSIONAL_VIEW_HPP

/* two_dimensional_view.hpp
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
*/