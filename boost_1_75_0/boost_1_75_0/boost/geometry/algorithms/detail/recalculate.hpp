// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Bruno Lalande, Paris, France.
// Copyright (c) 2013 Mateusz Loskot, London, UK.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RECALCULATE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RECALCULATE_HPP


#include <cstddef>

#include <boost/concept/requires.hpp>
#include <boost/concept_check.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/size.hpp>

#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/algorithms/append.hpp>
#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace recalculate
{

template <std::size_t Dimension>
struct recalculate_point
{
    template <typename Point1, typename Point2, typename Strategy>
    static inline void apply(Point1& point1, Point2 const& point2, Strategy const& strategy)
    {
        std::size_t const dim = Dimension - 1;
        geometry::set<dim>(point1, strategy.template apply<dim>(geometry::get<dim>(point2)));
        recalculate_point<dim>::apply(point1, point2, strategy);
    }
};

template <>
struct recalculate_point<0>
{
    template <typename Point1, typename Point2, typename Strategy>
    static inline void apply(Point1&, Point2 const&, Strategy const&)
    {
    }
};


template <std::size_t Dimension>
struct recalculate_indexed
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline void apply(Geometry1& geometry1, Geometry2 const& geometry2, Strategy const& strategy)
    {
        // Do it for both indices in one dimension
        static std::size_t const dim = Dimension - 1;
        geometry::set<0, dim>(geometry1, strategy.template apply<dim>(geometry::get<0, dim>(geometry2)));
        geometry::set<1, dim>(geometry1, strategy.template apply<dim>(geometry::get<1, dim>(geometry2)));
        recalculate_indexed<dim>::apply(geometry1, geometry2, strategy);
    }
};

template <>
struct recalculate_indexed<0>
{

    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline void apply(Geometry1& , Geometry2 const& , Strategy const& )
    {
    }
};

struct range_to_range
{
    template
    <
        typename Range1,
        typename Range2,
        typename Strategy
    >
    static inline void apply(Range1& destination, Range2 const& source,
            Strategy const& strategy)
    {
        typedef typename geometry::point_type<Range2>::type point_type;
        typedef recalculate_point<geometry::dimension<point_type>::value> per_point;
        geometry::clear(destination);

        for (typename boost::range_iterator<Range2 const>::type it
                = boost::begin(source);
            it != boost::end(source);
            ++it)
        {
            point_type p;
            per_point::apply(p, *it, strategy);
            geometry::append(destination, p);
        }
    }
};

struct polygon_to_polygon
{
private:
    template
    <
        typename IteratorIn,
        typename IteratorOut,
        typename Strategy
    >
    static inline void iterate(IteratorIn begin, IteratorIn end,
                    IteratorOut it_out,
                    Strategy const& strategy)
    {
        for (IteratorIn it_in = begin; it_in != end;  ++it_in, ++it_out)
        {
            range_to_range::apply(*it_out, *it_in, strategy);
        }
    }

    template
    <
        typename InteriorRingsOut,
        typename InteriorRingsIn,
        typename Strategy
    >
    static inline void apply_interior_rings(
                    InteriorRingsOut& interior_rings_out,
                    InteriorRingsIn const& interior_rings_in,
                    Strategy const& strategy)
    {
        traits::resize<InteriorRingsOut>::apply(interior_rings_out,
            boost::size(interior_rings_in));

        iterate(
            boost::begin(interior_rings_in), boost::end(interior_rings_in),
            boost::begin(interior_rings_out),
            strategy);
    }

public:
    template
    <
        typename Polygon1,
        typename Polygon2,
        typename Strategy
    >
    static inline void apply(Polygon1& destination, Polygon2 const& source,
            Strategy const& strategy)
    {
        range_to_range::apply(geometry::exterior_ring(destination),
            geometry::exterior_ring(source), strategy);

        apply_interior_rings(geometry::interior_rings(destination),
            geometry::interior_rings(source), strategy);
    }
};

}} // namespace detail::recalculate
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry1,
    typename Geometry2,
    typename Tag1 = typename geometry::tag<Geometry1>::type,
    typename Tag2 = typename geometry::tag<Geometry2>::type
>
struct recalculate : not_implemented<Tag1, Tag2>
{};

template <typename Point1, typename Point2>
struct recalculate<Point1, Point2, point_tag, point_tag>
    : detail::recalculate::recalculate_point<geometry::dimension<Point1>::value>
{};

template <typename Box1, typename Box2>
struct recalculate<Box1, Box2, box_tag, box_tag>
    : detail::recalculate::recalculate_indexed<geometry::dimension<Box1>::value>
{};

template <typename Segment1, typename Segment2>
struct recalculate<Segment1, Segment2, segment_tag, segment_tag>
    : detail::recalculate::recalculate_indexed<geometry::dimension<Segment1>::value>
{};

template <typename Polygon1, typename Polygon2>
struct recalculate<Polygon1, Polygon2, polygon_tag, polygon_tag>
    : detail::recalculate::polygon_to_polygon
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH



template <typename Geometry1, typename Geometry2, typename Strategy>
inline void recalculate(Geometry1& geometry1, Geometry2 const& geometry2, Strategy const& strategy)
{
    concepts::check<Geometry1>();
    concepts::check<Geometry2 const>();

    // static assert dimensions (/types) are the same

    dispatch::recalculate<Geometry1, Geometry2>::apply(geometry1, geometry2, strategy);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RECALCULATE_HPP

/* recalculate.hpp
L5/RS8ZQuPjp5fahwgmkSXpXr3LfZyCnLPRzKK76Jv2Gcbg73V2wn+2svnAUnNfhB/zuLfWqVf3Cll51OmR+2o/LUO7u59z7V6droc561RS+zzv7hS3f5/2Q+X0/LpM9apXHfJ+PZvip73OEHBCpHdIG4ds8MaUsDfltsrRekLnNz2VpWX6nLG14ugAfLODTPN1lyenTKE58fS+UXePAiW/PHqSgfvV9UL8aA/WLZ6J+vG2YDcEcKJL5dN4LxON+umcxtYRNLmqqK/gYtEafkJeGN+OYtBiOfwlY8yOqW4nKVPg0W9cpOJuWq7AxxGPM3oH8NQXIHx+C/GkxR4zZ6/DqH1KeKa1/GN0OaVT/sIUZx218avk02cFzb/LcQMwXtxNMOv2d/tboL4OhdlfvnAkYD3ZJ6+QCMkdZp8bIBKxdJ+kYleMwrGAqVM9DIhrV+aaphMZxqqNSEO6v8QDyxP8LedLuc/hrNMNLHqV2vnuB+DOkL/on9Tx17PQpZA0nXPM5r2n3CmI081SrHsE0PX+16tz+JNR5rx79GteRcUQqkMPSTmUfnK9qlDn6CmOakifNJgm8iuiSB3hrquxBpj/XJOCNfoSMtKqkP1cTFjLm+ijqEx8k7PuE/C8Q5jZ99wCxCFITJElWTv5nD9TO/OeXBpxNOUiSF2JyGeOlqJR0G8P6WXgqGcP6Rcj8KcDH7qtWcSyG9cV03Ety
*/