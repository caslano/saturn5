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
fDhz9TMxjKb/kwHkgf7cMZjvz/Gy9a6CulHLPINmqexTQ/uCwe286hf3JIJL8lbYtlt4a970NLEYuFDWsDc6ZTuH2qxzQBIgPuW/gKEDIpLKOtUdwLRlX79+5dg04YDJs0YeitunEb4RWMkQfpiSJ1r+gF8ZQOn/cHSOCNDf0L00sP6VQMiiENbadaKhYU2NjDXj+nmYv3AcTadTxUNrDea2izZ1f3oq7PhIRJ2cbxAzQr/raxXpXqYolY0iYZ7wBTBHHokDGX3OpiLhs7Mo156X8rNTrCuUSyMEOjjFjrKYYL+dx6xkQey+n2UhZcOi78c4l6vCDLDjErl8QMVcZgpmUCyHRZnoBqGPftSUMx/hGGwbeJm+IzKKsncBGNFd7N+3R4nPohMvs8P2s5IrTXPir5AW7ww8p2DOSjAjDSwZJWPThovN+XxBIv+S7UQfdS10Gk975Q1A7GNzJS2CzjZKR6AqTHBAZe2YHEjvxXPmZxKneCn4lWNQvBl8MZj1ATed76GJxXu4Dc6b4ESWHxaIDaI+s3dBMK29EM004eOtT7uzI4X62rnvVg==
*/