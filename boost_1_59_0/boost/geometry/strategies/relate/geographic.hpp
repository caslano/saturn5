// Boost.Geometry

// Copyright (c) 2020-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_RELATE_GEOGRAPHIC_HPP
#define BOOST_GEOMETRY_STRATEGIES_RELATE_GEOGRAPHIC_HPP


// TEMP - move to strategy
#include <boost/geometry/strategies/agnostic/point_in_box_by_side.hpp>
#include <boost/geometry/strategies/cartesian/box_in_box.hpp>
#include <boost/geometry/strategies/geographic/intersection.hpp>
#include <boost/geometry/strategies/geographic/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>
#include <boost/geometry/strategies/spherical/disjoint_box_box.hpp>

#include <boost/geometry/strategies/envelope/geographic.hpp>
#include <boost/geometry/strategies/relate/services.hpp>
#include <boost/geometry/strategies/detail.hpp>

#include <boost/geometry/strategy/geographic/area.hpp>
#include <boost/geometry/strategy/geographic/area_box.hpp>

#include <boost/geometry/util/type_traits.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace relate
{

template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class geographic
    : public strategies::envelope::geographic<FormulaPolicy, Spheroid, CalculationType>
{
    using base_t = strategies::envelope::geographic<FormulaPolicy, Spheroid, CalculationType>;

public:
    geographic() = default;

    explicit geographic(Spheroid const& spheroid)
        : base_t(spheroid)
    {}

    // area

    template <typename Geometry>
    auto area(Geometry const&,
              std::enable_if_t<! util::is_box<Geometry>::value> * = nullptr) const
    {
        return strategy::area::geographic
            <
                FormulaPolicy,
                strategy::default_order<FormulaPolicy>::value,
                Spheroid, CalculationType
            >(base_t::m_spheroid);
    }

    template <typename Geometry>
    auto area(Geometry const&,
              std::enable_if_t<util::is_box<Geometry>::value> * = nullptr) const
    {
        return strategy::area::geographic_box
            <
                Spheroid, CalculationType
            >(base_t::m_spheroid);
    }

    // covered_by

    template <typename Geometry1, typename Geometry2>
    static auto covered_by(Geometry1 const&, Geometry2 const&,
                           std::enable_if_t
                                <
                                    util::is_pointlike<Geometry1>::value
                                 && util::is_box<Geometry2>::value
                                > * = nullptr)
    {
        return strategy::covered_by::spherical_point_box();
    }

    template <typename Geometry1, typename Geometry2>
    static auto covered_by(Geometry1 const&, Geometry2 const&,
                           std::enable_if_t
                            <
                                util::is_box<Geometry1>::value
                             && util::is_box<Geometry2>::value
                            > * = nullptr)
    {
        return strategy::covered_by::spherical_box_box();
    }

    // disjoint

    template <typename Geometry1, typename Geometry2>
    static auto disjoint(Geometry1 const&, Geometry2 const&,
                         std::enable_if_t
                            <
                                util::is_box<Geometry1>::value
                             && util::is_box<Geometry2>::value
                            > * = nullptr)
    {
        return strategy::disjoint::spherical_box_box();
    }

    template <typename Geometry1, typename Geometry2>
    auto disjoint(Geometry1 const&, Geometry2 const&,
                  std::enable_if_t
                    <
                        util::is_segment<Geometry1>::value
                        && util::is_box<Geometry2>::value
                    > * = nullptr) const
    {
        // NOTE: Inconsistent name
        // The only disjoint(Seg, Box) strategy that takes CalculationType.
        return strategy::disjoint::segment_box_geographic
            <
                FormulaPolicy, Spheroid, CalculationType
            >(base_t::m_spheroid);
    }

    // relate

    template <typename Geometry1, typename Geometry2>
    static auto relate(Geometry1 const&, Geometry2 const&,
                       std::enable_if_t
                            <
                                util::is_pointlike<Geometry1>::value
                             && util::is_pointlike<Geometry2>::value
                            > * = nullptr)
    {
        return strategy::within::spherical_point_point();
    }

    template <typename Geometry1, typename Geometry2>
    auto relate(Geometry1 const&, Geometry2 const&,
                std::enable_if_t
                    <
                        util::is_pointlike<Geometry1>::value
                        && ( util::is_linear<Geometry2>::value
                        || util::is_polygonal<Geometry2>::value )
                    > * = nullptr) const
    {
        return strategy::within::geographic_winding
                <
                    void, void, FormulaPolicy, Spheroid, CalculationType
                >(base_t::m_spheroid);
    }

    //template <typename Geometry1, typename Geometry2>
    auto relate(/*Geometry1 const&, Geometry2 const&,
                std::enable_if_t
                    <
                        ( util::is_linear<Geometry1>::value
                        || util::is_polygonal<Geometry1>::value )
                        && ( util::is_linear<Geometry2>::value
                        || util::is_polygonal<Geometry2>::value )
                    > * = nullptr*/) const
    {
        return strategy::intersection::geographic_segments
            <
                FormulaPolicy,
                strategy::default_order<FormulaPolicy>::value,
                Spheroid, CalculationType
            >(base_t::m_spheroid);
    }

    // side

    auto side() const
    {
        return strategy::side::geographic
            <
                FormulaPolicy, Spheroid, CalculationType
            >(base_t::m_spheroid);
    }

    // within

    template <typename Geometry1, typename Geometry2>
    static auto within(Geometry1 const&, Geometry2 const&,
                       std::enable_if_t
                            <
                                util::is_pointlike<Geometry1>::value
                                && util::is_box<Geometry2>::value
                            > * = nullptr)
    {
        return strategy::within::spherical_point_box();
    }

    template <typename Geometry1, typename Geometry2>
    static auto within(Geometry1 const&, Geometry2 const&,
                       std::enable_if_t
                            <
                                util::is_box<Geometry1>::value
                             && util::is_box<Geometry2>::value
                            > * = nullptr)
    {
        return strategy::within::spherical_box_box();
    }
};


namespace services
{

template <typename Geometry1, typename Geometry2>
struct default_strategy<Geometry1, Geometry2, geographic_tag, geographic_tag>
{
    using type = strategies::relate::geographic<>;
};


template <typename FormulaPolicy, typename Spheroid, typename CalculationType>
struct strategy_converter<strategy::disjoint::segment_box_geographic<FormulaPolicy, Spheroid, CalculationType>>
{
    static auto get(strategy::disjoint::segment_box_geographic<FormulaPolicy, Spheroid, CalculationType> const& s)
    {
        return strategies::relate::geographic
            <
                FormulaPolicy,
                Spheroid,
                CalculationType
            >(s.model());
    }
};

template <typename P1, typename P2, typename FormulaPolicy, typename Spheroid, typename CalculationType>
struct strategy_converter<strategy::within::geographic_winding<P1, P2, FormulaPolicy, Spheroid, CalculationType>>
{
    static auto get(strategy::within::geographic_winding<P1, P2, FormulaPolicy, Spheroid, CalculationType> const& s)
    {
        return strategies::relate::geographic
            <
                FormulaPolicy,
                Spheroid,
                CalculationType
            >(s.model());
    }
};

template <typename FormulaPolicy, std::size_t SeriesOrder, typename Spheroid, typename CalculationType>
struct strategy_converter<strategy::intersection::geographic_segments<FormulaPolicy, SeriesOrder, Spheroid, CalculationType>>
{
    struct altered_strategy
        : strategies::relate::geographic<FormulaPolicy, Spheroid, CalculationType>
    {
        typedef strategies::relate::geographic<FormulaPolicy, Spheroid, CalculationType> base_t;

        explicit altered_strategy(Spheroid const& spheroid)
            : base_t(spheroid)
        {}

        template <typename Geometry>
        auto area(Geometry const&) const
        {
            return strategy::area::geographic
                <
                    FormulaPolicy, SeriesOrder, Spheroid, CalculationType
                >(base_t::m_spheroid);
        }

        using base_t::relate;

        auto relate(/*...*/) const
        {
            return strategy::intersection::geographic_segments
                <
                    FormulaPolicy, SeriesOrder, Spheroid, CalculationType
                >(base_t::m_spheroid);
        }
    };

    static auto get(strategy::intersection::geographic_segments<FormulaPolicy, SeriesOrder, Spheroid, CalculationType> const& s)
    {
        return altered_strategy(s.model());
    }
};

template <typename FormulaPolicy, typename Spheroid, typename CalculationType>
struct strategy_converter<strategy::within::geographic_point_box_by_side<FormulaPolicy, Spheroid, CalculationType>>
{
    struct altered_strategy
        : strategies::relate::geographic<FormulaPolicy, Spheroid, CalculationType>
    {
        altered_strategy(Spheroid const& spheroid)
            : strategies::relate::geographic<FormulaPolicy, Spheroid, CalculationType>(spheroid)
        {}

        template <typename Geometry1, typename Geometry2>
        auto covered_by(Geometry1 const&, Geometry2 const&,
                        std::enable_if_t
                            <
                                util::is_pointlike<Geometry1>::value
                                && util::is_box<Geometry2>::value
                            > * = nullptr) const
        {
            return strategy::covered_by::geographic_point_box_by_side
                <
                    FormulaPolicy, Spheroid, CalculationType
                >(this->model());
        }

        template <typename Geometry1, typename Geometry2>
        auto within(Geometry1 const&, Geometry2 const&,
                    std::enable_if_t
                        <
                            util::is_pointlike<Geometry1>::value
                            && util::is_box<Geometry2>::value
                        > * = nullptr) const
        {
            return strategy::within::geographic_point_box_by_side
                <
                    FormulaPolicy, Spheroid, CalculationType
                >(this->model());
        }
    };

    static auto get(strategy::covered_by::geographic_point_box_by_side<FormulaPolicy, Spheroid, CalculationType> const& s)
    {
        return altered_strategy(s.model());
    }

    static auto get(strategy::within::geographic_point_box_by_side<FormulaPolicy, Spheroid, CalculationType> const& s)
    {
        return altered_strategy(s.model());
    }
};

template <typename CalculationType>
struct strategy_converter<strategy::covered_by::geographic_point_box_by_side<CalculationType>>
    : strategy_converter<strategy::within::geographic_point_box_by_side<CalculationType>>
{};


} // namespace services

}} // namespace strategies::relate

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_RELATE_GEOGRAPHIC_HPP

/* geographic.hpp
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
*/