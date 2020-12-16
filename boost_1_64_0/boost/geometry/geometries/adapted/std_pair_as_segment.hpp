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
v9n+bP5dgdyL7ERa+sk1f6zmox1+h7B87CZ5pfbE5gLyaxWpeoZ7Rry/I38F8vJdsT8H215mX5jXkxC9797drLwLtN31SwnL2Xei222Z64TtdVm+NHyvy8FLw/vThKXuvlP6wVp3u/8BurOdX2v04c0u2xyNb2oH9z3tkB6qthlprRxr9Y0XRy5bd7P3bPfqv9bzG9DZQXtTv7tQ57oi3ZDuSDryYAficxT3s4aLg2Vy5cXh/euyi939axW6M58XoDv713x0Z77noDv712kXH7kcnN+unPm+bnAgAW9ZYwnlGMvmkgj5ziAtvzC3ujJ/UVVJdUn5opB8T5V8V/+Edi3jifn+QY69Z8osiLt20Ha3gvd2F/pH+uxx6aLkgDToWbyjm5HvW5aF7MGLbpfD6cvC967tsSx879r4oBnZqO3qkvB29WLQTPxKOVziLqfRRh8eNnZOcZ35XQbc5bJNB+JXRtHXKc+2+rpLI5XLksqS6iJHwbjLZab2efPEf3nUYP4dh8xBbkceRfYgf0e60P+NRM5BypHrkDuRV5H3kS+QllHsbIpoO9N4pfq6UX7WULmEVPyEa/dKJQNSbTa/n2u8zF2WtaLr3sT8rfsam/I4I2hmyndY0MyUb1zQzJTvgeXhex3/Imhm/G4Nmpl+8/bl4XsYpy4P70tfvNTdpu9Hd9aVm9Cdbfoa9Eht2vkuum5o+DubgvaY10k9CXzXacac4ID7+IhzgtW+2e9CmjPv137/kZ6pFSAAxjL6PBNIQ1XRosLcArbwLplXUkCNtx8Tvfp79XOCmav4hujRzRgbu8elzvjtytR4qYdxGr/9wfhpI5TNoIpqAxspe8VP/YwPfCOU0PJL5+cuNO+coi6XNQlfK772u7OKYQGHqUhrlY6daaOXB+K7MHf69Mm5E87Mzjr93FzHvJR3OkhcF6JqfG0/qWa+e3y75s93JzziJuG54pc0PDx+acSvwiN+cnK7xq8+KTx+FSHxiz2K+fiEp/Fz18c6j/gd1xn3XvFbVLREpprgxo5Di2bEwZkf6SPCr/ee9f7P83o1ZYcrr8aQ/GjZjLgcqbwOeMTvbdzu8opfRU1VceTyUj+pYn+9x/qLXSHxTziK+DvK04x7rjfrK9xp2jkyPE1N1jc8rzSx/WhNUcQ8Vz+pjjFOSWEtNN/zQtLU+ijSxPVC06RjBrmG615QOCo8TT2ot0krXGmaNiVbapHEt3vnsPTg/uvXIcLzrEOjR4fHrQ9uM8LjprkdMX74OWx+Y//187t75+bn926PNE3pRJ9p0pQzIuPE3Knjp5xuZbjE9+xOHn3sN8hvwvPM700nhsdtGm4rPOKmGR4xfhVHyO+Kb5DfZ3dqfn4njQlP02+s71OuNJke+aj7Y7POzOM6FxHPRvd1TBsq98izxm9QpuXOMnWO9U4Kj9fHVj/sjldFeYXcNSVu0736YI1bCvZ721n2lvN5NYsKHP1wSPwPHkX8uabGP/ium+tgZl/Hnd+Tx4an6xOrLw5JF3eWiGna76ij08LvK9h//fvK9LD7Crq5r7jLaK9HWqooz6QrXGmpKi6ZZ1XzSOnBvTu+d6V8vfg647b15PC4LSZuGe64aXcQuW7j/vD97xVfvz8ob0Z/oOM02YdGvhvGBNI0Cb5gPSNrenhElqmaudXl9qEmpSXezw3qp485Y6JG9EExF3DFx5FU89ykIVXVlBC01i/b/2DxPxN9uejdY6bwRHavrq0ZofeyiuCcOPU3QPydh36J6L3ZYiXW9yAS3JOd5CzO5EGOvfLVf4nx30/8l6LXit4/ZhbPPI8iUkbyXUy2UHeeq6Z+9ewzx5jN5yjvWbgds9JylxPdSsc=
*/