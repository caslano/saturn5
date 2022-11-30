// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
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
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/range.hpp>

#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/algorithms/validity_failure_type.hpp>
#include <boost/geometry/algorithms/within.hpp>

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

        // call partition to check if polygons are disjoint from each other
        typename base::template item_visitor_type<Strategy> item_visitor(strategy);

        geometry::partition
            <
                geometry::model::box<typename point_type<MultiPolygon>::type>
            >::apply(polygon_iterators, item_visitor,
                     typename base::template expand_box<Strategy>(strategy),
                     typename base::template overlaps_box<Strategy>(strategy));

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
    struct is_invalid_polygon
    {
        is_invalid_polygon(VisitPolicy& policy, Strategy const& strategy)
            : m_policy(policy)
            , m_strategy(strategy)
        {}

        template <typename Polygon>
        inline bool operator()(Polygon const& polygon) const
        {
            return ! base::apply(polygon, m_policy, m_strategy);
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
        using debug_phase = debug_validity_phase<MultiPolygon>;

        if (BOOST_GEOMETRY_CONDITION(AllowEmptyMultiGeometries)
            && boost::empty(multipolygon))
        {
            return visitor.template apply<no_failure>();
        }

        // check validity of all polygons ring
        debug_phase::apply(1);

        if (std::any_of(boost::begin(multipolygon), boost::end(multipolygon),
                        is_invalid_polygon<VisitPolicy, Strategy>(visitor, strategy)))
        {
            return false;
        }

        // compute turns and check if all are acceptable
        debug_phase::apply(2);

        using has_valid_turns =  has_valid_self_turns
            <
                MultiPolygon, 
                typename Strategy::cs_tag
            >;

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