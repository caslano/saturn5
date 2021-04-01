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
ivHbSCE38Fur8jAdeKD9oqaGT3ZH4uxYV/0kvydXCqwKN2eVlC6cBu9lRNA6wzu4QmNS3C1P3UW4GwVm0XxyRAgfS8B43lX7t2znh6u7Y1pUdy7lqfQ444APwE2r3oGqBkW+JoHJRkCB39t7lbbv4YoT4kBql487DJdNG49ttsQ1+qzxiWaDd07oUkByLKL34ZPoN0f2pV1hJg71ZK9FqNM+3oqTU8RK6143ynib9nGT0SPUcuc3kMj3bMZX+6HqhJjQRB3gWe5wbz4/awJhneLc1FJguRURbrCariL0toba++JAPaIgt/ljFjQuzhhJUeI1PoTStmmllQP4MPIcZnuD/oo9KXopQCUEc9fDzrBOBCddRxMAt+rYhhCcANnMZln2Ivo6McpTH5NGfcxtoHrFc+LQuMMxSBfxqEkQkngt9CmeyJrTyUYx6Rv5T75HSEwl/9aBR27U0NCsSaOvhtB3pF2+3SSuyAZaWjhV6YGv8HqzGas0Uv6BNWkk9EhYfgIfL1OV/OhcPRhHtTSGpwKlkZU1stlIQL9TE+Vq8SpbFk7qx4iVSG/+Lw==
*/