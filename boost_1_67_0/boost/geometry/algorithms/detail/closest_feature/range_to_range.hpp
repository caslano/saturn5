// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_FEATURE_RANGE_TO_RANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_FEATURE_RANGE_TO_RANGE_HPP

#include <cstddef>

#include <iterator>
#include <utility>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/algorithms/dispatch/distance.hpp>
#include <boost/geometry/index/rtree.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace closest_feature
{


// returns a pair of a objects where the first is an object of the
// r-tree range and the second an object of the query range that
// realizes the closest feature of the two ranges
class range_to_range_rtree
{
private:
    template
    <
        typename RTreeRangeIterator,
        typename QueryRangeIterator,
        typename Strategy,
        typename RTreeValueType,
        typename Distance
    >
    static inline void apply(RTreeRangeIterator rtree_first,
                             RTreeRangeIterator rtree_last,
                             QueryRangeIterator queries_first,
                             QueryRangeIterator queries_last,
                             Strategy const& strategy,
                             RTreeValueType& rtree_min,
                             QueryRangeIterator& qit_min,
                             Distance& dist_min)
    {
        typedef strategy::index::services::from_strategy
            <
                Strategy
            > index_strategy_from;
        typedef index::parameters
            <
                index::linear<8>, typename index_strategy_from::type
            > index_parameters_type;
        typedef index::rtree<RTreeValueType, index_parameters_type> rtree_type;

        BOOST_GEOMETRY_ASSERT( rtree_first != rtree_last );
        BOOST_GEOMETRY_ASSERT( queries_first != queries_last );

        Distance const zero = Distance(0);
        dist_min = zero;

        // create -- packing algorithm
        rtree_type rt(rtree_first, rtree_last,
                      index_parameters_type(index::linear<8>(),
                                            index_strategy_from::get(strategy)));

        RTreeValueType t_v;
        bool first = true;

        for (QueryRangeIterator qit = queries_first;
             qit != queries_last; ++qit, first = false)
        {
            std::size_t n = rt.query(index::nearest(*qit, 1), &t_v);

            BOOST_GEOMETRY_ASSERT( n > 0 );
            // n above is unused outside BOOST_GEOMETRY_ASSERT,
            // hence the call to boost::ignore_unused below
            //
            // however, t_v (initialized by the call to rt.query(...))
            // is used below, which is why we cannot put the call to
            // rt.query(...) inside BOOST_GEOMETRY_ASSERT
            boost::ignore_unused(n);

            Distance dist = dispatch::distance
                <
                    RTreeValueType,
                    typename std::iterator_traits
                        <
                            QueryRangeIterator
                        >::value_type,
                    Strategy
                >::apply(t_v, *qit, strategy);

            if (first || dist < dist_min)
            {
                dist_min = dist;
                rtree_min = t_v;
                qit_min = qit;
                if ( math::equals(dist_min, zero) )
                {
                    return;
                }
            }
        }
    }

public:
    template <typename RTreeRangeIterator, typename QueryRangeIterator>
    struct return_type
    {
        typedef std::pair
            <
                typename std::iterator_traits<RTreeRangeIterator>::value_type,
                QueryRangeIterator
            > type;
    };


    template
    <
        typename RTreeRangeIterator,
        typename QueryRangeIterator,
        typename Strategy,
        typename Distance
    >
    static inline typename return_type
        <
            RTreeRangeIterator, QueryRangeIterator
        >::type apply(RTreeRangeIterator rtree_first,
                      RTreeRangeIterator rtree_last,
                      QueryRangeIterator queries_first,
                      QueryRangeIterator queries_last,
                      Strategy const& strategy,
                      Distance& dist_min)
    {
        typedef typename std::iterator_traits
            <
                RTreeRangeIterator
            >::value_type rtree_value_type;

        rtree_value_type rtree_min;
        QueryRangeIterator qit_min;

        apply(rtree_first, rtree_last, queries_first, queries_last,
              strategy, rtree_min, qit_min, dist_min);

        return std::make_pair(rtree_min, qit_min);        
    }


    template
    <
        typename RTreeRangeIterator,
        typename QueryRangeIterator,
        typename Strategy
    >
    static inline typename return_type
        <
            RTreeRangeIterator, QueryRangeIterator
        >::type apply(RTreeRangeIterator rtree_first,
                      RTreeRangeIterator rtree_last,
                      QueryRangeIterator queries_first,
                      QueryRangeIterator queries_last,
                      Strategy const& strategy)
    {
        typedef typename std::iterator_traits
            <
                RTreeRangeIterator
            >::value_type rtree_value_type;

        typename strategy::distance::services::return_type
            <
                Strategy,
                typename point_type<rtree_value_type>::type,
                typename point_type
                    <
                        typename std::iterator_traits
                            <
                                QueryRangeIterator
                            >::value_type
                    >::type
            >::type dist_min;

        return apply(rtree_first, rtree_last, queries_first, queries_last,
                     strategy, dist_min);
    }
};


}} // namespace detail::closest_feature
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_FEATURE_RANGE_TO_RANGE_HPP

/* range_to_range.hpp
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
*/