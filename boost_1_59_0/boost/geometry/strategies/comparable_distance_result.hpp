// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_COMPARABLE_DISTANCE_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_COMPARABLE_DISTANCE_RESULT_HPP


#include <boost/geometry/algorithms/detail/select_geometry_type.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/reverse_dispatch.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/distance/services.hpp>
#include <boost/geometry/util/select_most_precise.hpp>
#include <boost/geometry/util/sequence.hpp>
#include <boost/geometry/util/type_traits.hpp>


namespace boost { namespace geometry
{

namespace resolve_strategy
{


// TODO: This utility could be entirely implemented as:
//       decltype(geometry::comparable_distance(std::declval<Geometry1>(), std::declval<Geometry2>(), std::declval<Strategy>()))
//       however then the algorithm would have to be compiled.


template
<
    typename Geometry1, typename Geometry2, typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct comparable_distance_strategy2_type
{
    typedef decltype(std::declval<Strategy>().distance(
        std::declval<Geometry1>(), std::declval<Geometry2>())) type;
};

template <typename Geometry1, typename Geometry2, typename Strategy>
struct comparable_distance_strategy2_type<Geometry1, Geometry2, Strategy, false>
{
    typedef Strategy type;
};

template
<
    typename Geometry1, typename Geometry2, typename Strategy,
    bool Reverse = reverse_dispatch<Geometry1, Geometry2>::type::value
>
struct comparable_distance_strategy_type
    : strategy::distance::services::comparable_type
        <
            typename comparable_distance_strategy2_type
                <
                    Geometry1, Geometry2, Strategy
                >::type
        >
{};

template <typename Geometry1, typename Geometry2, typename Strategy>
struct comparable_distance_strategy_type<Geometry1, Geometry2, Strategy, true>
    : comparable_distance_strategy_type<Geometry2, Geometry1, Strategy, false>
{};

    
template <typename Geometry1, typename Geometry2, typename Strategy>
struct comparable_distance_result
    : strategy::distance::services::return_type
        <
            typename comparable_distance_strategy_type<Geometry1, Geometry2, Strategy>::type,
            typename point_type<Geometry1>::type,
            typename point_type<Geometry2>::type
        >
{};

template <typename Geometry1, typename Geometry2>
struct comparable_distance_result<Geometry1, Geometry2, default_strategy>
    : comparable_distance_result
        <
            Geometry1,
            Geometry2,
            typename strategies::distance::services::default_strategy
                <
                    Geometry1, Geometry2
                >::type
        >
{};


} // namespace resolve_strategy


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{

template <typename Strategy = geometry::default_strategy>
struct more_precise_comparable_distance_result
{
    template <typename Curr, typename Next>
    struct predicate
        : std::is_same
            <
                typename resolve_strategy::comparable_distance_result
                    <
                        typename util::sequence_element<0, Curr>::type,
                        typename util::sequence_element<1, Curr>::type,
                        Strategy
                    >::type,
                typename geometry::select_most_precise
                    <
                        typename resolve_strategy::comparable_distance_result
                            <
                                typename util::sequence_element<0, Curr>::type,
                                typename util::sequence_element<1, Curr>::type,
                                Strategy
                            >::type,
                        typename resolve_strategy::comparable_distance_result
                            <
                                typename util::sequence_element<0, Next>::type,
                                typename util::sequence_element<1, Next>::type,
                                Strategy
                            >::type
                    >::type
            >
    {};
};

}} // namespace detail::distance
#endif //DOXYGEN_NO_DETAIL


namespace resolve_dynamic
{

template
<
    typename Geometry1, typename Geometry2, typename Strategy,
    bool IsDynamicOrCollection = util::is_dynamic_geometry<Geometry1>::value
                              || util::is_dynamic_geometry<Geometry2>::value
                              || util::is_geometry_collection<Geometry1>::value
                              || util::is_geometry_collection<Geometry2>::value
>
struct comparable_distance_result
    : resolve_strategy::comparable_distance_result
        <
            Geometry1,
            Geometry2,
            Strategy
        >
{};

template <typename Geometry1, typename Geometry2, typename Strategy>
struct comparable_distance_result<Geometry1, Geometry2, Strategy, true>
{
    // Select the most precise distance strategy result type
    //   for all variant type combinations.
    // TODO: We should ignore the combinations that are not valid
    //   but is_implemented is not ready for prime time.
    using selected_types = typename detail::select_geometry_types
        <
            Geometry1, Geometry2,
            detail::distance::more_precise_comparable_distance_result<Strategy>::template predicate
        >::type;

    using type = typename resolve_strategy::comparable_distance_result
        <
            typename util::sequence_element<0, selected_types>::type,
            typename util::sequence_element<1, selected_types>::type,
            Strategy
        >::type;
};


} // namespace resolve_dynamic


/*!
\brief Meta-function defining return type of comparable_distance function
\ingroup distance
*/
template
<
    typename Geometry1,
    typename Geometry2 = Geometry1,
    typename Strategy = void
>
struct comparable_distance_result
    : resolve_dynamic::comparable_distance_result
        <
            Geometry1, Geometry2, Strategy
        >
{};

template <typename Geometry1, typename Geometry2>
struct comparable_distance_result<Geometry1, Geometry2, void>
    : comparable_distance_result<Geometry1, Geometry2, default_strategy>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_COMPARABLE_DISTANCE_RESULT_HPP

/* comparable_distance_result.hpp
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
*/