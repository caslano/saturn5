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
Oss3If6AdsYYLm2t67pHynU44mfiqsG4ATzpi+Qze8SMHpJBHuia9Ew6NrFVoREZHX9N8zwlW33EOPp8g68ysr9Q7F3w0IG5M87ooN7weYlqt9vMXaAvBS3Dtb1/PCK28PxF/u9Y0ydeCR4HImKLL+ax2uwve42S5wEjz2vBi+G2/Ooan1e7Kf8Ngb0YmqWVVtYjvDeVpnU/TXtlICdotY28BXIWkG47rsiX9VCteFoZrpb2ggw1Yf1c06T3jvp4O/d9h9A4HbufpXmX2I8vR9N8X5Y5VWH7eQ94Ya8xyjR3wKH/sp1oP/r+pvA6n/CO/jrQsx1p+g8aesI7+g+B/oDhf72hPwD+N4D+AUN/o6F/APQfVbogHtI2do/LTdI23FciYoYKz7Jb/M0BHuVY/C0K/0AE/laMXfPVmuY2+EyGf1iduf4c4Or+Sde+n+f2NG38BYJpumrYQZPZK/4lsXnDg8q5vUnaTPqdfiOL9H9QtZu1fUdxVyCH0IDOyPs1lEV2jbKUjVb5P8v7HiX7Z5G/GnGqb5o+93Ez5nzbjGdvUbzWHhfmdb8ZL74psklfdfy1rr5ryg94rj0OccMAD9nz0j8QNxQ8+rr0B8QNlb7sN+/PG3l/YngRj3Dc0PiWPGxZ979fGB6NwDdCnl8F+gNe6/Y3QV7IZuvyO9jViVXqzgaVfpKys4dIPw/TmJ5GGWnI9wjqvF3pQ+d5+aJiHsrv7/NSMjNMy/znJqHV3zlcWvufvyn/o3n/PagzeNt+/88Aj/75MdMm/2qSdyMdrm+RXwf7fh3h3PeRsnVSX0e3PWJ8mLMOZQY0pswjAh4ok8pxdJrHXNBAr47OtsWRhmZ7BM3RIouP/5GJWRwrPIp1Pwo0HwOPJ65DmyN9+yKMyZBf5TP6OsKrNnn/iPZeHNGfPmvuSzkOeeeYNNPZvAtNvGkxaBluaf+4MEz7ZNAy3DPnBSk/zrLTz/j0pet8W/2svotC8pjYDsrIa/mE3v9p+uXr9FwFPI2drVA8bqz3f5rH6evs/MOWQ+83oA6LzXi/cl24vxHe0T9D8TzF0JAeHM0q8OSyNM/Vhp7wjn4N6P9o5jT1hp7wjv5MJQPLNTaffuY7V6Pohmki9nkpPMtt8RtM+1j8RoVnuSy+dZ2eF7gy4FPMnfymDfNa38Snc13Rbm9Bv2Q6916/j6v6iIqBdK8LxwrOMnZ3timPygnHH6Q8xps7m4K84GtlPYdgy73wmxjq/lD3bSE/zkfAi++aDa7T32za6L7N9qhQcBSidCzuMPiw7rYa3W0z/mc70gTXYxWlTQxE7DagR4wj0B94W5t5tvHnTGP9eUxkgD/FmN5Y44/h99MYrtMPmzGd28HyHAVPxoGn2O7F8O1st983/m+XsvGHpqBLgs7yw/1HQneB4VeKbqIEP3s+M2P4laK7sARd/8owXS66XPfT95wULB3GRUu3dx3Ssr/VyhHN/yIjbyn+zzXzkACfRn+9ROzNlKXuETtgeKTN/OEFBn+xwb9oHeZXwOMNOm5TnAHW9JXepYbfQ4bfZQbPcmr8ywQvd6WE8K8Q3bl5i703X3T3KoxJz6zm79uIERp9G527+c7lyHfHouJ38VeqvxdXhfawytyv2pxzfqPyw5ctDPvwKwgHedBmkAc60fK8WfG5dHXYn10F+2O4nSOVHxemfRtoGQ5a+bal042Et7xuMPOtd4EXwaP2T7pYXN7cKfBeX68kqznzanwt4R39+0HP8mr6Dxh6wjv6D4L+KjMP+rChJ7yjvx70jYb/Rwx9I/jfCPobzBznY2F6wmOP1Tr9rTEiXhLg0VYWf7PCXxUVL1F4ltHib1V4lsnib9M+aKE=
*/