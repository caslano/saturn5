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
ALJs9q9ORmoj+WuKy6Kma+T8I32AoOpMX6dWlWzhGpq4eNlPo5eg3bXrtzsRr/LNE8uTrH2QfwI5pCsIWcMveoVAHEv4LyqOR2FC0GiCO9TWVNdGv9De/Lb7q4MhNP0FRT4appMxfaBBs9pC0eVp7b4sYxcQeVT+rt9hfcHHAMSzdJit6JCLS0HAh3MOmrlXuxq6bfdBlUbr73oJimLW9dCzuVluPWXp9cX8zZAMOURauhALCf34bv1ApRlqqRsXAm3bm+FmFpHK1695YesmSLn/eBaVMkhk2/udOf+bT3BwluMlVjdIg3qcv0HqBD9fp9VBnPGPU/CUm2lQY85cPBg0kd8mBY4amkqFvXJM6XwAmQYfTid2iLcivN/T8xFTf8ef26uuhLuMHYwby2uVWNuLN1qchNfp6QXg7APRsZ2FXgUJG0HXwyma0sjTYIyzu+BkRJZxpZo8JXpzZYE2itX2jqYSe9lxGlvdTrmr725kg9VqNin7So1jv/y5MHoET3AaDMqedAflDUpyCFVJFirwm+T7Qcag+Fd/rkjsZ7BH9J6KMdwso5kpAw==
*/