// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014, 2018.
// Modifications copyright (c) 2014, 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CONCEPTS_DISTANCE_CONCEPT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CONCEPTS_DISTANCE_CONCEPT_HPP

#include <vector>
#include <iterator>

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/geometry/util/parameter_type_of.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/geometries/point.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/tags.hpp>


namespace boost { namespace geometry { namespace concepts
{


/*!
    \brief Checks strategy for point-point or point-box or box-box distance
    \ingroup distance
*/
template <typename Strategy, typename Point1, typename Point2>
struct PointDistanceStrategy
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
private :

    struct checker
    {
        template <typename ApplyMethod>
        static void apply(ApplyMethod)
        {
            // 1: inspect and define both arguments of apply
            typedef typename parameter_type_of
                <
                    ApplyMethod, 0
                >::type ptype1;

            typedef typename parameter_type_of
                <
                    ApplyMethod, 1
                >::type ptype2;

            // 2) must define meta-function "return_type"
            typedef typename strategy::distance::services::return_type
                <
                    Strategy, ptype1, ptype2
                >::type rtype;

            // 3) must define meta-function "comparable_type"
            typedef typename strategy::distance::services::comparable_type
                <
                    Strategy
                >::type ctype;

            // 4) must define meta-function "tag"
            typedef typename strategy::distance::services::tag
                <
                    Strategy
                >::type tag;

            static const bool is_correct_strategy_tag =
                boost::is_same<tag, strategy_tag_distance_point_point>::value
                || boost::is_same<tag, strategy_tag_distance_point_box>::value
                || boost::is_same<tag, strategy_tag_distance_box_box>::value;

            BOOST_MPL_ASSERT_MSG
                ((is_correct_strategy_tag),
                 INCORRECT_STRATEGY_TAG,
                 (types<tag>));

            // 5) must implement apply with arguments
            Strategy* str = 0;
            ptype1 *p1 = 0;
            ptype2 *p2 = 0;
            rtype r = str->apply(*p1, *p2);

            // 6) must define (meta)struct "get_comparable" with apply
            ctype c = strategy::distance::services::get_comparable
                <
                    Strategy
                >::apply(*str);

            // 7) must define (meta)struct "result_from_distance" with apply
            r = strategy::distance::services::result_from_distance
                <
                    Strategy,
                    ptype1, ptype2
                >::apply(*str, 1.0);

            boost::ignore_unused<tag>();
            boost::ignore_unused(str, c, r);
        }
    };



public :
    BOOST_CONCEPT_USAGE(PointDistanceStrategy)
    {
        checker::apply(&Strategy::template apply<Point1, Point2>);
    }
#endif
};


/*!
    \brief Checks strategy for point-segment distance
    \ingroup strategy_concepts
*/
template <typename Strategy, typename Point, typename PointOfSegment>
struct PointSegmentDistanceStrategy
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
private :

    struct checker
    {
        template <typename ApplyMethod>
        static void apply(ApplyMethod)
        {
            // 1) inspect and define both arguments of apply
            typedef typename parameter_type_of
                <
                    ApplyMethod, 0
                >::type ptype;

            typedef typename parameter_type_of
                <
                    ApplyMethod, 1
                >::type sptype;

            namespace services = strategy::distance::services;
            // 2) must define meta-function "tag"
            typedef typename services::tag<Strategy>::type tag;

            BOOST_MPL_ASSERT_MSG
                ((boost::is_same
                      <
                          tag, strategy_tag_distance_point_segment
                      >::value),
                 INCORRECT_STRATEGY_TAG,
                 (types<tag>));

            // 3) must define meta-function "return_type"
            typedef typename services::return_type
                <
                    Strategy, ptype, sptype
                >::type rtype;

            // 4) must define meta-function "comparable_type"
            typedef typename services::comparable_type<Strategy>::type ctype;

            // 5) must implement apply with arguments
            Strategy *str = 0;
            ptype *p = 0;
            sptype *sp1 = 0;
            sptype *sp2 = 0;

            rtype r = str->apply(*p, *sp1, *sp2);

            // 6) must define (meta-)struct "get_comparable" with apply
            ctype cstrategy = services::get_comparable<Strategy>::apply(*str);

            // 7) must define (meta-)struct "result_from_distance" with apply
            r = services::result_from_distance
                <
                    Strategy, ptype, sptype
                >::apply(*str, rtype(1.0));

            boost::ignore_unused(str, r, cstrategy);
        }
    };

public :
    BOOST_CONCEPT_USAGE(PointSegmentDistanceStrategy)
    {
        checker::apply(&Strategy::template apply<Point, PointOfSegment>);
    }
#endif
};


}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_STRATEGIES_CONCEPTS_DISTANCE_CONCEPT_HPP

/* distance_concept.hpp
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
*/