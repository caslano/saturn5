// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CONCEPTS_SIMPLIFY_CONCEPT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CONCEPTS_SIMPLIFY_CONCEPT_HPP

#include <iterator>
#include <type_traits>
#include <vector>

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/strategies/concepts/distance_concept.hpp>


namespace boost { namespace geometry { namespace concepts
{


/*!
    \brief Checks strategy for simplify
    \ingroup simplify
*/
template <typename Strategy, typename Point>
struct SimplifyStrategy
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
private :

    // 1) must define distance_strategy_type,
    //    defining point-segment distance strategy (to be checked)
    typedef typename Strategy::distance_strategy_type ds_type;


    struct checker
    {
        template <typename ApplyMethod>
        static void apply(ApplyMethod)
        {
            namespace ft = boost::function_types;
            typedef typename ft::parameter_types
                <
                    ApplyMethod
                >::type parameter_types;

            typedef std::conditional_t
                <
                    ft::is_member_function_pointer<ApplyMethod>::value,
                    std::integral_constant<int, 1>,
                    std::integral_constant<int, 0>
                > base_index;

            BOOST_CONCEPT_ASSERT
                (
                    (concepts::PointSegmentDistanceStrategy<ds_type, Point, Point>)
                );

            Strategy *str = 0;
            std::vector<Point> const* v1 = 0;
            std::vector<Point> * v2 = 0;

            // 2) must implement method apply with arguments
            //    - Range
            //    - OutputIterator
            //    - floating point value
            str->apply(*v1, std::back_inserter(*v2), 1.0);

            boost::ignore_unused<parameter_types, base_index>();
            boost::ignore_unused(str);
        }
    };

public :
    BOOST_CONCEPT_USAGE(SimplifyStrategy)
    {
        checker::apply(&ds_type::template apply<Point, Point>);
    }
#endif
};



}}} // namespace boost::geometry::concepts

#endif // BOOST_GEOMETRY_STRATEGIES_CONCEPTS_SIMPLIFY_CONCEPT_HPP

/* simplify_concept.hpp
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
*/