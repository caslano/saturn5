// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_FEATURE_GEOMETRY_TO_RANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_FEATURE_GEOMETRY_TO_RANGE_HPP

#include <iterator>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/util/math.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace closest_feature
{



// returns the range iterator the realizes the closest
// distance between the geometry and the element of the range
class geometry_to_range
{
private:
    template
    <
        typename Geometry,
        typename RangeIterator,
        typename Strategy,
        typename Distance
    >
    static inline void apply(Geometry const& geometry,
                             RangeIterator first,
                             RangeIterator last,
                             Strategy const& strategy,
                             RangeIterator& it_min,
                             Distance& dist_min)
    {
        BOOST_GEOMETRY_ASSERT( first != last );

        Distance const zero = Distance(0);

        // start with first distance
        it_min = first;
        dist_min = dispatch::distance
            <
                Geometry,
                typename std::iterator_traits<RangeIterator>::value_type,
                Strategy
            >::apply(geometry, *it_min, strategy);

        // check if other elements in the range are closer
        for (RangeIterator it = ++first; it != last; ++it)
        {
            Distance dist = dispatch::distance
                <
                    Geometry,
                    typename std::iterator_traits<RangeIterator>::value_type,
                    Strategy
                >::apply(geometry, *it, strategy);

            if (geometry::math::equals(dist, zero))
            {
                dist_min = dist;
                it_min = it;
                return;
            }
            else if (dist < dist_min)
            {
                dist_min = dist;
                it_min = it;
            }
        }
    }

public:
    template
    <
        typename Geometry,
        typename RangeIterator,
        typename Strategy,
        typename Distance
    >    
    static inline RangeIterator apply(Geometry const& geometry,
                                      RangeIterator first,
                                      RangeIterator last,
                                      Strategy const& strategy,
                                      Distance& dist_min)
    {
        RangeIterator it_min;
        apply(geometry, first, last, strategy, it_min, dist_min);

        return it_min;
    }


    template
    <
        typename Geometry,
        typename RangeIterator,
        typename Strategy
    >    
    static inline RangeIterator apply(Geometry const& geometry,
                                      RangeIterator first,
                                      RangeIterator last,
                                      Strategy const& strategy)
    {
        typename strategy::distance::services::return_type
            <
                Strategy,
                typename point_type<Geometry>::type,
                typename point_type
                    <
                        typename std::iterator_traits
                            <
                                RangeIterator
                            >::value_type
                    >::type
            >::type dist_min;

        return apply(geometry, first, last, strategy, dist_min);
    }
};



}} // namespace detail::closest_feature
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_FEATURE_GEOMETRY_TO_RANGE_HPP

/* geometry_to_range.hpp
Cq46UBkcJXJRc4YYD212QeZJzbT1KzxbPcN2EKBJO486FieA518r8ArJbYrWu6TQXMKceXECnHLfcurA/lqlDt8Y9kVA3r7vxaHj9Y2BUJLCj6Nskpz0fDZSh03tqBbybjl1QeWZjCu3uUGNpqP4E6qgb0DUBm5qOgFko6A0ib+01uhI1IvaJVSPhmeXjJNRlDU5DU6EqsocNSMpHbLO8WM2qRcmMc5jIFJKgv2679vnJ/J9rti8PtFf4q+sTQeJGUcDMGYPVU1XFZIuF8xL2KR/WBKR1x8ECHL1J+hoecuXpCYpe2lzSoyKjVx+aZVEIGZUWfaZc71+V6v3fJITFgq7LrMQ1qjrb0WYW3NU6YMCyDymWZLvv9/rFirwCg772977V4n7WnMZa7z2jiaO13F6ov4ZZxPWgmfOndiaZAlgIWHtDFgMeaZgODs5um+giUWbeDvtqytMH2Np2EyvXpyjU1GpkXl9rt+0pjceNfGs10hT9IwODVFLTiCO2USIS+/FLbwXWTyeFHFXD+KGlhlcLe+7xru7dmFxiqGMJNf+Hqtpn1NuHySlzcXgDK8djzfwsKhVIN1cYnZnrTRlvuyUDgz/vIGEZ2N/gwQMByEAaQ3+rS+LgCUbEsVcYhwXiKBMGzG20Rj+jK+R
*/