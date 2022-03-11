// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_SIMPLIFY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_SIMPLIFY_HPP

#include <cstddef>
#include <set>

#include <boost/core/ignore_unused.hpp>
#include <boost/range.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/strategies/agnostic/simplify_douglas_peucker.hpp>
#include <boost/geometry/strategies/concepts/simplify_concept.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/distance.hpp>

#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/algorithms/is_empty.hpp>
#include <boost/geometry/algorithms/perimeter.hpp>

#include <boost/geometry/algorithms/detail/distance/default_strategies.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace simplify
{

template <typename Range, typename EqualsStrategy>
inline bool is_degenerate(Range const& range, EqualsStrategy const& strategy)
{
    return boost::size(range) == 2
        && detail::equals::equals_point_point(geometry::range::front(range),
                                              geometry::range::back(range),
                                              strategy);
}

struct simplify_range_insert
{
    template<typename Range, typename Strategy, typename OutputIterator, typename Distance>
    static inline void apply(Range const& range, OutputIterator out,
                             Distance const& max_distance, Strategy const& strategy)
    {
        typedef typename Strategy::distance_strategy_type::equals_point_point_strategy_type
            equals_strategy_type;

        boost::ignore_unused(strategy);

        if (is_degenerate(range, equals_strategy_type()))
        {
            std::copy(boost::begin(range), boost::begin(range) + 1, out);
        }
        else if (boost::size(range) <= 2 || max_distance < 0)
        {
            std::copy(boost::begin(range), boost::end(range), out);
        }
        else
        {
            strategy.apply(range, out, max_distance);
        }
    }
};


struct simplify_copy
{
    template <typename RangeIn, typename RangeOut, typename Strategy, typename Distance>
    static inline void apply(RangeIn const& range, RangeOut& out,
                             Distance const& , Strategy const& )
    {
        std::copy
            (
                boost::begin(range), boost::end(range),
                    geometry::range::back_inserter(out)
            );
    }
};


template <std::size_t MinimumToUseStrategy>
struct simplify_range
{
    template <typename RangeIn, typename RangeOut, typename Strategy, typename Distance>
    static inline void apply(RangeIn const& range, RangeOut& out,
                    Distance const& max_distance, Strategy const& strategy)
    {
        typedef typename Strategy::distance_strategy_type::equals_point_point_strategy_type
            equals_strategy_type;

        // For a RING:
        // Note that, especially if max_distance is too large,
        // the output ring might be self intersecting while the input ring is
        // not, although chances are low in normal polygons

        if (boost::size(range) <= MinimumToUseStrategy || max_distance < 0)
        {
            simplify_copy::apply(range, out, max_distance, strategy);
        }
        else
        {
            simplify_range_insert::apply
                (
                    range, geometry::range::back_inserter(out), max_distance, strategy
                );
        }

        // Verify the two remaining points are equal. If so, remove one of them.
        // This can cause the output being under the minimum size
        if (is_degenerate(out, equals_strategy_type()))
        {
            range::resize(out, 1);
        }
    }
};

struct simplify_ring
{
private :
    template <typename Area>
    static inline int area_sign(Area const& area)
    {
        return area > 0 ? 1 : area < 0 ? -1 : 0;
    }

    template <typename Strategy, typename Ring>
    static std::size_t get_opposite(std::size_t index, Ring const& ring)
    {
        typename Strategy::distance_strategy_type distance_strategy;

        // Verify if it is NOT the case that all points are less than the
        // simplifying distance. If so, output is empty.
        typename Strategy::distance_type max_distance(-1);

        typename geometry::point_type<Ring>::type point = range::at(ring, index);
        std::size_t i = 0;
        for (typename boost::range_iterator<Ring const>::type
                it = boost::begin(ring); it != boost::end(ring); ++it, ++i)
        {
            // This actually is point-segment distance but will result
            // in point-point distance
            typename Strategy::distance_type dist = distance_strategy.apply(*it, point, point);
            if (dist > max_distance)
            {
                max_distance = dist;
                index = i;
            }
        }
        return index;
    }

public :
    template <typename Ring, typename Strategy, typename Distance>
    static inline void apply(Ring const& ring, Ring& out,
                    Distance const& max_distance, Strategy const& strategy)
    {
        std::size_t const size = boost::size(ring);
        if (size == 0)
        {
            return;
        }

        int const input_sign = area_sign(geometry::area(ring));

        std::set<std::size_t> visited_indexes;

        // Rotate it into a copied vector
        // (vector, because source type might not support rotation)
        // (duplicate end point will be simplified away)
        typedef typename geometry::point_type<Ring>::type point_type;

        std::vector<point_type> rotated(size);

        // Closing point (but it will not start here)
        std::size_t index = 0;

        // Iterate (usually one iteration is enough)
        for (std::size_t iteration = 0; iteration < 4u; iteration++)
        {
            // Always take the opposite. Opposite guarantees that no point
            // "halfway" is chosen, creating an artefact (very narrow triangle)
            // Iteration 0: opposite to closing point (1/2, = on convex hull)
            //              (this will start simplification with that point
            //               and its opposite ~0)
            // Iteration 1: move a quarter on that ring, then opposite to 1/4
            //              (with its opposite 3/4)
            // Iteration 2: move an eight on that ring, then opposite (1/8)
            // Iteration 3: again move a quarter, then opposite (7/8)
            // So finally 8 "sides" of the ring have been examined (if it were
            // a semi-circle). Most probably, there are only 0 or 1 iterations.
            switch (iteration)
            {
                case 1 : index = (index + size / 4) % size; break;
                case 2 : index = (index + size / 8) % size; break;
                case 3 : index = (index + size / 4) % size; break;
            }
            index = get_opposite<Strategy>(index, ring);

            if (visited_indexes.count(index) > 0)
            {
                // Avoid trying the same starting point more than once
                continue;
            }

            std::rotate_copy(boost::begin(ring), range::pos(ring, index),
                             boost::end(ring), rotated.begin());

            // Close the rotated copy
            rotated.push_back(range::at(ring, index));

            simplify_range<0>::apply(rotated, out, max_distance, strategy);

            // Verify that what was positive, stays positive (or goes to 0)
            // and what was negative stays negative (or goes to 0)
            int const output_sign = area_sign(geometry::area(out));
            if (output_sign == input_sign)
            {
                // Result is considered as satisfactory (usually this is the
                // first iteration - only for small rings, having a scale
                // similar to simplify_distance, next iterations are tried
                return;
            }

            // Original is simplified away. Possibly there is a solution
            // when another starting point is used
            geometry::clear(out);

            if (iteration == 0
                && geometry::perimeter(ring) < 3 * max_distance)
            {
                // Check if it is useful to iterate. A minimal triangle has a
                // perimeter of a bit more than 3 times the simplify distance
                return;
            }

            // Prepare next try
            visited_indexes.insert(index);
            rotated.resize(size);
        }
    }
};


struct simplify_polygon
{
private:

    template
    <
        typename IteratorIn,
        typename InteriorRingsOut,
        typename Distance,
        typename Strategy
    >
    static inline void iterate(IteratorIn begin, IteratorIn end,
                    InteriorRingsOut& interior_rings_out,
                    Distance const& max_distance, Strategy const& strategy)
    {
        typedef typename boost::range_value<InteriorRingsOut>::type single_type;
        for (IteratorIn it = begin; it != end; ++it)
        {
            single_type out;
            simplify_ring::apply(*it, out, max_distance, strategy);
            if (! geometry::is_empty(out))
            {
                range::push_back(interior_rings_out, out);
            }
        }
    }

    template
    <
        typename InteriorRingsIn,
        typename InteriorRingsOut,
        typename Distance,
        typename Strategy
    >
    static inline void apply_interior_rings(
                    InteriorRingsIn const& interior_rings_in,
                    InteriorRingsOut& interior_rings_out,
                    Distance const& max_distance, Strategy const& strategy)
    {
        range::clear(interior_rings_out);

        iterate(
            boost::begin(interior_rings_in), boost::end(interior_rings_in),
            interior_rings_out,
            max_distance, strategy);
    }

public:
    template <typename Polygon, typename Strategy, typename Distance>
    static inline void apply(Polygon const& poly_in, Polygon& poly_out,
                    Distance const& max_distance, Strategy const& strategy)
    {
        // Note that if there are inner rings, and distance is too large,
        // they might intersect with the outer ring in the output,
        // while it didn't in the input.
        simplify_ring::apply(exterior_ring(poly_in), exterior_ring(poly_out),
            max_distance, strategy);

        apply_interior_rings(interior_rings(poly_in),
            interior_rings(poly_out), max_distance, strategy);
    }
};


template<typename Policy>
struct simplify_multi
{
    template <typename MultiGeometry, typename Strategy, typename Distance>
    static inline void apply(MultiGeometry const& multi, MultiGeometry& out,
                    Distance const& max_distance, Strategy const& strategy)
    {
        range::clear(out);

        typedef typename boost::range_value<MultiGeometry>::type single_type;

        for (typename boost::range_iterator<MultiGeometry const>::type
                it = boost::begin(multi); it != boost::end(multi); ++it)
        {
            single_type single_out;
            Policy::apply(*it, single_out, max_distance, strategy);
            if (! geometry::is_empty(single_out))
            {
                range::push_back(out, single_out);
            }
        }
    }
};


}} // namespace detail::simplify
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type
>
struct simplify: not_implemented<Tag>
{};

template <typename Point>
struct simplify<Point, point_tag>
{
    template <typename Distance, typename Strategy>
    static inline void apply(Point const& point, Point& out,
                    Distance const& , Strategy const& )
    {
        geometry::convert(point, out);
    }
};

// Linestring, keep 2 points (unless those points are the same)
template <typename Linestring>
struct simplify<Linestring, linestring_tag>
    : detail::simplify::simplify_range<2>
{};

template <typename Ring>
struct simplify<Ring, ring_tag>
    : detail::simplify::simplify_ring
{};

template <typename Polygon>
struct simplify<Polygon, polygon_tag>
    : detail::simplify::simplify_polygon
{};


template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type
>
struct simplify_insert: not_implemented<Tag>
{};


template <typename Linestring>
struct simplify_insert<Linestring, linestring_tag>
    : detail::simplify::simplify_range_insert
{};

template <typename Ring>
struct simplify_insert<Ring, ring_tag>
    : detail::simplify::simplify_range_insert
{};

template <typename MultiPoint>
struct simplify<MultiPoint, multi_point_tag>
    : detail::simplify::simplify_copy
{};


template <typename MultiLinestring>
struct simplify<MultiLinestring, multi_linestring_tag>
    : detail::simplify::simplify_multi<detail::simplify::simplify_range<2> >
{};


template <typename MultiPolygon>
struct simplify<MultiPolygon, multi_polygon_tag>
    : detail::simplify::simplify_multi<detail::simplify::simplify_polygon>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy
{

struct simplify
{
    template <typename Geometry, typename Distance, typename Strategy>
    static inline void apply(Geometry const& geometry,
                             Geometry& out,
                             Distance const& max_distance,
                             Strategy const& strategy)
    {
        dispatch::simplify<Geometry>::apply(geometry, out, max_distance, strategy);
    }

    template <typename Geometry, typename Distance>
    static inline void apply(Geometry const& geometry,
                             Geometry& out,
                             Distance const& max_distance,
                             default_strategy)
    {
        typedef typename point_type<Geometry>::type point_type;

        typedef typename strategy::distance::services::default_strategy
        <
            point_tag, segment_tag, point_type
        >::type ds_strategy_type;

        typedef strategy::simplify::douglas_peucker
        <
            point_type, ds_strategy_type
        > strategy_type;

        BOOST_CONCEPT_ASSERT(
            (concepts::SimplifyStrategy<strategy_type, point_type>)
        );

        apply(geometry, out, max_distance, strategy_type());
    }
};

struct simplify_insert
{
    template
    <
        typename Geometry,
        typename OutputIterator,
        typename Distance,
        typename Strategy
    >
    static inline void apply(Geometry const& geometry,
                             OutputIterator& out,
                             Distance const& max_distance,
                             Strategy const& strategy)
    {
        dispatch::simplify_insert<Geometry>::apply(geometry, out, max_distance, strategy);
    }

    template <typename Geometry, typename OutputIterator, typename Distance>
    static inline void apply(Geometry const& geometry,
                             OutputIterator& out,
                             Distance const& max_distance,
                             default_strategy)
    {
        typedef typename point_type<Geometry>::type point_type;

        typedef typename strategy::distance::services::default_strategy
        <
            point_tag, segment_tag, point_type
        >::type ds_strategy_type;

        typedef strategy::simplify::douglas_peucker
        <
            point_type, ds_strategy_type
        > strategy_type;

        BOOST_CONCEPT_ASSERT(
            (concepts::SimplifyStrategy<strategy_type, point_type>)
        );

        apply(geometry, out, max_distance, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_variant {

template <typename Geometry>
struct simplify
{
    template <typename Distance, typename Strategy>
    static inline void apply(Geometry const& geometry,
                             Geometry& out,
                             Distance const& max_distance,
                             Strategy const& strategy)
    {
        resolve_strategy::simplify::apply(geometry, out, max_distance, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct simplify<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Distance, typename Strategy>
    struct visitor: boost::static_visitor<void>
    {
        Distance const& m_max_distance;
        Strategy const& m_strategy;

        visitor(Distance const& max_distance, Strategy const& strategy)
            : m_max_distance(max_distance)
            , m_strategy(strategy)
        {}

        template <typename Geometry>
        void operator()(Geometry const& geometry, Geometry& out) const
        {
            simplify<Geometry>::apply(geometry, out, m_max_distance, m_strategy);
        }
    };

    template <typename Distance, typename Strategy>
    static inline void
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
          boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& out,
          Distance const& max_distance,
          Strategy const& strategy)
    {
        boost::apply_visitor(
            visitor<Distance, Strategy>(max_distance, strategy),
            geometry,
            out
        );
    }
};

} // namespace resolve_variant


/*!
\brief Simplify a geometry using a specified strategy
\ingroup simplify
\tparam Geometry \tparam_geometry
\tparam Distance A numerical distance measure
\tparam Strategy A type fulfilling a SimplifyStrategy concept
\param strategy A strategy to calculate simplification
\param geometry input geometry, to be simplified
\param out output geometry, simplified version of the input geometry
\param max_distance distance (in units of input coordinates) of a vertex
    to other segments to be removed
\param strategy simplify strategy to be used for simplification, might
    include point-distance strategy

\image html svg_simplify_country.png "The image below presents the simplified country"
\qbk{distinguish,with strategy}
*/
template<typename Geometry, typename Distance, typename Strategy>
inline void simplify(Geometry const& geometry, Geometry& out,
                     Distance const& max_distance, Strategy const& strategy)
{
    concepts::check<Geometry>();

    geometry::clear(out);

    resolve_variant::simplify<Geometry>::apply(geometry, out, max_distance, strategy);
}




/*!
\brief Simplify a geometry
\ingroup simplify
\tparam Geometry \tparam_geometry
\tparam Distance \tparam_numeric
\note This version of simplify simplifies a geometry using the default
    strategy (Douglas Peucker),
\param geometry input geometry, to be simplified
\param out output geometry, simplified version of the input geometry
\param max_distance distance (in units of input coordinates) of a vertex
    to other segments to be removed

\qbk{[include reference/algorithms/simplify.qbk]}
 */
template<typename Geometry, typename Distance>
inline void simplify(Geometry const& geometry, Geometry& out,
                     Distance const& max_distance)
{
    concepts::check<Geometry>();

    geometry::simplify(geometry, out, max_distance, default_strategy());
}


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace simplify
{


/*!
\brief Simplify a geometry, using an output iterator
    and a specified strategy
\ingroup simplify
\tparam Geometry \tparam_geometry
\param geometry input geometry, to be simplified
\param out output iterator, outputs all simplified points
\param max_distance distance (in units of input coordinates) of a vertex
    to other segments to be removed
\param strategy simplify strategy to be used for simplification,
    might include point-distance strategy

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/simplify.qbk]}
*/
template<typename Geometry, typename OutputIterator, typename Distance, typename Strategy>
inline void simplify_insert(Geometry const& geometry, OutputIterator out,
                            Distance const& max_distance, Strategy const& strategy)
{
    concepts::check<Geometry const>();

    resolve_strategy::simplify_insert::apply(geometry, out, max_distance, strategy);
}

/*!
\brief Simplify a geometry, using an output iterator
\ingroup simplify
\tparam Geometry \tparam_geometry
\param geometry input geometry, to be simplified
\param out output iterator, outputs all simplified points
\param max_distance distance (in units of input coordinates) of a vertex
    to other segments to be removed

\qbk{[include reference/algorithms/simplify_insert.qbk]}
 */
template<typename Geometry, typename OutputIterator, typename Distance>
inline void simplify_insert(Geometry const& geometry, OutputIterator out,
                            Distance const& max_distance)
{
    // Concept: output point type = point type of input geometry
    concepts::check<Geometry const>();
    concepts::check<typename point_type<Geometry>::type>();

    simplify_insert(geometry, out, max_distance, default_strategy());
}

}} // namespace detail::simplify
#endif // DOXYGEN_NO_DETAIL



}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_SIMPLIFY_HPP

/* simplify.hpp
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
*/