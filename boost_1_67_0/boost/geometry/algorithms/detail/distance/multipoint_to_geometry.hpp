// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, 2019, 2020 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_MULTIPOINT_TO_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_MULTIPOINT_TO_GEOMETRY_HPP

#include <boost/range.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/tags.hpp>

#include <boost/geometry/algorithms/covered_by.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>

#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>
#include <boost/geometry/algorithms/detail/distance/range_to_geometry_rtree.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template <typename MultiPoint1, typename MultiPoint2, typename Strategy>
struct multipoint_to_multipoint
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<MultiPoint1>::type,
            typename point_type<MultiPoint2>::type
        >::type return_type;   

    static inline return_type apply(MultiPoint1 const& multipoint1,
                                    MultiPoint2 const& multipoint2,
                                    Strategy const& strategy)
    {
        if (boost::size(multipoint2) < boost::size(multipoint1))

        {
            return point_or_segment_range_to_geometry_rtree
                <
                    typename boost::range_iterator<MultiPoint2 const>::type,
                    MultiPoint1,
                    Strategy
                >::apply(boost::begin(multipoint2),
                         boost::end(multipoint2),
                         multipoint1,
                         strategy);
        }

        return point_or_segment_range_to_geometry_rtree
            <
                typename boost::range_iterator<MultiPoint1 const>::type,
                MultiPoint2,
                Strategy
            >::apply(boost::begin(multipoint1),
                     boost::end(multipoint1),
                     multipoint2,
                     strategy);
    }
};


template <typename MultiPoint, typename Linear, typename Strategy>
struct multipoint_to_linear
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<MultiPoint>::type,
            typename point_type<Linear>::type
        >::type return_type;

    static inline return_type apply(MultiPoint const& multipoint,
                                    Linear const& linear,
                                    Strategy const& strategy)
    {
        return detail::distance::point_or_segment_range_to_geometry_rtree
            <
                typename boost::range_iterator<MultiPoint const>::type,
                Linear,
                Strategy
            >::apply(boost::begin(multipoint),
                     boost::end(multipoint),
                     linear,
                     strategy);
    }

    static inline return_type apply(Linear const& linear,
                                    MultiPoint const& multipoint,
                                    Strategy const& strategy)
    {
        return apply(multipoint, linear, strategy);
    }
};


template <typename MultiPoint, typename Areal, typename Strategy>
class multipoint_to_areal
{
private:
    template <typename CoveredByStrategy>
    struct not_covered_by_areal
    {
        not_covered_by_areal(Areal const& areal, CoveredByStrategy const& strategy)
            : m_areal(areal), m_strategy(strategy)
        {}

        template <typename Point>
        inline bool apply(Point const& point) const
        {
            return !geometry::covered_by(point, m_areal, m_strategy);
        }

        Areal const& m_areal;
        CoveredByStrategy const& m_strategy;
    };

public:
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<MultiPoint>::type,
            typename point_type<Areal>::type
        >::type return_type;

    static inline return_type apply(MultiPoint const& multipoint,
                                    Areal const& areal,
                                    Strategy const& strategy)
    {
        typedef typename Strategy::point_in_geometry_strategy_type pg_strategy_type;

        typedef not_covered_by_areal<pg_strategy_type> predicate_type;
        
        // predicate holds references so the strategy has to be created here
        pg_strategy_type pg_strategy = strategy.get_point_in_geometry_strategy();
        predicate_type predicate(areal, pg_strategy);

        if (check_iterator_range
                <
                    predicate_type, false
                >::apply(boost::begin(multipoint),
                         boost::end(multipoint),
                         predicate))
        {
            return detail::distance::point_or_segment_range_to_geometry_rtree
                <
                    typename boost::range_iterator<MultiPoint const>::type,
                    Areal,
                    Strategy
                >::apply(boost::begin(multipoint),
                         boost::end(multipoint),
                         areal,
                         strategy);
        }
        return 0;
    }

    static inline return_type apply(Areal const& areal,
                                    MultiPoint const& multipoint,
                                    Strategy const& strategy)
    {
        return apply(multipoint, areal, strategy);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename MultiPoint1, typename MultiPoint2, typename Strategy>
struct distance
    <
        MultiPoint1, MultiPoint2, Strategy,
        multi_point_tag, multi_point_tag,
        strategy_tag_distance_point_point, false
    > : detail::distance::multipoint_to_multipoint
        <
            MultiPoint1, MultiPoint2, Strategy
        >
{};


template <typename MultiPoint, typename Linear, typename Strategy>
struct distance
    <
         MultiPoint, Linear, Strategy, multi_point_tag, linear_tag,
         strategy_tag_distance_point_segment, false
    > : detail::distance::multipoint_to_linear<MultiPoint, Linear, Strategy>
{};


template <typename Linear, typename MultiPoint, typename Strategy>
struct distance
    <
         Linear, MultiPoint, Strategy, linear_tag, multi_point_tag,
         strategy_tag_distance_point_segment, false
    > : detail::distance::multipoint_to_linear<MultiPoint, Linear, Strategy>
{};


template <typename MultiPoint, typename Areal, typename Strategy>
struct distance
    <
         MultiPoint, Areal, Strategy, multi_point_tag, areal_tag,
         strategy_tag_distance_point_segment, false
    > : detail::distance::multipoint_to_areal<MultiPoint, Areal, Strategy>
{};


template <typename Areal, typename MultiPoint, typename Strategy>
struct distance
    <
         Areal, MultiPoint, Strategy, areal_tag, multi_point_tag,
         strategy_tag_distance_point_segment, false
    > : detail::distance::multipoint_to_areal<MultiPoint, Areal, Strategy>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_MULTIPOINT_TO_GEOMETRY_HPP

/* multipoint_to_geometry.hpp
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
*/