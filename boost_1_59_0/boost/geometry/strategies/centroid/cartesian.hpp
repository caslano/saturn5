// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_CENTROID_CARTESIAN_HPP
#define BOOST_GEOMETRY_STRATEGIES_CENTROID_CARTESIAN_HPP


#include <boost/geometry/strategies/cartesian/centroid_average.hpp>
#include <boost/geometry/strategies/cartesian/centroid_bashein_detmer.hpp>
#include <boost/geometry/strategies/cartesian/centroid_weighted_length.hpp>

#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/centroid/services.hpp>

#include <boost/geometry/util/type_traits.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace centroid
{

template <typename CalculationType = void>
struct cartesian
    : public strategies::detail::cartesian_base
{
    template <typename Geometry>
    static auto centroid(Geometry const&,
                         std::enable_if_t
                            <
                                util::is_pointlike<Geometry>::value
                            > * = nullptr)
    {
        return strategy::centroid::average<>();
    }

    template <typename Geometry>
    static auto centroid(Geometry const&,
                         std::enable_if_t
                            <
                                util::is_polylinear<Geometry>::value
                            > * = nullptr)
    {
        return strategy::centroid::weighted_length<void, void, CalculationType>();
    }

    template <typename Geometry>
    static auto centroid(Geometry const&,
                         std::enable_if_t
                            <
                                util::is_polygonal<Geometry>::value
                             // TODO: This condition was used for the legacy default strategy
                             // && geometry::dimension<Geometry>::value == 2
                            > * = nullptr)
    {
        return strategy::centroid::bashein_detmer<void, void, CalculationType>();
    }

    // TODO: Box and Segment should have proper strategies.
    template <typename Geometry, typename Point>
    static auto centroid(Geometry const&, Point const&,
                         std::enable_if_t
                            <
                                util::is_segment<Geometry>::value
                             || util::is_box<Geometry>::value
                            > * = nullptr)
    {
        return strategy::centroid::not_applicable_strategy();
    }
};


namespace services
{

template <typename Geometry>
struct default_strategy<Geometry, cartesian_tag>
{
    using type = strategies::centroid::cartesian<>;
};


template <typename PC, typename PG>
struct strategy_converter<strategy::centroid::average<PC, PG> >
{
    static auto get(strategy::centroid::average<PC, PG> const&)
    {
        return strategies::centroid::cartesian<>();
    }
};

template <typename PC, typename PG>
struct strategy_converter<strategy::centroid::weighted_length<PC, PG> >
{
    static auto get(strategy::centroid::weighted_length<PC, PG> const&)
    {
        return strategies::centroid::cartesian<>();
    }
};

template <typename PC, typename PG, typename CT>
struct strategy_converter<strategy::centroid::bashein_detmer<PC, PG, CT> >
{
    static auto get(strategy::centroid::bashein_detmer<PC, PG, CT> const&)
    {
        return strategies::centroid::cartesian<CT>();
    }
};

} // namespace services

}} // namespace strategies::centroid

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CENTROID_CARTESIAN_HPP

/* cartesian.hpp
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
*/