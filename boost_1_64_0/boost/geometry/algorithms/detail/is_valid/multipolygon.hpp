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
iP2peJ3YULazIWeNwptHjG0eO4DhjZuIpauisLW/dd0Uh/q5o3/9jYOcy+hhaxQyfR6HMjXFqursqDsMpee96Y3pDFyfjZuU5es/89EHrMFnUWjPfv84FIfa+Gf3d60RHKzLb7PAzTLfxuGpv8Whv3hS5Q6Y2Q6+54hCTxzsbZwmE5/PtdYeN3r6ojRMehwOWodmy/CMm2BJZeOC8yPqyGWcf6oQ2yLZbTZtuc/c4doT+GFl+lt1DV6bU+a9uFFP586hv0fF8PlRaF0vDrW6wfwmYr1jziyKQoVmdD0oDktesU5HrcsvfAs+dp7MF17FfdnMr4PYLx468O98+LY43MWXFtHTHzhYoao4xuviW2Nzih1jzS8KPXO/jMJ3pRyDb716QxzuFRM2ZzAH9lkZB6gkT+uzxHqx0S/4aM3b2KLc4Lfpcfjs0ygsc9xUfKwDHE3bw3hbJMJHV+E9/1mxPg5T4HKnKVHYD8NXn43C83KbH9fjeunNS5y+vjW8xxOb7xKXSvLhJ/EW/vfetTjcjP/tdM/b6fvzfOyWjirw4fr1o/D2m7jfAtg5SB4iZ2nxEQ74SiLkkIusvAw7xOQ2I6NQkQ7msvEBi+jkaBzexZ1vysjfk/b+IQ6Xlf5PxuFpeJeAx6nu2YV0Il1JD9KbtCBtSYfk3yoh6eixNnueJia+UZ3d+Wwbe5h0K56Rz7HFcWku2OglPjwvCgt9P7C03+UuW8SKt2ZHIQ2dTKoqHzoOU867L99+sWUcCsCFPDdH4Z5X4jD0e/zqETFP3LlcD4bBn2eqRGFeM9xTnnCH/PHRleZOR2WO4SD3W1vcustbUbhVLGkwkg+lw/34RSvjqnlvkr8kwtm3EuHwG/IFcWHiavc1vqGpsPyzRHh1pmt6qcNrm/F/8WsR26gzzP/h/AL49R3O3e0jWPq6XG1CHArXgy3i15F6wfzYhWsdIl+Q4+QUOUtOkz3kAFl1MA4rv4vDoWFRGHE3v8nKpu+Qiz7CpsndWfDth0JYw94q7kyEnHx0Rz1jq8HO78Iv8+DWcO8SHd0uv2tI33eWldtvEWfq4HVL5EB03fc7Y0zit7z0asVEyIivlhIX+r/Az5ab5734snpCDjnklQrwy+fd17FT/tOMPXy6CX7llLv8IxHGPCPXz8+2+8ZhJgyu3SMRSuHDn7aQxz/Nfvhm32I4ttpAXxjVm7Qq4js58o+uP7ST9XskDj+Ive8UicMQ49+6nm+PTYQC3eXDa7w75FVY3MU4Z/CjxXL5NLCzhTzVsUeX4j9y0555jc91H7+V34s/j3TE087xQ9fMl97c0+IO+OR3zYy5QRT+fkke7vh2dBV6ss3kexJLwyhxtcRh814glrwXhZpiV8EkB36QjTi+rg0rr2xRy9gUhcSNiXDbXmsP68/fwR+nxqHVq3SKI/7EXne4zmV+VWBPFHrAyFYr2cqaOFTLjP/day0Ws4unxA8872f4s40N1nqWPSwWE1fC9G+iMKZ/ItTl++2uZ5PmtYS+G+ZwTDs4cyoKk9yrjvpIOTEtR295tLhUmW+3eVAeN0IuMFytZWQcjsDKwd/ijR+yHznuTWoxXz+bCNXhfZmbYb1rdfqUX62MQzp8s8gG+iwJw//uOaPncaNv+CI7z9vEZyfk7hNwuDdw14Fy/0p835y6ZObnLd0jl+8XWx9xbveMSF7C6Uu5Riu5bAF5wUb5H9+eXxH/1GsvnpoI2WtF4b20fPIdnNwm7bsPJUKjlmy0C32zq9Fv4C24TIWHxK/JfnbAvdjGkaQt/Sq+4sHvLYDbleMw/Dt8awq9s9Mv+eIt4snt4l3+vlHIe0kN5nccWBz9yrklvohCdCoOk9c=
*/