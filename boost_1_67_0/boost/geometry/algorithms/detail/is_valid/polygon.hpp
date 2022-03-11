// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

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
#include <boost/range.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/range.hpp>

#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/iterators/point_iterator.hpp>

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/disjoint.hpp>
#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/algorithms/num_interior_rings.hpp>
#include <boost/geometry/algorithms/validity_failure_type.hpp>
#include <boost/geometry/algorithms/detail/point_on_border.hpp>
#include <boost/geometry/algorithms/within.hpp>

#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>
#include <boost/geometry/algorithms/detail/partition.hpp>

#include <boost/geometry/algorithms/detail/is_valid/complement_graph.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_valid_self_turns.hpp>
#include <boost/geometry/algorithms/detail/is_valid/is_acceptable_turn.hpp>
#include <boost/geometry/algorithms/detail/is_valid/ring.hpp>

#include <boost/geometry/algorithms/detail/is_valid/debug_print_turns.hpp>
#include <boost/geometry/algorithms/detail/is_valid/debug_validity_phase.hpp>
#include <boost/geometry/algorithms/detail/is_valid/debug_complement_graph.hpp>

#include <boost/geometry/algorithms/dispatch/is_valid.hpp>


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
    struct per_ring
    {
        per_ring(VisitPolicy& policy, Strategy const& strategy)
            : m_policy(policy)
            , m_strategy(strategy)
        {}

        template <typename Ring>
        inline bool apply(Ring const& ring) const
        {
            return detail::is_valid::is_valid_ring
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
        return
            detail::check_iterator_range
                <
                    per_ring<VisitPolicy, Strategy>,
                    true // allow for empty interior ring range
                >::apply(boost::begin(interior_rings),
                         boost::end(interior_rings),
                         per_ring<VisitPolicy, Strategy>(visitor, strategy));
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
    template <typename EnvelopeStrategy>
    struct expand_box
    {
        explicit expand_box(EnvelopeStrategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename Iterator>
        inline void apply(Box& total, partition_item<Iterator, Box> const& item) const
        {
            geometry::expand(total,
                             item.get_envelope(m_strategy),
                             m_strategy.get_box_expand_strategy());
        }

        EnvelopeStrategy const& m_strategy;
    };

    template <typename EnvelopeStrategy, typename DisjointBoxBoxStrategy>
    struct overlaps_box
    {
        explicit overlaps_box(EnvelopeStrategy const& envelope_strategy,
                              DisjointBoxBoxStrategy const& disjoint_strategy)
            : m_envelope_strategy(envelope_strategy)
            , m_disjoint_strategy(disjoint_strategy)
        {}

        template <typename Box, typename Iterator>
        inline bool apply(Box const& box, partition_item<Iterator, Box> const& item) const
        {
            return ! geometry::disjoint(item.get_envelope(m_envelope_strategy),
                                        box,
                                        m_disjoint_strategy);
        }

        EnvelopeStrategy const& m_envelope_strategy;
        DisjointBoxBoxStrategy const& m_disjoint_strategy;
    };


    template <typename WithinStrategy>
    struct item_visitor_type
    {
        bool items_overlap;
        WithinStrategy const& m_strategy;

        explicit item_visitor_type(WithinStrategy const& strategy)
            : items_overlap(false)
            , m_strategy(strategy)
        {}

        template <typename Iterator, typename Box>
        inline bool apply(partition_item<Iterator, Box> const& item1,
                          partition_item<Iterator, Box> const& item2)
        {
            typedef boost::mpl::vector
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

        // prepare strategy
        typedef typename std::iterator_traits<RingIterator>::value_type inter_ring_type;
        typename Strategy::template point_in_geometry_strategy
            <
                inter_ring_type, ExteriorRing
            >::type const in_exterior_strategy
            = strategy.template get_point_in_geometry_strategy<inter_ring_type, ExteriorRing>();

        signed_size_type ring_index = 0;
        for (RingIterator it = rings_first; it != rings_beyond;
             ++it, ++ring_index)
        {
            // do not examine interior rings that have turns with the
            // exterior ring
            if (ring_indices.find(ring_index) == ring_indices.end()
                && ! geometry::covered_by(range::front(*it), exterior_ring, in_exterior_strategy))
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

        // prepare strategies
        typedef typename Strategy::envelope_strategy_type envelope_strategy_type;
        envelope_strategy_type const envelope_strategy
            = strategy.get_envelope_strategy();
        typedef typename Strategy::disjoint_box_box_strategy_type disjoint_box_box_strategy_type;
        disjoint_box_box_strategy_type const disjoint_strategy
            = strategy.get_disjoint_box_box_strategy();

        // call partition to check if interior rings are disjoint from
        // each other
        item_visitor_type<Strategy> item_visitor(strategy);

        geometry::partition
            <
                box_type
            >::apply(ring_iterators, item_visitor,
                     expand_box
                        <
                            envelope_strategy_type
                        >(envelope_strategy),
                     overlaps_box
                        <
                            envelope_strategy_type,
                            disjoint_box_box_strategy_type
                        >(envelope_strategy, disjoint_strategy));

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