// Boost.Geometry

// Copyright (c) 2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_RELATE_CARTESIAN_HPP
#define BOOST_GEOMETRY_STRATEGIES_RELATE_CARTESIAN_HPP


// TEMP - move to strategy
#include <boost/geometry/strategies/agnostic/point_in_box_by_side.hpp>
#include <boost/geometry/strategies/cartesian/intersection.hpp>
#include <boost/geometry/strategies/cartesian/box_in_box.hpp>
#include <boost/geometry/strategies/cartesian/point_in_point.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_crossings_multiply.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_franklin.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/cartesian/disjoint_box_box.hpp>

#include <boost/geometry/strategies/envelope/cartesian.hpp>
#include <boost/geometry/strategies/relate/services.hpp>
#include <boost/geometry/strategies/detail.hpp>

#include <boost/geometry/strategy/cartesian/area.hpp>
#include <boost/geometry/strategy/cartesian/side_robust.hpp>
#include <boost/geometry/strategy/cartesian/side_by_triangle.hpp>
#include <boost/geometry/strategy/cartesian/area_box.hpp>

#include <boost/geometry/util/type_traits.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace relate
{

template <typename CalculationType = void>
class cartesian
    : public strategies::envelope::cartesian<CalculationType>
{
public:
    //area

    template <typename Geometry>
    static auto area(Geometry const&,
                     std::enable_if_t<! util::is_box<Geometry>::value> * = nullptr)
    {
        return strategy::area::cartesian<CalculationType>();
    }

    template <typename Geometry>
    static auto area(Geometry const&,
                     std::enable_if_t<util::is_box<Geometry>::value> * = nullptr)
    {
        return strategy::area::cartesian_box<CalculationType>();
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
        return strategy::covered_by::cartesian_point_box();
    }

    template <typename Geometry1, typename Geometry2>
    static auto covered_by(Geometry1 const&, Geometry2 const&,
                           std::enable_if_t
                            <
                                util::is_box<Geometry1>::value
                             && util::is_box<Geometry2>::value
                            > * = nullptr)
    {
        return strategy::covered_by::cartesian_box_box();
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
        return strategy::disjoint::cartesian_box_box();
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
        return strategy::disjoint::segment_box();
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
        return strategy::within::cartesian_point_point();
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
        return strategy::within::cartesian_winding<void, void, CalculationType>();
    }

    // The problem is that this strategy is often used with non-geometry ranges.
    // So dispatching only by geometry categories is impossible.
    // In the past it was taking two segments, now it takes 3-point sub-ranges.
    // So dispatching by segments is impossible.
    // It could be dispatched by (linear || polygonal || non-geometry point range).
    // For now implement as 0-parameter, special case relate.

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
        return strategy::intersection::cartesian_segments<CalculationType>();
    }

    // side

    static auto side()
    {
        using side_strategy_type
            = typename strategy::side::services::default_strategy
                <cartesian_tag, CalculationType>::type;
        return side_strategy_type();
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
        return strategy::within::cartesian_point_box();
    }

    template <typename Geometry1, typename Geometry2>
    static auto within(Geometry1 const&, Geometry2 const&,
                       std::enable_if_t
                            <
                                util::is_box<Geometry1>::value
                             && util::is_box<Geometry2>::value
                            > * = nullptr)
    {
        return strategy::within::cartesian_box_box();
    }
};


namespace services
{

template <typename Geometry1, typename Geometry2>
struct default_strategy<Geometry1, Geometry2, cartesian_tag, cartesian_tag>
{
    using type = strategies::relate::cartesian<>;
};


template <>
struct strategy_converter<strategy::within::cartesian_point_point>
{
    static auto get(strategy::within::cartesian_point_point const& )
    {
        return strategies::relate::cartesian<>();
    }
};

template <>
struct strategy_converter<strategy::within::cartesian_point_box>
{
    static auto get(strategy::within::cartesian_point_box const&)
    {
        return strategies::relate::cartesian<>();
    }
};

template <>
struct strategy_converter<strategy::covered_by::cartesian_point_box>
{
    static auto get(strategy::covered_by::cartesian_point_box const&)
    {
        return strategies::relate::cartesian<>();
    }
};

template <>
struct strategy_converter<strategy::covered_by::cartesian_box_box>
{
    static auto get(strategy::covered_by::cartesian_box_box const&)
    {
        return strategies::relate::cartesian<>();
    }
};

template <>
struct strategy_converter<strategy::disjoint::cartesian_box_box>
{
    static auto get(strategy::disjoint::cartesian_box_box const&)
    {
        return strategies::relate::cartesian<>();
    }
};

template <>
struct strategy_converter<strategy::disjoint::segment_box>
{
    static auto get(strategy::disjoint::segment_box const&)
    {
        return strategies::relate::cartesian<>();
    }
};

template <>
struct strategy_converter<strategy::within::cartesian_box_box>
{
    static auto get(strategy::within::cartesian_box_box const&)
    {
        return strategies::relate::cartesian<>();
    }
};

template <typename P1, typename P2, typename CalculationType>
struct strategy_converter<strategy::within::cartesian_winding<P1, P2, CalculationType>>
{
    static auto get(strategy::within::cartesian_winding<P1, P2, CalculationType> const& )
    {
        return strategies::relate::cartesian<CalculationType>();
    }
};

template <typename CalculationType>
struct strategy_converter<strategy::intersection::cartesian_segments<CalculationType>>
{
    static auto get(strategy::intersection::cartesian_segments<CalculationType> const& )
    {
        return strategies::relate::cartesian<CalculationType>();
    }
};

template <typename CalculationType>
struct strategy_converter<strategy::within::cartesian_point_box_by_side<CalculationType>>
{
    struct altered_strategy
        : strategies::relate::cartesian<CalculationType>
    {
        template <typename Geometry1, typename Geometry2>
        static auto covered_by(Geometry1 const&, Geometry2 const&,
                               std::enable_if_t
                                    <
                                        util::is_pointlike<Geometry1>::value
                                     && util::is_box<Geometry2>::value
                                    > * = nullptr)
        {
            return strategy::covered_by::cartesian_point_box_by_side<CalculationType>();
        }

        template <typename Geometry1, typename Geometry2>
        static auto within(Geometry1 const&, Geometry2 const&,
                           std::enable_if_t
                                <
                                    util::is_pointlike<Geometry1>::value
                                    && util::is_box<Geometry2>::value
                                > * = nullptr)
        {
            return strategy::within::cartesian_point_box_by_side<CalculationType>();
        }
    };

    static auto get(strategy::covered_by::cartesian_point_box_by_side<CalculationType> const&)
    {
        return altered_strategy();
    }

    static auto get(strategy::within::cartesian_point_box_by_side<CalculationType> const&)
    {
        return altered_strategy();
    }
};

template <typename CalculationType>
struct strategy_converter<strategy::covered_by::cartesian_point_box_by_side<CalculationType>>
    : strategy_converter<strategy::within::cartesian_point_box_by_side<CalculationType>>
{};

template <typename P1, typename P2, typename CalculationType>
struct strategy_converter<strategy::within::franklin<P1, P2, CalculationType>>
{
    struct altered_strategy
        : strategies::relate::cartesian<CalculationType>
    {
        template <typename Geometry1, typename Geometry2>
        static auto relate(Geometry1 const&, Geometry2 const&,
                           std::enable_if_t
                                <
                                    util::is_pointlike<Geometry1>::value
                                 && ( util::is_linear<Geometry2>::value
                                   || util::is_polygonal<Geometry2>::value )
                                > * = nullptr)
        {
            return strategy::within::franklin<void, void, CalculationType>();
        }
    };

    static auto get(strategy::within::franklin<P1, P2, CalculationType> const&)
    {
        return altered_strategy();
    }
};

template <typename P1, typename P2, typename CalculationType>
struct strategy_converter<strategy::within::crossings_multiply<P1, P2, CalculationType>>
{
    struct altered_strategy
        : strategies::relate::cartesian<CalculationType>
    {
        template <typename Geometry1, typename Geometry2>
        static auto relate(Geometry1 const&, Geometry2 const&,
                           std::enable_if_t
                                <
                                    util::is_pointlike<Geometry1>::value
                                 && ( util::is_linear<Geometry2>::value
                                   || util::is_polygonal<Geometry2>::value )
                                > * = nullptr)
        {
            return strategy::within::crossings_multiply<void, void, CalculationType>();
        }
    };

    static auto get(strategy::within::crossings_multiply<P1, P2, CalculationType> const&)
    {
        return altered_strategy();
    }
};

// TEMP used in distance segment/box
template <typename CalculationType>
struct strategy_converter<strategy::side::side_by_triangle<CalculationType>>
{
    static auto get(strategy::side::side_by_triangle<CalculationType> const&)
    {
        return strategies::relate::cartesian<CalculationType>();
    }
};

template <typename CalculationType>
struct strategy_converter<strategy::side::side_robust<CalculationType>>
{
    static auto get(strategy::side::side_robust<CalculationType> const&)
    {
        return strategies::relate::cartesian<CalculationType>();
    }
};


} // namespace services

}} // namespace strategies::relate

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_RELATE_CARTESIAN_HPP

/* cartesian.hpp
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
*/