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
n09A6+r8VG9flK0m6JSjQa3FEiDbg2TQ8oxOEXzPemYcM3vd7kOUeXzdPzJ3p4m2HpQmVtbXpgKdMqghARjKT6GCO1e/QVKnceNoiG6i+EFA+IOkZHDzzNDUpoK67Q5ftztDlOmqd94fti9Prs+6/auEr1dQaq/5H1BLAwQKAAAACAAtZ0pSwGrIVqUCAAC+BQAAGwAJAGN1cmwtbWFzdGVyL2xpYi9wYXJzZWRhdGUuaFVUBQABtkgkYK1U30/bMBB+719xgpe2yhrgZWND06K2G9VGQW0Qq2Cy3PhCvDl2ZDv9IfHH75yGwSRQX3DV2LHvu+/uu3MOZa4F5nA+TkbjGRtez36wq2Q2H4+SdMzOO4d0KDW+eh733250oA97B2v+jAbNDeLKmt+Y+ZetGXuA3Y9QdzTvI4nhCfLAerAf8gDdBsJalrOwZmwf0V2ILTzigLxjYUk7BAvIoam2Vt4XHrrDHhyfnn6Ad3BydHIUwYhriQrmHvUS7X0EZ6LZ+VLwzWbg8HME6IGrQesqLaQDZ3K/5haB1kpmqB0K4A4EuszKJb1IDb5AyKVCGF5eLSbTbxGsC5kVwcnW1OAKUysBBV8hWMxQrnY+Km49mJzg5FxI58lh7aXRA+JG8GhLF3wEeq6cAb7iUvEl
*/