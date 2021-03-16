// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DISPATCH_SEGMENT_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_DISPATCH_SEGMENT_ITERATOR_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// dispatch for segments_begin
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct segments_begin
    : not_implemented<Geometry>
{};



// dispatch for segments_end
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct segments_end
    : not_implemented<Geometry>
{};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ITERATORS_DISPATCH_SEGMENT_ITERATOR_HPP

/* segment_iterator.hpp
MGcTfDX4TZKQfty5LNUbCeDawtR2xujxy2LOAfpAxlJ9sgqXVeF7frJnPgSW4QBreQvoJOBUQyF9VwLkFugajrMHMhb6NmsAV/v1yV4cZg9kLJIftAhklOL8U+3blGnHKsgmon7texz3Cbw6WU74PY6NViRA5+rTU3L1ud6QRt+YmJ0xL1Sf7dWzXYH1JRm0mtv8aMY4WoYYqgtlZNJQdKhudsZg5zc0XqKo95ujyjjaGBXCsbUwBoJrtmPq9q0=
*/