// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2020 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017-2021.
// Modifications copyright (c) 2017-2021 Oracle and/or its affiliates.
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
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/detail/direction_code.hpp>
#include <boost/geometry/algorithms/detail/buffer/buffered_piece_collection.hpp>
#include <boost/geometry/algorithms/detail/buffer/line_line_intersection.hpp>

#include <boost/geometry/algorithms/num_interior_rings.hpp>
#include <boost/geometry/algorithms/simplify.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>

#include <boost/geometry/strategies/buffer.hpp>
#include <boost/geometry/strategies/side.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/type_traits.hpp>

#include <boost/geometry/views/detail/closed_clockwise_view.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace buffer
{

template <typename Range, typename DistanceStrategy, typename Strategies>
inline void simplify_input(Range const& range,
        DistanceStrategy const& distance,
        Range& simplified,
        Strategies const& strategies)
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

    geometry::detail::simplify::simplify_range<2>::apply(range,
        simplified, distance.simplify_distance(),
        detail::simplify::douglas_peucker(),
        strategies);

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
        typename SegmentStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename RobustPolicy,
        typename Strategies
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
            SegmentStrategy const& segment_strategy,
            JoinStrategy const& join_strategy,
            EndStrategy const& end_strategy,
            RobustPolicy const& ,
            Strategies const& strategies)
    {
        geometry::strategy::buffer::join_selector const join
                = get_join_type(penultimate_input, previous_input, input,
                                strategies);

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
                    output_point_type intersection_point;
                    if (line_line_intersection::apply(prev_perp1, prev_perp2,
                                                      perp1, perp2, previous_input,
                                                      segment_strategy.equidistant(),
                                                      intersection_point))
                    {
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
                }
                break;
        }
    }

    // Returns true if collinear point p2 continues after p0 and p1.
    // If it turns back (spike), it returns false.
    static inline bool same_direction(output_point_type const& p0,
            output_point_type const& p1,
            output_point_type const& p2)
    {
        typedef typename cs_tag<output_point_type>::type cs_tag;
        return direction_code<cs_tag>(p0, p1, p2) == 1;
    }

    template <typename Strategies>
    static inline geometry::strategy::buffer::join_selector get_join_type(
            output_point_type const& p0,
            output_point_type const& p1,
            output_point_type const& p2,
            Strategies const& strategies)
    {
        int const side = strategies.side().apply(p0, p1, p2);
        return side == -1 ? geometry::strategy::buffer::join_convex
            :  side == 1  ? geometry::strategy::buffer::join_concave
            :  same_direction(p0, p1, p2) ? geometry::strategy::buffer::join_continue
            : geometry::strategy::buffer::join_spike;
    }

    template
    <
        typename Collection,
        typename Iterator,
        typename DistanceStrategy,
        typename SegmentStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename RobustPolicy,
        typename Strategies
    >
    static inline geometry::strategy::buffer::result_code iterate(Collection& collection,
                Iterator begin, Iterator end,
                geometry::strategy::buffer::buffer_side_selector side,
                DistanceStrategy const& distance_strategy,
                SegmentStrategy const& segment_strategy,
                JoinStrategy const& join_strategy,
                EndStrategy const& end_strategy,
                RobustPolicy const& robust_policy,
                Strategies const& strategies,
                bool linear,
                output_point_type& first_p1,
                output_point_type& first_p2,
                output_point_type& last_p1,
                output_point_type& last_p2)
    {
        boost::ignore_unused(segment_strategy);

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
                = segment_strategy.apply(*prev, *it, side,
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
                        distance_strategy, segment_strategy, join_strategy, end_strategy,
                        robust_policy, strategies);
            }

            collection.add_side_piece(*prev, *it, generated_side, first);

            if (first && mark_flat)
            {
                collection.mark_flat_start(*prev);
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
            collection.mark_flat_end(ultimate_point);
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
        typename SegmentStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename PointStrategy,
        typename RobustPolicy,
        typename Strategies
    >
    static inline void apply(Multi const& multi,
            Collection& collection,
            DistanceStrategy const& distance_strategy,
            SegmentStrategy const& segment_strategy,
            JoinStrategy const& join_strategy,
            EndStrategy const& end_strategy,
            PointStrategy const& point_strategy,
            RobustPolicy const& robust_policy,
            Strategies const& strategies)
    {
        for (typename boost::range_iterator<Multi const>::type
                it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it, collection,
                distance_strategy, segment_strategy,
                join_strategy, end_strategy, point_strategy,
                robust_policy, strategies);
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
        typename SegmentStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename PointStrategy,
        typename RobustPolicy,
        typename Strategies
    >
    static inline void apply(Point const& point, Collection& collection,
            DistanceStrategy const& distance_strategy,
            SegmentStrategy const& ,
            JoinStrategy const& ,
            EndStrategy const& ,
            PointStrategy const& point_strategy,
            RobustPolicy const& ,
            Strategies const& )
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
        typename SegmentStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename RobustPolicy,
        typename Strategies
    >
    static inline geometry::strategy::buffer::result_code iterate(Collection& collection,
                Iterator begin, Iterator end,
                geometry::strategy::buffer::buffer_side_selector side,
                DistanceStrategy const& distance_strategy,
                SegmentStrategy const& segment_strategy,
                JoinStrategy const& join_strategy,
                EndStrategy const& end_strategy,
                RobustPolicy const& robust_policy,
                Strategies const& strategies)
    {
        output_point_type first_p1, first_p2, last_p1, last_p2;

        typedef detail::buffer::buffer_range<RingOutput> buffer_range;

        geometry::strategy::buffer::result_code result
            = buffer_range::iterate(collection, begin, end,
                side,
                distance_strategy, segment_strategy, join_strategy, end_strategy,
                robust_policy, strategies,
                false, first_p1, first_p2, last_p1, last_p2);

        // Generate closing join
        if (result == geometry::strategy::buffer::result_normal)
        {
            buffer_range::add_join(collection,
                *(end - 2),
                *(end - 1), last_p1, last_p2,
                *(begin + 1), first_p1, first_p2,
                side,
                distance_strategy, segment_strategy, join_strategy, end_strategy,
                robust_policy, strategies);
        }

        // Buffer is closed automatically by last closing corner
        return result;
    }

    template
    <
        typename Collection,
        typename DistanceStrategy,
        typename SegmentStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename PointStrategy,
        typename RobustPolicy,
        typename Strategies
    >
    static inline geometry::strategy::buffer::result_code apply(RingInput const& ring,
            Collection& collection,
            DistanceStrategy const& distance,
            SegmentStrategy const& segment_strategy,
            JoinStrategy const& join_strategy,
            EndStrategy const& end_strategy,
            PointStrategy const& point_strategy,
            RobustPolicy const& robust_policy,
            Strategies const& strategies)
    {
        RingInput simplified;
        detail::buffer::simplify_input(ring, distance, simplified, strategies);

        geometry::strategy::buffer::result_code code = geometry::strategy::buffer::result_no_output;

        std::size_t n = boost::size(simplified);
        std::size_t const min_points = core_detail::closure::minimum_ring_size
            <
                geometry::closure<RingInput>::value
            >::value;

        if (n >= min_points)
        {
            detail::closed_clockwise_view<RingInput const> view(simplified);
            if (distance.negative())
            {
                // Walk backwards (rings will be reversed afterwards)
                code = iterate(collection, boost::rbegin(view), boost::rend(view),
                        geometry::strategy::buffer::buffer_side_right,
                        distance, segment_strategy, join_strategy, end_strategy,
                        robust_policy, strategies);
            }
            else
            {
                code = iterate(collection, boost::begin(view), boost::end(view),
                        geometry::strategy::buffer::buffer_side_left,
                        distance, segment_strategy, join_strategy, end_strategy,
                        robust_policy, strategies);
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
        typename SegmentStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename PointStrategy,
        typename RobustPolicy,
        typename Strategies
    >
    static inline geometry::strategy::buffer::result_code apply(RingInput const& ring,
            Collection& collection,
            DistanceStrategy const& distance,
            SegmentStrategy const& segment_strategy,
            JoinStrategy const& join_strategy,
            EndStrategy const& end_strategy,
            PointStrategy const& point_strategy,
            RobustPolicy const& robust_policy,
            Strategies const& strategies)
    {
        collection.start_new_ring(distance.negative());
        geometry::strategy::buffer::result_code const code
            = buffer_inserter_ring<RingInput, RingOutput>::apply(ring,
                collection, distance,
                segment_strategy, join_strategy, end_strategy, point_strategy,
                robust_policy, strategies);
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
        typename SegmentStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename RobustPolicy,
        typename Strategies
    >
    static inline geometry::strategy::buffer::result_code iterate(Collection& collection,
                Iterator begin, Iterator end,
                geometry::strategy::buffer::buffer_side_selector side,
                DistanceStrategy const& distance_strategy,
                SegmentStrategy const& segment_strategy,
                JoinStrategy const& join_strategy,
                EndStrategy const& end_strategy,
                RobustPolicy const& robust_policy,
                Strategies const& strategies,
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
                = segment_strategy.apply(ultimate_point, penultimate_point,
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
                distance_strategy, segment_strategy, join_strategy, end_strategy,
                robust_policy, strategies,
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
        typename SegmentStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename PointStrategy,
        typename RobustPolicy,
        typename Strategies
    >
    static inline geometry::strategy::buffer::result_code apply(Linestring const& linestring,
            Collection& collection,
            DistanceStrategy const& distance,
            SegmentStrategy const& segment_strategy,
            JoinStrategy const& join_strategy,
            EndStrategy const& end_strategy,
            PointStrategy const& point_strategy,
            RobustPolicy const& robust_policy,
            Strategies const& strategies)
    {
        Linestring simplified;
        detail::buffer::simplify_input(linestring, distance, simplified, strategies);

        geometry::strategy::buffer::result_code code = geometry::strategy::buffer::result_no_output;
        std::size_t n = boost::size(simplified);
        if (n > 1)
        {
            collection.start_new_ring(false);
            output_point_type first_p1;
            code = iterate(collection,
                    boost::begin(simplified), boost::end(simplified),
                    geometry::strategy::buffer::buffer_side_left,
                    distance, segment_strategy, join_strategy, end_strategy,
                    robust_policy, strategies,
                    first_p1);

            if (code == geometry::strategy::buffer::result_normal)
            {
                code = iterate(collection,
                        boost::rbegin(simplified), boost::rend(simplified),
                        geometry::strategy::buffer::buffer_side_right,
                        distance, segment_strategy, join_strategy, end_strategy,
                        robust_policy, strategies,
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
        typename SegmentStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename PointStrategy,
        typename RobustPolicy,
        typename Strategies
    >
    static inline
    void iterate(Iterator begin, Iterator end,
            Collection& collection,
            DistanceStrategy const& distance,
            SegmentStrategy const& segment_strategy,
            JoinStrategy const& join_strategy,
            EndStrategy const& end_strategy,
            PointStrategy const& point_strategy,
            RobustPolicy const& robust_policy,
            Strategies const& strategies,
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
                    = policy::apply(*it, collection, distance, segment_strategy,
                    join_strategy, end_strategy, point_strategy,
                    robust_policy, strategies);

            collection.finish_ring(code, *it, is_interior, false);
        }
    }

    template
    <
        typename InteriorRings,
        typename Collection,
        typename DistanceStrategy,
        typename SegmentStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename PointStrategy,
        typename RobustPolicy,
        typename Strategies
    >
    static inline
    void apply_interior_rings(InteriorRings const& interior_rings,
            Collection& collection,
            DistanceStrategy const& distance,
            SegmentStrategy const& segment_strategy,
            JoinStrategy const& join_strategy,
            EndStrategy const& end_strategy,
            PointStrategy const& point_strategy,
            RobustPolicy const& robust_policy,
            Strategies const& strategies)
    {
        iterate(boost::begin(interior_rings), boost::end(interior_rings),
            collection, distance, segment_strategy,
            join_strategy, end_strategy, point_strategy,
            robust_policy, strategies, true);
    }

public:
    template
    <
        typename Collection,
        typename DistanceStrategy,
        typename SegmentStrategy,
        typename JoinStrategy,
        typename EndStrategy,
        typename PointStrategy,
        typename RobustPolicy,
        typename Strategies
    >
    static inline void apply(PolygonInput const& polygon,
            Collection& collection,
            DistanceStrategy const& distance,
            SegmentStrategy const& segment_strategy,
            JoinStrategy const& join_strategy,
            EndStrategy const& end_strategy,
            PointStrategy const& point_strategy,
            RobustPolicy const& robust_policy,
            Strategies const& strategies)
    {
        {
            collection.start_new_ring(distance.negative());

            geometry::strategy::buffer::result_code const code
                = policy::apply(exterior_ring(polygon), collection,
                    distance, segment_strategy,
                    join_strategy, end_strategy, point_strategy,
                    robust_policy, strategies);

            collection.finish_ring(code, exterior_ring(polygon), false,
                    geometry::num_interior_rings(polygon) > 0u);
        }

        apply_interior_rings(interior_rings(polygon),
                collection, distance, segment_strategy,
                join_strategy, end_strategy, point_strategy,
                robust_policy, strategies);
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
    typename SegmentStrategy,
    typename JoinStrategy,
    typename EndStrategy,
    typename PointStrategy,
    typename Strategies,
    typename RobustPolicy,
    typename VisitPiecesPolicy
>
inline void buffer_inserter(GeometryInput const& geometry_input, OutputIterator out,
        DistanceStrategy const& distance_strategy,
        SegmentStrategy const& segment_strategy,
        JoinStrategy const& join_strategy,
        EndStrategy const& end_strategy,
        PointStrategy const& point_strategy,
        Strategies const& strategies,
        RobustPolicy const& robust_policy,
        VisitPiecesPolicy& visit_pieces_policy
    )
{
    boost::ignore_unused(visit_pieces_policy);

    typedef detail::buffer::buffered_piece_collection
    <
        typename geometry::ring_type<GeometryOutput>::type,
        Strategies,
        DistanceStrategy,
        RobustPolicy
    > collection_type;
    collection_type collection(strategies, distance_strategy, robust_policy);
    collection_type const& const_collection = collection;

    bool const areal = util::is_areal<GeometryInput>::value;

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
                 distance_strategy, segment_strategy, join_strategy,
                 end_strategy, point_strategy,
                 robust_policy, strategies);

    collection.get_turns();
    if (BOOST_GEOMETRY_CONDITION(areal))
    {
        collection.check_turn_in_original();
    }

    collection.verify_turns();

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

    if (BOOST_GEOMETRY_CONDITION(areal))
    {
        collection.deflate_check_turns();
    }

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
    typename SegmentStrategy,
    typename JoinStrategy,
    typename EndStrategy,
    typename PointStrategy,
    typename Strategies,
    typename RobustPolicy
>
inline void buffer_inserter(GeometryInput const& geometry_input, OutputIterator out,
        DistanceStrategy const& distance_strategy,
        SegmentStrategy const& segment_strategy,
        JoinStrategy const& join_strategy,
        EndStrategy const& end_strategy,
        PointStrategy const& point_strategy,
        Strategies const& strategies,
        RobustPolicy const& robust_policy)
{
    detail::buffer::visit_pieces_default_policy visitor;
    buffer_inserter<GeometryOutput>(geometry_input, out,
        distance_strategy, segment_strategy, join_strategy,
        end_strategy, point_strategy,
        strategies, robust_policy, visitor);
}
#endif // DOXYGEN_NO_DETAIL

}} // namespace detail::buffer

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFER_INSERTER_HPP

/* buffer_inserter.hpp
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
*/