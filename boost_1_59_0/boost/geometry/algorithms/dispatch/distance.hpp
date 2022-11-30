// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISTANCE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISTANCE_HPP


#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/core/reverse_dispatch.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/distance/services.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry1, typename Geometry2, typename Strategies,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategies>::value,
    bool Reverse = reverse_dispatch<Geometry1, Geometry2>::value
>
struct distance_strategy_type
{
    typedef decltype(std::declval<Strategies>().distance(std::declval<Geometry1>(), std::declval<Geometry2>())) type;
};

// TODO: right now legacy single strategy can be passed here in some cases
//       so for now dispatch also by IsUmbrella. Later this could be removed.
template <typename Geometry1, typename Geometry2, typename Strategy, bool Reverse>
struct distance_strategy_type<Geometry1, Geometry2, Strategy, false, Reverse>
{
    typedef Strategy type;
};

template <typename Geometry1, typename Geometry2, typename Strategies>
struct distance_strategy_type<Geometry1, Geometry2, Strategies, true, true>
    : distance_strategy_type<Geometry2, Geometry1, Strategies, true, false>
{};


template
<
    typename Geometry1, typename Geometry2, typename Strategies,
    bool IsDynamicOrGC = util::is_dynamic_geometry<Geometry1>::value
                      || util::is_dynamic_geometry<Geometry2>::value
                      || util::is_geometry_collection<Geometry1>::value
                      || util::is_geometry_collection<Geometry2>::value
>
struct distance_strategy_tag
{
    using type = void;
};

template <typename Geometry1, typename Geometry2, typename Strategies>
struct distance_strategy_tag<Geometry1, Geometry2, Strategies, false>
{
    using type = typename strategy::distance::services::tag
        <
            typename distance_strategy_type<Geometry1, Geometry2, Strategies>::type
        >::type;
};


template
<
    typename Geometry1, typename Geometry2,
    typename Strategy = typename strategies::distance::services::default_strategy
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
    typename StrategyTag = typename distance_strategy_tag
        <
            Geometry1, Geometry2, Strategy
        >::type,
    bool Reverse = reverse_dispatch<Geometry1, Geometry2>::value
>
struct distance : not_implemented<Tag1, Tag2>
{};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISTANCE_HPP

/* distance.hpp
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
*/