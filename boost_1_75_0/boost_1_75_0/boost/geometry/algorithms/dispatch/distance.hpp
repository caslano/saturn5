// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014, 2018.
// Modifications copyright (c) 2014-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISTANCE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISTANCE_HPP


#include <boost/geometry/core/reverse_dispatch.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/algorithms/detail/distance/default_strategies.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/strategies/distance.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry1, typename Geometry2,
    typename Strategy = typename detail::distance::default_strategy
        <
            Geometry1, Geometry2
        >::type,
    typename Tag1 = typename tag_cast
        <
            typename tag<Geometry1>::type,
            segment_tag,
            box_tag,
            linear_tag,
            areal_tag
        >::type,
    typename Tag2 = typename tag_cast
        <
            typename tag<Geometry2>::type,
            segment_tag,
            box_tag,
            linear_tag,
            areal_tag
        >::type,
    typename StrategyTag = typename strategy::distance::services::tag
        <
            Strategy
        >::type,
    bool Reverse = reverse_dispatch<Geometry1, Geometry2>::type::value
>
struct distance: not_implemented<Tag1, Tag2>
{};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISTANCE_HPP

/* distance.hpp
2brJOYVlEkM0jPSV5xdp/Uf7lndy5nNcCety7oXXa6K+VVCiRbsGJ8+8uvuhBGkxm2LFAYH3L5PZ83U/FKybxSjCf7rIF76aXaKCm4F2j1cTddPLkO8QK1ceUUASRh57mvZGtr/QtN5GJw3/ZUwU50/jfcPICnntaC0XvZR7fyWgkB7DH/hMRWsMvRya+HnUH4DqfUolKw9U+x/1LVanPBUy81fOGacY84eTLHSwWq08sVlb5+g5fnGnGFiaepG+i7BgurF7PBK72rOTwCXj94yIfqGpD99Gnw3rttNrrtZfGhSI+TDybDFkS8lUBShrgHlZWGbUReJ2FYWCN1/0TL2JUjFwU1dpbqodaPcFbfb0dmedeRIhxI16VdhuZqqYQq0RSlodtbMvA+WuVLL6w/s+6Z1bs3C++jWc4Nxcnq8vDWPqrUAjdr6AofywmiR8EpT1W1DiSMQo1RCL0hOB5+hV5eZxZazRhGKDgQp3/tCMoqykMM83X+uZyHaJ5M+Yi6dDfMJBcFPQ5qr2MT6+pv3sg3pPaEAhrRZ7bwG4sLPIDs0l58+JMP9rAJdEF2cfmNHAGsaLJ9mSwNEjuQklRsaJWqJ1qXZyoeYuPwQMmcrHJxiFFbJk5CTsftNEUbNCSrjYTlOUsH8cxWaFVEMtCuvMhMC1nd+/sK7yVvd//8G/xtswkjNZ28120UnPkeU3K+GJ7Yp9Ofz3eUEB
*/