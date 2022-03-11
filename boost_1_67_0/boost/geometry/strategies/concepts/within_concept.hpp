// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018, 2019.
// Modifications copyright (c) 2018, 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CONCEPTS_WITHIN_CONCEPT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CONCEPTS_WITHIN_CONCEPT_HPP



#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/function_types/result_type.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/box_concept.hpp>
#include <boost/geometry/geometries/concepts/point_concept.hpp>

#include <boost/geometry/util/parameter_type_of.hpp>


namespace boost { namespace geometry { namespace concepts
{


/*!
\brief Checks strategy for within (point-in-polygon)
\ingroup within
*/
template <typename Point, typename Polygonal, typename Strategy>
class WithinStrategyPolygonal
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    typedef typename geometry::point_type<Polygonal>::type point_of_segment;

    // 1) must define state_type
    typedef typename Strategy::state_type state_type;

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
            BOOST_MPL_ASSERT_MSG
                (
                    (boost::is_same
                        <
                            bool, typename boost::function_types::result_type<ApplyMethod>::type
                        >::type::value),
                    WRONG_RETURN_TYPE_OF_APPLY
                    , (bool)
                );
            BOOST_MPL_ASSERT_MSG
                (
                    (boost::is_same
                        <
                            int, typename boost::function_types::result_type<ResultMethod>::type
                        >::type::value),
                    WRONG_RETURN_TYPE_OF_RESULT
                    , (int)
                );


            // CHECK: calling method apply and result
            Strategy const* str = 0;
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
        checker::apply(&Strategy::template apply<Point, point_of_segment>,
                       &Strategy::result);
    }
#endif
};

template <typename Point, typename Box, typename Strategy>
class WithinStrategyPointBox
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

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
            BOOST_MPL_ASSERT_MSG
                (
                    (boost::is_same
                        <
                            bool,
                            typename boost::function_types::result_type<ApplyMethod>::type
                        >::type::value),
                    WRONG_RETURN_TYPE
                    , (bool)
                );


            // CHECK: calling method apply
            Strategy const* str = 0;
            point_type const* p = 0;
            box_type const* bx = 0;

            bool b = str->apply(*p, *bx);

            boost::ignore_unused(b, str);
        }
    };


public :
    BOOST_CONCEPT_USAGE(WithinStrategyPointBox)
    {
        checker::apply(&Strategy::template apply<Point, Box>);
    }
#endif
};

template <typename Box1, typename Box2, typename Strategy>
class WithinStrategyBoxBox
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

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
            BOOST_MPL_ASSERT_MSG
                (
                    (boost::is_same
                        <
                            bool,
                            typename boost::function_types::result_type<ApplyMethod>::type
                        >::type::value),
                    WRONG_RETURN_TYPE
                    , (bool)
                );


            // CHECK: calling method apply
            Strategy const* str = 0;
            box_type1 const* b1 = 0;
            box_type2 const* b2 = 0;

            bool b = str->apply(*b1, *b2);

            boost::ignore_unused(b, str);
        }
    };


public :
    BOOST_CONCEPT_USAGE(WithinStrategyBoxBox)
    {
        checker::apply(&Strategy::template apply<Box1, Box2>);
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