// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_DISTANCE_SPHERICAL_HPP
#define BOOST_GEOMETRY_STRATEGIES_DISTANCE_SPHERICAL_HPP


#include <boost/geometry/strategies/distance/comparable.hpp>
#include <boost/geometry/strategies/distance/detail.hpp>
#include <boost/geometry/strategies/distance/services.hpp>
#include <boost/geometry/strategies/detail.hpp>

#include <boost/geometry/strategies/normalize.hpp>
#include <boost/geometry/strategies/relate/spherical.hpp>

#include <boost/geometry/strategies/spherical/azimuth.hpp>

#include <boost/geometry/strategies/spherical/distance_cross_track.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track_box_box.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track_point_box.hpp>
#include <boost/geometry/strategies/spherical/distance_haversine.hpp>
#include <boost/geometry/strategies/spherical/distance_segment_box.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace distance
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

// TODO: azimuth and normalize getters would not be needed if distance_segment_box was implemented differently
//       right now it calls disjoint algorithm details.

template <typename RadiusTypeOrSphere, typename CalculationType>
class spherical
    : public strategies::relate::detail::spherical<RadiusTypeOrSphere, CalculationType>
{
    using base_t = strategies::relate::detail::spherical<RadiusTypeOrSphere, CalculationType>;

public:
    spherical() = default;

    template <typename RadiusOrSphere>
    explicit spherical(RadiusOrSphere const& radius_or_sphere)
        : base_t(radius_or_sphere)
    {}

    // azimuth

    static auto azimuth()
    {
        return strategy::azimuth::spherical<CalculationType>();
    }

    // distance

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  detail::enable_if_pp_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::haversine
                <
                    typename base_t::radius_type, CalculationType
                >(base_t::radius());
    }

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  detail::enable_if_ps_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::cross_track
            <
                CalculationType,
                strategy::distance::haversine<typename base_t::radius_type, CalculationType>
            >(base_t::radius());
    }

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  detail::enable_if_pb_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::cross_track_point_box
            <
                CalculationType,
                strategy::distance::haversine<typename base_t::radius_type, CalculationType>
            >(base_t::radius());
    }

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  detail::enable_if_sb_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::spherical_segment_box
            <
                CalculationType,
                strategy::distance::haversine<typename base_t::radius_type, CalculationType>
            >(base_t::radius());
    }

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  detail::enable_if_bb_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::cross_track_box_box
            <
                CalculationType,
                strategy::distance::haversine<typename base_t::radius_type, CalculationType>
            >(base_t::radius());
    }

    // normalize

    template <typename Geometry>
    static auto normalize(Geometry const&,
                          std::enable_if_t
                            <
                                util::is_point<Geometry>::value
                            > * = nullptr)
    {
        return strategy::normalize::spherical_point();
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


template
<
    typename RadiusTypeOrSphere = double,
    typename CalculationType = void
>
class spherical
    : public strategies::distance::detail::spherical<RadiusTypeOrSphere, CalculationType>
{
    using base_t = strategies::distance::detail::spherical<RadiusTypeOrSphere, CalculationType>;

public:
    spherical() = default;

    template <typename RadiusOrSphere>
    explicit spherical(RadiusOrSphere const& radius_or_sphere)
        : base_t(radius_or_sphere)
    {}
};


namespace services
{

template <typename Geometry1, typename Geometry2>
struct default_strategy
    <
        Geometry1, Geometry2,
        spherical_equatorial_tag, spherical_equatorial_tag
    >
{
    using type = strategies::distance::spherical<>;
};


template <typename R, typename CT>
struct strategy_converter<strategy::distance::haversine<R, CT> >
{
    template <typename S>
    static auto get(S const& s)
    {
        return strategies::distance::spherical<R, CT>(s.radius());
    }
};

template <typename CT, typename PPS>
struct strategy_converter<strategy::distance::cross_track<CT, PPS> >
    : strategy_converter<PPS>
{};

template <typename CT, typename PPS>
struct strategy_converter<strategy::distance::cross_track_point_box<CT, PPS> >
    : strategy_converter<PPS>
{};

template <typename CT, typename PPS>
struct strategy_converter<strategy::distance::spherical_segment_box<CT, PPS> >
    : strategy_converter<PPS>
{};

template <typename CT, typename PPS>
struct strategy_converter<strategy::distance::cross_track_box_box<CT, PPS> >
    : strategy_converter<PPS>
{};


template <typename R, typename CT>
struct strategy_converter<strategy::distance::comparable::haversine<R, CT> >
{
    template <typename S>
    static auto get(S const& s)
    {
        return strategies::distance::detail::make_comparable(
                strategies::distance::spherical<R, CT>(s.radius()));
    }
};

template <typename CT, typename PPS>
struct strategy_converter<strategy::distance::comparable::cross_track<CT, PPS> >
    : strategy_converter<PPS>
{};


} // namespace services

}} // namespace strategies::distance

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_DISTANCE_SPHERICAL_HPP

/* spherical.hpp
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
*/