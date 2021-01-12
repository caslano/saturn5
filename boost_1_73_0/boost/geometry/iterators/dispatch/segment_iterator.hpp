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
M/8V7SNnXgxPkFx/BXyUV+XxNdSure/hZR7eTKfrwOKL61sdeCvm4vqWDp99i+v7uB4xGP4sufv84O0qPwT+FLn7/ODl+u538JnMxfODE95E8P0x7vl1Eb5BbB9b3y7BPxR8CVvfrsD/KvgJtr753Ya1VfCmn7pXoyD4I4JPgVfUrwReIOn/DXCHpP/T4vGU8RblG7i+HwQ/gM+RzLch/yEV+YPvE/y9P+l0wa72DYbvETxg
*/