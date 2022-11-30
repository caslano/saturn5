// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_DISTANCE_BACKWARD_COMPATIBILITY_HPP
#define BOOST_GEOMETRY_STRATEGIES_DISTANCE_BACKWARD_COMPATIBILITY_HPP


#include <boost/geometry/strategies/distance/cartesian.hpp>
#include <boost/geometry/strategies/distance/comparable.hpp>
#include <boost/geometry/strategies/distance/detail.hpp>
#include <boost/geometry/strategies/distance/geographic.hpp>
#include <boost/geometry/strategies/distance/spherical.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace distance
{  

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template
<
    typename Strategy,
    typename CSTag,
    typename StrategyTag = typename strategy::distance::services::tag<Strategy>::type
>
struct custom_strategy
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Strategy.",
        Strategy);
};

// NOTES:
// - There is no guarantee that any of the custom strategies are compatible with other
//   strategies.
// - In many cases it is not possible to pass the custom strategy into other strategies.
// - The old backward compatibility code creating default Pt/Seg strategy from custom
//   Pt/Pt strategy worked the same way. The custom strategy is default-created.
// - There are two versions of algorithm for Polyseg/Box, one for Seg/Box strategy the
//   other one for Pt/Seg strategy. However there is only one version of algorithm for
//   Seg/Box taking Seg/Box strategy.
// - Geographic strategies are default-created which means WGS84 spheroid is used.
// - Currently only Pt/Pt custom strategies are supported because this is what the old
//   backward compatibility code was addressing.

template <typename Strategy>
struct custom_strategy<Strategy, cartesian_tag, strategy_tag_distance_point_point>
    : cartesian<>
{
    custom_strategy(Strategy const& strategy)
        : m_strategy(strategy)
    {}

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  enable_if_pp_t<Geometry1, Geometry2> * = nullptr) const
    {
        return m_strategy;
    }

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  enable_if_ps_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::projected_point<void, Strategy>();
    }

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  enable_if_pb_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::pythagoras_point_box<>();
    }

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  enable_if_sb_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::cartesian_segment_box<void, Strategy>();
    }

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  enable_if_bb_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::pythagoras_box_box<>();
    }

private:
    Strategy const& m_strategy;
};

template <typename Strategy>
struct custom_strategy<Strategy, spherical_tag, strategy_tag_distance_point_point>
    : detail::spherical<void, void>
{
    custom_strategy(Strategy const& strategy)
        : m_strategy(strategy)
    {}

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  enable_if_pp_t<Geometry1, Geometry2> * = nullptr) const
    {
        return m_strategy;
    }

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  enable_if_ps_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::cross_track<void, Strategy>(m_strategy);
    }

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  enable_if_pb_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::cross_track_point_box<void, Strategy>(m_strategy);
    }

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  enable_if_sb_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::spherical_segment_box<void, Strategy>(m_strategy);
    }

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  enable_if_bb_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::cross_track_box_box<void, Strategy>(m_strategy);
    }

private:
    Strategy const& m_strategy;
};

template <typename Strategy>
struct custom_strategy<Strategy, geographic_tag, strategy_tag_distance_point_point>
    : geographic<>
{
    custom_strategy(Strategy const& strategy)
        : m_strategy(strategy)
    {}

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  enable_if_pp_t<Geometry1, Geometry2> * = nullptr) const
    {
        return m_strategy;
    }

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  enable_if_ps_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::geographic_cross_track<>();
    }

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  enable_if_pb_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::geographic_cross_track_point_box<>();
    }

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  enable_if_sb_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::geographic_segment_box<>();
    }

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  enable_if_bb_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::geographic_cross_track_box_box<>();
    }

private:
    Strategy const& m_strategy;
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

namespace services
{

template <typename Geometry1, typename Geometry2, typename Strategy>
struct custom_strategy_converter<Geometry1, Geometry2, Strategy, cartesian_tag, cartesian_tag>
{
    static auto get(Strategy const& strategy)
    {
        return detail::custom_strategy<Strategy, cartesian_tag>(strategy);
    }
};

template <typename Geometry1, typename Geometry2, typename Strategy>
struct custom_strategy_converter<Geometry1, Geometry2, Strategy, spherical_equatorial_tag, spherical_equatorial_tag>
{
    static auto get(Strategy const& strategy)
    {
        return detail::custom_strategy<Strategy, spherical_tag>(strategy);
    }
};

template <typename Geometry1, typename Geometry2, typename Strategy>
struct custom_strategy_converter<Geometry1, Geometry2, Strategy, geographic_tag, geographic_tag>
{
    static auto get(Strategy const& strategy)
    {
        return detail::custom_strategy<Strategy, geographic_tag>(strategy);
    }
};


} // namespace services

}} // namespace strategies::distance

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_DISTANCE_BACKWARD_COMPATIBILITY_HPP

/* backward_compatibility.hpp
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
*/