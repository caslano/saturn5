// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018-2020.
// Modifications copyright (c) 2018-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CONCEPTS_WITHIN_CONCEPT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CONCEPTS_WITHIN_CONCEPT_HPP


#include <type_traits>

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/function_types/result_type.hpp>

#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/box_concept.hpp>
#include <boost/geometry/geometries/concepts/point_concept.hpp>

#include <boost/geometry/strategies/detail.hpp>

#include <boost/geometry/util/parameter_type_of.hpp>


namespace boost { namespace geometry { namespace concepts
{


namespace detail
{


template
<
    typename Point, typename Geometry, typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct relate_strategy_dispatch
{
    using type = decltype(std::declval<Strategy>().relate(
                    std::declval<Point>(), std::declval<Geometry>()));
};

template <typename Point, typename Geometry, typename Strategy>
struct relate_strategy_dispatch<Point, Geometry, Strategy, false>
{
    using type = Strategy;
};

template
<
    typename Point, typename Geometry, typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct within_strategy_dispatch
{
    using type = decltype(std::declval<Strategy>().within(
                    std::declval<Point>(), std::declval<Geometry>()));
};

template <typename Point, typename Geometry, typename Strategy>
struct within_strategy_dispatch<Point, Geometry, Strategy, false>
{
    using type = Strategy;
};


} // namespace detail


/*!
\brief Checks strategy for within (point-in-polygon)
\ingroup within
*/
template <typename Point, typename Polygonal, typename Strategy>
class WithinStrategyPolygonal
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    typedef typename geometry::point_type<Polygonal>::type point_of_segment;

    // 0)
    typedef typename concepts::detail::relate_strategy_dispatch
        <
            Point, Polygonal, Strategy
        >::type strategy_type;

    // 1) must define state_type
    typedef typename strategy_type::state_type state_type;

    struct checker
    {
        template <typename ApplyMethod, typename ResultMethod>
        static void apply(ApplyMethod, ResultMethod)
        {
            typedef typename parameter_type_of
                <
                    ApplyMethod, 0
                >::type point_type;
            typedef typename parameter_type_of
                <
                    ApplyMethod, 1
                >::type segment_point_type;

            // CHECK: apply-arguments should both fulfill point concept
            BOOST_CONCEPT_ASSERT
                (
                    (concepts::ConstPoint<point_type>)
                );

            BOOST_CONCEPT_ASSERT
                (
                    (concepts::ConstPoint<segment_point_type>)
                );

            // CHECK: return types (result: int, apply: bool)
            BOOST_GEOMETRY_STATIC_ASSERT
                (
                    (std::is_same
                        <
                            bool, typename boost::function_types::result_type<ApplyMethod>::type
                        >::value),
                    "Wrong return type of apply().",
                    bool, ApplyMethod
                );
            BOOST_GEOMETRY_STATIC_ASSERT
                (
                    (std::is_same
                        <
                            int, typename boost::function_types::result_type<ResultMethod>::type
                        >::value),
                    "Wrong return type of result().",
                    int, ResultMethod
                );


            // CHECK: calling method apply and result
            strategy_type const* str = 0;
            state_type* st = 0;
            point_type const* p = 0;
            segment_point_type const* sp = 0;

            bool b = str->apply(*p, *sp, *sp, *st);
            int r = str->result(*st);

            boost::ignore_unused(r, b, str);
        }
    };


public :
    BOOST_CONCEPT_USAGE(WithinStrategyPolygonal)
    {
        checker::apply(&strategy_type::template apply<Point, point_of_segment>,
                       &strategy_type::result);
    }
#endif
};

template <typename Point, typename Box, typename Strategy>
class WithinStrategyPointBox
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    // 0)
    typedef typename concepts::detail::within_strategy_dispatch
        <
            Point, Box, Strategy
        >::type strategy_type;

    struct checker
    {
        template <typename ApplyMethod>
        static void apply(ApplyMethod)
        {
            typedef typename parameter_type_of
                <
                    ApplyMethod, 0
                >::type point_type;
            typedef typename parameter_type_of
                <
                    ApplyMethod, 1
                >::type box_type;

            // CHECK: apply-arguments should fulfill point/box concept
            BOOST_CONCEPT_ASSERT
                (
                    (concepts::ConstPoint<point_type>)
                );

            BOOST_CONCEPT_ASSERT
                (
                    (concepts::ConstBox<box_type>)
                );

            // CHECK: return types (apply: bool)
            BOOST_GEOMETRY_STATIC_ASSERT
                (
                    (std::is_same
                        <
                            bool,
                            typename boost::function_types::result_type<ApplyMethod>::type
                        >::value),
                    "Wrong return type of apply().",
                    bool, ApplyMethod
                );


            // CHECK: calling method apply
            strategy_type const* str = 0;
            point_type const* p = 0;
            box_type const* bx = 0;

            bool b = str->apply(*p, *bx);

            boost::ignore_unused(b, str);
        }
    };


public :
    BOOST_CONCEPT_USAGE(WithinStrategyPointBox)
    {
        checker::apply(&strategy_type::template apply<Point, Box>);
    }
#endif
};

template <typename Box1, typename Box2, typename Strategy>
class WithinStrategyBoxBox
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    // 0)
    typedef typename concepts::detail::within_strategy_dispatch
        <
            Box1, Box2, Strategy
        >::type strategy_type;

    struct checker
    {
        template <typename ApplyMethod>
        static void apply(ApplyMethod const&)
        {
            typedef typename parameter_type_of
                <
                    ApplyMethod, 0
                >::type box_type1;
            typedef typename parameter_type_of
                <
                    ApplyMethod, 1
                >::type box_type2;

            // CHECK: apply-arguments should both fulfill box concept
            BOOST_CONCEPT_ASSERT
                (
                    (concepts::ConstBox<box_type1>)
                );

            BOOST_CONCEPT_ASSERT
                (
                    (concepts::ConstBox<box_type2>)
                );

            // CHECK: return types (apply: bool)
            BOOST_GEOMETRY_STATIC_ASSERT
                (
                    (std::is_same
                        <
                            bool,
                            typename boost::function_types::result_type<ApplyMethod>::type
                        >::value),
                    "Wrong return type of apply().",
                    bool, ApplyMethod
                );


            // CHECK: calling method apply
            strategy_type const* str = 0;
            box_type1 const* b1 = 0;
            box_type2 const* b2 = 0;

            bool b = str->apply(*b1, *b2);

            boost::ignore_unused(b, str);
        }
    };


public :
    BOOST_CONCEPT_USAGE(WithinStrategyBoxBox)
    {
        checker::apply(&strategy_type::template apply<Box1, Box2>);
    }
#endif
};

// So now: boost::geometry::concepts::within
namespace within
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry1, typename Geometry2,
    typename FirstTag, typename SecondTag, typename CastedTag,
    typename Strategy
>
struct check_within
{};


template
<
    typename Geometry1, typename Geometry2,
    typename AnyTag,
    typename Strategy
>
struct check_within<Geometry1, Geometry2, point_tag, AnyTag, areal_tag, Strategy>
{
    BOOST_CONCEPT_ASSERT( (WithinStrategyPolygonal<Geometry1, Geometry2, Strategy>) );
};


template <typename Geometry1, typename Geometry2, typename Strategy>
struct check_within<Geometry1, Geometry2, point_tag, box_tag, areal_tag, Strategy>
{
    BOOST_CONCEPT_ASSERT( (WithinStrategyPointBox<Geometry1, Geometry2, Strategy>) );
};

template <typename Geometry1, typename Geometry2, typename Strategy>
struct check_within<Geometry1, Geometry2, box_tag, box_tag, areal_tag, Strategy>
{
    BOOST_CONCEPT_ASSERT( (WithinStrategyBoxBox<Geometry1, Geometry2, Strategy>) );
};


} // namespace dispatch
#endif


/*!
\brief Checks, in compile-time, the concept of any within-strategy
\ingroup concepts
*/
template <typename Geometry1, typename Geometry2, typename Strategy>
inline void check()
{
    dispatch::check_within
        <
            Geometry1,
            Geometry2,
            typename tag<Geometry1>::type,
            typename tag<Geometry2>::type,
            typename tag_cast<typename tag<Geometry2>::type, areal_tag>::type,
            Strategy
        > c;
    boost::ignore_unused(c);
}


}}}} // namespace boost::geometry::concepts::within


#endif // BOOST_GEOMETRY_STRATEGIES_CONCEPTS_WITHIN_CONCEPT_HPP

/* within_concept.hpp
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
*/