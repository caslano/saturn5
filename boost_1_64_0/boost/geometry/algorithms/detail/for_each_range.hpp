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
/cDzsJErA3sUdgY6tYn2JvjzdzFp45/HeuH2w1jrer5zWvbuaKc7XOYBwzfGdFxWPV6Dv1sEf9ffjzEoy/wCjM1D5xkOY57C3m894dj88PTR0BwCzTVhNA9zHs3QG5kEj4cz92tojlXmWRM8gn7Q0E5OyO/h+dmGZho0bxNtT+7X3Gl1K8U17NunYQuPy6qybXTUwmNZeYPOLuBDbIyfsvBeLraMyzjbE+Bc7AXi8bW714fDFo18XeOHFO6epK+7eIK1rD3wedfA1u0dZ+tyzEHnmHcuFX3OuarPOa+SPtXnnI8+Z7/qI59W+/IuAN6Fon9botK8HrQr0a++AWneqPAWqrmvNwPvLYJ2k/h9ikr/NqR/K/J5O9K/A3iXTzg+JTO3lkY+u3uVX3Pk815uDXGMlvg9sYZowu6trc2Yq32nnKt9QfYNONm8Vcn2Esjm3ZXBuwp2EP9UTlsOfTbxPZU5zvtNcmxj8nufy4/Heu+35R2L96XcPoIz3b43bx3Wjj4wqfYUzCxK4h+NuX204ba7ubtjabS7p6u1eUO0ueuVvjQVWLafyybsCw6vPX5ItkHMi5eqs7EfrsS+U8SnxTsb+izmRxVu8dzcuB9TuHVFuXE/QfGCR44vxZ0pVxEMuiPzZTxnJ6d5nxZ0ukLofLYSe15FvD7z/XmJw3mpOzjYjsGHV/wV5uDvaorz28o1qIcrYEe+KvIlGN7uVHuE/fTAkW/0fcPnAXFXzcW+dNW+viXwyB/PiXetnxfwZF7XcZxLL8txvagDA6tUNv97CF9cwmsPOAPgcOcv8rz+ue7bQTg984JnkW9kORl88K7k9COfB+Bcq97a/THskoGzXQLu2QvpHCz4kPK4GWk+GJLG8HoL/so0typejX3WvP5c8Xq14vUOlh/Li8+dXQEdBl38NXbV6eDRc2WfONO7W+oY5JLxfBzc34z8aBwHvcK5MfE2HZcdNK4GHVn2+1W59L1GByDP00uC78UOqz7kNwgPC36kPNaVuD37M8WY+5Dqsx9SaX7n84Y4gqNPd7z9odLRPEnQ/JOi+bCi+YiguTxE7//sxyNtmuXu4v+CPI8WeT6h8nxS5fmUoPkkaGIPi6X5NMEC5wWPCp4fbKDwmnzrjPHEWDq1LjnKN6RreNbn/ievrbLPDR8bA305aIQ/9Ixb8xP0PAv/60LileE9Zm6B97I8q8aFzE+XewqUOdUx/I6q9M/o5ciNyXXmrcmeBNZfkL/n578+QRSz+0yem5SvkHue+d/K5/6P9LkPU+67c/ma8PlnKJ+f59ry1gv8SzG/0+2vZGHP3UqsiRRU6TUR8KjYBij33PPzqEejc1OrxF0S6o5IqkP6XHuYVuX8jKOqsv2WgUk7M53ChqZJwzSB1z/XnUWbWeU+eb5rFsKEh7M+0pdx6aUdmIN8DFz7Zi9SuEVVsi91n4wvrsrhK0+yLuyeCPBh6Jp6x34J7ieK0W/p87cLmTf4ZIq3RVVMw5ZrYK4Js6wsjTJBw8B2qL6vwtVX0RxhE6sIJm1iRMqM4NU+TcTxu3Sws7V+PHSkaUHwXN1xVdn+baxQ3S8s+rcXCzqXFSl/jOi8BPVsyiTr+aUE1/X4MuBeIcad9Sin5QX32iwh2In0gRfCd7w0MM+Gl9x4jZDnh4Q8T5J6iHyWKz1cocqq45tU/sp/ZZmtVHQOLPD5w7qkjEc5ZPwqle9LBP7CED+vGXK9UZ2JJlz2MVuqlO8GP3Mt6y/7sTadbAPrBI70XSVOG3i+ZhL+bhgfZyA9rXcgPZfZ7pfX/mJHFehjnF3rn08Fvr5fubMqSO8qRa8LOrNB6EyPaoObVBvcLGgavhfq9QqOt2mZp4U=
*/