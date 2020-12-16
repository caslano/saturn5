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
0ZUGqjTCemepf69x1h5IqA568LgnD+DXtYTvUWbYMzApPY90qff7/EexXaBWXjpjrBSg5+H/Hrm+adaZOBbOOqdP7ywkUyO1lJq+/EAc6+i/U7BrjLoyF9fwPN4V+qaVmFzKDx/q678W+uXuv88WVa2Gk7ZaQwlramv220zHW3t0PbH7XNyam5WdEe+D4xm74CNe6Na2tBifJBUcyKkPOt3UV+JeUi/NyGF/xdy7Er1yFb+6/6sQmigWPQ7TcmUyU9LO392nIfDyB6sD5hq65br94eDC3fDVfesN4PrNcC4nrz8PzvrO3BKJs0aqI7X5V3GcJoaHY/FYy5jzcUI6r9tpnpgFW6Iv6t1leLsSnZcQfuj9fKlgihlio9gWSBnjTdKshfUm7/4BXz0fXC8BR454XyJ4VktfLsMLIQnlVn/O3Wlm856nxfSkteWdBIf0969hvH34kUCd/9mOt9rL19VUVfe8eAd/9DbXd6ARh4qJc+TjRei1xQFcgv9/03Ow5nc1FHUAtgwTpy5qg1ceV72lFatQ/sjYT1yfdp79yNyQF77B3xLmjWrd9WJdumGE/NBRO2F6CjyzFTb889p59EAzxVS+SGzckwyu6/+63YLFnC/a1Ppg5tZucAD2/hUJo9uaW2B++pgz9W5i8Jle2sfT+o2Wv8srwoPr4FN/fXF0DX3t69loqnFmqRNfym8yfBAzc56zxppqGGZU7mm/+iKWWbsa/r6+XD7GwoBQPHwETsQ8E9PN+rOLaRivpi9OTuN8fYmZ7gWuoRcn0ot/pKQf5vETPwxmmptJ5WSlXs2tRouJyYRk5o4U7kPb7ZvAs4hSl4XNwnBn7d+4fS6/gj641Mu53Bd0o77KdI0ve0PfwdPBwUH+5h3sDObrDoz53XJqLpvnmcW2wmMxEaszfYJgldksFc1A5wZnUUOl3HOrupCbYfD3zkT1G+NFt8cpk2ir4rxKWi4/jP6Sxkl5LwC31LFzs9Sr5HExnSAXYTfU6yK6/oa+UsuB2/ACJy+jT0ptpFv01tdb6Z3vgtWquQ7vlx4HjzPrcZrwoj766ZE8RpvRceV5Omv3Mjr0oHnQ+87p/QV0Svteaq4P376qGi0m5p289lfcPoK3QYdkvRJzziW3ZpPvzJdvPrU3uR4CD0bRru8SwYEHMd483iqoZy7KqX6pBCeL8ELqOqcJWYqLaI66NeFKVVoF3qbH2dtotSZD7eGc3PQK4qd7bjIRfc47+088deuey57zDgqY4/VVZrU4e6K+oC0n2EPTD3HsQj3QxNc2qUFcNiEItlt/ipK8Kn19/iBt0kXfF8Wvq+HRGxqhtzhV9+83NHMkjBS/Ru3llu+1Xi3coc+C66sRvbDfXNPA9w9nspemdFAEn4mOXHuURqexDnT1DEVlGuKNOl8Uwns1s9H3Uxqas+ireSvV5DprLIwbaLRKd9RcdjV5D3bCjRnhdDVPfOpD8w3fdkaYeoDzTWi3g6N5H7vgVMqAZ/zUWYj3brZu3pK5L1CrNU1jb8XVXFw43+cWrjqirp/CU/PWyL3m3Mt4rgmtUR4/XKSXLsAQOP0Jj2gazVbxZ/GipR/b3168l3sRPRNTQyfkcyUcnCq2uOTdWPgQDxbRIDeS0GizzcHbzTaekfvtFJ1TT52YyU7pvWpVXM+9D6zjF5+Fa14zvzycpFkjAs6g+Ho3QoPxN6ztrA7dp0aw7yWDjWlpJDV1Akc2/p7HFUEvl4OTdXkTvdWKOK1LYv1fwlk4EKzO5uiH/Hp96SZeHw5blVbdH7auHWr6GY5/QzdOtObLNP9QuhweDmgjpzR7s3rwnPa4oH8L0a47UuOV4XR4C9jYixafTA+570Q=
*/