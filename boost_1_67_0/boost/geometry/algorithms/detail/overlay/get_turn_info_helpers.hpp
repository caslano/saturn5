// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014, 2015, 2017, 2018, 2019.
// Modifications copyright (c) 2013-2019 Oracle and/or its affiliates.

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
#include <boost/geometry/geometries/segment.hpp> // referring_segment
#include <boost/geometry/policies/relate/direction.hpp>
#include <boost/geometry/policies/relate/intersection_points.hpp>
#include <boost/geometry/policies/relate/tupled.hpp>
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
    typename TurnPointCSTag,
    typename UniqueSubRange1,
    typename UniqueSubRange2,
    typename SideStrategy
>
struct side_calculator
{
    typedef typename UniqueSubRange1::point_type point1_type;
    typedef typename UniqueSubRange2::point_type point2_type;

    inline side_calculator(UniqueSubRange1 const& range_p,
                           UniqueSubRange2 const& range_q,
                           SideStrategy const& side_strategy)
        : m_side_strategy(side_strategy)
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

    // Used side-strategy, owned by the calculator,
    // created from .get_side_strategy()
    SideStrategy m_side_strategy;

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
    typedef policies::relate::segments_tupled
        <
            policies::relate::segments_intersection_points
                <
                    intersection_point_type
                >,
            policies::relate::segments_direction
        > intersection_policy_type;

    typedef typename intersection_policy_type::return_type result_type;

    typedef typename robust_calc_type::robust_point1_type robust_point1_type;
    typedef typename robust_calc_type::robust_point2_type robust_point2_type;

    typedef robust_subrange_adapter<robust_point1_type, UniqueSubRange1, RobustPolicy> robust_subrange1;
    typedef robust_subrange_adapter<robust_point2_type, UniqueSubRange2, RobustPolicy> robust_subrange2;

    typedef typename cs_tag<TurnPoint>::type cs_tag;

    typedef typename UmbrellaStrategy::side_strategy_type side_strategy_type;
    typedef side_calculator<cs_tag, robust_subrange1, robust_subrange2,
             side_strategy_type> side_calculator_type;

    typedef side_calculator
        <
            cs_tag, robust_subrange2, robust_subrange1,
            side_strategy_type
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
        , m_side_calc(m_robust_range_p, m_robust_range_q,
                      umbrella_strategy.get_side_strategy())
        , m_result(umbrella_strategy.apply(range_p, range_q,
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

    robust_swapped_side_calculator_type get_swapped_sides() const
    {
        robust_swapped_side_calculator_type result(
                            m_robust_range_q, m_robust_range_p,
                            m_side_calc.m_side_strategy);
        return result;
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
    typedef policies::relate::segments_tupled
        <
            policies::relate::segments_intersection_points
                <
                    intersection_point_type
                >,
            policies::relate::segments_direction
        > intersection_policy_type;

    typedef typename intersection_policy_type::return_type result_type;

    typedef typename UniqueSubRange1::point_type point1_type;
    typedef typename UniqueSubRange2::point_type point2_type;

    typedef typename UmbrellaStrategy::cs_tag cs_tag;

    typedef typename UmbrellaStrategy::side_strategy_type side_strategy_type;
    typedef side_calculator<cs_tag, UniqueSubRange1, UniqueSubRange2, side_strategy_type> side_calculator_type;

    typedef side_calculator
        <
            cs_tag, UniqueSubRange2, UniqueSubRange1,
            side_strategy_type
        > swapped_side_calculator_type;
    
    intersection_info_base(UniqueSubRange1 const& range_p,
                           UniqueSubRange2 const& range_q,
                           UmbrellaStrategy const& umbrella_strategy,
                           no_rescale_policy const& )
        : m_range_p(range_p)
        , m_range_q(range_q)
        , m_side_calc(range_p, range_q,
                      umbrella_strategy.get_side_strategy())
        , m_result(umbrella_strategy.apply(range_p, range_q, intersection_policy_type()))
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

    swapped_side_calculator_type get_swapped_sides() const
    {
        swapped_side_calculator_type result(
            m_range_q, m_range_p,
            m_side_calc.m_side_strategy);
        return result;
    }

private :
    // Owned by get_turns
    UniqueSubRange1 const& m_range_p;
    UniqueSubRange2 const& m_range_q;

    // Owned by this class
    side_calculator_type m_side_calc;

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

    typedef UmbrellaStrategy intersection_strategy_type;
    typedef typename UmbrellaStrategy::side_strategy_type side_strategy_type;
    typedef typename UmbrellaStrategy::cs_tag cs_tag;

    typedef typename base::side_calculator_type side_calculator_type;
    typedef typename base::result_type result_type;
    
    typedef typename boost::tuples::element<0, result_type>::type i_info_type; // intersection_info
    typedef typename boost::tuples::element<1, result_type>::type d_info_type; // dir_info

    intersection_info(UniqueSubRange1 const& range_p,
                      UniqueSubRange2 const& range_q,
                      UmbrellaStrategy const& umbrella_strategy,
                      RobustPolicy const& robust_policy)
        : base(range_p, range_q,
               umbrella_strategy, robust_policy)
        , m_intersection_strategy(umbrella_strategy)
        , m_robust_policy(robust_policy)
    {}

    inline result_type const& result() const { return base::m_result; }
    inline i_info_type const& i_info() const { return base::m_result.template get<0>(); }
    inline d_info_type const& d_info() const { return base::m_result.template get<1>(); }

    inline side_strategy_type get_side_strategy() const
    {
        return m_intersection_strategy.get_side_strategy();
    }

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

    UmbrellaStrategy const& m_intersection_strategy;
    RobustPolicy const& m_robust_policy;
};

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_TURN_INFO_HELPERS_HPP

/* get_turn_info_helpers.hpp
FqEjrz1ICTdTKQ1u3QYvM6OAQz371wRdSBQTlDAPJYf6LuFdkz1+CSE0Lr4ACwAw22fpBEonly3hqlVO80Mmb6DDqW1xhn+R5Q1d7ubkg5xf0KcaawSRKCTVhz0VUCs06d1D57VKAq0kOtCkNzVLKFdMOZ9Qwiq14MGsRlCHAUoguudJY8UVPWDfIAkI7GZhyafvxzTLWi02gBxqrodWBF2Jk8BQQpigtVoQ3b//J04Sbflkn1lyma7WjbL6dXWIgRmRmhRJKkEe+BLDprCQ7Yl1fPg+3ycves8Xuyo3TSUCT3YMNNXZ6NM3SusFRkHGPFFyNAXs/MrUFSusVjBx1LWKi9Wn3ZCbxapY5IaXPqUDg2N1m6RnpJRPkPT1ijbaphZrmxqB2XlsSty9KE4MLip16FhP2jgcUZoqwscnrXfBCMIW1GAwjRtP00EzqDkSdsUTl8HGsFlubVS7oAflBfnDWqIVdkHai2rI+jro5ayt7xcGxRfZ1yszCNKZ9NBbbNj683x0Z+gJZSoYDseDSpvk3OXsqP7su8SvmyHSQra/TFgTqr2U6N9Udpy8YO7sC7h5IFmTulCjTHmtvV2kvJExQwz2uTZqWvPul5nvI6sYEvmxmhQ7iw8zaQi+AqNu6+DFSp31Yus8vw9kHeoo83PAlWRlbFaIq2JkPniwAU4ykpUf7PlkcmHSCbEsHWrZJeEztTO7+MwQbi2zgRjv8+VhWlMy7D8bsNBp0wFuxZS8yV2FzbcEihr8Vn1KOEa+aWB0ScmrMdT0YN4lTq1L8RBF74sQxOvLbhqkBzC/xorjsBSh1t0kZiDj4wpa/pJ3RwXma5xpywCkI6NSAAx8Pyju3bbwtWfWRsS4dLnJRyTjmU+2ot5jdPkqxFOH0znUHcjNwMjhkTlN/0/QyJIxaxR1wFTvk6jhhmCTCD2q9E4q6gAe2U6RiAKcg86FCX5bQYpi03+7OQTVhg2qgqRIvSW1k0gKXPlmQII8Sie4vNK5k7blVqxjv1vGT7Bh5EvEwlfM82q28BqchC/aEycvuf+/OWoIx2PDMvuRgzjTuK2Of6A0Bd/lYkAaV+lsh5qbttriutwM5ktobkhVtrbUwy096a7mfakKgoefh0QUlcE5j06BWDHEMddnBpA8XRfiHxq6qepingmGnpl+R9Dvw2dWPWGHubB+dhLI+4k+e4vSz66SCD3iPx8+IhFlY3S9tWPIlAtfPiJZykUv0CJvXr6OTuOl6URq/LOPvDJY7d6e5N4ZCSVqeq3TT2BxnPgIQwQUeBxnyzODFnFXXb9hYdmlki15h53Mqicx7sc8NNY7NM5tgha0uDdFIY9bK+zDXJvTGylZC0tYU+av/wHGyClTUlFXOSYqQOgQiSPycWesLRUoiURy9vmaHDvPh/Vr7/4uGzDrtABsmx3+XtapQv7n598KpkRnrn4CN8IbtVph+M/RdBI12CXbETd9gGMOmZabIxSBtWYk1J163lv9dF8Vq9Pqxb8kz42YsnI9AJAow5VoOfNtyCCapp2EpEHFQQwB8xqnHQOu1HpOZdhpbPmc84wX9JuEZSyF7WAjoLZsFI/VWgnTlaFY4/a1k+I75zlQgZxrtOPG7Mj721ZzlUH+UalwXL4TfLqdz/uLvvflyuC994BnVwiPxHNn8Me4L+d1KezY5qqK+qKNp2z50ZePO/xDBxJGYAL3xdrohEo2/yUK6SPCwV1wF+l5gSan7N/dUMf64m2I30/AL/3XqdPXKf0PML9la/0WIkjbNJYtz1BN2SL4PXxTFM8TC+wBAfbQa97wlJPTBP5FZLE5wWsuwfNgQe4A/rQkLWy1pIaNARpPrILcBKkUVWhtDLpWMtYi/RQd7DxVLM7Jah277IBLst/bQZveGRGPcDWN/4vDs+/LOt+4eBaYJRDs0vW7sTwHJCZSDeZ/umnUkS1fVxVImCLHJ5dHcnokq+Ns9AJXHSEUOshcrgZotVYF33m1v7lZFt+/8R0QVPtqTYihdoFhNAw9N/mZt9wTr/4bgyM8oVD5vIWxvavomAnmk7HAlLcliYyE3LdCFjBuISlmAeXPK1Yepu5ate7WHYhgZYJUu5RG9sS2HJkpU+zmTm2O+JzAsZGXz7HhK+qOc3beyyT0M+bnvwv5g94f4OzcDYNo6z56B/jxPt+7+ZBT68zM4oBR7bv3TtilYZjv+dZB0aGSHoiHtky3ON59G1xyiemGhlMjvGLsgx2w21PNqXc2F2UhEplcfahRkvpwngO4HiDgsb3XBrfcA6Nyv9p4grqO8xbow2T3jE0ueTnfuKI+OS+ILZA+EgZueVreXNtqsHWHd5xPlDskovaEMfr9wpj93a1CZC2iZuCTg9fTmOmGJ+sKBuO3A9ed5EDvt/M+mCO16wNaQ6avWCH2beCHiArxXzytTXUscIBYOzFwDsK3gREaTQQm65A4etvhDl2oczMRxnx3jGDHDIt1Uw0UjUNzLqhrpoZnpnu0puHxGIQcLLOIyZP8L/bX6lXKmzPV0YlwW9RQnY2ndajjKbqiZISuWkKSZ+TdBZs/ryjJULtK8+gVEJ0QKJAw5RlifF2nteqbdPmvyahRzY0vCF8AVjaSTpTcEzuBCt+2i26Uoc7lh2/QyncThNd2fQGsNzH0GmiPJYlHZLhvF4PjqW6iYn5pKGXtzSQfMBU5rBiMSo9LFM0OrKDp52BPwjX1tqwGusnZ8/Er09klaeWbHet16JY8F1Ai0r76cyPmHoS2sk3lU6/Atc1bA44R9Gp2XybMEIC0bgwXYEMjpO5JFsxg3V0AGW/b3Vdla0xHvDEUqjrgBpj7GhqFSjlVqrIUVtS6vDt4tgyFdUG0YkxCCJmd9e7nqzIXm9GPnymmZpiv72t4DeObhgma4RirIx7rMmo5S3fK2WPeZ3YONDT5jP91bizWCVPaCTqgWRCbUi6EHxXKa4o5RFHBJ4USXcFxMETdz07DRy4DitzQZEqvj6OE3XQ0/hAkhUxgglXJuTS82h3IvjrSNUEesmNwzTc8hmN5iNNcdlS3nWCCdfCyBKFfvmDHU/k/gkXxPJQgr3xWqKWjPmBjhNNWPi4BWiDuLf3YQ2xfdvG2HBkmmX2+44e1rCtstw+cGPXXhg3ZjhDyELueglnqx90LvAAfqYEwurQNgSRTrVfdRSRi0uJNM9HHaj/VN+f/NwgnhF7epD9VMaeK9WkOK0dtalM7ggTavuoijwXn6JE+uMGLmqO/e3sLDA2fNbJiLVAOaByqi3y9PUqfgaKvz1x3CbexxmIqc/iIy9IhmzfU0K1McfO5eL40LmIlxj1V9vr+V13KoURwxKu/nC2zzYM+/C8pyxHVaRddM7GoqIt1ITzzkeZzl187ZTpCh89tm0QtG/VmP3OqYjyThYb8PrzzI5XAZyHvZm0C8/d88oa5dqVrfmeSEe+vR5NBqC8Du2mhOTiH5EXCHJwokAj5XII4Z0PSkDQ5XhT3gJ2LdojuNbvOFHFiUeypwVmN1XT4Pqxe6XCAl5w2w/wHEd/HwW0LPUKYl0p0lVLWRa2bcmPAnJnYDO6vgIodM0AhURtkGG0nhSA14y/1ULy8GQRSn0ByRzvbDw8+UMuorPuNhVso+JHfamLaUNVgrp6C5s0icQ0BiLH40YB3BmOqg4gW0q0idpd+1NMf2IeL8Y7ExYExRPICUcQ3lXWBLKgCPcjb4AMJSk+g0OQ6p5BEY6Cop/h218tg7wPNlTBg7fiKJuPRzc199hWvHLn48xvNkTgOj01CpgGt9PZcYE9TkZGWUk8sOz20T0oREFAvxaCVd6DRAhG4XsghL5li8bEjxZ5LmPE6dtiOztkQiqbSxNtYrTwvj/8yxnxGWaUTAz6kpegz0QSFIvP2Hgd+DPROzhii1uwaF5Va7/ExTOPAbyZPJCa9fVUZgVg3qZkoF+cGCihs+j4fF30Y5V1hN5DhoLw+ggLROpLj/O7i0r2HUzOJcohYj0QfYiKNQ9AX6bW+FPpuQTO+klPY8AnlmAGe+BksPL7XTjVPTNAw5znIYKHAt2lStJMREfZ/xYzWfssZYrEUsZyKqBsZtjZRQrmbtB4rwdWhoMk7vQ4B5s4uDF8mTJKiPlW3Ge3TNSa5AuO8tvAmTx8sQk3qt6A309bbcPIaMP9tg0/H6o7VSPZpTOyvAcaSR5u+aLCafj8sN8avl3m7+EEzEy/zUanP1QPLFV6cxNkVSSlZ7qpoegWyxpl8caOH8vLfxJJAptVy2KPV8CjrghdgUWFRQfg7aNYoHAvZlMajqDPtjL7YcZZMa61SRAPZGjfC7dlGnlRsDjrCWX2T6Gv72wJxiIGu3D0zHLExc5BfcBkV6XWLihHXYfQGsHimViZW/Vp65e8p7zF7WjwJOHIXHD/3PRsOO6VlXKrw3FpO0xPflshoLYHi4SAqfBaNbwKjwdoMRk0U9Ir3hpH+mmN5VfImZ2M+VA/+R+UFEAHn8PG+7i3EbCuDtfRmHWGUga6MLpM2VU8hY+/yQmA5L8bFsZQ+2DU7EuYhukH/+xSSb/Cyk8Y5dYgnjXfSznrjTyj3URNwoxVBsBvl5FM2eDIIChxFlAKOvUAbD78rYtkugqIMGIYb2+FlftwLVd1bj2YmwDK10rW4FHA2vMs04UOo2ZxlkGeXk+1gyHuU2gVC2gxgb27KHhy4NG1TOGhrnnlRn2sQWbluvBF1g+GC77CM0PEoxt3dtNx9zG8kZ7XwPg4Dq6W5exg6hMt3YELnw/WfV5fEdowDTTCVfexmb+P0tqFkZtBMjJiDgvf+cUo7jGsPLbeXNhkiF2xdfVbDIW+CqiltyNgZE02IiB+25r+cj6Vi+ouAp2J5Lk29f6ferzmXn6DQkOvbHp75R2N5I246T9q7bjTRk0qpodF0MNAI+bUx6/TkbYLMHrGWc10ov6bRed+5Nm+Y58aL3UIGE4nWQyxyRsaaDHVTwZCakWPmKtgMwUCYyzUEiRJYUepiMP+mezsCsDyCVYEQWPERUhrWhtjHYhTcG1XQQtcp3OXR8Ja0M3KBGLucQXLK1pP0WLFvwrAmNGNvskT2XbtewVjzK5vqXlNS+jpEjiZg5IA3UQ1iNmvsBDa2T/7L8TsR7FY+g6Q0fv1cVrsvz8XBxhCK/ocBbK0F1+VACKIy6rl/o3wSoPOz5B+Ki06P3wBz3k8TckQgQ/E4sMwyX4uIiUolWstjliKhX+pXLbahYmQCw/o+01Bi4SgkbyjjB9Qidy9fp/eqqq69fXWh0OYdh1dTW6sXO5+BCaU+u9xXEVO7+gvFLJRLD1fN6oUgTlWYaGMyAVSYp4pKrpL2SuktxJAJaSME/G/P0jQevWbUG6K2DFDV+M6wwHjdsrKa0tLRQuWryJzZuyhJ1K0ddmW1kW+1iOoigIOiZAcAaUc/3kzJP87wJNBuArN0XKr5WKTqVZF2T5z1xgClD97N3QB2tkIBM1J9WGR34ANq9h+9UX/r2YFMZV2VQkLhvGHDPGBZpdXStjWs3cE65fW7xoXtKwNHWDekXCHHlRhaYem7/au1628iMKZF4DLgiQBFcQPE9xrpYqO/MWEAppGp0h2d8YelnJll++bHdajyrZrkUmiEsgeI81ZHDKKP3h0xAyhLFaDn0Y6lzSiSBx7Wd9EMlbJuMIZ3/nRqgx8PoM3C3b7Jh9Blx/YZE96S/7R+byjYElK516GWjNClRPPywnNztWZHvmZHS4cmJSRDo7PAf+ELb/CNGpt+FMSBP55SnzcYHRThNQu1EYVSz5UF5vy9GYg2IA8VTYVuSNakytdLq2GbRs753OFwSWTg4uVBs+RPpjkmIBWJMYWqZKIf3DOIYbrDYmDj0Ew0F3fZ0f91xfM8Ips1mPFmn5bQo3uwgkxQ+OA6jl9Vs8txP7BCZR+EL2AxFb7eRUHFIAPpkxWY/LIVY5uRJ3un5waOw8eTZEgPCJnni0CobPL/5w57p1akvZWYCG3IBUzSjg294tUoIm42JzDRNPAL9NCluYMcMUMbfeQGijS/pcc3CLWGoGMr1Lry+wXHqEb4hDY+coEI2CvYF6q5atOPDoPWF/X0jeGUU6I/6xAEeWWhqHfx/br2aHToZjgrTx3AM6v+n9HsiDrYizcjVQBP9FWOPOWL9TjY1bgCpwZxzzRsjvDq1uXClrWCo6BGI718wkC7CN0hlU0HFO6EHrD8v2cFYB0OaUDR524qbLLhWd6aHYlolShgsuxh00JWQX0ReSbmvXo/Qa1Q9fFbK34JS+CscF0D4BlJmz4oMnMzcS8JdSzU1X3+M1oAGxlwH4cBTwAinvWlbF88rlxrs4B7mqh0sI1mFr0yXCkD4VSSOEM8OSt7Zr5GlxGmlpvpWyudgkOM6srhOL5G66OENirZMHi1khVX8gwcTRgU9XzVTN3KL5MnGZt2GsDCqgVTnzKksX/TEeRfm/09lM2BkUrgXoiuo/HSbYHRETkH2RvpZ0nf0Chf9MWBwuVLkgXlRi/zd5I5UqoNNMtTSd9384D8e/nLiK8BZUXi8L7TSGIRqtyAdV5VNtEY7SQcaloGArspu/0bkTHEsQQvqeia2U4hOH1pZL3hAvgnbCW4l59rWrEA3WPgQK7Lt2224uWsiTRF/zGIVNDoVlnHHG4mYcDIXr5RMPb53d3JP3ZXfSNYl1/qrw2aUj4QFAdQqKC+LIqReyrI48dmEz3zNzZ3IYoh1WXzFFFnM4ySk8N856uSijeWuQkzcwC3dZFfnaMPWDpqXaJeXFAvL57XMFbm2DgeH8hX8Tdosbl1Wom0My9Rbhxd0ZoqVVifIYYvq3DBQ6V4pDXjIGj15VA2dMvuZ7eEaHIZBDPQwtODZGd0hTwT+liexcrW3KKH6T7sRK2MyaV6fBSD1sjSfaWuTFnORCgTMcMzKwvBMxg8UUIz4dAAsmYcxFZ5kcq6Ux6ciy2sOhyTC+tVd+NDtcHOXEUuKEjz8g/NBzj6gMfZe1ro6xuXm42plWmtg6MIleQKOIVVo8p/gTMhlUOv2ERdkv6Y72GOs/YGWUBeTVCDy/Rp3GESR4tRMhKzRuQFmayf7470nqITGPYJ+oD7Yq0uLBGJ6YB/m0S7lu0XwxgTAWmf3jeIhnHj0McfIBSaVTZeVeTvyAF2PUJiCcQjhDAAJ/E0nyAJSijo6CjewmCuFcgBwHszl+Q4EkyXxPLijiSFqG6Alr1YlqXMXPyW65qV1t1lwXtBxTXXkSzRQ7gjA8gOQGxbr0KK7oLPnmU7unS8kKT2ONzA1/ozTq45QQsSf764KR5MkhynS/2DGejlCNyfLvAw+Q0njIQX+wxmWpecW9FPVj/bK28SxAH2QooYjVmbK+Ypj7kil9UFs7k6wRGLjzkWBlk6Lxm1snfpACc2SxdLmrk/kDj8sNaTJ0r1xW6COczQnCu8/breKmBDGeSz3b4L7V8qd211yafRN8+d67ELsbFQPStqMQTRUB5A0+IawXJaYTUe6i2SnKV5VCduEra/zqMUmMKGkRlLvArnDItH1iD+prRUqw2ASZSAHxc/e2bLnbJzygZ4R92bcrqGilHuPIXDVbJDnlTYtdnO6n1ivU4F69fHtM92xNP5WLbefuBjpK5CfnjHxbImSrGZmppRqsU6G1zY/MhsO4l1H2JSi2rmXAKb71jvOWgJUq+/xFn0dyyEcGlkAm2UDPDWAjtCe5yBeGf5XP6lGkN+hzRucJV5iBP1BemrlbuHZI8tQGPBqzXTMDLqs+4v7liczOGgKglpybSL8ypExdOKBrN2d/P2XbzDkFS2x1C5u1o8R4mqMbPbvqcAd8UOqO7lcUj9VwXsMWfAoCTXkqsebnw/YF/c/wFESiYKteK9wOQsmWtkClXMrGibL906fYBRRUnDGSyBHRiNn7dlgAXHDz9hwO0p3TLYTMc96Hrt3zyJmmPw/fv7GzgAABD0J/hPyJ/QP2F//vsT/ifiT+SfqD/Rf2L+xP6J+xP/J+FP4p+kP8l/Uv6k/kn7k/4n40/mn6w/2X9y/uT+yfuT/6fgT+Gfoj/Ff0r+lP4p+1P+p+JP5Z+qP9V/av7U/qn7U/+n4U/jn6Y/zX9a/rT+afvT/qfjT+efrj/df3r+9P7p+9P/Z+DP4J+hP8N/Rv6M/hn7M/5n4s/kn6k/039m/sz+mfsz/2fhz+KfpT/Lf1b+rP5Z+7P+Z+PP5p+tP9t/dv7s/tn7s//n4M/hn6M/x39O/pz+Oftz/ufiz+Wfqz/Xf27+3P65+3P/5+HP45+nP89/Xv68/nn78/7n48/nn68/339+/gAM/p3/7n4nA1eoPEwr+TvtY/0dmYCnOcvNqSRDx637obANEzxuTfymxjPkhi0paB437mtvHjHz3s35mL4VL8lNmAxkLisFQxPWyl14UvXebXVSLFOR0ByEft59tPqMgu3UUlGC4rqb2A2HwCHyG3P6rz+wgjAbW1oH/d8G6Ri4dVbt+wJ431g6RutsXtJOYsSJAgXnhkx14Q9PEz8+7dHz6aPGCkOVLvB9Qo/1RKFFS/Em/HoO6mjfk5sPS1dc0KlppVernjfpmsqQfSEXkxpp5kLtx1l4eQyiReXySTTWEq5XXoqPeMTkBveF3jyK48p2pQCx8bjDWfAWrHqyLUUrAxtcv8QxUUp6qcEtQSPWWXiiDXF/7aKMeGCukcDLaqvu8PBPs+SP3NOtNXRUSCMfxgA4letTjvGdpMWoz4J+2TVfQGU2Pi2v/TeUZntiYC159brZvmV4Olv84A/JG6RK4Uob+0zeN934YdAloqPDMONsAdOTxPJ74VSwv4EaZd8YADmqahzUSxbBHOsSpnv8KRFm3x04zlMatkTZbMgURxN+6K1YtndcxqLyAXzufjZtEGWN60mbh/FzcSaKoSZm1HY2lwZyvs7+Y71NJ7q7Y3uDi50zITqI+2/NSBncP7ssIyWug1zWmnFk43S9L1NbxkWZboiTFuJ4AXT5Pmz1xhryqReKexQHM/XgZNqrxJAglGLIb13BDYjS/4JffrRGUP4YUv74PG8Ky87W4BQmICM0jx0tLmz16lzZn0/I/1cGQAoJQCoRQGzj1hZyDWFvZ1HCnwQEvpoFYeNK2RwKfgM7UDXLXzULdjp8TlBoLgJC0zfUOu943+lltlLRXy+iD3wS/i0J5I7ivM+IPQoNFtAN8S4=
*/