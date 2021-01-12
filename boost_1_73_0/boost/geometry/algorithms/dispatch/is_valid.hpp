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
7Vf/wHLa7x3IZXJ9YxlfdShVSotBVkwG5l7qiqB4iPoD5ur+8uKmkIIuLfae2b9zQi6i/f6gcTHtadcFxUFUF3iWMn11sxUkELTM66fyew0p4v+tbS00FpPQKZcUt/s+LioljJLkx6zpwYn1i+uDKLvsG3vB3/mX34ayMC4hZpyRdh2+jRNVUvsjxeBj3m2/JSjmpvrABCLf3Hko+RMuLlYI+BdnX5YT/28tq5TGoe71YzF/
*/