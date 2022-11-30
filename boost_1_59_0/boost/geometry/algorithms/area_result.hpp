// Boost.Geometry

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2020-2021.
// Modifications copyright (c) 2020-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_AREA_RESULT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_AREA_RESULT_HPP


#include <type_traits>

#include <boost/geometry/algorithms/detail/select_geometry_type.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/geometry_types.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/area/services.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/detail.hpp>

#include <boost/geometry/util/select_most_precise.hpp>
#include <boost/geometry/util/sequence.hpp>
#include <boost/geometry/util/type_traits.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace area
{


template
<
    typename Geometry,
    typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct area_result
{
    typedef decltype(std::declval<Strategy>().area(std::declval<Geometry>())) strategy_type;
    typedef typename strategy_type::template result_type<Geometry>::type type;
};

template <typename Geometry, typename Strategy>
struct area_result<Geometry, Strategy, false>
{
    typedef typename Strategy::template result_type<Geometry>::type type;
};


template <typename Geometry>
struct default_area_result
    : area_result
        <
            Geometry,
            typename geometry::strategies::area::services::default_strategy
                <
                    Geometry
                >::type
        >
{};


template <typename Curr, typename Next>
struct more_precise_coordinate_type
    : std::is_same
        <
            typename geometry::coordinate_type<Curr>::type,
            typename geometry::select_most_precise
                <
                    typename geometry::coordinate_type<Curr>::type,
                    typename geometry::coordinate_type<Next>::type
                >::type
        >
{};


template <typename Curr, typename Next>
struct more_precise_default_area_result
    : std::is_same
        <
            typename default_area_result<Curr>::type,
            typename geometry::select_most_precise
                <
                    typename default_area_result<Curr>::type,
                    typename default_area_result<Next>::type
                >::type
        >
{};


}} // namespace detail::area
#endif //DOXYGEN_NO_DETAIL


/*!
\brief Meta-function defining return type of area function
\ingroup area
\note The return-type is defined by Geometry and Strategy
 */
template
<
    typename Geometry,
    typename Strategy = default_strategy
>
struct area_result
    : detail::area::area_result
        <
            typename detail::select_geometry_type
                <
                    Geometry,
                    detail::area::more_precise_coordinate_type
                >::type,
            Strategy
        >
{};

template <typename Geometry>
struct area_result<Geometry, default_strategy>
    : detail::area::default_area_result
        <
            typename detail::select_geometry_type
                <
                    Geometry,
                    detail::area::more_precise_default_area_result
                >::type
        >
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_AREA_RESULT_HPP

/* area_result.hpp
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
*/