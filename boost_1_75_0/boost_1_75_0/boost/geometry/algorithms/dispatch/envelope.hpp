// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DISPATCH_ENVELOPE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DISPATCH_ENVELOPE_HPP

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tag.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type
>
struct envelope : not_implemented<Tag>
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DISPATCH_ENVELOPE_HPP

/* envelope.hpp
LXtW/B9fD40GVTvJr3TgWmMeNRqjVLvr6RoCo/fpmJr1Syt76a4j5GTGy7FLEtvyJaFH2p5K6TVFxnuRpF2HVapp/Y+3tLQwsdO2P79LymWq20v0HYNrdcI54sZtP7NKwGthRWOPB+yTQZ1lYwtyNsbbe7aimynfx9Nnn58VymT/utGi/8aSHue9AzqARgTs2MSMCJlgJe1L+8tMvqIFJGG28Fjzh6M9AzeTjcrFHe8aQ4TMyuvffikzXlD/spO+EvjTFpgggocceCmluZJztqwi7hqFY/07qsAkXLelDQ/t5a3eNBRMmykD50WX63drqSbTBXDEjrw+6cq9t/3SYfjmwAAb7k2wKE5zclc7i0DIl8kOiFZNHpUjndtMN9+xZMtKzYhPHbxfq1MkZeYKb9BykFia68id7MVr5EELK0vwNxON7dA9wsEstcb+2BhYaaMZR2f5Zhziz6fmhuZw909HDXWOxSmzE3pnqGuh0HJjgQHBNGj5ZM/YdboLE1isceGP7eTreQvWP0yJW2IDf0fF9T/689LWuX1DIxT5JTRilVGVPbRe4XqFxo6eq0+c8eDwtpwXPW6bTtuXwyr7Y+1hj2IaBj4dWNILVhsX6RULgRtCKlKcjeTGQpmKkF6hOlaSrBJetRBsp+7oIDfmXek3nt0258R0Wlho/yf7hwYvx2FpUFT1sjksLxE7xlZDh2Ca3rsrX39JCvW9
*/