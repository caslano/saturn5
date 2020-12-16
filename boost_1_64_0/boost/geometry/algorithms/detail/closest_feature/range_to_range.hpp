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
oh3A3Y+538OY292n5naPmH7/BzOveNSUFzNz/T8FeOSlfNJW7t00vZbCGNE8zR0AO3o7h7ox4zdA8Vd/h9zL9Xhv3qj9hxvfk6M5Sq+Ez/1naFx3XAP/GCRcGe6NbjUvXRklc3R+kdHbUDxHVLYhPEaXU7pR7ioz9zYRTtERTTTdEYbuFC+abi7hgvZlObRfP5LTaL8yyKTjxUdrPGTR+GM1HjJo/BNRHuFMfMXJjLFC09DZtA1+//yFiS8sNPSEd/SLjAx2bDle4TmPxT/J1w/ZlDqvtcGc19pgzmspnmRnjq/meVKAR968lpnwJ2/Q4x3LHT3eLdP6w1o6uv8M9QzGujpbh7YOdLorMZxNWiBse86i5Rt8/7SU/FPwrqnv4+hVU/Qfbut5Hl+F4Mm7pis2qP4zizIDPcZMHP501C9m429YtzHcxh/OEN36+E3zzZkxzRN7ys5CHa8l/qTliUlPn0HNZ/L09GyQXuhdlMhm6CxTzhOaGh82QquHgytx1qtO6WKJ192/rZ5vJvFfnpGU3NGPe13V//YMyBrY/VrYnrorxunAvgV7JugJp+nFXzQSXtM3UVrTMNzSrDc0PC5ammZDUxFRVotqo2MQd9X9o83gx0yf7CC8tDnu1JW7XXGfgr4//FSrU/SfzRswp7J0uIdW6/8sotU8K0rw7JH6C09Fg3u+N4i8mDcUeZ9U5f/KTsYaSvE+Z4PM66hsyIv/z6yy9JXeIGxgCDbjfK+9hxhnCeydwduRl2XU8Z1zCW7vbd25QeZtDsfweoIVREarz7nes1RdrO7zoNd1OW+DjsNgbyt06M5lET5yHC7d91z9hnV/Urqw339GiU7Hhe1YN6bG0WXGHsfFdoJ7nVBXM8ffHdiOsgPPyJFSNNYGKe1o0tIeoJnWv8z1JjeE3xReWuHv5+oAfcoLp89D+s7lfvrBslL3jcfaB87tH4q19mzip7g3b4l1d9CFTN1d3Z0DrkWmwNvYj+XZ1k2/nr42x8fAKO/p8Ot7nC9u5Xt5kvlx/13uvQSr8frd3TxnJ/bLunvfBn0G1Y+u9G9to4ASvyHuAi0oLQIzjbx9rf3dVl6BUd6VkNdfu0zmLuob3t096o8zF5Fc87z+eJZG3Hwi687oDkDm5yiZa/5DfQc68+8/HxnuwBnf4ns1kw6mY3oX63F/hnXtmkJPTp8U3dqmrqWPxKAPPw99+D2Q/UJff3tzF1FcL09RvUS2lycqAW6ew/VnM3sc+CDqS7KP7mXo0P5JxDHxBg/Bu9xJZcCcnkeY1DVIQHuA5FjqZXcJQtGvIB5kZ4N0N4er+1zS2/O1rdm6K1OLQLh5U/S7WogISm5JytrjhdDX8lBbT8R3JUc8pMkb0X0ntGWW63Y62vnFIi/rkI2fZHKF4G8qIfBNX6V1+LXLD32j5CUYVy6DDPWl68DbZYcoqIlqKAjug3nZhuKc/OXgB7/n4gR30AS2s8r9CO5+Ej94xQbf770S8rxKjZGcT8exXhPIWqb3GI8mhgu7Yu5wPNp5km0L8LFkCjYU2BZd3MWvVAmts6HcpJtCF+mWMszQrfBy9N5VwlEGsFr3jtdIKkl3psQYrey4waePudP1ai673ktlMhcUJmPkQsYzo9LWLd5oYWIS5JD5pVTnzR7489UHMf/drQD/asL3e4zw4aOpXY7f5QTf4e1K5EcopL43mR7N7HVvVx1L9vNaZT/ne+3sDdqHdgRLZJWm9m2bhR8q6nhka5quGhhtS+ap3nK32uu1f5zh2NEbeoNsmFyCfoNseBuCCa7sk90MIJugSw72JOCvC64PxZPU52ngoXvesC54o+lDbgChrjNID1C2O1kMjMeU0uM=
*/