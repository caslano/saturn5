// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_MULTIPOINT_TO_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_MULTIPOINT_TO_GEOMETRY_HPP

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/detail/distance/range_to_geometry_rtree.hpp>
#include <boost/geometry/algorithms/detail/distance/strategy_utils.hpp>
#include <boost/geometry/algorithms/dispatch/distance.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/tags.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template <typename MultiPoint1, typename MultiPoint2, typename Strategies>
struct multipoint_to_multipoint
{
    typedef distance::return_t<MultiPoint1, MultiPoint2, Strategies> return_type;

    static inline return_type apply(MultiPoint1 const& multipoint1,
                                    MultiPoint2 const& multipoint2,
                                    Strategies const& strategies)
    {
        if (boost::size(multipoint2) < boost::size(multipoint1))
        {
            return point_or_segment_range_to_geometry_rtree
                <
                    typename boost::range_iterator<MultiPoint2 const>::type,
                    MultiPoint1,
                    Strategies
                >::apply(boost::begin(multipoint2),
                         boost::end(multipoint2),
                         multipoint1,
                         strategies);
        }

        return point_or_segment_range_to_geometry_rtree
            <
                typename boost::range_iterator<MultiPoint1 const>::type,
                MultiPoint2,
                Strategies
            >::apply(boost::begin(multipoint1),
                     boost::end(multipoint1),
                     multipoint2,
                     strategies);
    }
};


template <typename MultiPoint, typename Linear, typename Strategies>
struct multipoint_to_linear
{
    static inline auto apply(MultiPoint const& multipoint,
                             Linear const& linear,
                             Strategies const& strategies)
    {
        return detail::distance::point_or_segment_range_to_geometry_rtree
            <
                typename boost::range_iterator<MultiPoint const>::type,
                Linear,
                Strategies
            >::apply(boost::begin(multipoint),
                     boost::end(multipoint),
                     linear,
                     strategies);
    }

    static inline auto apply(Linear const& linear,
                             MultiPoint const& multipoint,
                             Strategies const& strategies)
    {
        return apply(multipoint, linear, strategies);
    }
};


template <typename MultiPoint, typename Areal, typename Strategies>
class multipoint_to_areal
{
private:
    struct covered_by_areal
    {
        covered_by_areal(Areal const& areal, Strategies const& strategy)
            : m_areal(areal), m_strategy(strategy)
        {}

        template <typename Point>
        inline bool operator()(Point const& point) const
        {
            return geometry::covered_by(point, m_areal, m_strategy);
        }

        Areal const& m_areal;
        Strategies const& m_strategy;
    };

public:
    typedef distance::return_t<MultiPoint, Areal, Strategies> return_type;

    static inline return_type apply(MultiPoint const& multipoint,
                                    Areal const& areal,
                                    Strategies const& strategies)
    {
        covered_by_areal predicate(areal, strategies);

        if (! boost::empty(multipoint) && 
            std::none_of(boost::begin(multipoint), boost::end(multipoint), predicate))
        {
            return detail::distance::point_or_segment_range_to_geometry_rtree
                <
                    typename boost::range_iterator<MultiPoint const>::type,
                    Areal,
                    Strategies
                >::apply(boost::begin(multipoint),
                         boost::end(multipoint),
                         areal,
                         strategies);
        }
        return return_type(0);
    }

    static inline return_type apply(Areal const& areal,
                                    MultiPoint const& multipoint,
                                    Strategies const& strategies)
    {
        return apply(multipoint, areal, strategies);
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