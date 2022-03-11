// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2014-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2014-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2015, 2019.
// Modifications copyright (c) 2015, 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_ROBUSTNESS_GET_RESCALE_POLICY_HPP
#define BOOST_GEOMETRY_POLICIES_ROBUSTNESS_GET_RESCALE_POLICY_HPP


#include <cstddef>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/config.hpp>
#include <boost/geometry/core/tag_cast.hpp>

#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/algorithms/is_empty.hpp>
#include <boost/geometry/algorithms/detail/recalculate.hpp>
#include <boost/geometry/algorithms/detail/get_max_size.hpp>
#include <boost/geometry/policies/robustness/robust_type.hpp>

#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/policies/robustness/no_rescale_policy.hpp>
#include <boost/geometry/policies/robustness/rescale_policy.hpp>

#include <boost/geometry/util/promote_floating_point.hpp>

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
    typename Factor, typename EnvelopeStrategy
>
static inline void init_rescale_policy(Geometry const& geometry,
        Point& min_point,
        RobustPoint& min_robust_point,
        Factor& factor,
        EnvelopeStrategy const& strategy)
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
    typename Factor, typename EnvelopeStrategy1, typename EnvelopeStrategy2
>
static inline void init_rescale_policy(Geometry1 const& geometry1,
        Geometry2 const& geometry2,
        Point& min_point,
        RobustPoint& min_robust_point,
        Factor& factor,
        EnvelopeStrategy1 const& strategy1,
        EnvelopeStrategy2 const& strategy2)
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
        geometry::expand(env, env2, strategy1.get_box_expand_strategy());
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
    template <typename Geometry, typename EnvelopeStrategy>
    static inline Policy apply(Geometry const& geometry,
                               EnvelopeStrategy const& strategy)
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

    template <typename Geometry1, typename Geometry2, typename EnvelopeStrategy1, typename EnvelopeStrategy2>
    static inline Policy apply(Geometry1 const& geometry1, Geometry2 const& geometry2,
                               EnvelopeStrategy1 const& strategy1,
                               EnvelopeStrategy2 const& strategy2)
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
        boost::is_floating_point
            <
                typename geometry::coordinate_type<Point>::type
            >::type::value
        &&
        boost::is_same
            <
                CSTag,
                geometry::cartesian_tag
            >::value
#else
        false
#endif
    >
{
    static const bool is_point
        = boost::is_same
            <
                typename geometry::tag<Point>::type,
                geometry::point_tag
            >::type::value;

    BOOST_MPL_ASSERT_MSG((is_point),
                         INVALID_INPUT_GEOMETRY,
                         (typename geometry::tag<Point>::type));
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


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace get_rescale_policy
{


// get envelope strategy compatible with relate strategy based on geometry tag
// and strategy cs_tag
template
<
    typename Geometry,
    typename Strategy,
    typename Tag = typename geometry::tag<Geometry>::type,
    typename CSTag = typename Strategy::cs_tag
>
struct get_envelope_strategy
{
    typedef typename Strategy::envelope_strategy_type type;

    static inline type apply(Strategy const& strategy)
    {
        return strategy.get_envelope_strategy();
    }
};

template <typename Geometry, typename Strategy, typename CSTag>
struct get_envelope_strategy<Geometry, Strategy, box_tag, CSTag>
{
    typedef typename Strategy::envelope_box_strategy_type type;

    static inline type apply(Strategy const& )
    {
        return type();
    }
};

// NOTE: within::xxx_point_point shouldn't have a getter for envelope strategy
// so dispatch by CStag. In the future strategies should probably be redesigned.
template <typename Geometry, typename Strategy>
struct get_envelope_strategy<Geometry, Strategy, point_tag, cartesian_tag>
{
    typedef strategy::envelope::cartesian_point type;

    static inline type apply(Strategy const& )
    {
        return type();
    }
};
template <typename Geometry, typename Strategy>
struct get_envelope_strategy<Geometry, Strategy, point_tag, spherical_tag>
{
    typedef strategy::envelope::spherical_point type;

    static inline type apply(Strategy const& )
    {
        return type();
    }
};

template <typename Geometry, typename Strategy>
struct get_envelope_strategy<Geometry, Strategy, multi_point_tag, cartesian_tag>
{
    typedef strategy::envelope::cartesian_point type;

    static inline type apply(Strategy const& )
    {
        return type();
    }
};
template <typename Geometry, typename Strategy>
struct get_envelope_strategy<Geometry, Strategy, multi_point_tag, spherical_tag>
{
    typedef strategy::envelope::spherical_point type;

    static inline type apply(Strategy const& )
    {
        return type();
    }
};


// utility for backward-compatibility either treating the argument as geometry
// or envelope strategy for get_rescale_policy
template
<
    typename Geometry2OrStrategy,
    typename Tag = typename geometry::tag<Geometry2OrStrategy>::type
>
struct get_rescale_policy_geometry_or_strategy
{
    template <typename Policy, typename Geometry>
    static inline Policy apply(Geometry const& geometry, Geometry2OrStrategy const& geometry2)
    {
        typename geometry::strategy::envelope::services::default_strategy
            <
                typename geometry::tag<Geometry>::type,
                typename geometry::cs_tag<Geometry>::type
            >::type strategy1;
        typename geometry::strategy::envelope::services::default_strategy
            <
                typename geometry::tag<Geometry2OrStrategy>::type,
                typename geometry::cs_tag<Geometry2OrStrategy>::type
            >::type strategy2;

        return detail::get_rescale_policy::get_rescale_policy
            <
                Policy
            >::apply(geometry, geometry2, strategy1, strategy2);
    }
};

template <typename Strategy>
struct get_rescale_policy_geometry_or_strategy<Strategy, void>
{
    template <typename Policy, typename Geometry>
    static inline Policy apply(Geometry const& geometry, Strategy const& strategy)
    {
        return detail::get_rescale_policy::get_rescale_policy
            <
                Policy
            >::apply(geometry,
                     get_envelope_strategy
                        <
                            Geometry, Strategy
                        >::apply(strategy));
    }
};


}} // namespace detail::get_rescale_policy
#endif // DOXYGEN_NO_DETAIL


template <typename Policy, typename Geometry>
inline Policy get_rescale_policy(Geometry const& geometry)
{
    typename geometry::strategy::envelope::services::default_strategy
        <
            typename geometry::tag<Geometry>::type,
            typename geometry::cs_tag<Geometry>::type
        >::type strategy;

    return detail::get_rescale_policy::get_rescale_policy<Policy>::apply(geometry, strategy);
}

template <typename Policy, typename Geometry, typename Geometry2OrStrategy>
inline Policy get_rescale_policy(Geometry const& geometry, Geometry2OrStrategy const& geometry2_or_strategy)
{
    // if the second argument is a geometry use default strategy
    // otherwise assume it's envelope strategy for the first argument
    return detail::get_rescale_policy::get_rescale_policy_geometry_or_strategy
        <
            Geometry2OrStrategy
        > ::template apply<Policy, Geometry>(geometry, geometry2_or_strategy);
}

template <typename Policy, typename Geometry1, typename Geometry2, typename IntersectionStrategy>
inline Policy get_rescale_policy(Geometry1 const& geometry1, Geometry2 const& geometry2,
                                 IntersectionStrategy const& strategy)
{
    return detail::get_rescale_policy::get_rescale_policy
            <
                Policy
            >::apply(geometry1, geometry2,
                     detail::get_rescale_policy::get_envelope_strategy
                        <
                            Geometry1, IntersectionStrategy
                        >::apply(strategy),
                     detail::get_rescale_policy::get_envelope_strategy
                        <
                            Geometry2, IntersectionStrategy
                        >::apply(strategy));
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_POLICIES_ROBUSTNESS_GET_RESCALE_POLICY_HPP

/* get_rescale_policy.hpp
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
*/