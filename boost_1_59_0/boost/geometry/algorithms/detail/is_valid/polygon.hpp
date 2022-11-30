// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_POLYGON_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_POLYGON_HPP

#include <cstddef>
#ifdef BOOST_GEOMETRY_TEST_DEBUG
#include <iostream>
#endif // BOOST_GEOMETRY_TEST_DEBUG

#include <algorithm>
#include <deque>
#include <iterator>
#include <set>
#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/range.hpp>
#include <boost/geometry/util/sequence.hpp>

#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/iterators/point_iterator.hpp>

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/disjoint.hpp>
#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/algorithms/num_interior_rings.hpp>
#include <boost/geometry/algorithms/validity_failure_type.hpp>
#include <boost/geometry/algorithms/detail/point_on_border.hpp>
#include <boost/geometry/algorithms/within.hpp>

#include <boost/geometry/algorithms/detail/partition.hpp>

#include <boost/geometry/algorithms/detail/is_valid/complement_graph.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_valid_self_turns.hpp>
#include <boost/geometry/algorithms/detail/is_valid/is_acceptable_turn.hpp>
#include <boost/geometry/algorithms/detail/is_valid/ring.hpp>

#include <boost/geometry/algorithms/detail/is_valid/debug_print_turns.hpp>
#include <boost/geometry/algorithms/detail/is_valid/debug_validity_phase.hpp>
#include <boost/geometry/algorithms/detail/is_valid/debug_complement_graph.hpp>

#include <boost/geometry/algorithms/dispatch/is_valid.hpp>


// TEMP
#include <boost/geometry/strategies/envelope/cartesian.hpp>
#include <boost/geometry/strategies/envelope/geographic.hpp>
#include <boost/geometry/strategies/envelope/spherical.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_valid
{


template <typename Polygon, bool CheckRingValidityOnly = false>
class is_valid_polygon
{
protected:

    template <typename VisitPolicy, typename Strategy>
    struct is_invalid_ring
    {
        is_invalid_ring(VisitPolicy& policy, Strategy const& strategy)
            : m_policy(policy)
            , m_strategy(strategy)
        {}

        template <typename Ring>
        inline bool operator()(Ring const& ring) const
        {
            return ! detail::is_valid::is_valid_ring
                <
                    Ring, false, true
                >::apply(ring, m_policy, m_strategy);
        }

        VisitPolicy& m_policy;
        Strategy const& m_strategy;
    };

    template <typename InteriorRings, typename VisitPolicy, typename Strategy>
    static bool has_valid_interior_rings(InteriorRings const& interior_rings,
                                         VisitPolicy& visitor,
                                         Strategy const& strategy)
    {
        return std::none_of(boost::begin(interior_rings), 
                            boost::end(interior_rings),
                            is_invalid_ring<VisitPolicy, Strategy>(visitor, strategy));
    }

    struct has_valid_rings
    {
        template <typename VisitPolicy, typename Strategy>
        static inline bool apply(Polygon const& polygon,
                                 VisitPolicy& visitor,
                                 Strategy const& strategy)
        {
            typedef debug_validity_phase<Polygon> debug_phase;
            typedef typename ring_type<Polygon>::type ring_type;

            // check validity of exterior ring
            debug_phase::apply(1);

            if (! detail::is_valid::is_valid_ring
                     <
                         ring_type,
                         false // do not check self intersections
                     >::apply(exterior_ring(polygon), visitor, strategy))
            {
                return false;
            }

            // check validity of interior rings
            debug_phase::apply(2);

            return has_valid_interior_rings(geometry::interior_rings(polygon),
                                            visitor,
                                            strategy);
        }
    };


    // Iterator value_type is a Ring or Polygon
    template <typename Iterator, typename Box>
    struct partition_item
    {
        explicit partition_item(Iterator it)
            : m_it(it)
            , m_is_initialized(false)
        {}

        Iterator get() const
        {
            return m_it;
        }

        template <typename EnvelopeStrategy>
        Box const& get_envelope(EnvelopeStrategy const& strategy) const
        {
            if (! m_is_initialized)
            {
                m_box = geometry::return_envelope<Box>(*m_it, strategy);
                m_is_initialized = true;
            }
            return m_box;
        }

    private:
        Iterator m_it;
        mutable Box m_box;
        mutable bool m_is_initialized;
    };

    // structs for partition -- start
    template <typename Strategy>
    struct expand_box
    {
        explicit expand_box(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename Iterator>
        inline void apply(Box& total, partition_item<Iterator, Box> const& item) const
        {
            geometry::expand(total,
                             item.get_envelope(m_strategy),
                             m_strategy);
        }

        Strategy const& m_strategy;
    };

    template <typename Strategy>
    struct overlaps_box
    {
        explicit overlaps_box(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename Iterator>
        inline bool apply(Box const& box, partition_item<Iterator, Box> const& item) const
        {
            return ! geometry::disjoint(item.get_envelope(m_strategy),
                                        box,
                                        m_strategy);
        }

        Strategy const& m_strategy;
    };


    template <typename Strategy>
    struct item_visitor_type
    {
        bool items_overlap;
        Strategy const& m_strategy;

        explicit item_visitor_type(Strategy const& strategy)
            : items_overlap(false)
            , m_strategy(strategy)
        {}

        template <typename Iterator, typename Box>
        inline bool apply(partition_item<Iterator, Box> const& item1,
                          partition_item<Iterator, Box> const& item2)
        {
            typedef util::type_sequence
                <
                    geometry::de9im::static_mask<'T'>,
                    geometry::de9im::static_mask<'*', 'T'>,
                    geometry::de9im::static_mask<'*', '*', '*', 'T'>
                > relate_mask_t;

            if ( ! items_overlap
              && geometry::relate(*item1.get(), *item2.get(), relate_mask_t(), m_strategy) )
            {
                items_overlap = true;
                return false; // interrupt
            }
            return true;
        }
    };
    // structs for partition -- end


    template
    <
        typename RingIterator,
        typename ExteriorRing,
        typename TurnIterator,
        typename VisitPolicy,
        typename Strategy
    >
    static inline bool are_holes_inside(RingIterator rings_first,
                                        RingIterator rings_beyond,
                                        ExteriorRing const& exterior_ring,
                                        TurnIterator turns_first,
                                        TurnIterator turns_beyond,
                                        VisitPolicy& visitor,
                                        Strategy const& strategy)
    {
        boost::ignore_unused(visitor);

        // collect the interior ring indices that have turns with the
        // exterior ring
        std::set<signed_size_type> ring_indices;
        for (TurnIterator tit = turns_first; tit != turns_beyond; ++tit)
        {
            if (tit->operations[0].seg_id.ring_index == -1)
            {
                BOOST_GEOMETRY_ASSERT(tit->operations[1].seg_id.ring_index != -1);
                ring_indices.insert(tit->operations[1].seg_id.ring_index);
            }
            else if (tit->operations[1].seg_id.ring_index == -1)
            {
                BOOST_GEOMETRY_ASSERT(tit->operations[0].seg_id.ring_index != -1);
                ring_indices.insert(tit->operations[0].seg_id.ring_index);
            }
        }

        signed_size_type ring_index = 0;
        for (RingIterator it = rings_first; it != rings_beyond;
             ++it, ++ring_index)
        {
            // do not examine interior rings that have turns with the
            // exterior ring
            if (ring_indices.find(ring_index) == ring_indices.end()
                && ! geometry::covered_by(range::front(*it), exterior_ring, strategy))
            {
                return visitor.template apply<failure_interior_rings_outside>();
            }
        }

        // collect all rings (exterior and/or interior) that have turns
        for (TurnIterator tit = turns_first; tit != turns_beyond; ++tit)
        {
            ring_indices.insert(tit->operations[0].seg_id.ring_index);
            ring_indices.insert(tit->operations[1].seg_id.ring_index);
        }

        typedef geometry::model::box<typename point_type<Polygon>::type> box_type;
        typedef partition_item<RingIterator, box_type> item_type;

        // put iterators for interior rings without turns in a vector
        std::vector<item_type> ring_iterators;
        ring_index = 0;
        for (RingIterator it = rings_first; it != rings_beyond;
             ++it, ++ring_index)
        {
            if (ring_indices.find(ring_index) == ring_indices.end())
            {
                ring_iterators.push_back(item_type(it));
            }
        }

        // call partition to check if interior rings are disjoint from
        // each other
        item_visitor_type<Strategy> item_visitor(strategy);

        geometry::partition
            <
                box_type
            >::apply(ring_iterators, item_visitor,
                     expand_box<Strategy>(strategy),
                     overlaps_box<Strategy>(strategy));

        if (item_visitor.items_overlap)
        {
            return visitor.template apply<failure_nested_interior_rings>();
        }
        else
        {
            return visitor.template apply<no_failure>();
        }
    }

    template
    <
        typename InteriorRings,
        typename ExteriorRing,
        typename TurnIterator,
        typename VisitPolicy,
        typename Strategy
    >
    static inline bool are_holes_inside(InteriorRings const& interior_rings,
                                        ExteriorRing const& exterior_ring,
                                        TurnIterator first,
                                        TurnIterator beyond,
                                        VisitPolicy& visitor,
                                        Strategy const& strategy)
    {
        return are_holes_inside(boost::begin(interior_rings),
                                boost::end(interior_rings),
                                exterior_ring,
                                first,
                                beyond,
                                visitor,
                                strategy);
    }

    struct has_holes_inside
    {    
        template <typename TurnIterator, typename VisitPolicy, typename Strategy>
        static inline bool apply(Polygon const& polygon,
                                 TurnIterator first,
                                 TurnIterator beyond,
                                 VisitPolicy& visitor,
                                 Strategy const& strategy)
        {
            return are_holes_inside(geometry::interior_rings(polygon),
                                    geometry::exterior_ring(polygon),
                                    first,
                                    beyond,
                                    visitor,
                                    strategy);
        }
    };




    struct has_connected_interior
    {
        template <typename TurnIterator, typename VisitPolicy, typename Strategy>
        static inline bool apply(Polygon const& polygon,
                                 TurnIterator first,
                                 TurnIterator beyond,
                                 VisitPolicy& visitor,
                                 Strategy const& )
        {
            boost::ignore_unused(visitor);

            typedef typename std::iterator_traits
                <
                    TurnIterator
                >::value_type turn_type;
            typedef complement_graph
                <
                    typename turn_type::point_type,
                    typename Strategy::cs_tag
                > graph;

            graph g(geometry::num_interior_rings(polygon) + 1);
            for (TurnIterator tit = first; tit != beyond; ++tit)
            {
                typename graph::vertex_handle v1 = g.add_vertex
                    ( tit->operations[0].seg_id.ring_index + 1 );
                typename graph::vertex_handle v2 = g.add_vertex
                    ( tit->operations[1].seg_id.ring_index + 1 );
                typename graph::vertex_handle vip = g.add_vertex(tit->point);

                g.add_edge(v1, vip);
                g.add_edge(v2, vip);
            }

#ifdef BOOST_GEOMETRY_TEST_DEBUG
            debug_print_complement_graph(std::cout, g);
#endif // BOOST_GEOMETRY_TEST_DEBUG

            if (g.has_cycles())
            {
                return visitor.template apply<failure_disconnected_interior>();
            }
            else
            {
                return visitor.template apply<no_failure>();
            }
        }
    };

public:
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Polygon const& polygon,
                             VisitPolicy& visitor,
                             Strategy const& strategy)
    {
        if (! has_valid_rings::apply(polygon, visitor, strategy))
        {
            return false;
        }

        if (BOOST_GEOMETRY_CONDITION(CheckRingValidityOnly))
        {
            return true;
        }

        // compute turns and check if all are acceptable
        typedef debug_validity_phase<Polygon> debug_phase;
        debug_phase::apply(3);

        typedef has_valid_self_turns<Polygon, typename Strategy::cs_tag> has_valid_turns;

        std::deque<typename has_valid_turns::turn_type> turns;
        bool has_invalid_turns
            = ! has_valid_turns::apply(polygon, turns, visitor, strategy);
        debug_print_turns(turns.begin(), turns.end());

        if (has_invalid_turns)
        {
            return false;
        }

        // check if all interior rings are inside the exterior ring
        debug_phase::apply(4);

        if (! has_holes_inside::apply(polygon,
                                      turns.begin(), turns.end(),
                                      visitor,
                                      strategy))
        {
            return false;
        }

        // check whether the interior of the polygon is a connected set
        debug_phase::apply(5);

        return has_connected_interior::apply(polygon,
                                             turns.begin(),
                                             turns.end(),
                                             visitor,
                                             strategy);
    }
};


}} // namespace detail::is_valid
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// A Polygon is always a simple geometric object provided that it is valid.
//
// Reference (for validity of Polygons): OGC 06-103r4 (6.1.11.1)
template <typename Polygon, bool AllowEmptyMultiGeometries>
struct is_valid
    <
        Polygon, polygon_tag, AllowEmptyMultiGeometries
    > : detail::is_valid::is_valid_polygon<Polygon>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_POLYGON_HPP

/* polygon.hpp
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
*/