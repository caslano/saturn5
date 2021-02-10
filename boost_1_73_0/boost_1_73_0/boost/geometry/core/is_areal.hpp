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
FA7USR7GZ2F63lQve5TyPy6C6+vlLHzVVGGugsGyBnV6EWUqS/r5VZCGCj4Pom4YZ2FPBZnqhVk3jc7gSxSr/CJU/WgQqp2jD5/2D9821dVF1L1AIDfJWGUXyXjQUxfBZajSsBtGlwxjFKS5SvpQHYD3oiwHgOM8SuJlaDtUeZgOM4SBzQeDLFHBZRANgjNoKMjVRZ6Pss2Vle44HQD2K72km610TfeXL/Kh7cknQGIY3KhklKs8UeMsbCos2VTDpBf18V8gCCSOxmeDKLtoOmygqbi3kqQqCwcDhAX1ojBjtEN1osnTxGJqBBhHOf6TJXGGTV1dJEOvINARofTHaQwNAR2gUC8BMjfVOO6FKRWmnpsmNE2JwLVD4/DtqSQGZNRC60TtnyyosyCLsqb6ff/03dHHU/V76/i4dXj6SR3tqdbhJwT26/7hLgx9BI2lKrwepWEGjacqGo4GUdjTbT7cz8rc3N+iuDsY90K1gKPXycJ8PFq+WBAZLzGDx/bilawwjIYhFnUpcRIvBVk3ivxkIE08gK74qQCwF+SBn5iFca+v2++rxfle2I/isLe48/H4oLO7f9J6c9DuvDs9/dBQjx6p6uz3++/bDZj2MCXnVE2Zk/cIAopUZ++/b31oMA4m/13rt3bnYP/N
*/