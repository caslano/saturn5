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
Z84EonSxSV4Fey2dZQq//KKgirglNlVFK3GY2n1IH9bkK4FSmq/TF7X39kf0Tn8oDv6VKRKn4HycRBclIN7vnmENftF4d4DqxFcGdJOkO+u42TOjGpvhSfPlSqKeHQnis6tsB/tFCe98LK4NIbmmAByo2wcEsrK+PA3jQ+SZvijEsQhDa8fTlqE7+i5Ust+JYasv+k1bZPx7Sck/EABMXOlvBOZTBJlXM6XicQfZxROI0+3BROJUC/rkHAthLsJeCcJphXP+qGavxRoflZTP1/SijatYAMEhphfNUlDP6sQqAKKWgVfafpnmi3qtppB+hs2H8TojAPBMv9aGTs2T3aFtlZ+smRLuP6zgEacPBy0EpPqNkQntHqTuw0AixgbPQcCAL3qHbCBouGWzdlqbcVmNXGJKoxNnSJOjmuQjnwrsbX9AKhzE9MMUbjf6xUbjEqnwkOOLjHeYOAVRnh1Vn0iM8sg7EzxifHsyH3Y0tQI4EaGmqEYgoG3ADJNt6gf4tO0oB9UNOGxfAYtKIB3r+Ha8oJf1eV/kBgcS1RQkAOFJJVtkWgKHv1Bxuw+Tqjk5R+jPTnVtcC4aDl4rM08WRBUCMzNy66aa4Fx6NTIlngxga0Yh/Wex3yeuTCWuhG2Z/PNutQ4GUrV2pzNjNjnMj/20eJTitZh5subdqxz7zKxyDlBxFHvUuWq8NWwN4AQ/7DsDC8lplH1L77TOQ4YpZ/AZPztS5yErpfNA1I6MPyRyQg1Zoac4taCtcmqmE9emJpo1zAS+0AYHmzZiBZFVJLVSXE/IRnUu6g3klEhIjISiM2JhBWz1Rb5PLQixPSLalV5EJEQFiUhIKkTk3oCFggw4sDDzWZ5L0ayxtw6isovRpPj++OA/+WjX/3//gh9VMBtrV6cEQDyb7hEL74VbbPJKrl8WuU2heYcG1LypFSQaITiu1GGPdJ9oWt/TflDdaFcf5qT8g7lJeu2VsSkrHzO8ZftIn/mqRFsAbmDrR5gWKklliz8EeE4zUPGglPmdYDR9R3LrfJxh8QfqDmd0Kf0bJ6V/BZ6KB4bvlixLPdQ1IFi85g5zmX9LKbVtuYcr/ELMmCuNuwoUZ/D7YBUiNDasCzjnVNz/FkbEnDlY1tvkav39PXB7xYa6jfNPDZRsSgaQe9WNetjeR8cWVRCGXU/dxgWvJUMMnr4MYSgs0mFyPbEhvPhEJuVxPUTvWW9yasiBtnh/zm6iIda7l+IjPv0tOcV7+N10raxweZqN/haFiumK5Spts49/lqzY+cZ6p6rYGlOqWW/h+wlJGXD7PS+Av5ke8ZRZwRC1GJQ+r3iIXQ0mqslOxPHBQSzGO/MkNXhrlSMZhlOwkcWCfwrKo78vCn2IwWi94mDvRDORwvXprA9dn9bkeSIIz3D74o8h5GOiWa5mWmdogb1fMN9TcYMjmINAaZkhUllhsBN7Iwi65UfIRskBG8nynGD3uD50Lp5i5zLdt6YP+64mN1CBk1fOOp3Qc23OxSfnqOWsthwkFFDHU3FtubPu8ixG6odDcvKjfw10Zy56P6D6GCQTOyZ+IkLUXK2vJV8XXruV1ysSCzZ7SxyeigkOj9M9wUHp4Bk81ptab8SUAl1grR1fiPs+bG6JHJbE+ILEBBzOa0zUvO6tKJyd1zJeqkXGarHqQYeWJK9fMruZvd25qNzKHIXEu/KRvKtPNs3MpCpUIf0rVrRKajgXDjQfo3rKH9rrJLV8l1063pCO25TjTelYZO8mCxumViZKw/uLE+Tq1KNY8Ddz1W7AneguFhwNN3rrkIVpnwoHA188S71/dqOKlA94Gn97Z7PU+7SUGMhEQAy/w0zsoWc1Oq7qLgj8+g0=
*/