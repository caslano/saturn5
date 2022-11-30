// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_DISTANCE_GEOGRAPHIC_HPP
#define BOOST_GEOMETRY_STRATEGIES_DISTANCE_GEOGRAPHIC_HPP


#include <boost/geometry/strategies/distance/comparable.hpp>
#include <boost/geometry/strategies/distance/detail.hpp>
#include <boost/geometry/strategies/distance/services.hpp>
#include <boost/geometry/strategies/detail.hpp>

#include <boost/geometry/strategies/geographic/azimuth.hpp>

#include <boost/geometry/strategies/geographic/distance.hpp>
#include <boost/geometry/strategies/geographic/distance_cross_track.hpp>
#include <boost/geometry/strategies/geographic/distance_cross_track_box_box.hpp>
#include <boost/geometry/strategies/geographic/distance_cross_track_point_box.hpp>
#include <boost/geometry/strategies/geographic/distance_segment_box.hpp>
// TODO - for backwards compatibility, remove?
#include <boost/geometry/strategies/geographic/distance_andoyer.hpp>
#include <boost/geometry/strategies/geographic/distance_thomas.hpp>
#include <boost/geometry/strategies/geographic/distance_vincenty.hpp>

#include <boost/geometry/strategies/normalize.hpp>
#include <boost/geometry/strategies/relate/geographic.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace distance
{

// TODO: azimuth and normalize getters would not be needed if distance_segment_box was implemented differently
//       right now it calls disjoint algorithm details.

template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class geographic
    : public strategies::relate::geographic<FormulaPolicy, Spheroid, CalculationType>
{
    using base_t = strategies::relate::geographic<FormulaPolicy, Spheroid, CalculationType>;

public:
    geographic() = default;

    explicit geographic(Spheroid const& spheroid)
        : base_t(spheroid)
    {}

    // azimuth

    auto azimuth() const
    {
        return strategy::azimuth::geographic
            <
                FormulaPolicy, Spheroid, CalculationType
            >(base_t::m_spheroid);
    }

    // distance

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  detail::enable_if_pp_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::geographic
                <
                    FormulaPolicy, Spheroid, CalculationType
                >(base_t::m_spheroid);
    }

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  detail::enable_if_ps_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::geographic_cross_track
            <
                FormulaPolicy, Spheroid, CalculationType
            >(base_t::m_spheroid);
    }

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  detail::enable_if_pb_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::geographic_cross_track_point_box
            <
                FormulaPolicy, Spheroid, CalculationType
            >(base_t::m_spheroid);
    }

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  detail::enable_if_sb_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::geographic_segment_box
            <
                FormulaPolicy, Spheroid, CalculationType
            >(base_t::m_spheroid);
    }

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  detail::enable_if_bb_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::geographic_cross_track_box_box
            <
                FormulaPolicy, Spheroid, CalculationType
            >(base_t::m_spheroid);
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


namespace services
{

template <typename Geometry1, typename Geometry2>
struct default_strategy<Geometry1, Geometry2, geographic_tag, geographic_tag>
{
    using type = strategies::distance::geographic<>;
};


template <typename FP, typename S, typename CT>
struct strategy_converter<strategy::distance::geographic<FP, S, CT> >
{
    static auto get(strategy::distance::geographic<FP, S, CT> const& s)
    {
        return strategies::distance::geographic<FP, S, CT>(s.model());
    }
};
// TODO - for backwards compatibility, remove?
template <typename S, typename CT>
struct strategy_converter<strategy::distance::andoyer<S, CT> >
{
    static auto get(strategy::distance::andoyer<S, CT> const& s)
    {
        return strategies::distance::geographic<strategy::andoyer, S, CT>(s.model());
    }
};
// TODO - for backwards compatibility, remove?
template <typename S, typename CT>
struct strategy_converter<strategy::distance::thomas<S, CT> >
{
    static auto get(strategy::distance::thomas<S, CT> const& s)
    {
        return strategies::distance::geographic<strategy::thomas, S, CT>(s.model());
    }
};
// TODO - for backwards compatibility, remove?
template <typename S, typename CT>
struct strategy_converter<strategy::distance::vincenty<S, CT> >
{
    static auto get(strategy::distance::vincenty<S, CT> const& s)
    {
        return strategies::distance::geographic<strategy::vincenty, S, CT>(s.model());
    }
};

template <typename FP, typename S, typename CT>
struct strategy_converter<strategy::distance::geographic_cross_track<FP, S, CT> >
{
    static auto get(strategy::distance::geographic_cross_track<FP, S, CT> const& s)
    {
        return strategies::distance::geographic<FP, S, CT>(s.model());
    }
};

template <typename FP, typename S, typename CT>
struct strategy_converter<strategy::distance::geographic_cross_track_point_box<FP, S, CT> >
{
    static auto get(strategy::distance::geographic_cross_track_point_box<FP, S, CT> const& s)
    {
        return strategies::distance::geographic<FP, S, CT>(s.model());
    }
};

template <typename FP, typename S, typename CT>
struct strategy_converter<strategy::distance::geographic_segment_box<FP, S, CT> >
{
    static auto get(strategy::distance::geographic_segment_box<FP, S, CT> const& s)
    {
        return strategies::distance::geographic<FP, S, CT>(s.model());
    }
};

template <typename FP, typename S, typename CT>
struct strategy_converter<strategy::distance::geographic_cross_track_box_box<FP, S, CT> >
{
    static auto get(strategy::distance::geographic_cross_track_box_box<FP, S, CT> const& s)
    {
        return strategies::distance::geographic<FP, S, CT>(s.model());
    }
};


// details

// TODO: This specialization wouldn't be needed if strategy::distance::geographic_cross_track was implemented as an alias
template <typename FP, typename S, typename CT, bool B, bool ECP>
struct strategy_converter<strategy::distance::detail::geographic_cross_track<FP, S, CT, B, ECP> >
{
    struct altered_strategy
        : strategies::distance::geographic<FP, S, CT>
    {
        typedef strategies::distance::geographic<FP, S, CT> base_t;

        explicit altered_strategy(S const& s) : base_t(s) {}

        using base_t::distance;

        template <typename Geometry1, typename Geometry2>
        auto distance(Geometry1 const&, Geometry2 const&,
                      detail::enable_if_ps_t<Geometry1, Geometry2> * = nullptr) const
        {
            return strategy::distance::detail::geographic_cross_track
                <
                    FP, S, CT, B, ECP
                >(base_t::m_spheroid);
        }
    };

    static auto get(strategy::distance::detail::geographic_cross_track<FP, S, CT, B, ECP> const& s)
    {
        return altered_strategy(s.model());
    }
};


} // namespace services

}} // namespace strategies::distance

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_DISTANCE_GEOGRAPHIC_HPP

/* geographic.hpp
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
*/