// Boost.Geometry Index
//
// boxes union/intersection area/volume
//
// Copyright (c) 2011-2018 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_INTERSECTION_CONTENT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_INTERSECTION_CONTENT_HPP

#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/detail/overlay/intersection_box_box.hpp>

#include <boost/geometry/index/detail/algorithms/content.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

// Util to distinguish between default and non-default index strategy
template <typename Box, typename Strategy>
inline bool disjoint_box_box(Box const& box1, Box const& box2, Strategy const&)
{
    return geometry::detail::disjoint::disjoint_box_box(box1, box2,
                typename Strategy::disjoint_box_box_strategy_type());
}

template <typename Box>
inline bool disjoint_box_box(Box const& box1, Box const& box2, default_strategy const& )
{
    typedef typename strategy::disjoint::services::default_strategy<Box, Box>::type strategy_type;
    return geometry::detail::disjoint::disjoint_box_box(box1, box2, strategy_type());
}

/**
 * \brief Compute the area, volume, ... of the intersection of b1 and b2
 */
template <typename Box, typename Strategy>
inline typename default_content_result<Box>::type intersection_content(Box const& box1, Box const& box2, Strategy const& strategy)
{
    bool const intersects = ! index::detail::disjoint_box_box(box1, box2, strategy);

    // NOTE: the code below may be inconsistent with the disjoint_box_box()
    // however intersection_box_box checks if the boxes intersect on the fly so it should be ok
    // but this also means that disjoint_box_box() is probably not needed

    if ( intersects )
    {
        Box box_intersection;
        bool const ok = geometry::detail::intersection::intersection_box_box
                            <
                                0, geometry::dimension<Box>::value
                            >::apply(box1, box2, 0, box_intersection, 0);
        if ( ok )
        {
            return index::detail::content(box_intersection);
        }
    }
    return 0;
}

template <typename Box>
inline typename default_content_result<Box>::type intersection_content(Box const& box1, Box const& box2)
{
    return intersection_content(box1, box2, default_strategy());
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_INTERSECTION_CONTENT_HPP

/* intersection_content.hpp
5q6pTdtLk3gob6NSmOq5tjutt2xYHx/nlz9NjcfCBvKrD9GeynGxeNvZ8mthKL/EP1fyqyfZz+AxBuysO+ES/4nmG31Xnceu1+tODyrxbVh3Omgb1Z0OGkV3emYzzgXrdaer8Tm+3rkm+6ZR39T4NHrXFvRyNvEj8l8QAL3EB/7K2cRXI1j7S5X4OPcW8Q240TeU+PTfwPvufF72NODbiE+9Eh+5m+aID98hQULQXpa32H5elvNEN/8dL/5tRZ/xT2Tv6i3HX8prkhBTaDo9FXovvDt96zOMwRM9HZE+aIdpbns56/swTCHPbe9twruiznRzf1u2+G4+Z8z1eA7rjw9m2NON3y4oMvpIvf6YO4j+HE4zi78jnfcchLzJw3cSEQ9fdM/ExMSTsBWVlWWViSvgbtCtA91hmKWwR08WVWZSdjbxvpJF2+Zupj3dndYwllvLZt5/lHNSG03CzTx3uxFmK3zyMtW0gqoTfo/Ttd4wTwcpM8PIvhIrgF7bWIxDsZXPM4huMUZLiVz+rLDa8ZgsxGcfk7UGnk5013jmcdkuF95cbkPNNZZ9jb9Rr+jUl/LmeOuL5Xe89cXyad7RGHQPr+17zTTOBZ6abhRgJY2pfdbpdexAdL94LkX6vCnzY4u/g9tYAP6chpwf7cju815tjC1h1D4ptO+cS3QtvcYY+kPr3X8JL5fK9S6Um12bzPX06K5YTG9hLKbHO9bS2zHtMab1xQR3JCaBPlZPn8r0fhTIFSb9Lqof7D5kM38zuEE+6vbNus1wM+rShYldE8+OSwB5lM+Xou1b7d9YB76FdHfa12JZNHhifLbxk0q7W2ijg58apC08Dlpe44X+OcjTjPqqGX9xOXXv2/tvcfaF7+agDcuylzk+ijvDpW/PCvWDlzvfSWR/97e12V/S4/kI+km3uF8u7ym6vq0tbVr5vXy/k+O+gMc1W9W4q/c7nfFn+r7aswXjxb+d3Kd9BfaG3tT7B/ztb+rlZEfJ3cxByC//vda9yzNO+E09l3u1PH6ieKj76/eZzDXcZ87mPrMwW0kzft+BO02XMXA58UzhdLTCyKJ2Yy7iOO0+q9/s6tpvvgW6bvdxXzjRvS+0aKdYtAP/u/2mvA22ld+D4X7zTpgbjLGZml5IqpCeRDmW4KJTxZsTRXokRoTaeITHfSroT6JxmhUIl0OhaSf97s9kvwF3KLyOummN034kmmUY3XD7LuHkUnm8FRFbcz/r+s6qVsrglgj70rAyKP0o4gG7xEPOw0h95v2IEqQH6/NW2rb6rbK3JP96ZxhnC5S0Ly2bMX+2y7yFaaNpzSbBo+qvBRufr1PpEESz55wIG3YKW5k7b3zAea7lfcR3jz0uTbjjCD7ZXz/T+aYy/Bs9+9JgPBCm1Q4r9yIDDzrj8bpRH+zxaMa9yHqWt6WU4/mhct/MuLRS1gHmK2Vr7kPOfvMDYy1DjQevYOhlBm1Dd9vg33C/yf7Sfh1swt23Lm5339z7TRmn3rotpGsvi/E0+OTlKnGf5bJmxnRtpY0ZSvYFnmHKPgzYJS0snhzRpXMa2a+g85KOu5LcTp5NNCVYw0wUneRXI6PKeT90JX6viqh9ik3ZlCv7om59Jqchya3U3VsfNgMbw33mIJhPjDKvptds7BnUoLtUznG4zKGYN1PWg47mhsYgCfb6zGnxPfl3DtWJXPVcwecQ7IsTnGcnuLyhXv6Is658hvgXtLHHn5aP+FkFbblhen5r0vmmAvzV+nBtM9aPrLjMV99OkPFP/0ed7VcffCegxMVxv881H8En7bDf2Q7Dv9G2a1xj70D4XfIla7szLl8YY381LpW1syUq7nrnbPGIcsZD/DONMSw=
*/