// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2020.
// Modifications copyright (c) 2014-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CONCEPTS_DISTANCE_CONCEPT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CONCEPTS_DISTANCE_CONCEPT_HPP

#include <iterator>
#include <type_traits>
#include <vector>

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/static_assert.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/geometries/point.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/tags.hpp>

#include <boost/geometry/util/parameter_type_of.hpp>


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
                std::is_same<tag, strategy_tag_distance_point_point>::value
                || std::is_same<tag, strategy_tag_distance_point_box>::value
                || std::is_same<tag, strategy_tag_distance_box_box>::value;

            BOOST_GEOMETRY_STATIC_ASSERT(
                 is_correct_strategy_tag,
                 "Incorrect Strategy tag.",
                 Strategy, tag);

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

            BOOST_GEOMETRY_STATIC_ASSERT(
                (std::is_same
                    <
                        tag, strategy_tag_distance_point_segment
                    >::value),
                "Incorrect Strategy tag.",
                Strategy, tag);

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