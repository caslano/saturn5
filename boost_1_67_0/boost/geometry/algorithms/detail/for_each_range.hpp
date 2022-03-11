// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_FOR_EACH_RANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_FOR_EACH_RANGE_HPP


#include <boost/mpl/assert.hpp>
#include <boost/concept/requires.hpp>
#include <boost/range.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/add_const_if_c.hpp>
#include <boost/geometry/views/box_view.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace for_each
{


template <typename Range, typename Actor>
struct fe_range_range
{
    static inline void apply(Range & range, Actor & actor)
    {
        actor.apply(range);
    }
};


template <typename Polygon, typename Actor>
struct fe_range_polygon
{
    static inline void apply(Polygon & polygon, Actor & actor)
    {
        actor.apply(exterior_ring(polygon));

        // TODO: If some flag says true, also do the inner rings.
        // for convex hull, it's not necessary
    }
};

template <typename Box, typename Actor>
struct fe_range_box
{
    static inline void apply(Box & box, Actor & actor)
    {
        actor.apply(box_view<typename boost::remove_const<Box>::type>(box));
    }
};

template <typename Multi, typename Actor, typename SinglePolicy>
struct fe_range_multi
{
    static inline void apply(Multi & multi, Actor & actor)
    {
        for ( typename boost::range_iterator<Multi>::type
                it = boost::begin(multi); it != boost::end(multi); ++it)
        {
            SinglePolicy::apply(*it, actor);
        }
    }
};

}} // namespace detail::for_each
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry,
    typename Actor,
    typename Tag = typename tag<Geometry>::type
>
struct for_each_range
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_OR_NOT_YET_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};


template <typename Linestring, typename Actor>
struct for_each_range<Linestring, Actor, linestring_tag>
    : detail::for_each::fe_range_range<Linestring, Actor>
{};


template <typename Ring, typename Actor>
struct for_each_range<Ring, Actor, ring_tag>
    : detail::for_each::fe_range_range<Ring, Actor>
{};


template <typename Polygon, typename Actor>
struct for_each_range<Polygon, Actor, polygon_tag>
    : detail::for_each::fe_range_polygon<Polygon, Actor>
{};


template <typename Box, typename Actor>
struct for_each_range<Box, Actor, box_tag>
    : detail::for_each::fe_range_box<Box, Actor>
{};


template <typename MultiPoint, typename Actor>
struct for_each_range<MultiPoint, Actor, multi_point_tag>
    : detail::for_each::fe_range_range<MultiPoint, Actor>
{};


template <typename Geometry, typename Actor>
struct for_each_range<Geometry, Actor, multi_linestring_tag>
    : detail::for_each::fe_range_multi
        <
            Geometry,
            Actor,
            detail::for_each::fe_range_range
                <
                    typename add_const_if_c
                        <
                            boost::is_const<Geometry>::value,
                            typename boost::range_value<Geometry>::type
                        >::type,
                    Actor
                >
        >
{};


template <typename Geometry, typename Actor>
struct for_each_range<Geometry, Actor, multi_polygon_tag>
    : detail::for_each::fe_range_multi
        <
            Geometry,
            Actor,
            detail::for_each::fe_range_polygon
                <
                    typename add_const_if_c
                        <
                            boost::is_const<Geometry>::value,
                            typename boost::range_value<Geometry>::type
                        >::type,
                    Actor
                >
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

namespace detail
{

template <typename Geometry, typename Actor>
inline void for_each_range(Geometry const& geometry, Actor & actor)
{
    dispatch::for_each_range
        <
            Geometry const,
            Actor
        >::apply(geometry, actor);
}


}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_FOR_EACH_RANGE_HPP

/* for_each_range.hpp
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
*/