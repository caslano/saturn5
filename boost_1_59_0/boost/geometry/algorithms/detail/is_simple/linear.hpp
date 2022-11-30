// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_LINEAR_HPP

#include <algorithm>
#include <deque>

#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

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
    typename Strategy,
    typename Tag = typename tag<Geometry>::type
>
class is_acceptable_turn
    : not_implemented<Geometry>
{};

template <typename Linestring, typename Strategy>
class is_acceptable_turn<Linestring, Strategy, linestring_tag>
{
public:
    is_acceptable_turn(Linestring const& linestring, Strategy const& strategy)
        : m_linestring(linestring)
        , m_is_closed(geometry::detail::equals::equals_point_point(
                          range::front(linestring), range::back(linestring), strategy))
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

template <typename MultiLinestring, typename Strategy>
class is_acceptable_turn<MultiLinestring, Strategy, multi_linestring_tag>
{
private:
    template <typename Point, typename Linestring>
    inline bool is_boundary_point_of(Point const& point, Linestring const& linestring) const
    {
        BOOST_GEOMETRY_ASSERT(boost::size(linestring) > 1);
        using geometry::detail::equals::equals_point_point;
        return ! equals_point_point(range::front(linestring), range::back(linestring), m_strategy)
            && (equals_point_point(point, range::front(linestring), m_strategy)
                || equals_point_point(point, range::back(linestring), m_strategy));
    }

    template <typename Turn, typename Linestring>
    inline bool is_closing_point_of(Turn const& turn, Linestring const& linestring) const
    {
        BOOST_GEOMETRY_ASSERT(boost::size(linestring) > 1);
        using geometry::detail::equals::equals_point_point;
        return turn.method == overlay::method_none
            && check_segment_indices(turn, boost::size(linestring) - 2)
            && equals_point_point(range::front(linestring), range::back(linestring), m_strategy)
            && turn.operations[0].fraction.is_zero();
    }

    template <typename Linestring1, typename Linestring2>
    inline bool have_same_boundary_points(Linestring1 const& ls1, Linestring2 const& ls2) const
    {
        using geometry::detail::equals::equals_point_point;
        return equals_point_point(range::front(ls1), range::front(ls2), m_strategy)
             ? equals_point_point(range::back(ls1), range::back(ls2), m_strategy)
             : (equals_point_point(range::front(ls1), range::back(ls2), m_strategy)
                && equals_point_point(range::back(ls1), range::front(ls2), m_strategy));
    }

public:
    is_acceptable_turn(MultiLinestring const& multilinestring, Strategy const& strategy)
        : m_multilinestring(multilinestring)
        , m_strategy(strategy)
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
    Strategy const& m_strategy;
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
            Linear, Strategy
        > is_acceptable_turn_type;

    is_acceptable_turn_type predicate(linear, strategy);
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
            && ! detail::is_valid::has_duplicates<Linestring>::apply(linestring, policy, strategy)
            && ! detail::is_valid::has_spikes<Linestring>::apply(linestring, policy, strategy);
    }
};

template <typename Linestring>
struct is_simple_linestring<Linestring, true>
{
    template <typename Strategy>
    static inline bool apply(Linestring const& linestring,
                             Strategy const& strategy)
    {
        return is_simple_linestring<Linestring, false>::apply(linestring, strategy)
            && ! has_self_intersections(linestring, strategy);
    }
};


template <typename MultiLinestring>
struct is_simple_multilinestring
{
private:
    template <typename Strategy>
    struct not_simple
    {
        not_simple(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Linestring>
        inline bool operator()(Linestring const& linestring) const
        {
            return ! detail::is_simple::is_simple_linestring
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
        // check each of the linestrings for simplicity
        // but do not compute self-intersections yet; these will be
        // computed for the entire multilinestring
        // return true for empty multilinestring

        using not_simple = not_simple<Strategy>; // do not compute self-intersections
 
        if (std::any_of(boost::begin(multilinestring),
                        boost::end(multilinestring),
                        not_simple(strategy)))
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