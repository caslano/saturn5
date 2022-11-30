// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013-2020.
// Modifications copyright (c) 2013-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_TURN_INFO_HELPERS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_TURN_INFO_HELPERS_HPP

#include <boost/geometry/algorithms/detail/direction_code.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/recalculate.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/policies/relate/intersection_policy.hpp>
#include <boost/geometry/policies/robustness/rescale_policy_tags.hpp>
#include <boost/geometry/strategies/intersection_result.hpp>

namespace boost { namespace geometry {

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay {

enum turn_position { position_middle, position_front, position_back };

template <typename Point, typename SegmentRatio>
struct turn_operation_linear
    : public turn_operation<Point, SegmentRatio>
{
    turn_operation_linear()
        : position(position_middle)
        , is_collinear(false)
    {}

    turn_position position;
    bool is_collinear; // valid only for Linear geometry
};

template
<
    typename UniqueSubRange1,
    typename UniqueSubRange2,
    typename Strategy
>
struct side_calculator
{
    typedef typename UniqueSubRange1::point_type point1_type;
    typedef typename UniqueSubRange2::point_type point2_type;
    typedef decltype(std::declval<Strategy>().side()) side_strategy_type;

    inline side_calculator(UniqueSubRange1 const& range_p,
                           UniqueSubRange2 const& range_q,
                           Strategy const& strategy)
        : m_side_strategy(strategy.side())
        , m_range_p(range_p)
        , m_range_q(range_q)
    {}

    inline int pk_wrt_p1() const { return m_side_strategy.apply(get_pi(), get_pj(), get_pk()); }
    inline int pk_wrt_q1() const { return m_side_strategy.apply(get_qi(), get_qj(), get_pk()); }
    inline int qk_wrt_p1() const { return m_side_strategy.apply(get_pi(), get_pj(), get_qk()); }
    inline int qk_wrt_q1() const { return m_side_strategy.apply(get_qi(), get_qj(), get_qk()); }

    inline int pk_wrt_q2() const { return m_side_strategy.apply(get_qj(), get_qk(), get_pk()); }
    inline int qk_wrt_p2() const { return m_side_strategy.apply(get_pj(), get_pk(), get_qk()); }

    // Necessary when rescaling turns off:
    inline int qj_wrt_p1() const { return m_side_strategy.apply(get_pi(), get_pj(), get_qj()); }
    inline int qj_wrt_p2() const { return m_side_strategy.apply(get_pj(), get_pk(), get_qj()); }
    inline int pj_wrt_q1() const { return m_side_strategy.apply(get_qi(), get_qj(), get_pj()); }
    inline int pj_wrt_q2() const { return m_side_strategy.apply(get_qj(), get_qk(), get_pj()); }

    inline point1_type const& get_pi() const { return m_range_p.at(0); }
    inline point1_type const& get_pj() const { return m_range_p.at(1); }
    inline point1_type const& get_pk() const { return m_range_p.at(2); }

    inline point2_type const& get_qi() const { return m_range_q.at(0); }
    inline point2_type const& get_qj() const { return m_range_q.at(1); }
    inline point2_type const& get_qk() const { return m_range_q.at(2); }

    // Used side-strategy, owned by the calculator
    side_strategy_type m_side_strategy;

    // Used ranges - owned by get_turns or (for robust points) by intersection_info_base
    UniqueSubRange1 const& m_range_p;
    UniqueSubRange2 const& m_range_q;
};

template<typename Point, typename UniqueSubRange, typename RobustPolicy>
struct robust_subrange_adapter
{
    typedef Point point_type;

    robust_subrange_adapter(UniqueSubRange const& unique_sub_range,
                     Point const& robust_point_i, Point const& robust_point_j,
                     RobustPolicy const& robust_policy)

        : m_unique_sub_range(unique_sub_range)
        , m_robust_policy(robust_policy)
        , m_robust_point_i(robust_point_i)
        , m_robust_point_j(robust_point_j)
        , m_k_retrieved(false)
    {}

    std::size_t size() const { return m_unique_sub_range.size(); }

    //! Get precalculated point
    Point const& at(std::size_t index) const
    {
        BOOST_GEOMETRY_ASSERT(index < size());
        switch (index)
        {
            case 0 : return m_robust_point_i;
            case 1 : return m_robust_point_j;
            case 2 : return get_point_k();
            default : return m_robust_point_i;
        }
    }

private :
    Point const& get_point_k() const
    {
        if (! m_k_retrieved)
        {
            geometry::recalculate(m_robust_point_k, m_unique_sub_range.at(2), m_robust_policy);
            m_k_retrieved = true;
        }
        return m_robust_point_k;
    }

    UniqueSubRange const& m_unique_sub_range;
    RobustPolicy const& m_robust_policy;

    Point const& m_robust_point_i;
    Point const& m_robust_point_j;
    mutable Point m_robust_point_k;

    mutable bool m_k_retrieved;
};

template
<
    typename UniqueSubRange1, typename UniqueSubRange2,
    typename RobustPolicy
>
struct robust_point_calculator
{
    typedef typename geometry::robust_point_type
        <
            typename UniqueSubRange1::point_type, RobustPolicy
        >::type robust_point1_type;
    typedef typename geometry::robust_point_type
        <
            typename UniqueSubRange2::point_type, RobustPolicy
        >::type robust_point2_type;

    inline robust_point_calculator(UniqueSubRange1 const& range_p,
                                   UniqueSubRange2 const& range_q,
                                   RobustPolicy const& robust_policy)
        : m_robust_policy(robust_policy)
        , m_range_p(range_p)
        , m_range_q(range_q)
        , m_pk_retrieved(false)
        , m_qk_retrieved(false)
    {
        // Calculate pi,pj and qi,qj which are almost always necessary
        // But don't calculate pk/qk yet, which is retrieved (taking
        // more time) and not always necessary.
        geometry::recalculate(m_rpi, range_p.at(0), robust_policy);
        geometry::recalculate(m_rpj, range_p.at(1), robust_policy);
        geometry::recalculate(m_rqi, range_q.at(0), robust_policy);
        geometry::recalculate(m_rqj, range_q.at(1), robust_policy);
    }

    inline robust_point1_type const& get_rpk() const
    {
        if (! m_pk_retrieved)
        {
            geometry::recalculate(m_rpk, m_range_p.at(2), m_robust_policy);
            m_pk_retrieved = true;
        }
        return m_rpk;
    }
    inline robust_point2_type const& get_rqk() const
    {
        if (! m_qk_retrieved)
        {
            geometry::recalculate(m_rqk, m_range_q.at(2), m_robust_policy);
            m_qk_retrieved = true;
        }
        return m_rqk;
    }

    robust_point1_type m_rpi, m_rpj;
    robust_point2_type m_rqi, m_rqj;

private :
    RobustPolicy const& m_robust_policy;
    UniqueSubRange1 const& m_range_p;
    UniqueSubRange2 const& m_range_q;

    // On retrieval
    mutable robust_point1_type m_rpk;
    mutable robust_point2_type m_rqk;
    mutable bool m_pk_retrieved;
    mutable bool m_qk_retrieved;
};

// Default version (empty - specialized below)
template
<
    typename UniqueSubRange1, typename UniqueSubRange2,
    typename TurnPoint, typename UmbrellaStrategy,
    typename RobustPolicy,
    typename Tag = typename rescale_policy_type<RobustPolicy>::type
>
class intersection_info_base {};

// Version with rescaling, having robust points
template
<
    typename UniqueSubRange1, typename UniqueSubRange2,
    typename TurnPoint, typename UmbrellaStrategy,
    typename RobustPolicy
>
class intersection_info_base<UniqueSubRange1, UniqueSubRange2,
        TurnPoint, UmbrellaStrategy, RobustPolicy, rescale_policy_tag>
{
    typedef robust_point_calculator
    <
        UniqueSubRange1, UniqueSubRange2,
        RobustPolicy
    >
    robust_calc_type;

public:
    typedef segment_intersection_points
    <
        TurnPoint,
        geometry::segment_ratio<boost::long_long_type>
    > intersection_point_type;
    typedef policies::relate::segments_intersection_policy
        <
            intersection_point_type
        > intersection_policy_type;

    typedef typename intersection_policy_type::return_type result_type;

    typedef typename robust_calc_type::robust_point1_type robust_point1_type;
    typedef typename robust_calc_type::robust_point2_type robust_point2_type;

    typedef robust_subrange_adapter<robust_point1_type, UniqueSubRange1, RobustPolicy> robust_subrange1;
    typedef robust_subrange_adapter<robust_point2_type, UniqueSubRange2, RobustPolicy> robust_subrange2;

    typedef side_calculator
        <
            robust_subrange1, robust_subrange2, UmbrellaStrategy
        > side_calculator_type;

    typedef side_calculator
        <
            robust_subrange2, robust_subrange1, UmbrellaStrategy
        > robust_swapped_side_calculator_type;

    intersection_info_base(UniqueSubRange1 const& range_p,
                           UniqueSubRange2 const& range_q,
                           UmbrellaStrategy const& umbrella_strategy,
                           RobustPolicy const& robust_policy)
        : m_range_p(range_p)
        , m_range_q(range_q)
        , m_robust_calc(range_p, range_q, robust_policy)
        , m_robust_range_p(range_p, m_robust_calc.m_rpi, m_robust_calc.m_rpj, robust_policy)
        , m_robust_range_q(range_q, m_robust_calc.m_rqi, m_robust_calc.m_rqj, robust_policy)
        , m_side_calc(m_robust_range_p, m_robust_range_q, umbrella_strategy)
        , m_swapped_side_calc(m_robust_range_q, m_robust_range_p, umbrella_strategy)
        , m_result(umbrella_strategy.relate().apply(range_p, range_q,
                       intersection_policy_type(),
                       m_robust_range_p, m_robust_range_q))
    {}

    inline bool p_is_last_segment() const { return m_range_p.is_last_segment(); }
    inline bool q_is_last_segment() const { return m_range_q.is_last_segment(); }

    inline robust_point1_type const& rpi() const { return m_robust_calc.m_rpi; }
    inline robust_point1_type const& rpj() const { return m_robust_calc.m_rpj; }
    inline robust_point1_type const& rpk() const { return m_robust_calc.get_rpk(); }

    inline robust_point2_type const& rqi() const { return m_robust_calc.m_rqi; }
    inline robust_point2_type const& rqj() const { return m_robust_calc.m_rqj; }
    inline robust_point2_type const& rqk() const { return m_robust_calc.get_rqk(); }

    inline side_calculator_type const& sides() const { return m_side_calc; }
    inline robust_swapped_side_calculator_type const& swapped_sides() const
    {
        return m_swapped_side_calc;
    }

private :

    // Owned by get_turns
    UniqueSubRange1 const& m_range_p;
    UniqueSubRange2 const& m_range_q;

    // Owned by this class
    robust_calc_type m_robust_calc;
    robust_subrange1 m_robust_range_p;
    robust_subrange2 m_robust_range_q;
    side_calculator_type m_side_calc;
    robust_swapped_side_calculator_type m_swapped_side_calc;

protected :
    result_type m_result;
};

// Version without rescaling
template
<
    typename UniqueSubRange1, typename UniqueSubRange2,
    typename TurnPoint, typename UmbrellaStrategy,
    typename RobustPolicy
>
class intersection_info_base<UniqueSubRange1, UniqueSubRange2,
        TurnPoint, UmbrellaStrategy, RobustPolicy, no_rescale_policy_tag>
{
public:

    typedef segment_intersection_points<TurnPoint> intersection_point_type;
    typedef policies::relate::segments_intersection_policy
        <
            intersection_point_type
        > intersection_policy_type;

    typedef typename intersection_policy_type::return_type result_type;

    typedef typename UniqueSubRange1::point_type point1_type;
    typedef typename UniqueSubRange2::point_type point2_type;

    typedef side_calculator
        <
            UniqueSubRange1, UniqueSubRange2, UmbrellaStrategy
        > side_calculator_type;

    typedef side_calculator
        <
            UniqueSubRange2, UniqueSubRange1, UmbrellaStrategy
        > swapped_side_calculator_type;
    
    intersection_info_base(UniqueSubRange1 const& range_p,
                           UniqueSubRange2 const& range_q,
                           UmbrellaStrategy const& umbrella_strategy,
                           no_rescale_policy const& )
        : m_range_p(range_p)
        , m_range_q(range_q)
        , m_side_calc(range_p, range_q, umbrella_strategy)
        , m_swapped_side_calc(range_q, range_p, umbrella_strategy)
        , m_result(umbrella_strategy.relate()
                        .apply(range_p, range_q, intersection_policy_type()))
    {}

    inline bool p_is_last_segment() const { return m_range_p.is_last_segment(); }
    inline bool q_is_last_segment() const { return m_range_q.is_last_segment(); }

    inline point1_type const& rpi() const { return m_side_calc.get_pi(); }
    inline point1_type const& rpj() const { return m_side_calc.get_pj(); }
    inline point1_type const& rpk() const { return m_side_calc.get_pk(); }

    inline point2_type const& rqi() const { return m_side_calc.get_qi(); }
    inline point2_type const& rqj() const { return m_side_calc.get_qj(); }
    inline point2_type const& rqk() const { return m_side_calc.get_qk(); }

    inline side_calculator_type const& sides() const { return m_side_calc; }
    inline swapped_side_calculator_type const& swapped_sides() const
    {
        return m_swapped_side_calc;
    }

private :
    // Owned by get_turns
    UniqueSubRange1 const& m_range_p;
    UniqueSubRange2 const& m_range_q;

    // Owned by this class
    side_calculator_type m_side_calc;
    swapped_side_calculator_type m_swapped_side_calc;

protected :
    result_type m_result;
};


template
<
    typename UniqueSubRange1, typename UniqueSubRange2,
    typename TurnPoint,
    typename UmbrellaStrategy,
    typename RobustPolicy
>
class intersection_info
    : public intersection_info_base<UniqueSubRange1, UniqueSubRange2,
        TurnPoint, UmbrellaStrategy, RobustPolicy>
{
    typedef intersection_info_base<UniqueSubRange1, UniqueSubRange2,
        TurnPoint, UmbrellaStrategy, RobustPolicy> base;

public:

    typedef typename UniqueSubRange1::point_type point1_type;
    typedef typename UniqueSubRange2::point_type point2_type;

    typedef typename UmbrellaStrategy::cs_tag cs_tag;

    typedef typename base::side_calculator_type side_calculator_type;
    typedef typename base::result_type result_type;
    
    typedef typename result_type::intersection_points_type i_info_type;
    typedef typename result_type::direction_type d_info_type;

    intersection_info(UniqueSubRange1 const& range_p,
                      UniqueSubRange2 const& range_q,
                      UmbrellaStrategy const& umbrella_strategy,
                      RobustPolicy const& robust_policy)
        : base(range_p, range_q, umbrella_strategy, robust_policy)
        , m_umbrella_strategy(umbrella_strategy)
        , m_robust_policy(robust_policy)
    {}

    inline result_type const& result() const { return base::m_result; }
    inline i_info_type const& i_info() const { return base::m_result.intersection_points; }
    inline d_info_type const& d_info() const { return base::m_result.direction; }

    // TODO: it's more like is_spike_ip_p
    inline bool is_spike_p() const
    {
        if (base::p_is_last_segment())
        {
            return false;
        }
        if (base::sides().pk_wrt_p1() == 0)
        {
            // p:  pi--------pj--------pk
            // or: pi----pk==pj

            if (! is_ip_j<0>())
            {
                return false;
            }

            // TODO: why is q used to determine spike property in p?
            bool const has_qk = ! base::q_is_last_segment();
            int const qk_p1 = has_qk ? base::sides().qk_wrt_p1() : 0;
            int const qk_p2 = has_qk ? base::sides().qk_wrt_p2() : 0;

            if (qk_p1 == -qk_p2)
            {
                if (qk_p1 == 0)
                {
                    // qk is collinear with both p1 and p2,
                    // verify if pk goes backwards w.r.t. pi/pj
                    return direction_code<cs_tag>(base::rpi(), base::rpj(), base::rpk()) == -1;
                }

                // qk is at opposite side of p1/p2, therefore
                // p1/p2 (collinear) are opposite and form a spike
                return true;
            }
        }
        
        return false;
    }

    inline bool is_spike_q() const
    {
        if (base::q_is_last_segment())
        {
            return false;
        }

        // See comments at is_spike_p
        if (base::sides().qk_wrt_q1() == 0)
        {
            if (! is_ip_j<1>())
            {
                return false;
            }

            // TODO: why is p used to determine spike property in q?
            bool const has_pk = ! base::p_is_last_segment();
            int const pk_q1 = has_pk ? base::sides().pk_wrt_q1() : 0;
            int const pk_q2 = has_pk ? base::sides().pk_wrt_q2() : 0;
                
            if (pk_q1 == -pk_q2)
            {
                if (pk_q1 == 0)
                {
                    return direction_code<cs_tag>(base::rqi(), base::rqj(), base::rqk()) == -1;
                }
                        
                return true;
            }
        }
        
        return false;
    }

    UmbrellaStrategy const& strategy() const
    {
        return m_umbrella_strategy;
    }

private:
    template <std::size_t OpId>
    bool is_ip_j() const
    {
        int arrival = d_info().arrival[OpId];
        bool same_dirs = d_info().dir_a == 0 && d_info().dir_b == 0;

        if (same_dirs)
        {
            if (i_info().count == 2)
            {
                return arrival != -1;
            }
            else
            {
                return arrival == 0;
            }
        }
        else
        {
            return arrival == 1;
        }
    }

    UmbrellaStrategy const& m_umbrella_strategy;
    RobustPolicy const& m_robust_policy;
};

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_TURN_INFO_HELPERS_HPP

/* get_turn_info_helpers.hpp
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
*/