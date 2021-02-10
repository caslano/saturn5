// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_RANGE_TO_GEOMETRY_RTREE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_RANGE_TO_GEOMETRY_RTREE_HPP

#include <iterator>
#include <utility>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/iterators/has_one_element.hpp>

#include <boost/geometry/strategies/distance.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>

#include <boost/geometry/algorithms/detail/closest_feature/range_to_range.hpp>
#include <boost/geometry/algorithms/detail/distance/is_comparable.hpp>
#include <boost/geometry/algorithms/detail/distance/iterator_selector.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template
<
    typename PointOrSegmentIterator,
    typename Geometry,
    typename Strategy
>
class point_or_segment_range_to_geometry_rtree
{
private:
    typedef typename std::iterator_traits
        <
            PointOrSegmentIterator
        >::value_type point_or_segment_type;

    typedef iterator_selector<Geometry const> selector_type;

    typedef detail::closest_feature::range_to_range_rtree range_to_range;

public:
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<point_or_segment_type>::type,
            typename point_type<Geometry>::type
        >::type return_type;

    static inline return_type apply(PointOrSegmentIterator first,
                                    PointOrSegmentIterator last,
                                    Geometry const& geometry,
                                    Strategy const& strategy)
    {
        namespace sds = strategy::distance::services;

        BOOST_GEOMETRY_ASSERT( first != last );

        if ( geometry::has_one_element(first, last) )
        {
            return dispatch::distance
                <
                    point_or_segment_type, Geometry, Strategy
                >::apply(*first, geometry, strategy);
        }

        typename sds::return_type
            <
                typename sds::comparable_type<Strategy>::type,
                typename point_type<point_or_segment_type>::type,
                typename point_type<Geometry>::type
            >::type cd_min;

        std::pair
            <
                point_or_segment_type,
                typename selector_type::iterator_type
            > closest_features
            = range_to_range::apply(first,
                                    last,
                                    selector_type::begin(geometry),
                                    selector_type::end(geometry),
                                    sds::get_comparable
                                        <
                                            Strategy
                                        >::apply(strategy),
                                    cd_min);

        return
            is_comparable<Strategy>::value
            ?
            cd_min
            :
            dispatch::distance
                <
                    point_or_segment_type,                    
                    typename std::iterator_traits
                        <
                            typename selector_type::iterator_type
                        >::value_type,
                    Strategy
                >::apply(closest_features.first,
                         *closest_features.second,
                         strategy);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_RANGE_TO_GEOMETRY_RTREE_HPP

/* range_to_geometry_rtree.hpp
BZGC7kWQrBQHuqwSB9NXezdx5RHSB7OItJimkrWIshLOliBtHdb+MNqq8VZAnK4llwPtGVArbXC8xShDl6w9fWtrRUEj2YoMnhSiFHlW6TWSK7xf4f+lOwDla1I8q55F3pFKK02TlVehWKqa5NL7kvAWNqOUAJQaq/bjWTuyUsGnJAzxH3PgqP5amR+yu1bI4KtzxsaMfz6P/OFAftJnQnF/NVbiG6cV50Kr4lxQkZkaJwfBpnUHgNp/1+ayDrI9LOfiyg6LL63NsrMA+3dn3dOPg+FZd/UZkCJ+XUxWYn+VzOpcWIrq56TDVmU6zDp5jZur896z/LyBp/9vUmAa2JV394X7emCbgenefaMuO8BgVO9o3D87qscFYIGhKReQN/+ybaTThwoRIGq8lHNNbBio8eKobiNkmowzV9JIEoO8FG68drk/V11sSpyKcCrFJKqqrhjsfKo89qgut9wta7x1snW2Nfq9rtZbKhl2axIsEDvMIGXJON6U2srWRnYUINq+US5SGma7HEmDLd/50MjPjmYLAjSzSkoenh+7/dOjQ7N/3l+dBrKStrfVDNyhju7sADuSgvGAQpbwICPrW1HVpyy0awB38AcCrzx+LV41tQbb29lZnRqq+jaq5Uh1x7GuuXaQ62CLQ1Bm
*/