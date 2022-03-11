// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_LINEAR_HPP

#include <algorithm>
#include <deque>

#include <boost/range.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/range.hpp>

#include <boost/geometry/policies/predicate_based_interrupt_policy.hpp>
#include <boost/geometry/policies/robustness/no_rescale_policy.hpp>
#include <boost/geometry/policies/robustness/segment_ratio.hpp>

#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>

#include <boost/geometry/algorithms/detail/disjoint/linear_linear.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/self_turn_points.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_duplicates.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_spikes.hpp>

#include <boost/geometry/algorithms/detail/is_simple/debug_print_boundary_points.hpp>
#include <boost/geometry/algorithms/detail/is_simple/failure_policy.hpp>
#include <boost/geometry/algorithms/detail/is_valid/debug_print_turns.hpp>

#include <boost/geometry/algorithms/dispatch/is_simple.hpp>

#include <boost/geometry/strategies/intersection.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_simple
{


template <typename Turn>
inline bool check_segment_indices(Turn const& turn,
                                  signed_size_type last_index)
{
    return
        (turn.operations[0].seg_id.segment_index == 0
         && turn.operations[1].seg_id.segment_index == last_index)
        ||
        (turn.operations[0].seg_id.segment_index == 0
         && turn.operations[1].seg_id.segment_index == last_index);
}


template
<
    typename Geometry,
    typename EqPPStrategy,
    typename Tag = typename tag<Geometry>::type
>
class is_acceptable_turn
    : not_implemented<Geometry>
{};

template <typename Linestring, typename EqPPStrategy>
class is_acceptable_turn<Linestring, EqPPStrategy, linestring_tag>
{
public:
    is_acceptable_turn(Linestring const& linestring)
        : m_linestring(linestring)
        , m_is_closed(geometry::detail::equals::equals_point_point(range::front(linestring),
                                                                   range::back(linestring),
                                                                   EqPPStrategy()))
    {}

    template <typename Turn>
    inline bool apply(Turn const& turn) const
    {
        BOOST_GEOMETRY_ASSERT(boost::size(m_linestring) > 1);
        return m_is_closed
            && turn.method == overlay::method_none
            && check_segment_indices(turn, boost::size(m_linestring) - 2)
            && turn.operations[0].fraction.is_zero();
    }

private:
    Linestring const& m_linestring;
    bool const m_is_closed;
};

template <typename MultiLinestring, typename EqPPStrategy>
class is_acceptable_turn<MultiLinestring, EqPPStrategy, multi_linestring_tag>
{
private:
    template <typename Point1, typename Point2>
    static inline bool equals_point_point(Point1 const& point1, Point2 const& point2)
    {
        return geometry::detail::equals::equals_point_point(point1, point2,
                                                            EqPPStrategy());
    }

    template <typename Point, typename Linestring>
    static inline bool is_boundary_point_of(Point const& point,
                                            Linestring const& linestring)
    {
        BOOST_GEOMETRY_ASSERT(boost::size(linestring) > 1);
        return
            !equals_point_point(range::front(linestring), range::back(linestring))
            &&
            (equals_point_point(point, range::front(linestring))
             || equals_point_point(point, range::back(linestring)));
    }

    template <typename Turn, typename Linestring>
    static inline bool is_closing_point_of(Turn const& turn,
                                           Linestring const& linestring)
    {
        BOOST_GEOMETRY_ASSERT(boost::size(linestring) > 1);
        return
            turn.method == overlay::method_none
            &&
            check_segment_indices(turn, boost::size(linestring) - 2)
            &&
            equals_point_point(range::front(linestring), range::back(linestring))
            &&
            turn.operations[0].fraction.is_zero();
            ;
    }

    template <typename Linestring1, typename Linestring2>
    static inline bool have_same_boundary_points(Linestring1 const& ls1,
                                                 Linestring2 const& ls2)
    {
        return
            equals_point_point(range::front(ls1), range::front(ls2))
            ?
            equals_point_point(range::back(ls1), range::back(ls2))
            :
            (equals_point_point(range::front(ls1), range::back(ls2))
             &&
                equals_point_point(range::back(ls1), range::front(ls2)))
            ;
    }

public:
    is_acceptable_turn(MultiLinestring const& multilinestring)
        : m_multilinestring(multilinestring)
    {}

    template <typename Turn>
    inline bool apply(Turn const& turn) const
    {
        typedef typename boost::range_value<MultiLinestring>::type linestring_type;
        
        linestring_type const& ls1 =
            range::at(m_multilinestring, turn.operations[0].seg_id.multi_index);

        linestring_type const& ls2 =
            range::at(m_multilinestring, turn.operations[1].seg_id.multi_index);

        if (turn.operations[0].seg_id.multi_index
            == turn.operations[1].seg_id.multi_index)
        {
            return is_closing_point_of(turn, ls1);
        }

        return
            is_boundary_point_of(turn.point, ls1)
            && is_boundary_point_of(turn.point, ls2)
            &&
            ( boost::size(ls1) != 2
              || boost::size(ls2) != 2
              || ! have_same_boundary_points(ls1, ls2) );
    }

private:
    MultiLinestring const& m_multilinestring;
};


template <typename Linear, typename Strategy>
inline bool has_self_intersections(Linear const& linear, Strategy const& strategy)
{
    typedef typename point_type<Linear>::type point_type;

    // compute self turns
    typedef detail::overlay::turn_info<point_type> turn_info;

    std::deque<turn_info> turns;

    typedef detail::overlay::get_turn_info
        <
            detail::disjoint::assign_disjoint_policy
        > turn_policy;

    typedef is_acceptable_turn
        <
            Linear,
            typename Strategy::equals_point_point_strategy_type
        > is_acceptable_turn_type;

    is_acceptable_turn_type predicate(linear);
    detail::overlay::predicate_based_interrupt_policy
        <
            is_acceptable_turn_type
        > interrupt_policy(predicate);

    // TODO: skip_adjacent should be set to false
    detail::self_get_turn_points::get_turns
        <
            false, turn_policy
        >::apply(linear,
                 strategy,
                 detail::no_rescale_policy(),
                 turns,
                 interrupt_policy, 0, true);

    detail::is_valid::debug_print_turns(turns.begin(), turns.end());
    debug_print_boundary_points(linear);

    return interrupt_policy.has_intersections;
}


template <typename Linestring, bool CheckSelfIntersections = true>
struct is_simple_linestring
{
    template <typename Strategy>
    static inline bool apply(Linestring const& linestring,
                             Strategy const& strategy)
    {
        simplicity_failure_policy policy;
        return ! boost::empty(linestring)
            && ! detail::is_valid::has_duplicates
                    <
                        Linestring, closed, typename Strategy::cs_tag
                    >::apply(linestring, policy)
            && ! detail::is_valid::has_spikes
                    <
                        Linestring, closed
                    >::apply(linestring, policy, strategy.get_side_strategy());
    }
};

template <typename Linestring>
struct is_simple_linestring<Linestring, true>
{
    template <typename Strategy>
    static inline bool apply(Linestring const& linestring,
                             Strategy const& strategy)
    {
        return is_simple_linestring
                <
                    Linestring, false
                >::apply(linestring, strategy)
            && ! has_self_intersections(linestring, strategy);
    }
};


template <typename MultiLinestring>
struct is_simple_multilinestring
{
private:
    template <typename Strategy>
    struct per_linestring
    {
        per_linestring(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Linestring>
        inline bool apply(Linestring const& linestring) const
        {
            return detail::is_simple::is_simple_linestring
                <
                    Linestring,
                    false // do not compute self-intersections
                >::apply(linestring, m_strategy);
        }

        Strategy const& m_strategy;
    };

public:
    template <typename Strategy>
    static inline bool apply(MultiLinestring const& multilinestring,
                             Strategy const& strategy)
    {
        typedef per_linestring<Strategy> per_ls;

        // check each of the linestrings for simplicity
        // but do not compute self-intersections yet; these will be
        // computed for the entire multilinestring
        if ( ! detail::check_iterator_range
                 <
                     per_ls, // do not compute self-intersections
                     true // allow empty multilinestring
                 >::apply(boost::begin(multilinestring),
                          boost::end(multilinestring),
                          per_ls(strategy))
             )
        {
            return false;
        }

        return ! has_self_intersections(multilinestring, strategy);
    }
};



}} // namespace detail::is_simple
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

// A linestring is a curve.
// A curve is simple if it does not pass through the same point twice,
// with the possible exception of its two endpoints
//
// Reference: OGC 06-103r4 (6.1.6.1)
template <typename Linestring>
struct is_simple<Linestring, linestring_tag>
    : detail::is_simple::is_simple_linestring<Linestring>
{};


// A MultiLinestring is a MultiCurve
// A MultiCurve is simple if all of its elements are simple and the
// only intersections between any two elements occur at Points that
// are on the boundaries of both elements.
//
// Reference: OGC 06-103r4 (6.1.8.1; Fig. 9)
template <typename MultiLinestring>
struct is_simple<MultiLinestring, multi_linestring_tag>
    : detail::is_simple::is_simple_multilinestring<MultiLinestring>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_LINEAR_HPP

/* linear.hpp
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
*/