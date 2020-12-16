// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_DEFAULT_STRATEGIES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_DEFAULT_STRATEGIES_HPP

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/reverse_dispatch.hpp>

#include <boost/geometry/strategies/distance.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{



// Helper metafunction for default strategy retrieval
template
<
    typename Geometry1,
    typename Geometry2 = Geometry1,
    typename Tag1 = typename tag_cast
        <
            typename tag<Geometry1>::type, pointlike_tag
        >::type,
    typename Tag2 = typename tag_cast
        <
            typename tag<Geometry2>::type, pointlike_tag
        >::type,
    bool Reverse = geometry::reverse_dispatch<Geometry1, Geometry2>::type::value
>
struct default_strategy
    : strategy::distance::services::default_strategy
          <
              point_tag, segment_tag,
              typename point_type<Geometry1>::type,
              typename point_type<Geometry2>::type
          >
{};

template
<
    typename Geometry1,
    typename Geometry2,
    typename Tag1,
    typename Tag2
>
struct default_strategy<Geometry1, Geometry2, Tag1, Tag2, true>
    : default_strategy<Geometry2, Geometry1, Tag2, Tag1, false>
{};


template <typename Pointlike1, typename Pointlike2>
struct default_strategy
    <
        Pointlike1, Pointlike2,
        pointlike_tag, pointlike_tag, false
    > : strategy::distance::services::default_strategy
          <
              point_tag, point_tag,
              typename point_type<Pointlike1>::type,
              typename point_type<Pointlike2>::type
          >
{};


template <typename Pointlike, typename Box>
struct default_strategy<Pointlike, Box, pointlike_tag, box_tag, false>
    : strategy::distance::services::default_strategy
          <
              point_tag, box_tag,
              typename point_type<Pointlike>::type,
              typename point_type<Box>::type
          >
{};


template <typename Box1, typename Box2>
struct default_strategy<Box1, Box2, box_tag, box_tag, false>
    : strategy::distance::services::default_strategy
          <
              box_tag, box_tag,
              typename point_type<Box1>::type,
              typename point_type<Box2>::type
          >
{};

template <typename Linear, typename Box>
struct default_strategy<Linear, Box, segment_tag, box_tag, false>
    : strategy::distance::services::default_strategy
          <
              segment_tag, box_tag,
              typename point_type<Linear>::type,
              typename point_type<Box>::type
          >
{};

template <typename Linear, typename Box>
struct default_strategy<Linear, Box, linear_tag, box_tag, false>
    : strategy::distance::services::default_strategy
          <
              segment_tag, box_tag,
              typename point_type<Linear>::type,
              typename point_type<Box>::type
          >
{};



// Helper metafunction for default point-segment strategy retrieval
template <typename Geometry1, typename Geometry2, typename Strategy>
struct default_ps_strategy
    : strategy::distance::services::default_strategy
          <
              point_tag, segment_tag,
              typename point_type<Geometry1>::type,
              typename point_type<Geometry2>::type,
              typename cs_tag<typename point_type<Geometry1>::type>::type,
              typename cs_tag<typename point_type<Geometry2>::type>::type,
              Strategy
          >
{};



}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_DEFAULT_STRATEGIES_HPP

/* default_strategies.hpp
dT3TliZMbm3NaKDt+ja5Of8RnErN8+7N81UH/fHxqc/VorimOaFmFrkHTByUyTOh1811hXlQY/595jtdlH1v4FFvMWu/hge7Pf9y27r1REXebqpacCSSR6+GQ5LSFlt4TZn0UEZaUq3kSmc/pcy5a8T8DS6mO0LgU/gRM7C4Xd2lvzyTfr03nG7i/zfUCSx6kFhNLVBv+qJRPvoIB9VbwP927tn1Ia/4snOiQvrmI3owL/9IjV4SrzsT9G0RPGtdJ7fTl67zRTq6upvnvSvBzJ9weKhns+MH/GwqTIXbk9fg7IVytCoAWJyvmFHG6NHEe3GCPvr5iR72+XN7WL7MmsyFwXI0iE491IW3lYHHNEW/j8P7tG/SHDTmffUvBl15EwXy4nk1GvustX6L4+Kqazq7t/fP0uxZ98B7fm92/V3OzJ34aoAvp0Ym0qGxaZAnzrto0Si8vDeTGYOOPlyGr65m1/jZztyf4w3PExwyg07/Az/C/glFfN8en66hbePAuQQwriMMoW2Lw7vcxwJmSWtLIA/qesIpvP5MvDKpY9q1Ovw71RjGB8Gy0ThsBg2G74fCrA6/iRs/KfdkdRoMI16pww9xZQM++R4x26225bbkSHrL2jqNoo834CgY214uCzf3tTH0glq/B5PKHIfFveDCXzFzMK02Dd++sQ7rWbFDPfAUFsCMwhEB3pjnC+i/b2N83ZT6fKO+MCONeK33u6rZH/RdKliynv6h63pOgRf6ekhevMffyFLLvEWLZ8uvL//EDzDmDm7+jC5JNxCXi3kye6+IW/gWgfR6MwPNFGzmewBjn/ehdfrK1wJnQPBvXn9zVTJ6k5Z4ZN8ZWtCdOTzXi9t+4EcUDnXdA/baMmYmUvuj9Of38NVZ8GH4d6GRZ9L10r14cN/9B9z1nME0dZCGFvyRFwor/vGazXX0gN49virm90a5t708rE1PLOLtFNSz7enGXnhB/WRfC+ey4uYwtd+G3k6i98wZfVvjKRhQvLVzd3Fp+RctStdlks9P4ESCDZLte+en0rTncTKN8p1rhrvOZetNqMfq9VDf5vg+sOt2Od4VLqpeik79xayYH05cp3tu2HM+2q0Dj62AOTkd7ZmC1mopZyl4U2VwPwx/9xIuFeN78DxC9Gh3s87moTSms4PK/PBc5pcNePPcC7HNRT+llb/RcCIlv5m+zarG8sOH7bB2dkZ8/wp/h8DKZAHeP4zLwWvg+7/lYyRTV6O8f19r2vA4XDwoB1NcLxQum4/Xz/Q8zn+dwU+gb5bxvn/nmRxRp2Fi3cGa5GWE2O2YSePwoOrbz2s9GUS3jptHG0eogfHm5pV609of6YXyS2kKeqh3JfiRiZ5r/a9WHZkeNsfjN1ygJePKJ62SFG8X+8D64M1Wc1mF8p4nitGWxcWuvjkznp4Ur4Ty2c56Ey/03vIwZFWAdsOXPXmp9MCT2LTD6mDP5+p3fHwDL+2BHzn2mSnpzvfOUlPL0WOz6enNavosXL0rj7DwF/hZAR4nUb/T4X9QGjX2nI7ztci9NJDZZR+vI8JM2fUxHfql/npppqApe+Nz402gg3VGzDQf1sKJ/Jm72XjOUXzh5vL5UbCfR6Q5Egfx/XkSS8z+GdznAu2pblvBo3kwsvpJHk47M850HL6X726OPHAQb+OAzqPpe333dq6abEyj75bbubTfN3R8T+eYdO71EnpotfNaZ+G19U3adc5nP7KWL/jK5rL/fID7YfxCNZAgxsv9G47H12s3+RC8l9Q1rO+S/RXic6j3nWquNpxJ9Sk9KNftjlv7Nq/9XF/28166soj/t5H/QtP0V3F4JYdPhsKjfDQnTfp+BP13yRn+KjmtAXM=
*/