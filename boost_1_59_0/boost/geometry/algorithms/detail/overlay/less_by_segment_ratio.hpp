// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020 Oracle and/or its affiliates.

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

#include <boost/core/addressof.hpp>
#include <boost/range/value_type.hpp>

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