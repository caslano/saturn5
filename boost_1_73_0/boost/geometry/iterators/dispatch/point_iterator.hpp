// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DISPATCH_POINT_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_DISPATCH_POINT_ITERATOR_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// dispatch for points_begin
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct points_begin
    : not_implemented<Geometry>
{};



// dispatch for points_end
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct points_end
    : not_implemented<Geometry>
{};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ITERATORS_DISPATCH_POINT_ITERATOR_HPP

/* point_iterator.hpp
Kr8Dvl3wNfCK75rG6nTjBa/dxD2/msELBC+C0/xqhP7WiflBn7jq9xe4k5zaR/l5D24SfGgrd2uTG2MOSObXGHgtyfpkg0dLfBY8gV1f9BL4TloK3R7i8k3wzVo9md9b3wvzG6rlB75J8Blwf1drtsHXC34IXjF/P4WvE/zOBu7+n9UE19C+Y/3z+ijt+9Dy/onDWuJ5fHIX++dXlw+sYXzfGsYPrEZ8Gy//T1xXQw+soceQ
*/