// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013-2017 Adam Wulkiewicz, Lodz, Poland

// This file was modified by Oracle on 2015, 2017, 2019.
// Modifications copyright (c) 2015-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_OVERLAY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_OVERLAY_HPP


#include <deque>
#include <map>

#include <boost/range.hpp>
#include <boost/mpl/assert.hpp>


#include <boost/geometry/algorithms/detail/overlay/cluster_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/enrich_intersection_points.hpp>
#include <boost/geometry/algorithms/detail/overlay/enrichment_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turns.hpp>
#include <boost/geometry/algorithms/detail/overlay/is_self_turn.hpp>
#include <boost/geometry/algorithms/detail/overlay/needs_self_turns.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>
#include <boost/geometry/algorithms/detail/overlay/traverse.hpp>
#include <boost/geometry/algorithms/detail/overlay/traversal_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/self_turn_points.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>

#include <boost/geometry/algorithms/detail/recalculate.hpp>

#include <boost/geometry/algorithms/is_empty.hpp>
#include <boost/geometry/algorithms/reverse.hpp>

#include <boost/geometry/algorithms/detail/overlay/add_rings.hpp>
#include <boost/geometry/algorithms/detail/overlay/assign_parents.hpp>
#include <boost/geometry/algorithms/detail/overlay/ring_properties.hpp>
#include <boost/geometry/algorithms/detail/overlay/select_rings.hpp>
#include <boost/geometry/algorithms/detail/overlay/do_reverse.hpp>

#include <boost/geometry/policies/robustness/segment_ratio_type.hpp>

#include <boost/geometry/util/condition.hpp>

#ifdef BOOST_GEOMETRY_DEBUG_ASSEMBLE
#  include <boost/geometry/io/dsv/write.hpp>
#endif


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


//! Default visitor for overlay, doing nothing
struct overlay_null_visitor
{
    void print(char const* ) {}

    template <typename Turns>
    void print(char const* , Turns const& , int) {}

    template <typename Turns>
    void print(char const* , Turns const& , int , int ) {}

    template <typename Turns>
    void visit_turns(int , Turns const& ) {}

    template <typename Clusters, typename Turns>
    void visit_clusters(Clusters const& , Turns const& ) {}

    template <typename Turns, typename Turn, typename Operation>
    void visit_traverse(Turns const& , Turn const& , Operation const& , char const*)
    {}

    template <typename Turns, typename Turn, typename Operation>
    void visit_traverse_reject(Turns const& , Turn const& , Operation const& , traverse_error_type )
    {}

    template <typename Rings>
    void visit_generated_rings(Rings const& )
    {}
};

template
<
    overlay_type OverlayType,
    typename TurnInfoMap,
    typename Turns,
    typename Clusters
>
inline void get_ring_turn_info(TurnInfoMap& turn_info_map, Turns const& turns, Clusters const& clusters)
{
    typedef typename boost::range_value<Turns>::type turn_type;
    typedef typename turn_type::turn_operation_type turn_operation_type;
    typedef typename turn_type::container_type container_type;

    static const operation_type target_operation
            = operation_from_overlay<OverlayType>::value;
    static const operation_type opposite_operation
            = target_operation == operation_union
            ? operation_intersection
            : operation_union;

    for (typename boost::range_iterator<Turns const>::type
            it = boost::begin(turns);
         it != boost::end(turns);
         ++it)
    {
        turn_type const& turn = *it;

        bool cluster_checked = false;
        bool has_blocked = false;

        if (is_self_turn<OverlayType>(turn) && turn.discarded)
        {
            // Discarded self-turns don't count as traversed
            continue;
        }

        for (typename boost::range_iterator<container_type const>::type
                op_it = boost::begin(turn.operations);
            op_it != boost::end(turn.operations);
            ++op_it)
        {
            turn_operation_type const& op = *op_it;
            ring_identifier const ring_id = ring_id_by_seg_id(op.seg_id);

            if (! is_self_turn<OverlayType>(turn)
                && (
                    (BOOST_GEOMETRY_CONDITION(target_operation == operation_union)
                      && op.enriched.count_left > 0)
                  || (BOOST_GEOMETRY_CONDITION(target_operation == operation_intersection)
                      && op.enriched.count_right <= 2)))
            {
                // Avoid including untraversed rings which have polygons on
                // their left side (union) or not two on their right side (int)
                // This can only be done for non-self-turns because of count
                // information
                turn_info_map[ring_id].has_blocked_turn = true;
                continue;
            }

            if (turn.any_blocked())
            {
                turn_info_map[ring_id].has_blocked_turn = true;
            }
            if (turn_info_map[ring_id].has_traversed_turn
                    || turn_info_map[ring_id].has_blocked_turn)
            {
                continue;
            }

            // Check information in colocated turns
            if (! cluster_checked && turn.is_clustered())
            {
                check_colocation(has_blocked, turn.cluster_id, turns, clusters);
                cluster_checked = true;
            }

            // Block rings where any other turn is blocked,
            // and (with exceptions): i for union and u for intersection
            // Exceptions: don't block self-uu for intersection
            //             don't block self-ii for union
            //             don't block (for union) i/u if there is an self-ii too
            if (has_blocked
                || (op.operation == opposite_operation
                    && ! turn.has_colocated_both
                    && ! (turn.both(opposite_operation)
                          && is_self_turn<OverlayType>(turn))))
            {
                turn_info_map[ring_id].has_blocked_turn = true;
            }
        }
    }
}

template
<
    typename GeometryOut, overlay_type OverlayType, bool ReverseOut,
    typename Geometry1, typename Geometry2,
    typename OutputIterator, typename Strategy
>
inline OutputIterator return_if_one_input_is_empty(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            OutputIterator out, Strategy const& strategy)
{
    typedef std::deque
        <
            typename geometry::ring_type<GeometryOut>::type
        > ring_container_type;

    typedef typename geometry::point_type<Geometry1>::type point_type1;

    typedef ring_properties
        <
            point_type1,
            typename Strategy::template area_strategy
                <
                    point_type1
                >::type::template result_type<point_type1>::type
        > properties;

// Silence warning C4127: conditional expression is constant
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4127)
#endif

    // Union: return either of them
    // Intersection: return nothing
    // Difference: return first of them
    if (OverlayType == overlay_intersection
        || (OverlayType == overlay_difference && geometry::is_empty(geometry1)))
    {
        return out;
    }

#if defined(_MSC_VER)
#pragma warning(pop)
#endif


    std::map<ring_identifier, ring_turn_info> empty;
    std::map<ring_identifier, properties> all_of_one_of_them;

    select_rings<OverlayType>(geometry1, geometry2, empty, all_of_one_of_them, strategy);
    ring_container_type rings;
    assign_parents<OverlayType>(geometry1, geometry2, rings, all_of_one_of_them, strategy);
    return add_rings<GeometryOut>(all_of_one_of_them, geometry1, geometry2, rings, out,
                                  strategy.template get_area_strategy<point_type1>());
}


template
<
    typename Geometry1, typename Geometry2,
    bool Reverse1, bool Reverse2, bool ReverseOut,
    typename GeometryOut,
    overlay_type OverlayType
>
struct overlay
{
    template <typename RobustPolicy, typename OutputIterator, typename Strategy, typename Visitor>
    static inline OutputIterator apply(
                Geometry1 const& geometry1, Geometry2 const& geometry2,
                RobustPolicy const& robust_policy,
                OutputIterator out,
                Strategy const& strategy,
                Visitor& visitor)
    {
        bool const is_empty1 = geometry::is_empty(geometry1);
        bool const is_empty2 = geometry::is_empty(geometry2);

        if (is_empty1 && is_empty2)
        {
            return out;
        }

        if (is_empty1 || is_empty2)
        {
            return return_if_one_input_is_empty
                <
                    GeometryOut, OverlayType, ReverseOut
                >(geometry1, geometry2, out, strategy);
        }

        typedef typename geometry::point_type<GeometryOut>::type point_type;
        typedef detail::overlay::traversal_turn_info
        <
            point_type,
            typename segment_ratio_type<point_type, RobustPolicy>::type
        > turn_info;
        typedef std::deque<turn_info> turn_container_type;

        typedef std::deque
            <
                typename geometry::ring_type<GeometryOut>::type
            > ring_container_type;

        // Define the clusters, mapping cluster_id -> turns
        typedef std::map
            <
                signed_size_type,
                cluster_info
            > cluster_type;

        turn_container_type turns;

#ifdef BOOST_GEOMETRY_DEBUG_ASSEMBLE
std::cout << "get turns" << std::endl;
#endif
        detail::get_turns::no_interrupt_policy policy;
        geometry::get_turns
            <
                Reverse1, Reverse2,
                detail::overlay::assign_null_policy
            >(geometry1, geometry2, strategy, robust_policy, turns, policy);

        visitor.visit_turns(1, turns);

#if ! defined(BOOST_GEOMETRY_NO_SELF_TURNS)
        if (! turns.empty() || OverlayType == overlay_dissolve)
        {
            // Calculate self turns if the output contains turns already,
            // and if necessary (e.g.: multi-geometry, polygon with interior rings)
            if (needs_self_turns<Geometry1>::apply(geometry1))
            {
                self_get_turn_points::self_turns<Reverse1, assign_null_policy>(geometry1,
                    strategy, robust_policy, turns, policy, 0);
            }
            if (needs_self_turns<Geometry2>::apply(geometry2))
            {
                self_get_turn_points::self_turns<Reverse2, assign_null_policy>(geometry2,
                    strategy, robust_policy, turns, policy, 1);
            }
        }
#endif


#ifdef BOOST_GEOMETRY_DEBUG_ASSEMBLE
std::cout << "enrich" << std::endl;
#endif

        cluster_type clusters;
        std::map<ring_identifier, ring_turn_info> turn_info_per_ring;

        geometry::enrich_intersection_points<Reverse1, Reverse2, OverlayType>(
            turns, clusters, geometry1, geometry2, robust_policy, strategy);

        visitor.visit_turns(2, turns);

        visitor.visit_clusters(clusters, turns);

#ifdef BOOST_GEOMETRY_DEBUG_ASSEMBLE
std::cout << "traverse" << std::endl;
#endif
        // Traverse through intersection/turn points and create rings of them.
        // Note that these rings are always in clockwise order, even in CCW polygons,
        // and are marked as "to be reversed" below
        ring_container_type rings;
        traverse<Reverse1, Reverse2, Geometry1, Geometry2, OverlayType>::apply
                (
                    geometry1, geometry2,
                    strategy,
                    robust_policy,
                    turns, rings,
                    turn_info_per_ring,
                    clusters,
                    visitor
                );
        visitor.visit_turns(3, turns);

        get_ring_turn_info<OverlayType>(turn_info_per_ring, turns, clusters);

        typedef typename Strategy::template area_strategy<point_type>::type area_strategy_type;

        typedef ring_properties
            <
                point_type,
                typename area_strategy_type::template result_type<point_type>::type
            > properties;

        // Select all rings which are NOT touched by any intersection point
        std::map<ring_identifier, properties> selected_ring_properties;
        select_rings<OverlayType>(geometry1, geometry2, turn_info_per_ring,
                selected_ring_properties, strategy);

        // Add rings created during traversal
        area_strategy_type const area_strategy = strategy.template get_area_strategy<point_type>();
        {
            ring_identifier id(2, 0, -1);
            for (typename boost::range_iterator<ring_container_type>::type
                    it = boost::begin(rings);
                 it != boost::end(rings);
                 ++it)
            {
                selected_ring_properties[id] = properties(*it, area_strategy);
                selected_ring_properties[id].reversed = ReverseOut;
                id.multi_index++;
            }
        }

        assign_parents<OverlayType>(geometry1, geometry2,
            rings, selected_ring_properties, strategy);

        // NOTE: There is no need to check result area for union because
        // as long as the polygons in the input are valid the resulting
        // polygons should be valid as well.
        // By default the area is checked (this is old behavior) however this
        // can be changed with #define. This may be important in non-cartesian CSes.
        // The result may be too big, so the area is negative. In this case either
        // it can be returned or an exception can be thrown.
        return add_rings<GeometryOut>(selected_ring_properties, geometry1, geometry2, rings, out,
                                      area_strategy,
                                      OverlayType == overlay_union ? 
#if defined(BOOST_GEOMETRY_UNION_THROW_INVALID_OUTPUT_EXCEPTION)
                                      add_rings_throw_if_reversed
#elif defined(BOOST_GEOMETRY_UNION_RETURN_INVALID)
                                      add_rings_add_unordered
#else
                                      add_rings_ignore_unordered
#endif
                                      : add_rings_ignore_unordered);
    }

    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(
                Geometry1 const& geometry1, Geometry2 const& geometry2,
                RobustPolicy const& robust_policy,
                OutputIterator out,
                Strategy const& strategy)
    {
        overlay_null_visitor visitor;
        return apply(geometry1, geometry2, robust_policy, out, strategy, visitor);
    }
};


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_OVERLAY_HPP

/* overlay.hpp
nwIjF7+kZdWvCaIzrx1mWqk8HdjSHKTAANy1DKpYSjbK8WVjtjDCui6phR0U1MEu++jhlL/68fcZUI3dsjTh69Cx2ID5Vu1P3faj2YPG+y8a8TeQfe1iBSZnW1LHfi/znjN8AsT0YfCW2LZWengmydg1Ct78bIo8jJKRFV7o+S+n/ukVt34Dx3u+3e06gCds6C0YJwmDNo9SWVJX5qQYFAeRL+vLA9ALnoN4JPr+OtUI+8tT7YpRWR6vlg1n6ae8W/FIF3jbwoVHbTtVmOOhhPRPejKAKf6lbdV6bGRTmpvvMnmzwMDqyTj6Yr80zkCy9417VtE9CHHhp9LoMy1TJkEeZPNko812+GvFG5PrQyHJ3wflR38iyuMzBj1FxR3sELLzeiSFx111AMVeE5HFIf2if1i6DODfEk9CwevjPtbt45syyUFCm1SyRRcXMKP4fiDJG6bBXSOeq0PSweJs0bcrRuQFaNIhnp9lP7b2dcVItB/7obSLN2LtY4dMY0wT+Yee0O2nEnGiIDe8FMrGn/LgzmpPZ2Q9cUN/0ZhSBmYcqP6bqKU1VpJoa/mFggt7EN16ih4C5JIphINMmgXzDsdDqKj1rqJve7rZQtPkFAu0ELU+vTAdJ3ccWBIj29xy8NlA5ZktHHLD/47ivLmpu5dq9XTRQoasvFyXX7a8Q5/LxYx8KbU250gVeyv9zkUJEYz18ZJhHTSbtn0K0XqqUOvAC+ztJwG9aixUf4SI7AWNTXkhYqYZujU8r8SF6ALTuXUaIGRXqJsj3C9qBo7sdTdF1jRXVxgPfhhkwjRQMGntARaEyWtnjGpYgDSs23LzaHqw1K2mKlmQ4KeiMHF9Roxgr3cVlfnGUEejem6mRHDrI5yFgS/yy/4CFQV9feV5/oXx+mp6XBjASa743CrkHAZn8z7Coiy4uR/F6EC0NEQ27RJiWcpC+Ts+xNs6HKcJjM/A67mLYnpRLCVp+GzGTtDyJO/hVGWi/oEvWRutxUztjVusMiwKK3FT6ARi+qts9j9nRgLG4E67mzKzUKCn663PDgHHPniR6ynp4chV1RwPU+0c7VhDc4CzxKPqhsaEgsco0PuV/5jHWq6loChMc3vW72Mt7yuSkceuLx30qDpfuwizCAl1uv9AZu7Y02iNhutpQf2xd681eRdpVDDxs0wJ+kunBE6dVVRH7GHVT4yVmeocZEm1j2HRNjp67zzrbPqiVGXpel0A6q0Qhlibj1xXo35pvuUzaAdwJ4z6Cdx1GTXGNAVhgG2z0DtWyLvKQ6vTUx2z3VTL9T8vjqD0RhnkvUB8spBEXmUqJWC70+Z9g7pXq5Mb6jPLHv5jw8N8x2ui/6WD0Wb+hcuV3Y+7RP8z4+0G+L3zAU/LBb54n+PiwfazUMDTOD+f5XXjqd2SQpX4hotJeDcbfuhTPvx7uIga/WtRgview3gXs8RG/GpbR4p8t9EbtPplZyZ03jT+7JM3csdyFfz/S+gpPnDeSSsrfovFNv7igaUkhgvlClUjbiuDxVDmCaXIJfGJi6gFIRx/xzHdWmRyxeZa/c2DTVLxH5wmfQwjMRzZ3UkyYS6cNiIU5ECUQZTk5eVtpU9qzYLVLXN32U53SX41T2+fCc8fTn/ZZ788Z9tOvWQqZOugIfczu3Mv4+cUnANHLIpk63pM0mTmyy6BrSY1MQEu5UjajAQiZOeHcav5svMjNRd4GcVI30vBCC6BSKEX//5eSS///cWQ3ttTWALpSGT2F8WfdCn74whOhHUZdmvZiX01nehNmo5k15OB+/lZqakqLSFqujmuSmWNYTFvpD0xltPRBbRGazVNLNJK0MxQSDqdl1xEa84WN4lklIUZZ+yBb++yEfT18l+a9H6IKGYU8kupqR7UhIewiaU+mfVkl5H83qVF0M5PKfSJF8xkqir3fU/nnYuACCus+WYcm1BEdbLmEEPb4E9a+Jt4FlFPVqCxKCC/nKBdFOldYiEkBBhnZwt+CNwVXJB0Xyf1Q3QhAQl9RVgdjp8FPUzl58jpAQylAmzeXEQ64HDm+zwuu+uaHS6mtWuj9kFrujdDSg4jrJrYD46FpGXCRBSukjDayGi7EtPGkdAaRUiJOXw31rOzSEvtg9xtikKTLp7gTPe9ocV8j/lQsFKmAAppcAtIoCMmF5PC94Lz9fHeRsHfwhB34SZ3YoXsCSwsuFriGzjoAP1JTpj6Mm2EDhox5oT5qSzic/VVLd+IBp3s1CQTB8kIIO3lC3FFn/YofWg/EzUPaRknSx9aEORBypnAMmUFrq77PlQG+31WsPP8/oNzGxHC85Pi9UYCk24CAde9huJ00Jp+yJEBpPD4zS/dyKVx+Vt+vcZ+Y2Q9QYdm7YOTKcY63zMQPz7q+xFFboaVgosMkv/AtZo8k2EcuAmWMBKFsvJNT+qx4/WU6t+j/KUkq3J2HnZb11wIAaQRnL/diRtrOqnPXw8J8IDY2wqiZ4k64AVoTBanB2OUC+yD/C0ik/+TkofwYEq+1xPI7T8KdWB08ZQ8bSnFEE17rOrI//IVdK83Yrjn9v/79t1ln8WP+kVAlhFbdXZjOvasoP4SEoJJ6UFvgH7eNL6iXoFdckArGdM0XkQuxEfAlVLKbChseTw/dZEtnaXN/lt3vFbqdAv/UvSdK3sI0PdEQINkzlZDeSPmdT4A+8yCdmfHwJU95YkIE31+nBfD4wOnm8/2zkGv+L6U059CQp1598bsg8et56CfTbKOX6JHHKbu4PZIpZbJIYG5aCpm3ij693vQNAE+DfBnDtoTvDwQImXjeHYT6pHKKgD5kQLMLCC5I0PqAy3rL0ZtPHBsOpfWWDSVX5T0jcopG/nrCwS2F25R+jjDKJOVYI1V6T195a+xhG8G0wtJOgOMSa05y8DhrNNNQProNcGo9LqBvfvC4FIfhS2IbL6Vg7fkbF94E1Dj0p0Ny+rD+Y64VJD9h/Nl4HnpXB44fS7eDP23kKR5Iw5QBmyi8SXxaF0uKUdO6LePPuxH6D/X2WAeLySyD7FvjDlQ77MNkQxq3610qpg9pI78tPkgB8Ec3zIsZo4VPxTDIanodJ4yxYOlNFiDgxj7h/5zNF8baCnMRbGgv/QuNA/HDF8vdjS0LaNPfkTnjxBzRMh7z3SCRPTx0V9/oJcrF+T1yImu3/1KhL5xruw/+vEdGmeuzlYMYzVWb9DjJ5pIhCkbFVyjYVSJhum5caFrrmowDYZTE+cuHORwNAj3RzrQWy9xDSVV4iQL8EtDZFcwQoFEAGdaqTQbothOS4HsNVpqwOWf5fcdgO4qg/GAs4/qK8/bzfNgz+iny5udJwDcze0h13/GNxnPa2UkGzVzQLqNbZnEFjbyfEdf+vigohfxCL/LQw/Gi24mOo/YHA755P6jZmiT1B19DuQuCsAWNxTCm2bcQKjGe1rYQ5z3dyikANSMQJsH2PsolMkNKZ0L2kB3cKxRI5crETFxdDqDB7MnBSkQnRyEd1sStGTg89r+YT2O1D533yHNI6j5mHaE5kusetqcY0J59+sP7oyvASPq45YxPUOWgOK0zxL1ADfillKpy4zwXGE4FDZF2S5cRXCeR0ptjwmNCWnRkIEbFMxnAMHBLnvq90Ou+9/pFNrOgG6byKHIsNUGhgVzxVrFOA5Nf73kctwfG+GbfAb0qSEsNff38wi8xRr24f07/3cjxc4t055wIZS657sL9gmV3Sjro/3UcbZATJNMF/NdccRMm1qLlBTM55ndWizjKOX4AHMP8KMPXZHLQN8W9fqA9QrhJdFVUF5Upi0VcFIGsUNPZJFnKT19Grq80U1rwhpG3b5s2I9tDV0XdNqqlLdlKEuXmuTGpAAah2Sdv36ufT/j4UgrF3RV4Uhr5Ki0qDtcuqRajDMwwBUR56MnXfsd3YxzFZ4ultdHtqs1bPya8Ga86boSxbXgnN1TsfQUvl6vy0niWjr8nD2ax10CoTd5TYe49IT6SeZUUVZ+d+KoM87nw9fbV3Agw8H3zTvjb2JuaW4FM07RqZxXmISk5Izo9/Z+/2NDSdsIYSu9XDM3L/EdN5Zkdr78HOwuc6GKM3ZBgA/go9Qin3uZwpbkoNtA6cYLnaspPAz6u/5Pz9hTBmUasZlMcy5rhdINqdipAg4y1LfnOWyYI12xmZrNn4k+hVozCXmf1uFOalpwb/yuj4wPvlOa2YvDzp2uBSu1V0zJvijbQuklYVQu9o/fT8CrmBf74+rIAjK1GkkoTc8j2nRblOPo0WOXIdPhKnSmHTTdYcfLGeoEWeQfRGwr84AD8VbCAjkoZAD9C8ulfeVGRW316mkWlpjq6b/X5SbR34EcitDuFPf70IILO3yQQ2NkZ0MDmq4PwuekzPHGQNLrYovgjwk10Qm+vFzhqQ1n5WxQK4azhH2Z8LOlGpyIWAOkKSuNIyOnfTAbsLKi14U/7zvybWU/cpXDIMtUvfy8FBg1x9+78M8PMwphGWn4l1Z8ytIeGGEZOVJJeaWiH3l5MeGPiMo7YslzqPYLpgLs9Tk9dMxQC7Il7aILi0k+rFivNOy4Nk7zirrTUCre5cGlBi/ogqsozvXce7DRPjp1ffrt19cwkrYKld057q4sT/JjWmqalZVAP1KiWafKEU7lH69p2mTpqjK3af/CS6GOgMv/2hVvE7TOfdlz9Ev1dy5vJPplg8WY8vd0waDDGl3ISO1n0D7TtoF400CYr/6RiS9/uga45LJIWqkXmf7BS+xrK1WB1d/qwRjQPxEvveyneUSC+X5pIQWoX1DlYIOwC0i/pwSNF0CtTmqhqQ6RWtcQb9u69ZeCQI5OrOo139ItsfBIXs3RFuy2JPwXYcoLCv5rzcJyb9tLkTDAPDik5i0XhFM9+sogUnFuFKgs5AqgVfyn6rkW+6QtA/CYw12CgWz8P9VlhefUM5Zo8RdH8iQuM2jzERVbs3FpWpj2c4ItFZAtDOrUexLApjMdLSuyz+chvwhJnW4EypVUrZYTVO5risIVSjO4xmiKvQyxvQvpH1m/RzFJB5KPPWUFRJ8kqgcZNQ2+NeKgQNLNXIzTeZSLGoXBOD9SrSDtpTIBWTY+JlKessb6m/JG/+iNDUDb4JkokyJ8EfOdFvKyoSN+NgjYXiD3gc4EOSqAQeAmGDaMcLraEr9xab4gPFgOX3CO/A0pe6YMVMYkREBcvtfd+kec+/XHPko88FZ9HDucADhh6hksh4cwXsFTK0xX9D9v7AiRAGjEqHnc13Rvw2gopboJstB2+hVYOX5NSHMHlMGj+38AACz/0+BamZ2AyUOg9scmDYDtijFdcgTFaNDltVZgzNxzN4qfCG4nf5AjxJgAh4DW44jT/e3i9wI+rs2FeKgbzL2Nw8bQkoxt9VP5WaorUzL9aSrPmZTYlW1xnHo153HK95P6oXNodBkqw5G75WdqAA0VZqbhqYPep5aq4an41QuRZwskqYEBmYE7vR8rjNQTg85yjMEmhgTCd86ik/PN6KuaUZoM41IsA7bMRWXKxqmgUNi9h0nnHrgKPOpIy9+lO7y8urzV6NCWK6VHyfPFEtK4ZpJC1DIx5QEIGzcDIwh3qM25PmS2PFAn5bs0CHdQAml2bW8aRbHCqWNmdKLZlHeo0Bh5UuHDiKkcbUvxqFvcsxhl/9TVqFYrdl+Ml/SsIgyZwTjRjXYGHqCAwRJ+rHcfT/Ca51P3ZXwdgCBwYrwQshpdsG/Fs4JGw92S6sSfqmaymofc2xbA1rBWTsEUeNo6+r/wjQeSepl2oA6YIrPWwqjDpSPPJMQ7U5eEfTpmx8T8MpFfdv9r/vjRnhaSeNeaEb0o5fq/oPRH3ZoyXguXzte7tlYj62VPLqW5tNt6AvA5CKIOYdi07rmN3QJg2flCU6SD+EzXi2EbsXS+9cal99LH+Er7ZH9xf1zu/Rb12MT6AjB/b1CO7x+3aaQMmD4vX/+o8h9/m2SUbE1MVFkZ4qVSIczDm+ebUHcgUudg+4jncyTxRd5VoT77o4PeNnVUBYcJX80KXqk5nqXnhp7miaBWGJ8jMaIaKkUV8nG8By9B05BdkOea14Yacx1fNVy8tIj2/mK57fRnUvUhqkm9T3iABDjYORnXJj72QJvzORjdGP3waiM56R2JgMBNHgPwBm73W6jKfAasvf/K0MY1lGiaiuyVQxsTNFVDFoSnLFdQ8bZmznqznP8ZWcAdNmz4KPfZv2PrLA/UuafBMlrW3365we4TiCFL1h28LcY4smZplcgyhWpZMgnaVciIOjnnsRtaZb5GCAcEgR6aDYiNp/O75i/VqWxZxY+fuSby0eBWV8jq8sLEreRzk6WYqWZlm7ZWmYXo27+f3GP2tL0f3y43+etS5dbkqHpXV/9TiDMQUCx9f3gGAJY58mBZZalHUuuiTHKjv2YMh4zvE8lKsRRr5zAF72kAX/o5ygDkVut+vQWUgdsa/Ukbiqdwe66O++qcySe7ze06kvPll3v0BHogQ7qIqCrj/DWG5nF4TS4N7+tf0y+Pm3uCKMheG9B7PrVmJiukeV/zC5nhkQFQIerdYgLCPoAkWFsWHDtGTetAhsq6IjyWgkjGnUFFc9/UcPpTy2w2Wzq6By0lgzUlz6QVMqZzbmNzNsHpfCWLqVhADFBcn+49hTsisMs5GXEYZHHi7kwrhEqK6+t0El+ieSJL4mvP67uX4sS5Ggnw5P2Ablqj23XKMoOjvtwQgC7y4tf/EntLvBNjdKUKqTXng9bYDcjt66c+SkD+Yogd2RYDaygZ/sBNLhmLKbpHsW5jzIwLRBaXxIVl+J0hSs7tyTVff2OzwqTjMaQvFjUpVcF2QHN6FysC8abyYkUwj3N9BpN+fjgjwKMtBNAH7n5sEwbWFqL+BPT9EV0AAC+Z06IFMa1bsPZPsf4occibdNfvPbc9mIs3HQSxEtVQOkeMLtlX4h9XLzjieYJmLI2/n9maVwg4+RTuDwHjjB7q16WisljDp93niD4c3EVYKDNk5PSKHoTv+rWlR8ak9e2Y4grv74+kSecrbTLl3YI7Eu/4J7xgRoeQEDX/KxXnHxSq9ZvJDwxN6Uh1yJYHNnSRIii3hvjCyxXCS0ozYR4BB2TTzAYTocrH/gtFSsYccftA7qsZZmA1zdikNCToYtsrApD2XRjkGdDdhctMbOiTXROkiwhJFFrlHddP4za1n3w4ArzYV4FE+cAn12vWdVsNv0A9hX7wBBNnnFEnNNpF8U4mH9IrX7CNaUPmIzXb8CCFmZStikqDoZC71PD5L7mLYYQcIPT4ouVZvSFJ6hWCnPFbDLDSXV/CZ05NbmQt5RJfFOVP+x/npDiUZya4j+lpWgbFswZV0S+6bBKwDMDLxWN/nTnjOiI+iYkMYRoPxsXJlsz8Hfr76eJzP1tsfgGpfHpAOFmhCvmigOYxOFEoEgxmyJvHZsKqE5CHBzNxVyKoEunf0JKQpiVl6yitp331c2AACV7ibHECsJT6/iO0IEcl4d1Mo1kosbbtu8i1R1BilCo8WkQ61Wt8yTkzNQcGmm5S5MO+OdvBofOuFn0u/3fzPY4cFrQA2Kdsrjjkn8nYvR4KGeXKaW++gDTwehRw6ArYPKtAPg9kfJqJIfx/d/jH/GGPKuP9WvGQHL24ye/4FEI2blcuEhcFZdaoOLhP8sS0HPsOwdTwNVgqBRxcmiFRKsEZHVuOAgJzfO9N43ORYNYbLKS44ZcH9Mjhl6I2RCqDr1ErJbYwr63DLKF3h7B1otbU4juE9MaD3juYotz0S/YJOdis45Rw06BUrvUxvre1+7hGhxszKe0B3j57ph5hrRJApLg28D2JdJogzmHBCb0wZsFpCO10Au9tp+CmBtzcRQguP266ayFkXqsqhWBGich1yjOogHDvnNb973g06hGSZwC+t5BiE7wfAgog2wB1pm3DqVQEe6cqhUlnY6nK48cGr3YsLZ24v9/l8xaV8VuukVnmgL8hkiPRAg2ZA39mxEszH4r0ovm+Nlcs8v861cOJqfVHaBMqeDT1iJb9k0C35Uiey0C1Zc79XF19k9r7mjn+XFffeyDNU5U72NOZKGVrtZ6tF3RX+Tv2BwPCWoO5rOJYDmGCSzjF8E8c5EJfuJByvxDBZTf58E80cuGfXil/mM9s1+wblnmXbz6DO2MkiKx5L2ieGJ2IkEOblatjv+IZFmZOBZv2DQv5QbPuL/B0Q9zMlsVVwtx2ZCd6IkskNtF2BhGm+qKPcygILv0QKnsFRZRgGHqOC0AQeelxr/4SPJoAiry+vHZj8yHOqUxIZCGpZTHj922o/BZ7ZwbIqCrb/I/ezMCcJWU56Vuuuwi5W15fqu13C0uialDPi08K4b0RlIcImYPe+UzWTvi5auzqDriO3GJzLxZfR522Rw96W3mjkCAADwD1fk5BJIdJvyycvEc946XkvJa8Um+NZ+HJRrw227M5vgoCoW8kJ+yV14CaUQN2BsRjw3gveh29BQXoiwcm7rc4j14F2joI9mkprI8aP1Z0VEL6/KSaXEtS54GG796+7OVEVlFx3sklbnOrr6Dwht1XreGNyxU26OwP803oEML9iSqPdmmj9UsI9y/9XPWWGHxs1rFVb8kDIbGDE0Bp5W1sJUpgK3ASfjp7hgGAsamxE3x7GJyQd6QIeMTu9lhse+rPJsWy8GVp3PIhabMklLp632xaJ0wE2QtTvwUF5dpKlx5LnTzNtbrVkfe9CV/ph8Fx7y/uH+DagC65g9kwz2K0+0BuOyfMBVDE08VAX9UFNXt5miZ6u+p8pRwrlSqFRa3g7otXAsQBhYbHU1ghSWsyQ+jJBTofP5+4vzSIWMAjC+rh6IZ6U8XJwUyNDMAc9Ol4ejE4OUx+nVXcXopSC3w3veRg86dTV5+OHnKPDhGoEec2nN81sgLYILBiFO2tG4kGaY8jo+JBXNTzI6vf7384//L06z4IEJpCXMLCmudTwgX7dc82MWCGjrb5BPjTw2Z9Bf2V+QSsBFirQTAElHhq18Lc5Cdh1CEBG4lPf2Evd4buXVW7ZePc5C2K89egqKgivOZzUSe4m7QLPCevZT0l4RKTGjxox7lJzMuRYYjx3GpGfJLpD+doevHqUhzqKUtIMVnbwXWma4uialihhdCqosXIykNxjCAhIcvnl2DF6qjENgAOaMQN8Q0o+0S5ohnoQbc4NR/ly4I=
*/