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
Yxfez9O5kjP4AGfzQV7Jh3gdV/ExruZzfIyv8XF+zie4lWv4C5/knsroKdbm0zyca9mOz/AoPsv+fI4pXMez+Twv5Au8hK/wMr7BudyQuF8P7f64JMn9+l3he/X72ZwreSQf4Gl8kMP4MGfyEc7lo1zB1XyAj/NdPsEvuYbf8klWk+5TrM61bMtneCyf5Ug+x9F8npP5AqdxPf/Ml5h9vOP1fIXWz0VlTts/dSBcV8TqUSZjr/dLWT9uZC1+yPr8mM35KU/gZo7nZ8zgV7yZX/MRZvFD/p2f8hvuI9Fv2YDfsSW/5zBu4xT+wOv5I5fwZz7HX/gx/8ktLGJ99pLnojycxTmAJTmLpXgD9+CTLMNnWY4fc2+WcHzYh3VYnvVYgSewIodxX17MyryUVbmQ1biC+3EDq/Nd1uD7rMkvWYfVSrh/YzPWY38exJNZn2lsyL+yER9kY77HpvyIzbmFLblXSccr1uUR7MJW7M42HMa2PIftuIhH8UZ24H3syLd4DN9nJ25mZ25hV5aKXWewFk9gR3bjIHZnKntyHHsxjX04lf14MfvzKp7Iazkg1EPXcaHdo2NHqIen+/fPoR62tZ33YzseyKPYkB3ZhcdyKI/jVHbhX3gCb2Q3PsbufIq9+Tr78AP2ZYmi8sky7M/9eSKP4gAey5PYlwM5kSfzHJ7CC3kqL+Ug3snTuIJDuZopfIZjuI91G8+qTGNbprMDMziUk3guz+JFnMxbeDbv4BS+wKl8jefyXZ7HTZzGLzid3/B8buMF/JEXs4yyv4T7ciYrcxZrcQ678DL24uXM4FxO5jxezD9zDufzSl7JB/gXPsKFfJmL+Bav5z95A4urx0tYjjexMm9mTf6NHbmUx3E5S6mPd7M872E1rmA73suOXMnJfJAX8CH+iat4Bx/mPXyUD3M1H+cT/JpPsoh6+DRLcy0b8xk25bM8guvYmi/yBK5nX77ESXyZk/k6p3EDL+abvI5v8Va+zWV8h1vDbyKyxoXnQ+G6z3eDvk8Nv0cK551U9uYIDuRITuUons+xnMlxnMc0LmU6H+IkPsVz+BHPZXFpnMe9OI2Hcjpb8kJ25gwO4CWcwpmcxz/xYV7KVzib33MOf+blrGdd5rIxr2BvzuOJvJJj+BdewL/yG97EqsrhZu7HpazNW9mSy3gUb2cH3pHn/BbajmpTWvD8NruE5XIOa/Fy1ucVbM55bMP57M4rmc6/cCKv4Q28lrdwIZ/ndXyZ13Mzb2DsePJX1uWN7MKb2J1LOYC3cCxvZSZv41Qu42Lezpt4Jx/icj7Bu/gp7+GXvJe/8j7Wta73sz4fYHM+yCO4it35HFO4jlP4PK/ni1zCl3gLX+ZyvsJX+Crf5mvcyA38ie+ybOz3FazMj1iPH7MNP+Gx/JTduJlp/JyZ3MJL+BUv49e8ilm8nn/nE/yGa/kPfsptrOQ48RNr8mcexF94PH9lTxYt6bqJxXkBS3A2S/JvLMVnWZqvsAzf5p58l+X4LfehZRWpwL1YkTW4L2uzEmP10DVcaA/rXBGu72v7d9mwP78e9uc3eDDfZFu+xcF8m6P5DtP5PudwI6/lB3yUH/JVfsT3uIkfcwu/4VcsLc2vWZFZ3I/b2Jk/8lz+xBn8mVfzn7RfKxDPNViMz7E4N7IESxRTfizNMqzKvdiKZdmd5dibFXki96Xy8Zv/RDtb7W/j5ZPh30uKh9+rhd+PzmAtzubhnMP2vIxDeTlHcB6n8M+8gPP5J17J2/kX3s1r+QEX8jNex3IysYgVeQPrcQnb8yZ25s0czb9xPG/hdN7GuVzGBbydq3gHH+NdfJd3s6h1vIdluIJ78wmeyCd5Op9iJp/m23w=
*/