// Boost.Geometry

// Copyright (c) 2020-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_RELATE_SPHERICAL_HPP
#define BOOST_GEOMETRY_STRATEGIES_RELATE_SPHERICAL_HPP


// TEMP - move to strategy
#include <boost/geometry/strategies/agnostic/point_in_box_by_side.hpp>
#include <boost/geometry/strategies/cartesian/box_in_box.hpp>
#include <boost/geometry/strategies/spherical/intersection.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>
#include <boost/geometry/strategies/spherical/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/spherical/disjoint_box_box.hpp>

#include <boost/geometry/strategies/envelope/spherical.hpp>
#include <boost/geometry/strategies/relate/services.hpp>
#include <boost/geometry/strategies/detail.hpp>

#include <boost/geometry/strategy/spherical/area.hpp>
#include <boost/geometry/strategy/spherical/area_box.hpp>

#include <boost/geometry/util/type_traits.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace relate
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename RadiusTypeOrSphere, typename CalculationType>
class spherical
    : public strategies::envelope::detail::spherical<RadiusTypeOrSphere, CalculationType>
{
    using base_t = strategies::envelope::detail::spherical<RadiusTypeOrSphere, CalculationType>;

public:

    spherical() = default;

    template <typename RadiusOrSphere>
    explicit spherical(RadiusOrSphere const& radius_or_sphere)
        : strategies::envelope::detail::spherical<RadiusTypeOrSphere, CalculationType>(radius_or_sphere)
    {}

    // area

    template <typename Geometry>
    auto area(Geometry const&,
              std::enable_if_t<! util::is_box<Geometry>::value> * = nullptr) const
    {
        return strategy::area::spherical
            <
                typename base_t::radius_type, CalculationType
            >(base_t::radius());
    }

    template <typename Geometry>
    auto area(Geometry const&,
              std::enable_if_t<util::is_box<Geometry>::value> * = nullptr) const
    {
        return strategy::area::spherical_box
            <
                typename base_t::radius_type, CalculationType
            >(base_t::radius());
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
    static auto disjoint(Geometry1 const&, Geometry2 const&,
                         std::enable_if_t
                            <
                                util::is_segment<Geometry1>::value
                             && util::is_box<Geometry2>::value
                            > * = nullptr)
    {
        // NOTE: Inconsistent name.
        return strategy::disjoint::segment_box_spherical();
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
    static auto relate(Geometry1 const&, Geometry2 const&,
                       std::enable_if_t
                            <
                                util::is_pointlike<Geometry1>::value
                             && ( util::is_linear<Geometry2>::value
                               || util::is_polygonal<Geometry2>::value )
                            > * = nullptr)
    {
        return strategy::within::spherical_winding<void, void, CalculationType>();
    }

    //template <typename Geometry1, typename Geometry2>
    static auto relate(/*Geometry1 const&, Geometry2 const&,
                       std::enable_if_t
                            <
                                ( util::is_linear<Geometry1>::value
                               || util::is_polygonal<Geometry1>::value )
                             && ( util::is_linear<Geometry2>::value
                               || util::is_polygonal<Geometry2>::value )
                            > * = nullptr*/)
    {
        return strategy::intersection::spherical_segments<CalculationType>();
    }

    // side

    static auto side()
    {
        return strategy::side::spherical_side_formula<CalculationType>();
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


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


template <typename CalculationType = void>
class spherical
    : public strategies::relate::detail::spherical<void, CalculationType>
{};


namespace services
{

template <typename Geometry1, typename Geometry2>
struct default_strategy<Geometry1, Geometry2, spherical_tag, spherical_tag>
{
    using type = strategies::relate::spherical<>;
};

template <typename Geometry1, typename Geometry2>
struct default_strategy<Geometry1, Geometry2, spherical_equatorial_tag, spherical_equatorial_tag>
{
    using type = strategies::relate::spherical<>;
};

template <typename Geometry1, typename Geometry2>
struct default_strategy<Geometry1, Geometry2, spherical_polar_tag, spherical_polar_tag>
{
    using type = strategies::relate::spherical<>;
};


template <>
struct strategy_converter<strategy::within::spherical_point_point>
{
    static auto get(strategy::within::spherical_point_point const& )
    {
        return strategies::relate::spherical<>();
    }
};

template <>
struct strategy_converter<strategy::within::spherical_point_box>
{
    static auto get(strategy::within::spherical_point_box const&)
    {
        return strategies::relate::spherical<>();
    }
};

template <>
struct strategy_converter<strategy::covered_by::spherical_point_box>
{
    static auto get(strategy::covered_by::spherical_point_box const&)
    {
        return strategies::relate::spherical<>();
    }
};

template <>
struct strategy_converter<strategy::covered_by::spherical_box_box>
{
    static auto get(strategy::covered_by::spherical_box_box const&)
    {
        return strategies::relate::spherical<>();
    }
};

template <>
struct strategy_converter<strategy::disjoint::spherical_box_box>
{
    static auto get(strategy::disjoint::spherical_box_box const&)
    {
        return strategies::relate::spherical<>();
    }
};

template <>
struct strategy_converter<strategy::disjoint::segment_box_spherical>
{
    static auto get(strategy::disjoint::segment_box_spherical const&)
    {
        return strategies::relate::spherical<>();
    }
};

template <>
struct strategy_converter<strategy::within::spherical_box_box>
{
    static auto get(strategy::within::spherical_box_box const&)
    {
        return strategies::relate::spherical<>();
    }
};

template <typename P1, typename P2, typename CalculationType>
struct strategy_converter<strategy::within::spherical_winding<P1, P2, CalculationType>>
{
    static auto get(strategy::within::spherical_winding<P1, P2, CalculationType> const& )
    {
        return strategies::relate::spherical<CalculationType>();
    }
};

template <typename CalculationType>
struct strategy_converter<strategy::intersection::spherical_segments<CalculationType>>
{
    static auto get(strategy::intersection::spherical_segments<CalculationType> const& )
    {
        return strategies::relate::spherical<CalculationType>();
    }
};

template <typename CalculationType>
struct strategy_converter<strategy::within::spherical_point_box_by_side<CalculationType>>
{
    struct altered_strategy
        : strategies::relate::spherical<CalculationType>
    {
        template <typename Geometry1, typename Geometry2>
        static auto covered_by(Geometry1 const&, Geometry2 const&,
                               std::enable_if_t
                                    <
                                        util::is_pointlike<Geometry1>::value
                                     && util::is_box<Geometry2>::value
                                    > * = nullptr)
        {
            return strategy::covered_by::spherical_point_box_by_side<CalculationType>();
        }

        template <typename Geometry1, typename Geometry2>
        static auto within(Geometry1 const&, Geometry2 const&,
                           std::enable_if_t
                                <
                                    util::is_pointlike<Geometry1>::value
                                    && util::is_box<Geometry2>::value
                                > * = nullptr)
        {
            return strategy::within::spherical_point_box_by_side<CalculationType>();
        }
    };

    static auto get(strategy::covered_by::spherical_point_box_by_side<CalculationType> const&)
    {
        return altered_strategy();
    }

    static auto get(strategy::within::spherical_point_box_by_side<CalculationType> const&)
    {
        return altered_strategy();
    }
};

template <typename CalculationType>
struct strategy_converter<strategy::covered_by::spherical_point_box_by_side<CalculationType>>
    : strategy_converter<strategy::within::spherical_point_box_by_side<CalculationType>>
{};

// TEMP used in distance segment/box
template <typename CalculationType>
struct strategy_converter<strategy::side::spherical_side_formula<CalculationType>>
{
    static auto get(strategy::side::spherical_side_formula<CalculationType> const& )
    {
        return strategies::relate::spherical<CalculationType>();
    }
};


} // namespace services

}} // namespace strategies::relate

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_RELATE_SPHERICAL_HPP

/* spherical.hpp
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
*/