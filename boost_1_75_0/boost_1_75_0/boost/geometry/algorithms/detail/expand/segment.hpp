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

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_SEGMENT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_SEGMENT_HPP


#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/algorithms/dispatch/expand.hpp>

#include <boost/geometry/core/tags.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/expand_segment.hpp>
#include <boost/geometry/strategies/geographic/expand_segment.hpp>
#include <boost/geometry/strategies/spherical/expand_segment.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Box, typename Segment
>
struct expand
    <
        Box, Segment,
        box_tag, segment_tag
    >
{
    template <typename Strategy>
    static inline void apply(Box& box,
                             Segment const& segment,
                             Strategy const& strategy)
    {
        boost::ignore_unused(strategy);
        strategy.apply(box, segment);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_SEGMENT_HPP

/* segment.hpp
xEEu8Ww2zjLVNJiw3ebPD6C74Ia0D+OnURTP6x9zZF2DiV++vTiAdjRQ/PUWImQmzotZsQ0PN3C77hMQeQfC5Qaqj2FLEK0Yqo8522A9Wp9u1w4LpeIOkE9AuqI8U2/fwgn8jNBduh11ZhCNg8QP7iL9RZJvu6tXd5T8zwoPieukbLldCgs+qUD4EBP9pUZsSYSb4Qutu4vvt+yAyJ8hfHkXnZ/ZQkKZidnGRgHfgu+OxpYYW1CBxM0Om6go6n9ODiCXy01+YFL+yMhvVzkM4R2OODBY9fx0/OsQXuKBnJCvBvmwQC535DurXXnuAuciR0yulVpQHVRXnBnnc5ZLc7JzUBQPy4OG5bnJnm4CD6uhkdtszIfIbgh/akycweMH380agB6OFmreWjpNTxDsazTq+8JlN5qk5L4ptIv5sKo0KtvVarxEXasRG8mIPE8MqxtwDsj0+kH2Ag1mPoY/MoCOW/kZ3/PzQOQHEO78WSKfh81W4LOZaQnLoMnAhJ1z+NHPjFmEQJjfKedcF/LFRdIDYoFcq1Srz2mVSpY8kR0QRC2cb2G5dJDzDrQfDmcYh6Z++OjPuBz0DEQ+gHDDyN/GXNOMaTpx1GlWS7D8fWrkryLnczc6kRJ5pVf+Ck35a+uVO30cDrNgpcfn8DmVjN3pkPj5HKbnvXOO9bzJFFHajfE+G5pDx3QasZfIZecNV8Oj4U1wOQzBobCl
*/