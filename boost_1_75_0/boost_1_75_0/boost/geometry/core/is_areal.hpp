// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_CORE_IS_AREAL_HPP
#define BOOST_GEOMETRY_CORE_IS_AREAL_HPP


#include <boost/type_traits/integral_constant.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename GeometryTag> struct is_areal : boost::false_type {};

template <> struct is_areal<ring_tag> : boost::true_type {};
template <> struct is_areal<box_tag> : boost::true_type {};
template <> struct is_areal<polygon_tag> : boost::true_type {};
template <> struct is_areal<multi_polygon_tag> : boost::true_type {};

} // namespace core_dispatch
#endif



/*!
    \brief Meta-function defining "true" for areal types (box, (multi)polygon, ring),
    \note Used for tag dispatching and meta-function finetuning
    \note Also a "ring" has areal properties within Boost.Geometry
    \ingroup core
*/
template <typename Geometry>
struct is_areal : core_dispatch::is_areal<typename tag<Geometry>::type>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_IS_AREAL_HPP

/* is_areal.hpp
xwp5lZfSS4xfmjYAiI6db7QUf1aYUVb6TOcuL/9c5QGwg4NWa6JnuxbD3UGIe8+JiK9CQqW5RuFOGnmJNKBcZ7uiZon48lWQxW9U/xeiZlWN7Uaf/6UKKpcPx8i3svvmauzgprlTCfAyxpY7xC0CjV+/3v8uKFBYmhLAqHBCvrFzP9vUrLQgR12WamW3yuPuVI+6EXeCVup73wX6aonJDtH4Qjs/8d3SRYya/cIHa3rdxfdpj9Li2eaFmFuTSumSVbWNiH0If+kIW4q0Zkj0qkFBWoLCP3Kzfd0VqA6ll5cfH7ILXEuS17py/qO0a3MJjlnT3y9ioNdtY81docDfGAzIYmJSeBIzGGrVGk4UDj9mTGHs4278QFTbRpIHIBt6rJipLmmPm0CbkiP9I3c12DFYu3cuSoA5crHTKtW3XLwPgIsM1junpM3Mp+JB0cBvhbjvpU0BnZ/Tyz390GNN7IjgwcWEf6ah0H3UntRiW/bivs7+GVhiq01OBNJJcX3dWP52VokuDxc7H6Q1zoArKzLTtT2Y7KH13ZdqEvgZLDUvFpR/BGK7ZG9i80P+gtpwtZQHbr7z5XLp7t3/FeSxudhsT+z2SylskFHXMWis4epRQ9NUmfXPV36kv48eBrd4ELcltrJt9/jCjwTa6EnKyltfn1cF7D3yrQqKo64I+voTmqx2mhq0LNnUG6hUkg5fhNSHHPCK7/fr7+gL
*/