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
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
*/