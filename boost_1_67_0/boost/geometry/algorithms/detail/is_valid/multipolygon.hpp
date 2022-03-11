// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_MULTIPOLYGON_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_MULTIPOLYGON_HPP

#include <deque>
#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/range.hpp>

#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/range.hpp>

#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/algorithms/validity_failure_type.hpp>
#include <boost/geometry/algorithms/within.hpp>

#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>
#include <boost/geometry/algorithms/detail/partition.hpp>

#include <boost/geometry/algorithms/detail/is_valid/has_valid_self_turns.hpp>
#include <boost/geometry/algorithms/detail/is_valid/is_acceptable_turn.hpp>
#include <boost/geometry/algorithms/detail/is_valid/polygon.hpp>

#include <boost/geometry/algorithms/detail/is_valid/debug_print_turns.hpp>
#include <boost/geometry/algorithms/detail/is_valid/debug_validity_phase.hpp>

#include <boost/geometry/algorithms/dispatch/is_valid.hpp>

#include <boost/geometry/strategies/intersection.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_valid
{


template <typename MultiPolygon, bool AllowEmptyMultiGeometries>
class is_valid_multipolygon
    : is_valid_polygon
        <
            typename boost::range_value<MultiPolygon>::type,
            true // check only the validity of rings
        >
{
private:
    typedef is_valid_polygon
        <
            typename boost::range_value<MultiPolygon>::type,
            true
        > base;



    template
    <
        typename PolygonIterator,
        typename TurnIterator,
        typename VisitPolicy,
        typename Strategy
    >
    static inline
    bool are_polygon_interiors_disjoint(PolygonIterator polygons_first,
                                        PolygonIterator polygons_beyond,
                                        TurnIterator turns_first,
                                        TurnIterator turns_beyond,
                                        VisitPolicy& visitor,
                                        Strategy const& strategy)
    {
        boost::ignore_unused(visitor);

        // collect all polygons that have crossing turns
        std::set<signed_size_type> multi_indices;
        for (TurnIterator tit = turns_first; tit != turns_beyond; ++tit)
        {
            if (! tit->touch_only)
            {
                multi_indices.insert(tit->operations[0].seg_id.multi_index);
                multi_indices.insert(tit->operations[1].seg_id.multi_index);
            }
        }

        typedef geometry::model::box<typename point_type<MultiPolygon>::type> box_type;
        typedef typename base::template partition_item<PolygonIterator, box_type> item_type;

        // put polygon iterators without turns in a vector
        std::vector<item_type> polygon_iterators;
        signed_size_type multi_index = 0;
        for (PolygonIterator it = polygons_first; it != polygons_beyond;
             ++it, ++multi_index)
        {
            if (multi_indices.find(multi_index) == multi_indices.end())
            {
                polygon_iterators.push_back(item_type(it));
            }
        }

        // prepare strategies
        typedef typename Strategy::envelope_strategy_type envelope_strategy_type;
        envelope_strategy_type const envelope_strategy
            = strategy.get_envelope_strategy();
        typedef typename Strategy::disjoint_box_box_strategy_type disjoint_box_box_strategy_type;
        disjoint_box_box_strategy_type const disjoint_strategy
            = strategy.get_disjoint_box_box_strategy();

        // call partition to check if polygons are disjoint from each other
        typename base::template item_visitor_type<Strategy> item_visitor(strategy);

        geometry::partition
            <
                geometry::model::box<typename point_type<MultiPolygon>::type>
            >::apply(polygon_iterators, item_visitor,
                     typename base::template expand_box
                        <
                            envelope_strategy_type
                        >(envelope_strategy),
                     typename base::template overlaps_box
                        <
                            envelope_strategy_type,
                            disjoint_box_box_strategy_type
                        >(envelope_strategy, disjoint_strategy));

        if (item_visitor.items_overlap)
        {
            return visitor.template apply<failure_intersecting_interiors>();
        }
        else
        {
            return visitor.template apply<no_failure>();
        }
    }



    class has_multi_index
    {
    public:
        has_multi_index(signed_size_type multi_index)
            : m_multi_index(multi_index)
        {}

        template <typename Turn>
        inline bool operator()(Turn const& turn) const
        {
            return turn.operations[0].seg_id.multi_index == m_multi_index
                && turn.operations[1].seg_id.multi_index == m_multi_index;
        }

    private:
        signed_size_type const m_multi_index;
    };



    template <typename Predicate>
    struct has_property_per_polygon
    {
        template
        <
            typename PolygonIterator,
            typename TurnIterator,
            typename VisitPolicy,
            typename Strategy
        >
        static inline bool apply(PolygonIterator polygons_first,
                                 PolygonIterator polygons_beyond,
                                 TurnIterator turns_first,
                                 TurnIterator turns_beyond,
                                 VisitPolicy& visitor,
                                 Strategy const& strategy)
        {
            signed_size_type multi_index = 0;
            for (PolygonIterator it = polygons_first; it != polygons_beyond;
                 ++it, ++multi_index)
            {
                has_multi_index index_predicate(multi_index);

                typedef boost::filter_iterator
                    <
                        has_multi_index, TurnIterator
                    > filtered_turn_iterator;

                filtered_turn_iterator filtered_turns_first(index_predicate,
                                                            turns_first,
                                                            turns_beyond);

                filtered_turn_iterator filtered_turns_beyond(index_predicate,
                                                             turns_beyond,
                                                             turns_beyond);

                if (! Predicate::apply(*it,
                                       filtered_turns_first,
                                       filtered_turns_beyond,
                                       visitor,
                                       strategy))
                {
                    return false;
                }
            }
            return true;
        }
    };



    template
    <
        typename PolygonIterator,
        typename TurnIterator,
        typename VisitPolicy,
        typename Strategy
    >
    static inline bool have_holes_inside(PolygonIterator polygons_first,
                                         PolygonIterator polygons_beyond,
                                         TurnIterator turns_first,
                                         TurnIterator turns_beyond,
                                         VisitPolicy& visitor,
                                         Strategy const& strategy)
    {
        return has_property_per_polygon
            <
                typename base::has_holes_inside
            >::apply(polygons_first, polygons_beyond,
                     turns_first, turns_beyond, visitor, strategy);
    }



    template
    <
        typename PolygonIterator,
        typename TurnIterator,
        typename VisitPolicy,
        typename Strategy
    >
    static inline bool have_connected_interior(PolygonIterator polygons_first,
                                               PolygonIterator polygons_beyond,
                                               TurnIterator turns_first,
                                               TurnIterator turns_beyond,
                                               VisitPolicy& visitor,
                                               Strategy const& strategy)
    {
        return has_property_per_polygon
            <
                typename base::has_connected_interior
            >::apply(polygons_first, polygons_beyond,
                     turns_first, turns_beyond, visitor, strategy);
    }


    template <typename VisitPolicy, typename Strategy>
    struct per_polygon
    {
        per_polygon(VisitPolicy& policy, Strategy const& strategy)
            : m_policy(policy)
            , m_strategy(strategy)
        {}

        template <typename Polygon>
        inline bool apply(Polygon const& polygon) const
        {
            return base::apply(polygon, m_policy, m_strategy);
        }

        VisitPolicy& m_policy;
        Strategy const& m_strategy;
    };
public:
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(MultiPolygon const& multipolygon,
                             VisitPolicy& visitor,
                             Strategy const& strategy)
    {
        typedef debug_validity_phase<MultiPolygon> debug_phase;

        if (BOOST_GEOMETRY_CONDITION(AllowEmptyMultiGeometries)
            && boost::empty(multipolygon))
        {
            return visitor.template apply<no_failure>();
        }

        // check validity of all polygons ring
        debug_phase::apply(1);

        if (! detail::check_iterator_range
                  <
                      per_polygon<VisitPolicy, Strategy>,
                      false // do not check for empty multipolygon (done above)
                  >::apply(boost::begin(multipolygon),
                           boost::end(multipolygon),
                           per_polygon<VisitPolicy, Strategy>(visitor, strategy)))
        {
            return false;
        }


        // compute turns and check if all are acceptable
        debug_phase::apply(2);

        typedef has_valid_self_turns<MultiPolygon, typename Strategy::cs_tag> has_valid_turns;

        std::deque<typename has_valid_turns::turn_type> turns;
        bool has_invalid_turns =
            ! has_valid_turns::apply(multipolygon, turns, visitor, strategy);
        debug_print_turns(turns.begin(), turns.end());

        if (has_invalid_turns)
        {
            return false;
        }


        // check if each polygon's interior rings are inside the
        // exterior and not one inside the other
        debug_phase::apply(3);

        if (! have_holes_inside(boost::begin(multipolygon),
                                boost::end(multipolygon),
                                turns.begin(),
                                turns.end(),
                                visitor,
                                strategy))
        {
            return false;
        }


        // check that each polygon's interior is connected
        debug_phase::apply(4);

        if (! have_connected_interior(boost::begin(multipolygon),
                                      boost::end(multipolygon),
                                      turns.begin(),
                                      turns.end(),
                                      visitor,
                                      strategy))
        {
            return false;
        }


        // check if polygon interiors are disjoint
        debug_phase::apply(5);
        return are_polygon_interiors_disjoint(boost::begin(multipolygon),
                                              boost::end(multipolygon),
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


// Not clear what the definition is.
// Right now we check that each element is simple (in fact valid), and
// that the MultiPolygon is also valid.
//
// Reference (for validity of MultiPolygons): OGC 06-103r4 (6.1.14)
template <typename MultiPolygon, bool AllowEmptyMultiGeometries>
struct is_valid
    <
        MultiPolygon, multi_polygon_tag, AllowEmptyMultiGeometries
    > : detail::is_valid::is_valid_multipolygon
        <
            MultiPolygon, AllowEmptyMultiGeometries
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_MULTIPOLYGON_HPP

/* multipolygon.hpp
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
*/