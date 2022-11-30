// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018-2022.
// Modifications copyright (c) 2018-2022 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_SIMPLIFY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_SIMPLIFY_HPP

#include <cstddef>
#ifdef BOOST_GEOMETRY_DEBUG_DOUGLAS_PEUCKER
#include <iostream>
#endif
#include <set>
#include <vector>

#include <boost/core/addressof.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/detail/dummy_geometries.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/visit.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/algorithms/is_empty.hpp>
#include <boost/geometry/algorithms/perimeter.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/visit.hpp>

#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/concepts/simplify_concept.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/distance/comparable.hpp>
#include <boost/geometry/strategies/simplify/cartesian.hpp>
#include <boost/geometry/strategies/simplify/geographic.hpp>
#include <boost/geometry/strategies/simplify/spherical.hpp>

#include <boost/geometry/util/type_traits_std.hpp>

#ifdef BOOST_GEOMETRY_DEBUG_DOUGLAS_PEUCKER
#include <boost/geometry/io/dsv/write.hpp>
#endif

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace simplify
{

/*!
\brief Small wrapper around a point, with an extra member "included"
\details
    It has a const-reference to the original point (so no copy here)
\tparam the enclosed point type
*/
template <typename Point>
struct douglas_peucker_point
{
    typedef Point point_type;

    Point const* p;
    bool included;

    inline douglas_peucker_point(Point const& ap)
        : p(boost::addressof(ap))
        , included(false)
    {}
};

/*!
\brief Implements the simplify algorithm.
\details The douglas_peucker policy simplifies a linestring, ring or
    vector of points using the well-known Douglas-Peucker algorithm.
\tparam Point the point type
\tparam PointDistanceStrategy point-segment distance strategy to be used
\note This strategy uses itself a point-segment-distance strategy which
    can be specified
\author Barend and Maarten, 1995/1996
\author Barend, revised for Generic Geometry Library, 2008
*/

/*
For the algorithm, see for example:
 - http://en.wikipedia.org/wiki/Ramer-Douglas-Peucker_algorithm
 - http://www2.dcs.hull.ac.uk/CISRG/projects/Royal-Inst/demos/dp.html
*/
class douglas_peucker
{
    template <typename Iterator, typename Distance, typename PSDistanceStrategy>
    static inline void consider(Iterator begin,
                                Iterator end,
                                Distance const& max_dist,
                                int& n,
                                PSDistanceStrategy const& ps_distance_strategy)
    {
        typedef typename std::iterator_traits<Iterator>::value_type::point_type point_type;
        typedef decltype(ps_distance_strategy.apply(std::declval<point_type>(),
                            std::declval<point_type>(), std::declval<point_type>())) distance_type;

        std::size_t size = end - begin;

        // size must be at least 3
        // because we want to consider a candidate point in between
        if (size <= 2)
        {
#ifdef BOOST_GEOMETRY_DEBUG_DOUGLAS_PEUCKER
            if (begin != end)
            {
                std::cout << "ignore between " << dsv(*(begin->p))
                    << " and " << dsv(*((end - 1)->p))
                    << " size=" << size << std::endl;
            }
            std::cout << "return because size=" << size << std::endl;
#endif
            return;
        }

        Iterator last = end - 1;

#ifdef BOOST_GEOMETRY_DEBUG_DOUGLAS_PEUCKER
        std::cout << "find between " << dsv(*(begin->p))
            << " and " << dsv(*(last->p))
            << " size=" << size << std::endl;
#endif


        // Find most far point, compare to the current segment
        //geometry::segment<Point const> s(begin->p, last->p);
        distance_type md(-1.0); // any value < 0
        Iterator candidate = end;
        for (Iterator it = begin + 1; it != last; ++it)
        {
            distance_type dist = ps_distance_strategy.apply(*(it->p), *(begin->p), *(last->p));

#ifdef BOOST_GEOMETRY_DEBUG_DOUGLAS_PEUCKER
            std::cout << "consider " << dsv(*(it->p))
                << " at " << double(dist)
                << ((dist > max_dist) ? " maybe" : " no")
                << std::endl;

#endif
            if (md < dist)
            {
                md = dist;
                candidate = it;
            }
        }

        // If a point is found, set the include flag
        // and handle segments in between recursively
        if (max_dist < md && candidate != end)
        {
#ifdef BOOST_GEOMETRY_DEBUG_DOUGLAS_PEUCKER
            std::cout << "use " << dsv(candidate->p) << std::endl;
#endif

            candidate->included = true;
            n++;

            consider(begin, candidate + 1, max_dist, n, ps_distance_strategy);
            consider(candidate, end, max_dist, n, ps_distance_strategy);
        }
    }

    template
    <
        typename Range, typename OutputIterator, typename Distance,
        typename PSDistanceStrategy
    >
    static inline OutputIterator apply_(Range const& range,
                                        OutputIterator out,
                                        Distance const& max_distance,
                                        PSDistanceStrategy const& ps_distance_strategy)
    {
#ifdef BOOST_GEOMETRY_DEBUG_DOUGLAS_PEUCKER
            std::cout << "max distance: " << max_distance
                      << std::endl << std::endl;
#endif

        typedef typename boost::range_value<Range>::type point_type;
        typedef douglas_peucker_point<point_type> dp_point_type;

        // Copy coordinates, a vector of references to all points
        std::vector<dp_point_type> ref_candidates(boost::begin(range),
                                                  boost::end(range));

        // Include first and last point of line,
        // they are always part of the line
        int n = 2;
        ref_candidates.front().included = true;
        ref_candidates.back().included = true;

        // Get points, recursively, including them if they are further away
        // than the specified distance
        consider(boost::begin(ref_candidates), boost::end(ref_candidates), max_distance, n,
                 ps_distance_strategy);

        // Copy included elements to the output
        for (auto it = boost::begin(ref_candidates); it != boost::end(ref_candidates); ++it)
        {
            if (it->included)
            {
                // copy-coordinates does not work because OutputIterator
                // does not model Point (??)
                //geometry::convert(*(it->p), *out);
                *out = *(it->p);
                ++out;
            }
        }
        return out;
    }

public:
    template <typename Range, typename OutputIterator, typename Distance, typename Strategies>
    static inline OutputIterator apply(Range const& range,
                                       OutputIterator out,
                                       Distance const& max_distance,
                                       Strategies const& strategies)
    {
        typedef typename boost::range_value<Range>::type point_type;
        typedef decltype(strategies.distance(detail::dummy_point(), detail::dummy_segment())) distance_strategy_type;

        typedef typename strategy::distance::services::comparable_type
            <
                distance_strategy_type
            >::type comparable_distance_strategy_type;

        comparable_distance_strategy_type cstrategy = strategy::distance::services::get_comparable
            <
                distance_strategy_type
            >::apply(strategies.distance(detail::dummy_point(), detail::dummy_segment()));

        return apply_(range, out,
                      strategy::distance::services::result_from_distance
                          <
                              comparable_distance_strategy_type, point_type, point_type
                          >::apply(cstrategy, max_distance),
                      cstrategy);
    }
};


template <typename Range, typename Strategies>
inline bool is_degenerate(Range const& range, Strategies const& strategies)
{
    return boost::size(range) == 2
        && detail::equals::equals_point_point(geometry::range::front(range),
                                              geometry::range::back(range),
                                              strategies);
}

struct simplify_range_insert
{
    template
    <
        typename Range, typename OutputIterator, typename Distance,
        typename Impl, typename Strategies
    >
    static inline void apply(Range const& range, OutputIterator out,
                             Distance const& max_distance,
                             Impl const& impl,
                             Strategies const& strategies)
    {
        if (is_degenerate(range, strategies))
        {
            std::copy(boost::begin(range), boost::begin(range) + 1, out);
        }
        else if (boost::size(range) <= 2 || max_distance < 0)
        {
            std::copy(boost::begin(range), boost::end(range), out);
        }
        else
        {
            impl.apply(range, out, max_distance, strategies);
        }
    }
};


struct simplify_copy_assign
{
    template
    <
        typename In, typename Out, typename Distance,
        typename Impl, typename Strategies
    >
    static inline void apply(In const& in, Out& out,
                             Distance const& ,
                             Impl const& ,
                             Strategies const& )
    {
        out = in;
    }
};


struct simplify_copy
{
    template
    <
        typename RangeIn, typename RangeOut, typename Distance,
        typename Impl, typename Strategies
    >
    static inline void apply(RangeIn const& range, RangeOut& out,
                             Distance const& ,
                             Impl const& ,
                             Strategies const& )
    {
        std::copy(boost::begin(range), boost::end(range),
                  geometry::range::back_inserter(out));
    }
};


template <std::size_t MinimumToUseStrategy>
struct simplify_range
{
    template
    <
        typename RangeIn, typename RangeOut, typename Distance,
        typename Impl, typename Strategies
    >
    static inline void apply(RangeIn const& range, RangeOut& out,
                             Distance const& max_distance,
                             Impl const& impl,
                             Strategies const& strategies)
    {
        // For a RING:
        // Note that, especially if max_distance is too large,
        // the output ring might be self intersecting while the input ring is
        // not, although chances are low in normal polygons

        if (boost::size(range) <= MinimumToUseStrategy || max_distance < 0)
        {
            simplify_copy::apply(range, out, max_distance, impl, strategies);
        }
        else
        {
            simplify_range_insert::apply(range, geometry::range::back_inserter(out),
                                         max_distance, impl, strategies);
        }

        // Verify the two remaining points are equal. If so, remove one of them.
        // This can cause the output being under the minimum size
        if (is_degenerate(out, strategies))
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

    template <typename Ring, typename Strategies>
    static std::size_t get_opposite(std::size_t index, Ring const& ring,
                                    Strategies const& strategies)
    {
        // TODO: Instead of calling the strategy call geometry::comparable_distance() ?

        auto const cdistance_strategy = strategies::distance::detail::make_comparable(strategies)
            .distance(detail::dummy_point(), detail::dummy_point());

        using point_type = typename geometry::point_type<Ring>::type;
        using cdistance_type = decltype(cdistance_strategy.apply(
            std::declval<point_type>(), std::declval<point_type>()));

        // Verify if it is NOT the case that all points are less than the
        // simplifying distance. If so, output is empty.
        cdistance_type max_cdistance(-1);

        point_type const& point = range::at(ring, index);
        std::size_t i = 0;
        for (auto it = boost::begin(ring); it != boost::end(ring); ++it, ++i)
        {
            cdistance_type const cdistance = cdistance_strategy.apply(*it, point);
            if (cdistance > max_cdistance)
            {
                max_cdistance = cdistance;
                index = i;
            }
        }
        return index;
    }

public :
    template <typename Ring, typename Distance, typename Impl, typename Strategies>
    static inline void apply(Ring const& ring, Ring& out, Distance const& max_distance,
                             Impl const& impl, Strategies const& strategies)
    {
        std::size_t const size = boost::size(ring);
        if (size == 0)
        {
            return;
        }

        bool const is_closed = closure<Ring>::value == closed;

        // TODO: instead of area() use calculate_point_order() ?

        int const input_sign = area_sign(geometry::area(ring, strategies));

        std::set<std::size_t> visited_indexes;

        // Rotate it into a copied vector
        // (vector, because source type might not support rotation)
        // (duplicate end point will be simplified away)
        typedef typename geometry::point_type<Ring>::type point_type;

        std::vector<point_type> rotated;
        rotated.reserve(size + 1); // 1 because open rings are closed

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
            index = get_opposite(index, ring, strategies);

            if (visited_indexes.count(index) > 0)
            {
                // Avoid trying the same starting point more than once
                continue;
            }

            // Do not duplicate the closing point
            auto rot_end = boost::end(ring);
            std::size_t rot_index = index;
            if (is_closed && size > 1)
            {
                --rot_end;
                if (rot_index == size - 1) { rot_index = 0; }
            }

            std::rotate_copy(boost::begin(ring), range::pos(ring, rot_index),
                             rot_end, std::back_inserter(rotated));

            // Close the rotated copy
            rotated.push_back(range::at(ring, rot_index));

            simplify_range<0>::apply(rotated, out, max_distance, impl, strategies);

            // Open output if needed
            if (! is_closed && boost::size(out) > 1)
            {
                range::pop_back(out);
            }

            // TODO: instead of area() use calculate_point_order() ?

            // Verify that what was positive, stays positive (or goes to 0)
            // and what was negative stays negative (or goes to 0)
            int const output_sign = area_sign(geometry::area(out, strategies));
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
                && geometry::perimeter(ring, strategies) < 3 * max_distance)
            {
                // Check if it is useful to iterate. A minimal triangle has a
                // perimeter of a bit more than 3 times the simplify distance
                return;
            }

            // Prepare next try
            visited_indexes.insert(index);
            rotated.clear();
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
        typename Impl,
        typename Strategies
    >
    static inline void iterate(IteratorIn begin, IteratorIn end,
                               InteriorRingsOut& interior_rings_out,
                               Distance const& max_distance,
                               Impl const& impl, Strategies const& strategies)
    {
        typedef typename boost::range_value<InteriorRingsOut>::type single_type;
        for (IteratorIn it = begin; it != end; ++it)
        {
            single_type out;
            simplify_ring::apply(*it, out, max_distance, impl, strategies);
            if (! geometry::is_empty(out))
            {
                range::push_back(interior_rings_out, std::move(out));
            }
        }
    }

    template
    <
        typename InteriorRingsIn,
        typename InteriorRingsOut,
        typename Distance,
        typename Impl,
        typename Strategies
    >
    static inline void apply_interior_rings(InteriorRingsIn const& interior_rings_in,
                                            InteriorRingsOut& interior_rings_out,
                                            Distance const& max_distance,
                                            Impl const& impl, Strategies const& strategies)
    {
        range::clear(interior_rings_out);

        iterate(boost::begin(interior_rings_in), boost::end(interior_rings_in),
                interior_rings_out,
                max_distance,
                impl, strategies);
    }

public:
    template <typename Polygon, typename Distance, typename Impl, typename Strategies>
    static inline void apply(Polygon const& poly_in, Polygon& poly_out,
                             Distance const& max_distance,
                             Impl const& impl, Strategies const& strategies)
    {
        // Note that if there are inner rings, and distance is too large,
        // they might intersect with the outer ring in the output,
        // while it didn't in the input.
        simplify_ring::apply(exterior_ring(poly_in), exterior_ring(poly_out),
                             max_distance, impl, strategies);

        apply_interior_rings(interior_rings(poly_in), interior_rings(poly_out),
                             max_distance, impl, strategies);
    }
};


template<typename Policy>
struct simplify_multi
{
    template <typename MultiGeometry, typename Distance, typename Impl, typename Strategies>
    static inline void apply(MultiGeometry const& multi, MultiGeometry& out,
                             Distance const& max_distance,
                             Impl const& impl, Strategies const& strategies)
    {
        range::clear(out);

        typedef typename boost::range_value<MultiGeometry>::type single_type;

        for (typename boost::range_iterator<MultiGeometry const>::type
                it = boost::begin(multi); it != boost::end(multi); ++it)
        {
            single_type single_out;
            Policy::apply(*it, single_out, max_distance, impl, strategies);
            if (! geometry::is_empty(single_out))
            {
                range::push_back(out, std::move(single_out));
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
    template <typename Distance, typename Impl, typename Strategy>
    static inline void apply(Point const& point, Point& out, Distance const& ,
                             Impl const& , Strategy const& )
    {
        geometry::convert(point, out);
    }
};

template <typename Segment>
struct simplify<Segment, segment_tag>
    : detail::simplify::simplify_copy_assign
{};

template <typename Box>
struct simplify<Box, box_tag>
    : detail::simplify::simplify_copy_assign
{};


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

template
<
    typename Strategies,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategies>::value
>
struct simplify
{
    template <typename Geometry, typename Distance>
    static inline void apply(Geometry const& geometry,
                             Geometry& out,
                             Distance const& max_distance,
                             Strategies const& strategies)
    {
        dispatch::simplify
            <
                Geometry
            >::apply(geometry, out, max_distance,
                     detail::simplify::douglas_peucker(),
                     strategies);
    }
};

template <typename Strategy>
struct simplify<Strategy, false>
{
    template <typename Geometry, typename Distance>
    static inline void apply(Geometry const& geometry,
                             Geometry& out,
                             Distance const& max_distance,
                             Strategy const& strategy)
    {
        using strategies::simplify::services::strategy_converter;

        simplify
            <
                decltype(strategy_converter<Strategy>::get(strategy))
            >::apply(geometry, out, max_distance,
                     strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct simplify<default_strategy, false>
{
    template <typename Geometry, typename Distance>
    static inline void apply(Geometry const& geometry,
                             Geometry& out,
                             Distance const& max_distance,
                             default_strategy)
    {
        typedef typename strategies::simplify::services::default_strategy
            <
                Geometry
            >::type strategy_type;

        simplify
            <
                strategy_type
            >::apply(geometry, out, max_distance, strategy_type());
    }
};

template
<
    typename Strategies,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategies>::value
>
struct simplify_insert
{
    template<typename Geometry, typename OutputIterator, typename Distance>
    static inline void apply(Geometry const& geometry,
                             OutputIterator& out,
                             Distance const& max_distance,
                             Strategies const& strategies)
    {
        dispatch::simplify_insert
            <
                Geometry
            >::apply(geometry, out, max_distance,
                     detail::simplify::douglas_peucker(),
                     strategies);
    }
};

template <typename Strategy>
struct simplify_insert<Strategy, false>
{
    template<typename Geometry, typename OutputIterator, typename Distance>
    static inline void apply(Geometry const& geometry,
                             OutputIterator& out,
                             Distance const& max_distance,
                             Strategy const& strategy)
    {
        using strategies::simplify::services::strategy_converter;

        simplify_insert
            <
                decltype(strategy_converter<Strategy>::get(strategy))
            >::apply(geometry, out, max_distance,
                     strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct simplify_insert<default_strategy, false>
{
    template <typename Geometry, typename OutputIterator, typename Distance>
    static inline void apply(Geometry const& geometry,
                             OutputIterator& out,
                             Distance const& max_distance,
                             default_strategy)
    {
        typedef typename strategies::simplify::services::default_strategy
            <
                Geometry
            >::type strategy_type;
        
        simplify_insert
            <
                strategy_type
            >::apply(geometry, out, max_distance, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_dynamic {

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct simplify
{
    template <typename Distance, typename Strategy>
    static inline void apply(Geometry const& geometry,
                             Geometry& out,
                             Distance const& max_distance,
                             Strategy const& strategy)
    {
        resolve_strategy::simplify<Strategy>::apply(geometry, out, max_distance, strategy);
    }
};

template <typename Geometry>
struct simplify<Geometry, dynamic_geometry_tag>
{
    template <typename Distance, typename Strategy>
    static inline void apply(Geometry const& geometry,
                             Geometry& out,
                             Distance const& max_distance,
                             Strategy const& strategy)
    {
        traits::visit<Geometry>::apply([&](auto const& g)
        {
            using geom_t = util::remove_cref_t<decltype(g)>;
            geom_t o;
            simplify<geom_t>::apply(g, o, max_distance, strategy);
            out = std::move(o);
        }, geometry);
    }
};

template <typename Geometry>
struct simplify<Geometry, geometry_collection_tag>
{
    template <typename Distance, typename Strategy>
    static inline void apply(Geometry const& geometry,
                             Geometry& out,
                             Distance const& max_distance,
                             Strategy const& strategy)
    {
        detail::visit_breadth_first([&](auto const& g)
        {
            using geom_t = util::remove_cref_t<decltype(g)>;
            geom_t o;
            simplify<geom_t>::apply(g, o, max_distance, strategy);
            traits::emplace_back<Geometry>::apply(out, std::move(o));
            return true;
        }, geometry);
    }
};

} // namespace resolve_dynamic


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

    resolve_dynamic::simplify<Geometry>::apply(geometry, out, max_distance, strategy);
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

    resolve_strategy::simplify_insert<Strategy>::apply(geometry, out, max_distance, strategy);
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