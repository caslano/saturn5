// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_SEGMENT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_SEGMENT_HPP


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/expand/indexed.hpp>

#include <boost/geometry/strategies/expand.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace expand
{

class cartesian_segment
{
public:
    template <typename Box, typename Segment>
    static void apply(Box & box, Segment const& segment)
    {
        geometry::detail::expand::expand_indexed
            <
                0, dimension<Segment>::value
            >::apply(box, segment);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<segment_tag, cartesian_tag, CalculationType>
{
    typedef cartesian_segment type;
};


} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::expand

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_SEGMENT_HPP

/* expand_segment.hpp
aY/webKK4pVAVxjtds9+gr7h2Rzc0NXgkBEn27npz7cGpMlRpSXfs39/A+P7Nk2VcO1biOPt4zj8HiFhwCutyUug5vT/v3p9klFjfXUqsPvOHIbnRd/XxjZGaj51lBUdAjdiUkwbAmL6ra6X9naeniv0s0ZybmTh6lUFVz2nkmE59Q4a4c2M+zYmSdjZS843KmaGWi6rTrA13n4A+pnP7gMjyjNIdX3kQUQ+UXg2AFGK46qQrmpL4nfwbQwUtx3mXeGZNXCuCacIL7Vl6BtUdrRYYubMD7izaua/YQzVzAgXBW88ZS6ixS6EBDYYbpgQy/sfprkyvkWPZE3LcJfFwljJ8PPoPTexnAZjX0cBI95s/QJWTXvEqbmwr1pB42l8mIjYRqRV0JNe7gNmae7ixVrB3nTwNArsD4Rxya5yVTsaT37NQ8KCjw9F0CZl7NOEyzrIM7EK/VIexwqniYC47KiJiv4eMoiPAvREubKX5qq5YHdfPsiVJLYl4D6kEIF3MQVnF2femYXnJ/KMX0n7NfwkghLaBJzm74JYnNu7XTXrW/2Ev5rVcVXM/Q==
*/