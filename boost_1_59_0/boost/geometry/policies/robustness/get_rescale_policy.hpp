// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2014-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2014-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2015-2020.
// Modifications copyright (c) 2015-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_ROBUSTNESS_GET_RESCALE_POLICY_HPP
#define BOOST_GEOMETRY_POLICIES_ROBUSTNESS_GET_RESCALE_POLICY_HPP


#include <cstddef>
#include <type_traits>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/config.hpp>
#include <boost/geometry/core/coordinate_promotion.hpp>
#include <boost/geometry/core/tag_cast.hpp>

#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/algorithms/is_empty.hpp>
#include <boost/geometry/algorithms/detail/recalculate.hpp>
#include <boost/geometry/algorithms/detail/get_max_size.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/policies/robustness/no_rescale_policy.hpp>
#include <boost/geometry/policies/robustness/rescale_policy.hpp>
#include <boost/geometry/policies/robustness/robust_type.hpp>
#include <boost/geometry/util/type_traits.hpp>

// TEMP
#include <boost/geometry/strategies/envelope/cartesian.hpp>
#include <boost/geometry/strategies/envelope/geographic.hpp>
#include <boost/geometry/strategies/envelope/spherical.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace get_rescale_policy
{

template
<
    typename Box,
    typename Point,
    typename RobustPoint,
    typename Factor
>
inline void scale_box_to_integer_range(Box const& box,
                                       Point& min_point,
                                       RobustPoint& min_robust_point,
                                       Factor& factor)
{
    // Scale box to integer-range
    typedef typename promote_floating_point
        <
            typename geometry::coordinate_type<Point>::type
        >::type num_type;
    num_type const diff = boost::numeric_cast<num_type>(detail::get_max_size(box));
    num_type const range = 10000000.0; // Define a large range to get precise integer coordinates
    num_type const half = 0.5;
    if (math::equals(diff, num_type())
        || diff >= range
        || ! boost::math::isfinite(diff))
    {
        factor = 1;
    }
    else
    {
        factor = boost::numeric_cast<num_type>(
            boost::numeric_cast<boost::long_long_type>(half + range / diff));
        BOOST_GEOMETRY_ASSERT(factor >= 1);
    }

    // Assign input/output minimal points
    detail::assign_point_from_index<0>(box, min_point);
    num_type const two = 2;
    boost::long_long_type const min_coordinate
        = boost::numeric_cast<boost::long_long_type>(-range / two);
    assign_values(min_robust_point, min_coordinate, min_coordinate);
}

template
<
    typename Point, typename RobustPoint, typename Geometry,
    typename Factor, typename Strategy
>
static inline void init_rescale_policy(Geometry const& geometry,
        Point& min_point,
        RobustPoint& min_robust_point,
        Factor& factor,
        Strategy const& strategy)
{
    if (geometry::is_empty(geometry))
    {
        return;
    }

    // Get bounding box
    model::box<Point> env = geometry::return_envelope
                                <
                                    model::box<Point>
                                >(geometry, strategy);

    scale_box_to_integer_range(env, min_point, min_robust_point, factor);
}

// NOTE: Actually it should take 2 separate strategies, one for each geometry
// in case one of them was e.g. a Box
template
<
    typename Point, typename RobustPoint, typename Geometry1, typename Geometry2,
    typename Factor, typename Strategy1, typename Strategy2
>
static inline void init_rescale_policy(Geometry1 const& geometry1,
        Geometry2 const& geometry2,
        Point& min_point,
        RobustPoint& min_robust_point,
        Factor& factor,
        Strategy1 const& strategy1,
        Strategy2 const& strategy2)
{
    // Get bounding boxes (when at least one of the geometries is not empty)
    bool const is_empty1 = geometry::is_empty(geometry1);
    bool const is_empty2 = geometry::is_empty(geometry2);
    if (is_empty1 && is_empty2)
    {
        return;
    }

    model::box<Point> env;
    if (is_empty1)
    {
        geometry::envelope(geometry2, env, strategy2);
    }
    else if (is_empty2)
    {
        geometry::envelope(geometry1, env, strategy1);
    }
    else
    {
        // The following approach (envelope + expand) may not give the
        // optimal MBR when then two geometries are in the spherical
        // equatorial or geographic coordinate systems.
        // TODO: implement envelope for two (or possibly more geometries)
        geometry::envelope(geometry1, env, strategy1);
        model::box<Point> env2 = geometry::return_envelope
            <
                model::box<Point>
            >(geometry2, strategy2);
        geometry::expand(env, env2, strategy1);
    }

    scale_box_to_integer_range(env, min_point, min_robust_point, factor);
}


template
<
    typename Point,
    bool IsFloatingPoint
>
struct rescale_policy_type
{
    typedef no_rescale_policy type;
};

// We rescale only all FP types
template
<
    typename Point
>
struct rescale_policy_type<Point, true>
{
    typedef typename geometry::coordinate_type<Point>::type coordinate_type;
    typedef model::point
    <
        typename detail::robust_type<coordinate_type>::type,
        geometry::dimension<Point>::value,
        typename geometry::coordinate_system<Point>::type
    > robust_point_type;
    typedef typename promote_floating_point<coordinate_type>::type factor_type;
    typedef detail::robust_policy<Point, robust_point_type, factor_type> type;
};

template <typename Policy>
struct get_rescale_policy
{
    template <typename Geometry, typename Strategy>
    static inline Policy apply(Geometry const& geometry,
                               Strategy const& strategy)
    {
        typedef typename point_type<Geometry>::type point_type;
        typedef typename geometry::coordinate_type<Geometry>::type coordinate_type;
        typedef typename promote_floating_point<coordinate_type>::type factor_type;
        typedef model::point
        <
            typename detail::robust_type<coordinate_type>::type,
            geometry::dimension<point_type>::value,
            typename geometry::coordinate_system<point_type>::type
        > robust_point_type;

        point_type min_point;
        robust_point_type min_robust_point;
        factor_type factor;
        init_rescale_policy(geometry, min_point, min_robust_point,
                            factor, strategy);

        return Policy(min_point, min_robust_point, factor);
    }

    template <typename Geometry1, typename Geometry2, typename Strategy1, typename Strategy2>
    static inline Policy apply(Geometry1 const& geometry1, Geometry2 const& geometry2,
                               Strategy1 const& strategy1,
                               Strategy2 const& strategy2)
    {
        typedef typename point_type<Geometry1>::type point_type;
        typedef typename geometry::coordinate_type<Geometry1>::type coordinate_type;
        typedef typename promote_floating_point<coordinate_type>::type factor_type;
        typedef model::point
        <
            typename detail::robust_type<coordinate_type>::type,
            geometry::dimension<point_type>::value,
            typename geometry::coordinate_system<point_type>::type
        > robust_point_type;

        point_type min_point;
        robust_point_type min_robust_point;
        factor_type factor;
        init_rescale_policy(geometry1, geometry2, min_point, min_robust_point,
                            factor, strategy1, strategy2);

        return Policy(min_point, min_robust_point, factor);
    }
};

// Specialization for no-rescaling
template <>
struct get_rescale_policy<no_rescale_policy>
{
    template <typename Geometry, typename EnvelopeStrategy>
    static inline no_rescale_policy apply(Geometry const& , EnvelopeStrategy const&)
    {
        return no_rescale_policy();
    }

    template <typename Geometry1, typename Geometry2, typename EnvelopeStrategy1, typename EnvelopeStrategy2>
    static inline no_rescale_policy apply(Geometry1 const& , Geometry2 const& ,
                                          EnvelopeStrategy1 const& , EnvelopeStrategy2 const& )
    {
        return no_rescale_policy();
    }
};


}} // namespace detail::get_rescale_policy
#endif // DOXYGEN_NO_DETAIL

template
<
    typename Point,
    typename CSTag = typename geometry::cs_tag<Point>::type
>
struct rescale_policy_type
    : public detail::get_rescale_policy::rescale_policy_type
    <
        Point,
#if defined(BOOST_GEOMETRY_USE_RESCALING)
        std::is_floating_point
            <
                typename geometry::coordinate_type<Point>::type
            >::type::value
        &&
        std::is_same
            <
                CSTag,
                geometry::cartesian_tag
            >::value
#else
        false
#endif
    >
{
    BOOST_GEOMETRY_STATIC_ASSERT(
        (util::is_point<Point>::value),
        "Point type expected.",
        Point);
};


template
<
    typename Geometry1,
    typename Geometry2,
    typename CSTag = typename geometry::cs_tag<Geometry1>::type,
    typename Tag1 = typename tag_cast
    <
        typename tag<Geometry1>::type,
        box_tag,
        pointlike_tag,
        linear_tag,
        areal_tag
    >::type,
    typename Tag2 = typename tag_cast
    <
        typename tag<Geometry2>::type,
        box_tag,
        pointlike_tag,
        linear_tag,
        areal_tag
    >::type
>
struct rescale_overlay_policy_type
    // Default: no rescaling
    : public detail::get_rescale_policy::rescale_policy_type
        <
            typename geometry::point_type<Geometry1>::type,
            false
        >
{};

// Areal/areal: get rescale policy based on coordinate type
template
<
    typename Geometry1,
    typename Geometry2,
    typename CSTag
>
struct rescale_overlay_policy_type<Geometry1, Geometry2, CSTag, areal_tag, areal_tag>
    : public rescale_policy_type
        <
            typename geometry::point_type<Geometry1>::type,
            CSTag
        >
{};


template <typename Policy, typename Geometry>
inline Policy get_rescale_policy(Geometry const& geometry)
{
    typename geometry::strategies::envelope::services::default_strategy
        <
            Geometry,
            model::box<typename point_type<Geometry>::type>
        >::type strategy;

    return detail::get_rescale_policy::get_rescale_policy<Policy>::apply(geometry, strategy);
}

template
<
    typename Policy, typename Geometry, typename Strategy,
    std::enable_if_t<std::is_void<typename geometry::tag<Strategy>::type>::value, int> = 0
>
inline Policy get_rescale_policy(Geometry const& geometry, Strategy const& strategy)
{
    return detail::get_rescale_policy::get_rescale_policy
        <
            Policy
        >::apply(geometry, strategy);
}

template
<
    typename Policy, typename Geometry1, typename Geometry2,
    std::enable_if_t<! std::is_void<typename geometry::tag<Geometry2>::type>::value, int> = 0
>
inline Policy get_rescale_policy(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    typename geometry::strategies::envelope::services::default_strategy
        <
            Geometry1,
            model::box<typename point_type<Geometry1>::type>
        >::type strategy1;
    typename geometry::strategies::envelope::services::default_strategy
        <
            Geometry2,
            model::box<typename point_type<Geometry2>::type>
        >::type strategy2;

    return detail::get_rescale_policy::get_rescale_policy
        <
            Policy
        >::apply(geometry1, geometry2, strategy1, strategy2);
}

template <typename Policy, typename Geometry1, typename Geometry2, typename Strategy>
inline Policy get_rescale_policy(Geometry1 const& geometry1, Geometry2 const& geometry2,
                                 Strategy const& strategy)
{
    return detail::get_rescale_policy::get_rescale_policy
            <
                Policy
            >::apply(geometry1, geometry2, strategy, strategy);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_POLICIES_ROBUSTNESS_GET_RESCALE_POLICY_HPP

/* get_rescale_policy.hpp
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
*/