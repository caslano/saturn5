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
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
*/