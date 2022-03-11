// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SORT_ON_SEGMENT_RATIO_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SORT_ON_SEGMENT_RATIO_HPP

#include <cstddef>
#include <algorithm>
#include <map>
#include <set>
#include <vector>

#include <boost/range.hpp>

#include <boost/geometry/algorithms/detail/overlay/copy_segment_point.hpp>
#include <boost/geometry/algorithms/detail/overlay/sort_by_side.hpp>
#include <boost/geometry/strategies/side.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

// Wraps "turn_operation" from turn_info.hpp,
// giving it extra information, necessary for sorting
template <typename TurnOperation>
struct indexed_turn_operation
{
    typedef TurnOperation type;

    std::size_t turn_index;
    std::size_t operation_index;
    bool skip;
    // use pointers to avoid copies, const& is not possible because of usage in vector
    segment_identifier const* other_seg_id; // segment id of other segment of intersection of two segments
    TurnOperation const* subject;

    inline indexed_turn_operation(std::size_t ti, std::size_t oi,
                TurnOperation const& sub,
                segment_identifier const& oid)
        : turn_index(ti)
        , operation_index(oi)
        , skip(false)
        , other_seg_id(&oid)
        , subject(boost::addressof(sub))
    {}

};

template
<
    typename Turns,
    typename Indexed,
    typename Geometry1, typename Geometry2,
    typename RobustPolicy,
    typename SideStrategy,
    bool Reverse1, bool Reverse2
>
struct less_by_segment_ratio
{
    inline less_by_segment_ratio(Turns const& turns
            , Geometry1 const& geometry1
            , Geometry2 const& geometry2
            , RobustPolicy const& robust_policy
            , SideStrategy const& strategy)
        : m_turns(turns)
        , m_geometry1(geometry1)
        , m_geometry2(geometry2)
        , m_robust_policy(robust_policy)
        , m_strategy(strategy)
    {
    }

private :

    Turns const& m_turns;
    Geometry1 const& m_geometry1;
    Geometry2 const& m_geometry2;
    RobustPolicy const& m_robust_policy;
    SideStrategy const& m_strategy;

    typedef typename geometry::point_type<Geometry1>::type point_type;

    inline bool default_order(Indexed const& left, Indexed const& right) const
    {
        // We've nothing to sort on. Take the indexes
        return left.turn_index < right.turn_index;
    }

    inline bool consider_relative_order(Indexed const& left,
                    Indexed const& right) const
    {
        point_type pi, pj, ri, rj, si, sj;

        geometry::copy_segment_points<Reverse1, Reverse2>(m_geometry1, m_geometry2,
            left.subject->seg_id,
            pi, pj);
        geometry::copy_segment_points<Reverse1, Reverse2>(m_geometry1, m_geometry2,
            *left.other_seg_id,
            ri, rj);
        geometry::copy_segment_points<Reverse1, Reverse2>(m_geometry1, m_geometry2,
            *right.other_seg_id,
            si, sj);

        int const side_rj_p = m_strategy.apply(pi, pj, rj);
        int const side_sj_p = m_strategy.apply(pi, pj, sj);

        // Put the one turning left (1; right == -1) as last
        if (side_rj_p != side_sj_p)
        {
            return side_rj_p < side_sj_p;
        }

        int const side_sj_r = m_strategy.apply(ri, rj, sj);
        int const side_rj_s = m_strategy.apply(si, sj, rj);

        // If they both turn left: the most left as last
        // If they both turn right: this is not relevant, but take also here most left
        if (side_rj_s != side_sj_r)
        {
            return side_rj_s < side_sj_r;
        }

        return default_order(left, right);
    }


public :

    // Note that left/right do NOT correspond to m_geometry1/m_geometry2
    // but to the "indexed_turn_operation"
    inline bool operator()(Indexed const& left, Indexed const& right) const
    {
        if (! (left.subject->seg_id == right.subject->seg_id))
        {
            return left.subject->seg_id < right.subject->seg_id;
        }

        // Both left and right are located on the SAME segment.

        if (! (left.subject->fraction == right.subject->fraction))
        {
            return left.subject->fraction < right.subject->fraction;
        }


        typedef typename boost::range_value<Turns>::type turn_type;
        turn_type const& left_turn = m_turns[left.turn_index];
        turn_type const& right_turn = m_turns[right.turn_index];

        // First check "real" intersection (crosses)
        // -> distance zero due to precision, solve it by sorting
        if (left_turn.method == method_crosses
            && right_turn.method == method_crosses)
        {
            return consider_relative_order(left, right);
        }

        bool const left_both_xx = left_turn.both(operation_blocked);
        bool const right_both_xx = right_turn.both(operation_blocked);
        if (left_both_xx && ! right_both_xx)
        {
            return true;
        }
        if (! left_both_xx && right_both_xx)
        {
            return false;
        }

        bool const left_both_uu = left_turn.both(operation_union);
        bool const right_both_uu = right_turn.both(operation_union);
        if (left_both_uu && ! right_both_uu)
        {
            return true;
        }
        if (! left_both_uu && right_both_uu)
        {
            return false;
        }

        return default_order(left, right);
    }
};


}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SORT_ON_SEGMENT_RATIO_HPP

/* less_by_segment_ratio.hpp
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
*/