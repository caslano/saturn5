// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFER_INSERTER_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFER_INSERTER_HPP

#include <cstddef>
#include <iterator>


#include <boost/core/ignore_unused.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/range.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/math.hpp>

#include <boost/geometry/strategies/buffer.hpp>
#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/algorithms/detail/make/make.hpp>
#include <boost/geometry/algorithms/detail/buffer/buffered_piece_collection.hpp>
#include <boost/geometry/algorithms/detail/buffer/line_line_intersection.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/num_interior_rings.hpp>
#include <boost/geometry/algorithms/simplify.hpp>

#include <boost/geometry/arithmetic/infinite_line_functions.hpp>

#include <boost/geometry/views/detail/normalized_view.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace buffer
{

template <typename Range, typename DistanceStrategy>
inline void simplify_input(Range const& range,
        DistanceStrategy const& distance,
        Range& simplified)
{
    // We have to simplify the ring before to avoid very small-scaled
    // features in the original (convex/concave/convex) being enlarged
    // in a very large scale and causing issues (IP's within pieces).
    // This might be reconsidered later. Simplifying with a very small
    // distance (1%% of the buffer) will never be visible in the result,
    // if it is using round joins. For miter joins they are even more
    // sensitive to small scale input features, however the result will
    // look better.
    // It also gets rid of duplicate points

    typedef typename geometry::point_type<Range>::type point_type;
    typedef typename strategy::distance::services::default_strategy
    <
        point_tag, segment_tag, point_type
    >::type ds_strategy_type;
    typedef strategy::simplify::douglas_peucker
    <
        point_type, ds_strategy_type
    > strategy_type;

    geometry::detail::simplify::simplify_range<2>::apply(range,
        simplified, distance.simplify_distance(),
        strategy_type());

}


template <typename RingOutput>
struct buffer_range
{
    typedef typename point_type<RingOutput>::type output_point_type;
    typedef typename coordinate_type<RingOutput>::type coordinate_type;

    template
    <
        typename Collection,
        typename Point,
        typename DistanceStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename RobustPolicy,
        typename SideStrategy
    >
    static inline
    void add_join(Collection& collection,
            Point const& penultimate_input,
            Point const& previous_input,
            output_point_type const& prev_perp1,
            output_point_type const& prev_perp2,
            Point const& input,
            output_point_type const& perp1,
            output_point_type const& perp2,
            geometry::strategy::buffer::buffer_side_selector side,
            DistanceStrategy const& distance,
            JoinStrategy const& join_strategy,
            EndStrategy const& end_strategy,
            RobustPolicy const& ,
            SideStrategy const& side_strategy) // side strategy
    {
        output_point_type intersection_point;
        geometry::assign_zero(intersection_point);

        geometry::strategy::buffer::join_selector join
                = get_join_type(penultimate_input, previous_input, input, side_strategy);
        if (join == geometry::strategy::buffer::join_convex)
        {
            // Calculate the intersection-point formed by the two sides.
            // It might be that the two sides are not convex, but continue
            // or spikey, we then change the join-type
            join = line_line_intersection::apply(
                        perp1, perp2, prev_perp1, prev_perp2,
                        intersection_point);

        }

        switch(join)
        {
            case geometry::strategy::buffer::join_continue :
                // No join, we get two consecutive sides
                break;
            case geometry::strategy::buffer::join_concave :
                {
                    std::vector<output_point_type> range_out;
                    range_out.push_back(prev_perp2);
                    range_out.push_back(previous_input);
                    collection.add_piece(geometry::strategy::buffer::buffered_concave, previous_input, range_out);

                    range_out.clear();
                    range_out.push_back(previous_input);
                    range_out.push_back(perp1);
                    collection.add_piece(geometry::strategy::buffer::buffered_concave, previous_input, range_out);
                }
                break;
            case geometry::strategy::buffer::join_spike :
                {
                    // For linestrings, only add spike at one side to avoid
                    // duplicates
                    std::vector<output_point_type> range_out;
                    end_strategy.apply(penultimate_input, prev_perp2, previous_input, perp1, side, distance, range_out);
                    collection.add_endcap(end_strategy, range_out, previous_input);
                    collection.set_current_ring_concave();
                }
                break;
            case geometry::strategy::buffer::join_convex :
                {
                    // The corner is convex, we create a join
                    // TODO (future) - avoid a separate vector, add the piece directly
                    std::vector<output_point_type> range_out;
                    if (join_strategy.apply(intersection_point,
                                previous_input, prev_perp2, perp1,
                                distance.apply(previous_input, input, side),
                                range_out))
                    {
                        collection.add_piece(geometry::strategy::buffer::buffered_join,
                                previous_input, range_out);
                    }
                }
                break;
        }
    }

    static inline bool similar_direction(output_point_type const& p0,
            output_point_type const& p1,
            output_point_type const& p2)
    {
        typedef model::infinite_line<coordinate_type> line_type;
        line_type const p = detail::make::make_infinite_line<coordinate_type>(p0, p1);
        line_type const q = detail::make::make_infinite_line<coordinate_type>(p1, p2);
        return arithmetic::similar_direction(p, q);
    }

    template <typename SideStrategy>
    static inline geometry::strategy::buffer::join_selector get_join_type(
            output_point_type const& p0,
            output_point_type const& p1,
            output_point_type const& p2,
            SideStrategy const& side_strategy)
    {
        int const side = side_strategy.apply(p0, p1, p2);
        return side == -1 ? geometry::strategy::buffer::join_convex
            :  side == 1  ? geometry::strategy::buffer::join_concave
            :  similar_direction(p0, p1, p2)
                          ? geometry::strategy::buffer::join_continue
            : geometry::strategy::buffer::join_spike;
    }

    template
    <
        typename Collection,
        typename Iterator,
        typename DistanceStrategy,
        typename SideStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename RobustPolicy,
        typename Strategy
    >
    static inline geometry::strategy::buffer::result_code iterate(Collection& collection,
                Iterator begin, Iterator end,
                geometry::strategy::buffer::buffer_side_selector side,
                DistanceStrategy const& distance_strategy,
                SideStrategy const& side_strategy,
                JoinStrategy const& join_strategy,
                EndStrategy const& end_strategy,
                RobustPolicy const& robust_policy,
                Strategy const& strategy, // side strategy
                bool linear,
                output_point_type& first_p1,
                output_point_type& first_p2,
                output_point_type& last_p1,
                output_point_type& last_p2)
    {
        boost::ignore_unused(side_strategy);

        typedef typename std::iterator_traits
        <
            Iterator
        >::value_type point_type;

        point_type second_point, penultimate_point, ultimate_point; // last two points from begin/end

        /*
         * last.p1    last.p2  these are the "previous (last) perpendicular points"
         * --------------
         * |            |
         * *------------*____  <- *prev
         * pup          |    | p1           "current perpendicular point 1"
         *              |    |
         *              |    |       this forms a "side", a side is a piece
         *              |    |
         *              *____| p2
         *
         *              ^
         *             *it
         *
         * pup: penultimate_point
         */

        bool const mark_flat
            = linear
                && end_strategy.get_piece_type() == geometry::strategy::buffer::buffered_flat_end;

        geometry::strategy::buffer::result_code result = geometry::strategy::buffer::result_no_output;
        bool first = true;

        Iterator it = begin;

        std::vector<output_point_type> generated_side;
        generated_side.reserve(2);

        for (Iterator prev = it++; it != end; ++it)
        {
            generated_side.clear();
            geometry::strategy::buffer::result_code error_code
                = side_strategy.apply(*prev, *it, side,
                                distance_strategy, generated_side);

            if (error_code == geometry::strategy::buffer::result_no_output)
            {
                // Because input is simplified, this is improbable,
                // but it can happen for degenerate geometries
                // Further handling of this side is skipped
                continue;
            }
            else if (error_code == geometry::strategy::buffer::result_error_numerical)
            {
                return error_code;
            }

            BOOST_GEOMETRY_ASSERT(! generated_side.empty());

            result = geometry::strategy::buffer::result_normal;

            if (! first)
            {
                 add_join(collection,
                        penultimate_point,
                        *prev, last_p1, last_p2,
                        *it, generated_side.front(), generated_side.back(),
                        side,
                        distance_strategy, join_strategy, end_strategy,
                        robust_policy, strategy);
            }

            collection.add_side_piece(*prev, *it, generated_side, first);

            if (first && mark_flat)
            {
                collection.mark_flat_start();
            }

            penultimate_point = *prev;
            ultimate_point = *it;
            last_p1 = generated_side.front();
            last_p2 = generated_side.back();
            prev = it;
            if (first)
            {
                first = false;
                second_point = *it;
                first_p1 = generated_side.front();
                first_p2 = generated_side.back();
            }
        }

        if (mark_flat)
        {
            collection.mark_flat_end();
        }

        return result;
    }
};

template
<
    typename Multi,
    typename PolygonOutput,
    typename Policy
>
struct buffer_multi
{
    template
    <
        typename Collection,
        typename DistanceStrategy,
        typename SideStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename PointStrategy,
        typename RobustPolicy,
        typename Strategy
    >
    static inline void apply(Multi const& multi,
            Collection& collection,
            DistanceStrategy const& distance_strategy,
            SideStrategy const& side_strategy,
            JoinStrategy const& join_strategy,
            EndStrategy const& end_strategy,
            PointStrategy const& point_strategy,
            RobustPolicy const& robust_policy,
            Strategy const& strategy) // side strategy
    {
        for (typename boost::range_iterator<Multi const>::type
                it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it, collection,
                distance_strategy, side_strategy,
                join_strategy, end_strategy, point_strategy,
                robust_policy, strategy);
        }
    }
};

struct visit_pieces_default_policy
{
    template <typename Collection>
    static inline void apply(Collection const&, int)
    {}
};

template
<
    typename OutputPointType,
    typename Point,
    typename Collection,
    typename DistanceStrategy,
    typename PointStrategy
>
inline void buffer_point(Point const& point, Collection& collection,
        DistanceStrategy const& distance_strategy,
        PointStrategy const& point_strategy)
{
    collection.start_new_ring(false);
    std::vector<OutputPointType> range_out;
    point_strategy.apply(point, distance_strategy, range_out);
    collection.add_piece(geometry::strategy::buffer::buffered_point, range_out, false);
    collection.set_piece_center(point);
    collection.finish_ring(geometry::strategy::buffer::result_normal);
}


}} // namespace detail::buffer
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Tag,
    typename RingInput,
    typename RingOutput
>
struct buffer_inserter
{};



template
<
    typename Point,
    typename RingOutput
>
struct buffer_inserter<point_tag, Point, RingOutput>
{
    template
    <
        typename Collection,
        typename DistanceStrategy,
        typename SideStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename PointStrategy,
        typename RobustPolicy,
        typename Strategy
    >
    static inline void apply(Point const& point, Collection& collection,
            DistanceStrategy const& distance_strategy,
            SideStrategy const& ,
            JoinStrategy const& ,
            EndStrategy const& ,
            PointStrategy const& point_strategy,
            RobustPolicy const& ,
            Strategy const& ) // side strategy
    {
        detail::buffer::buffer_point
        <
            typename point_type<RingOutput>::type
        >(point, collection, distance_strategy, point_strategy);
    }
};

// Not a specialization, but called from specializations of ring and of polygon.
// Calling code starts/finishes ring before/after apply
template
<
    typename RingInput,
    typename RingOutput
>
struct buffer_inserter_ring
{
    typedef typename point_type<RingOutput>::type output_point_type;

    template
    <
        typename Collection,
        typename Iterator,
        typename DistanceStrategy,
        typename SideStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename RobustPolicy,
        typename Strategy
    >
    static inline geometry::strategy::buffer::result_code iterate(Collection& collection,
                Iterator begin, Iterator end,
                geometry::strategy::buffer::buffer_side_selector side,
                DistanceStrategy const& distance_strategy,
                SideStrategy const& side_strategy,
                JoinStrategy const& join_strategy,
                EndStrategy const& end_strategy,
                RobustPolicy const& robust_policy,
                Strategy const& strategy) // side strategy
    {
        output_point_type first_p1, first_p2, last_p1, last_p2;

        typedef detail::buffer::buffer_range<RingOutput> buffer_range;

        geometry::strategy::buffer::result_code result
            = buffer_range::iterate(collection, begin, end,
                side,
                distance_strategy, side_strategy, join_strategy, end_strategy,
                robust_policy, strategy,
                false, first_p1, first_p2, last_p1, last_p2);

        // Generate closing join
        if (result == geometry::strategy::buffer::result_normal)
        {
            buffer_range::add_join(collection,
                *(end - 2),
                *(end - 1), last_p1, last_p2,
                *(begin + 1), first_p1, first_p2,
                side,
                distance_strategy, join_strategy, end_strategy,
                robust_policy, strategy);
        }

        // Buffer is closed automatically by last closing corner
        return result;
    }

    template
    <
        typename Collection,
        typename DistanceStrategy,
        typename SideStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename PointStrategy,
        typename RobustPolicy,
        typename Strategy
    >
    static inline geometry::strategy::buffer::result_code apply(RingInput const& ring,
            Collection& collection,
            DistanceStrategy const& distance,
            SideStrategy const& side_strategy,
            JoinStrategy const& join_strategy,
            EndStrategy const& end_strategy,
            PointStrategy const& point_strategy,
            RobustPolicy const& robust_policy,
            Strategy const& strategy) // side strategy
    {
        RingInput simplified;
        detail::buffer::simplify_input(ring, distance, simplified);

        geometry::strategy::buffer::result_code code = geometry::strategy::buffer::result_no_output;

        std::size_t n = boost::size(simplified);
        std::size_t const min_points = core_detail::closure::minimum_ring_size
            <
                geometry::closure<RingInput>::value
            >::value;

        if (n >= min_points)
        {
            detail::normalized_view<RingInput const> view(simplified);
            if (distance.negative())
            {
                // Walk backwards (rings will be reversed afterwards)
                code = iterate(collection, boost::rbegin(view), boost::rend(view),
                        geometry::strategy::buffer::buffer_side_right,
                        distance, side_strategy, join_strategy, end_strategy,
                        robust_policy, strategy);
            }
            else
            {
                code = iterate(collection, boost::begin(view), boost::end(view),
                        geometry::strategy::buffer::buffer_side_left,
                        distance, side_strategy, join_strategy, end_strategy,
                        robust_policy, strategy);
            }
        }

        if (code == geometry::strategy::buffer::result_no_output && n >= 1)
        {
            // Use point_strategy to buffer degenerated ring
            detail::buffer::buffer_point<output_point_type>
                (
                    geometry::range::front(simplified),
                    collection, distance, point_strategy
                );
        }
        return code;
    }
};


template
<
    typename RingInput,
    typename RingOutput
>
struct buffer_inserter<ring_tag, RingInput, RingOutput>
{
    template
    <
        typename Collection,
        typename DistanceStrategy,
        typename SideStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename PointStrategy,
        typename RobustPolicy,
        typename Strategy
    >
    static inline geometry::strategy::buffer::result_code apply(RingInput const& ring,
            Collection& collection,
            DistanceStrategy const& distance,
            SideStrategy const& side_strategy,
            JoinStrategy const& join_strategy,
            EndStrategy const& end_strategy,
            PointStrategy const& point_strategy,
            RobustPolicy const& robust_policy,
            Strategy const& strategy) // side strategy
    {
        collection.start_new_ring(distance.negative());
        geometry::strategy::buffer::result_code const code
            = buffer_inserter_ring<RingInput, RingOutput>::apply(ring,
                collection, distance,
                side_strategy, join_strategy, end_strategy, point_strategy,
                robust_policy, strategy);
        collection.finish_ring(code, ring, false, false);
        return code;
    }
};

template
<
    typename Linestring,
    typename Polygon
>
struct buffer_inserter<linestring_tag, Linestring, Polygon>
{
    typedef typename ring_type<Polygon>::type output_ring_type;
    typedef typename point_type<output_ring_type>::type output_point_type;
    typedef typename point_type<Linestring>::type input_point_type;

    template
    <
        typename Collection,
        typename Iterator,
        typename DistanceStrategy,
        typename SideStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename RobustPolicy,
        typename Strategy
    >
    static inline geometry::strategy::buffer::result_code iterate(Collection& collection,
                Iterator begin, Iterator end,
                geometry::strategy::buffer::buffer_side_selector side,
                DistanceStrategy const& distance_strategy,
                SideStrategy const& side_strategy,
                JoinStrategy const& join_strategy,
                EndStrategy const& end_strategy,
                RobustPolicy const& robust_policy,
                Strategy const& strategy, // side strategy
                output_point_type& first_p1)
    {
        input_point_type const& ultimate_point = *(end - 1);
        input_point_type const& penultimate_point = *(end - 2);

        // For the end-cap, we need to have the last perpendicular point on the
        // other side of the linestring. If it is the second pass (right),
        // we have it already from the first phase (left).
        // But for the first pass, we have to generate it
        output_point_type reverse_p1;
        if (side == geometry::strategy::buffer::buffer_side_right)
        {
            reverse_p1 = first_p1;
        }
        else
        {
            std::vector<output_point_type> generated_side;
            geometry::strategy::buffer::result_code code
                = side_strategy.apply(ultimate_point, penultimate_point,
                    geometry::strategy::buffer::buffer_side_right,
                    distance_strategy, generated_side);
            if (code != geometry::strategy::buffer::result_normal)
            {
                // No output or numerical error
                return code;
            }
            reverse_p1 = generated_side.front();
        }

        output_point_type first_p2, last_p1, last_p2;

        geometry::strategy::buffer::result_code result
            = detail::buffer::buffer_range<output_ring_type>::iterate(collection,
                begin, end, side,
                distance_strategy, side_strategy, join_strategy, end_strategy,
                robust_policy, strategy,
                true, first_p1, first_p2, last_p1, last_p2);

        if (result == geometry::strategy::buffer::result_normal)
        {
            std::vector<output_point_type> range_out;
            end_strategy.apply(penultimate_point, last_p2, ultimate_point, reverse_p1,
                               side, distance_strategy, range_out);
            collection.add_endcap(end_strategy, range_out, ultimate_point);
        }
        return result;
    }

    template
    <
        typename Collection,
        typename DistanceStrategy,
        typename SideStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename PointStrategy,
        typename RobustPolicy,
        typename Strategy
    >
    static inline geometry::strategy::buffer::result_code apply(Linestring const& linestring,
            Collection& collection,
            DistanceStrategy const& distance,
            SideStrategy const& side_strategy,
            JoinStrategy const& join_strategy,
            EndStrategy const& end_strategy,
            PointStrategy const& point_strategy,
            RobustPolicy const& robust_policy,
            Strategy const& strategy) // side strategy
    {
        Linestring simplified;
        detail::buffer::simplify_input(linestring, distance, simplified);

        geometry::strategy::buffer::result_code code = geometry::strategy::buffer::result_no_output;
        std::size_t n = boost::size(simplified);
        if (n > 1)
        {
            collection.start_new_ring(false);
            output_point_type first_p1;
            code = iterate(collection,
                    boost::begin(simplified), boost::end(simplified),
                    geometry::strategy::buffer::buffer_side_left,
                    distance, side_strategy, join_strategy, end_strategy,
                    robust_policy, strategy,
                    first_p1);

            if (code == geometry::strategy::buffer::result_normal)
            {
                code = iterate(collection,
                        boost::rbegin(simplified), boost::rend(simplified),
                        geometry::strategy::buffer::buffer_side_right,
                        distance, side_strategy, join_strategy, end_strategy,
                        robust_policy, strategy,
                        first_p1);
            }
            collection.finish_ring(code);
        }
        if (code == geometry::strategy::buffer::result_no_output && n >= 1)
        {
            // Use point_strategy to buffer degenerated linestring
            detail::buffer::buffer_point<output_point_type>
                (
                    geometry::range::front(simplified),
                    collection, distance, point_strategy
                );
        }
        return code;
    }
};


template
<
    typename PolygonInput,
    typename PolygonOutput
>
struct buffer_inserter<polygon_tag, PolygonInput, PolygonOutput>
{
private:
    typedef typename ring_type<PolygonInput>::type input_ring_type;
    typedef typename ring_type<PolygonOutput>::type output_ring_type;

    typedef buffer_inserter_ring<input_ring_type, output_ring_type> policy;


    template
    <
        typename Iterator,
        typename Collection,
        typename DistanceStrategy,
        typename SideStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename PointStrategy,
        typename RobustPolicy,
        typename Strategy
    >
    static inline
    void iterate(Iterator begin, Iterator end,
            Collection& collection,
            DistanceStrategy const& distance,
            SideStrategy const& side_strategy,
            JoinStrategy const& join_strategy,
            EndStrategy const& end_strategy,
            PointStrategy const& point_strategy,
            RobustPolicy const& robust_policy,
            Strategy const& strategy, // side strategy
            bool is_interior)
    {
        for (Iterator it = begin; it != end; ++it)
        {
            // For exterior rings, it deflates if distance is negative.
            // For interior rings, it is vice versa
            bool const deflate = is_interior
                    ? ! distance.negative()
                    : distance.negative();

            collection.start_new_ring(deflate);
            geometry::strategy::buffer::result_code const code
                    = policy::apply(*it, collection, distance, side_strategy,
                    join_strategy, end_strategy, point_strategy,
                    robust_policy, strategy);

            collection.finish_ring(code, *it, is_interior, false);
        }
    }

    template
    <
        typename InteriorRings,
        typename Collection,
        typename DistanceStrategy,
        typename SideStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename PointStrategy,
        typename RobustPolicy,
        typename Strategy
    >
    static inline
    void apply_interior_rings(InteriorRings const& interior_rings,
            Collection& collection,
            DistanceStrategy const& distance,
            SideStrategy const& side_strategy,
            JoinStrategy const& join_strategy,
            EndStrategy const& end_strategy,
            PointStrategy const& point_strategy,
            RobustPolicy const& robust_policy,
            Strategy const& strategy) // side strategy
    {
        iterate(boost::begin(interior_rings), boost::end(interior_rings),
            collection, distance, side_strategy,
            join_strategy, end_strategy, point_strategy,
            robust_policy, strategy, true);
    }

public:
    template
    <
        typename Collection,
        typename DistanceStrategy,
        typename SideStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename PointStrategy,
        typename RobustPolicy,
        typename Strategy
    >
    static inline void apply(PolygonInput const& polygon,
            Collection& collection,
            DistanceStrategy const& distance,
            SideStrategy const& side_strategy,
            JoinStrategy const& join_strategy,
            EndStrategy const& end_strategy,
            PointStrategy const& point_strategy,
            RobustPolicy const& robust_policy,
            Strategy const& strategy) // side strategy
    {
        {
            collection.start_new_ring(distance.negative());

            geometry::strategy::buffer::result_code const code
                = policy::apply(exterior_ring(polygon), collection,
                    distance, side_strategy,
                    join_strategy, end_strategy, point_strategy,
                    robust_policy, strategy);

            collection.finish_ring(code, exterior_ring(polygon), false,
                    geometry::num_interior_rings(polygon) > 0u);
        }

        apply_interior_rings(interior_rings(polygon),
                collection, distance, side_strategy,
                join_strategy, end_strategy, point_strategy,
                robust_policy, strategy);
    }
};


template
<
    typename Multi,
    typename PolygonOutput
>
struct buffer_inserter<multi_tag, Multi, PolygonOutput>
    : public detail::buffer::buffer_multi
             <
                Multi,
                PolygonOutput,
                dispatch::buffer_inserter
                <
                    typename single_tag_of
                                <
                                    typename tag<Multi>::type
                                >::type,
                    typename boost::range_value<Multi const>::type,
                    typename geometry::ring_type<PolygonOutput>::type
                >
            >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace buffer
{

template
<
    typename GeometryOutput,
    typename GeometryInput,
    typename OutputIterator,
    typename DistanceStrategy,
    typename SideStrategy,
    typename JoinStrategy,
    typename EndStrategy,
    typename PointStrategy,
    typename IntersectionStrategy,
    typename RobustPolicy,
    typename VisitPiecesPolicy
>
inline void buffer_inserter(GeometryInput const& geometry_input, OutputIterator out,
        DistanceStrategy const& distance_strategy,
        SideStrategy const& side_strategy,
        JoinStrategy const& join_strategy,
        EndStrategy const& end_strategy,
        PointStrategy const& point_strategy,
        IntersectionStrategy const& intersection_strategy,
        RobustPolicy const& robust_policy,
        VisitPiecesPolicy& visit_pieces_policy
    )
{
    boost::ignore_unused(visit_pieces_policy);

    typedef detail::buffer::buffered_piece_collection
    <
        typename geometry::ring_type<GeometryOutput>::type,
        IntersectionStrategy,
        DistanceStrategy,
        RobustPolicy
    > collection_type;
    collection_type collection(intersection_strategy, distance_strategy, robust_policy);
    collection_type const& const_collection = collection;

    bool const areal = boost::is_same
        <
            typename tag_cast<typename tag<GeometryInput>::type, areal_tag>::type,
            areal_tag
        >::type::value;

    dispatch::buffer_inserter
        <
            typename tag_cast
                <
                    typename tag<GeometryInput>::type,
                    multi_tag
                >::type,
            GeometryInput,
            GeometryOutput
        >::apply(geometry_input, collection,
            distance_strategy, side_strategy, join_strategy,
            end_strategy, point_strategy,
            robust_policy, intersection_strategy.get_side_strategy());

    collection.get_turns();
    collection.classify_turns();
    if (BOOST_GEOMETRY_CONDITION(areal))
    {
        collection.check_remaining_points();
    }

    // Visit the piece collection. This does nothing (by default), but
    // optionally a debugging tool can be attached (e.g. console or svg),
    // or the piece collection can be unit-tested
    // phase 0: turns (before discarded)
    visit_pieces_policy.apply(const_collection, 0);

    collection.discard_rings();
    collection.block_turns();
    collection.enrich();

    // phase 1: turns (after enrichment/clustering)
    visit_pieces_policy.apply(const_collection, 1);

    collection.traverse();

    // Reverse all offsetted rings / traversed rings if:
    // - they were generated on the negative side (deflate) of polygons
    // - the output is counter clockwise
    // and avoid reversing twice
    bool reverse = distance_strategy.negative() && areal;
    if (BOOST_GEOMETRY_CONDITION(
            geometry::point_order<GeometryOutput>::value == counterclockwise))
    {
        reverse = ! reverse;
    }
    if (reverse)
    {
        collection.reverse();
    }

    if (BOOST_GEOMETRY_CONDITION(distance_strategy.negative() && areal))
    {
        collection.discard_nonintersecting_deflated_rings();
    }

    collection.template assign<GeometryOutput>(out);

    // Visit collection again
    // phase 2: rings (after traversing)
    visit_pieces_policy.apply(const_collection, 2);
}

template
<
    typename GeometryOutput,
    typename GeometryInput,
    typename OutputIterator,
    typename DistanceStrategy,
    typename SideStrategy,
    typename JoinStrategy,
    typename EndStrategy,
    typename PointStrategy,
    typename IntersectionStrategy,
    typename RobustPolicy
>
inline void buffer_inserter(GeometryInput const& geometry_input, OutputIterator out,
        DistanceStrategy const& distance_strategy,
        SideStrategy const& side_strategy,
        JoinStrategy const& join_strategy,
        EndStrategy const& end_strategy,
        PointStrategy const& point_strategy,
        IntersectionStrategy const& intersection_strategy,
        RobustPolicy const& robust_policy)
{
    detail::buffer::visit_pieces_default_policy visitor;
    buffer_inserter<GeometryOutput>(geometry_input, out,
        distance_strategy, side_strategy, join_strategy,
        end_strategy, point_strategy,
        intersection_strategy, robust_policy, visitor);
}
#endif // DOXYGEN_NO_DETAIL

}} // namespace detail::buffer

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFER_INSERTER_HPP

/* buffer_inserter.hpp
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
*/