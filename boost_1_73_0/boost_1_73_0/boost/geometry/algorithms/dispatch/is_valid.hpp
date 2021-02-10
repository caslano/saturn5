// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DISPATCH_IS_VALID_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DISPATCH_IS_VALID_HPP

#include <boost/geometry/core/tag.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type,
    // for multi-geometries: determines if empty multi-geometries are allowed
    bool AllowEmptyMultiGeometries = true
>
struct is_valid
    : not_implemented<Geometry>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DISPATCH_IS_VALID_HPP

/* is_valid.hpp
HbjalFkDozhNZDkFUyUMAFrIV9kABzGW5rB8CforEhDQ6Xb5F7DwPp39KFuUizeXIaP/rGUEVmaZDZh1dnpR1v8I/QAZ+kopZbZoPKOZgC9pVuBkOonkamWCWdaH4ci6nli/5i3Ph+Gv1vDy8vrj2SmvLL+vOLYBB3slTTXUKu5z/MZXL+dX4JBjYKd1oS2DMe17jl3ScHxzcX11hgReoOKzSKijzltBhZeX99BgDxcLqChQImMImvCeJE9JyubJGxji5vMoHOEKHsHYlIgBS1bbBMtwyHhjTrBMJeVrfFbKCzbU5ik4NObTSQAhHLdx8HqAWQa//esJ0Q9UpJMDHJCxh1Pbz0DIXvqBi5J5EZIgUYATikMhdpFEG0aQGCrmDhI4ZU5AYwSuCgtsZFIE/hcmZr2EgZo4+dggLLFhZILKiwEK42Hgc8nTGfDjDkGSo+sPH8Cep+Pzs8nUen99my1kqGEuVXLAazIhecUvG/JQHJzyAOeLURZjeSKORpb8+ZetVFu2RVKS8d+0DZbi3a12wj+4CZJsBFYG9kx383F81dHluFhZ+R/g11/dD6+MPSj/BRfl5vb6FzLjQXgTR1+P8gtQ4i/I7IImM9Dn6IfNTzCTcmZD5z9LP2Yj0Xi0dgFg/6SQo02u7i4v
*/