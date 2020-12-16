// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_ITERATOR_TYPE_HPP
#define BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_ITERATOR_TYPE_HPP

#include <boost/range.hpp>

#include <boost/geometry/core/interior_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/iterators/flatten_iterator.hpp>
#include <boost/geometry/iterators/concatenate_iterator.hpp>

#include <boost/geometry/iterators/detail/point_iterator/inner_range_type.hpp>
#include <boost/geometry/iterators/detail/point_iterator/value_type.hpp>

#include <boost/geometry/iterators/dispatch/point_iterator.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace point_iterator
{


template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct iterator_type
    : not_implemented<Geometry>
{};




template <typename Linestring>
struct iterator_type<Linestring, linestring_tag>
{
    typedef typename boost::range_iterator<Linestring>::type type;
};


template <typename Ring>
struct iterator_type<Ring, ring_tag>
{
    typedef typename boost::range_iterator<Ring>::type type;
};


template <typename Polygon>
class iterator_type<Polygon, polygon_tag>
{
private:
    typedef typename inner_range_type<Polygon>::type inner_range;

public:
    typedef concatenate_iterator
        <
            typename boost::range_iterator<inner_range>::type,
            flatten_iterator
                <
                    typename boost::range_iterator
                        <
                            typename geometry::interior_type<Polygon>::type
                        >::type,
                    typename iterator_type<inner_range>::type,
                    typename value_type<Polygon>::type,
                    dispatch::points_begin<inner_range>,
                    dispatch::points_end<inner_range>
                >,
            typename value_type<Polygon>::type
        > type;
};


template <typename MultiPoint>
struct iterator_type<MultiPoint, multi_point_tag>
{
    typedef typename boost::range_iterator<MultiPoint>::type type;
};


template <typename MultiLinestring>
class iterator_type<MultiLinestring, multi_linestring_tag>
{
private:
    typedef typename inner_range_type<MultiLinestring>::type inner_range;

public:
    typedef flatten_iterator
        <
            typename boost::range_iterator<MultiLinestring>::type,
            typename iterator_type<inner_range>::type,
            typename value_type<MultiLinestring>::type,
            dispatch::points_begin<inner_range>,
            dispatch::points_end<inner_range>
        > type;
};


template <typename MultiPolygon>
class iterator_type<MultiPolygon, multi_polygon_tag>
{
private:
    typedef typename inner_range_type<MultiPolygon>::type inner_range;

public:
    typedef flatten_iterator
        <
            typename boost::range_iterator<MultiPolygon>::type,
            typename iterator_type<inner_range>::type,
            typename value_type<MultiPolygon>::type,
            dispatch::points_begin<inner_range>,
            dispatch::points_end<inner_range>
        > type;
};


}} // namespace detail::point_iterator
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_ITERATOR_TYPE_HPP

/* iterator_type.hpp
/CL8JbwZPgMfgc/DX8MX4PPwRfgifAm+Av8M/wlfhu/Dv8CDcB88LgX/wq7wdTga/hVOgG/CIvh3WAzfhg3wILwKfgSvg21TeR7YDv4AdocPwJPhY/AUuB/2gVwL9Yenwjw4GI6Ct8MCeKeOH9Tx43A2XJ1G+MIb4MXwFngJ3Apr4QPwUvgybITvwStgKN05bgUjx8PgVfApeAP8LVwP34C3wlAr0h/sAe+DOXA7nAofglfDnXA9/Dm8Ff4Sfh/+Hu6Bz8Hn4UvwNfhn+A/4F/hP+Ao8CF+FrVrTLoXHwrdgN3gAZsH34AD4PjwXfggrYNs09ouAx8C1sD1cD4+FG2F3uBNG4usJeBA+Dz+Cf4Eh3HkXpsP34edgNyria+FJ8EuwH5yAOwNhAZwMJ8LpcDIsgYVwEewPq+EA+D2YB++GI+ED8Cy4B54N98J8+BIcB/8Ov45eRlv8ATvCDFgAz+H6RbAHXAB7wTD8iOvXwBDHa+DDHN8Bd8Ct8Fr4K/gl+DRcBp+Fl8HnYBX8N6yGH8ISeOIxtBlgFjwPngXPh+PhHHgOnAtnwInwXDgJngdHwyvgGHglHAJvg0PhHfB0+Dg8A+6GfeGzsAfcB0+Eb8L2sF07x//HwceJr1z4BNS+UsypsPuDUVYFsz+Y2WdL7s6Uu959gaah3xNOhwMjdmBO5H44TMdnwjmwAM6Ak3Ss/Zg0zp80J/e9+zGN1XPnwzQ4Drr+zdR9Pc19we1bli93exl3g923rBhT28Jz5+q58/ScI2BHOAx2gyNhdzhEzz1Sz70g4pbcrZa7x8A5cvde7HWA98Ou8AE4Df4EzoU74HzVL6VwJ1ykeqjCOZaOxsrCJh+dV6TzmnT+Knf3wwXwH7AMvg2r4DvwUvgmrNex4kHjKPG70Ql2f7eKkMYlwilyvx28UO7fJ/e3w1Y6bqvjXPhjOFzHo+GDsAA+DCfC++Fk59jG+0rpjTV6we0nt1vudjPuBrOfXDFmv9w9wcfdU5ROs2Br2Au2hf2U306Fx8G+sLPOy12NyyKN+7h7dorzPGOVP/OV7ifCk+B4mA0L4ECdt/vfyd0zjLvB7n+3ALNW7o/xSfd3yP3Ncu9OlbN3K3zvgifCrXL3+0pHP1D8Ys/u67ZXOtlG5+Pvs2fG2MBWxr3D22evKXKv7tuCWd9s/dLzFL8XwlPgArVbS+EcWKZ8Xg4r4WK4HFaqfXoJvBXWwNtgNdyo47e0n13mBLu+K/pO+n5C+t9VvXUHPFnhPUThOVzhfJ7CeYHOV8Mfws/DH8Fr4L1wvfLrRvgA/KHy8yPKv3+AP4H/gI/Cf8OdsE0K7XDYAT4Bj4c/h6fAXXCwzg+Dj8MROsZ/1GcaBwL7KHxbwaHyX6P8t0zxexnsAZvgKc6xdWe33Knwceczqpc+p/T2eThK5ctFcJXHnQUTE7tzjdz5kty5Tu58We6slTu73LEGcIfc6QIfkju/Vr7YDTvCpxVfb8CzVH9OULk1RcfT4XPwXPg8PE/nS+ALitcXYZ3ON8E/wM/p+Cr4jOL57/AbOr9B5d4d8DV4H3wdPuBcV/7RN3/YWv7x5h8urXTbV61gke4zz677uMZ9sfl4ourJSbAvnAyHR+6D4+E5aicV2npX39Hh1XLPW/6sU3q5Sfnha7Af/LrC92ZYqHrwQtWPjfBbcCXcoOdeG9J3aXC88t1xJp04f+15nt7wODgOZsIpsDP8LuwKf6L64RcwCz6h+uF3sDfco/rhWdgH/gWeoffQHvAAPFHvozmO/3k+fd+FT8n/HeE6PdelKo/qYWcdd9XxaHgZbILL4Sp4ObwGfhFeB1fAb8Ar4Gb4WXgPvAY+BFfDn8j+Th0=
*/