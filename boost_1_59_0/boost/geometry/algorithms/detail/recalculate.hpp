// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Bruno Lalande, Paris, France.
// Copyright (c) 2013 Mateusz Loskot, London, UK.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RECALCULATE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RECALCULATE_HPP


#include <cstddef>

#include <boost/concept/requires.hpp>
#include <boost/concept_check.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
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
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
*/