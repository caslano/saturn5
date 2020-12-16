// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_INNER_RANGE_TYPE_HPP
#define BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_INNER_RANGE_TYPE_HPP

#include <boost/range.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>

#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace point_iterator
{


template
<
    typename Geometry, 
    typename Tag = typename tag<Geometry>::type
>
struct inner_range_type
{
    typedef typename boost::mpl::if_c
        <
            !boost::is_const<Geometry>::type::value,
            typename boost::range_value<Geometry>::type,
            typename boost::range_value<Geometry>::type const
        >::type type;
};


template <typename Polygon>
struct inner_range_type<Polygon, polygon_tag>
{
    typedef typename boost::mpl::if_c
        <
            !boost::is_const<Polygon>::type::value,
            typename geometry::ring_type<Polygon>::type,
            typename geometry::ring_type<Polygon>::type const
        >::type type;
};


}} // namespace detail::point_iterator
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_DETAIL_POINT_ITERATOR_INNER_RANGE_TYPE_HPP

/* inner_range_type.hpp
riN0ovNjy6rLYcQuTsbZXR3qZux2cuqc0rrFdrxfQnfTnH1yrN2ZCe3Gjmvup3HNKZMwrBiXy/9jMNMwizD1mC9j3Pz7W/z5O8zvjyJ8Y/e1MmGgdhs054xf7dxc/MQ546fYNKe44bKt564nIPdO8s5PDy8qbaxqcGsUrBxyD1NTvkijQBXCVLWhxytd74/RWNrIMHkr4ZOmZX+qXR//WYVb9hGWJW66zMp1LF6tdLlSz1U8OfpcZuu9BOXdwsne59N9hLj5jo7obswT3JPWz3xG9yvL7braz3H8POYFma8eRZrwhvkteY7F47Ue3vuYb3eOZEaP3xaHvXHqF+ayP9iWI4PN8Z9NvfYt087BAb72LmqIliUDjJ0/OW0/68YAnoM+XcK8D8/2YiRcpjCkJiMtk563ToRQj85qY0415VN9gztWOlvnN5rzNUsv87SrKozbpxt7WZ6+k/xQy9/TR0K+pzdff8DuJYXfOPb67cyO04wW/dH6ln2Rjrd2jk3vzwxxxJ5SunpcbbQFhZ6wryitKfdP77Y9c5mxf3+okf/vImfKz3Knq2k3bCAsL0TvT6Yv6Tj6H9tldDk2ZPMIZYuJq2kwFBNX400YrDBu/cgJN7m3Bvf+oH6rtG6YjpH0m+HJd7HtkF9kOudeOso0676X1A51LHZXOZGpcKvNaRZuTONZEnZWcUiQbnVPd/vMLx/FvsDecnKKOlNH69mGu892jufZKutNfNax30RtJc1L/2fTPV1bjJdrjJ0+0Xg8irLO3dcYDW9ajmn7bRoWX/5/n/S8w+svp+laWeM0Xw+5XzTu2/lN+cPj+0+24f5ur/tyOkFcYtfbjtT7xlGEh7fsHzPCsfiB8ui7is/MqZ7nYitTTvu/axh7rxGL1PT2/Un3a2+lj5xvJbkhz1iHsLn+rVApfQOn4x+z5jX2XsN8DfO6jLceeP4o8lWkfHp4qtZ77RwbJw3agG+R1qS5QGvSFBd5/E5Lv265iRW/OJHdk6y/qs3xlJTRKfg+8g5P+D6BeYX7Mk4taRZ3Kj9k723X3skrn2zJXs+Rstdz5ft+9npzro095303FY8iHL3f8Dac6Vicpfb5ZEzPyA9v+cRu554yqiJcWh6u80/Xui/L1q1Z5jjX07atMLMutLaM7Pd1+pCa9aF0hl1yom3+CrnPsQ37N9H/21G8o8eu72Keya7v0tv2m8SmsaGjmu8bq/w13RtWFY0N5Usvq0kQPtiN2QN2/1GW4W69/LKe6XrF35Vq7+XEPFNDaV2DU4wnKI9k/yQbb9PM8VK16522zaqPkd7cMFw72rG4Ss/b6LabY593aa0e17fN3OxZO8wwY9j0rHrOQ7+XJ35W5Y2H1Gl6g8bafQ5zW2S8hdFbGWlpljXW1fHaah6WZ7XtR9tufMTYrdWzu/f2OqI2YTH3/cnc19+2CVtoD05N1B5U+8+k8+yIRXOMvudbLdqckzbl7WMzYtuHv9Px1tixiSyE4r9X+4LiI9urHfst7dXO9eD3anfWZkr+/jEJ1h5KsBZSojWPjnz/mKDWlvJfI+nI14o64jWDTPgszz9mRMEzj/a6dVDr1z+4t7pXojWJEq1pdeT76Py39mfyX1vqyPdbSrDWWMK1n941a+3zn8r79fxeh9nM7w2pdj8eftv9ePht9+Pht/bj0e+b+X2ffm/m9736vZ3fd5rf2qdHv9+MlCv6nYXuXfqdF+mH1e+xKYSnfkfK4x/o93TO/1C/v5eChn7fz+8t+v0av5+Qv5Zx75/0ewTmD/o9CfOKfp9NOjX7a0CzboDWMuAafXCEuwbIfp8Crj/cBkfBh2A+fBhOhI/CmfCnsBL+DNbAn8NlcBc=
*/