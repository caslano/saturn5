// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CONCEPTS_SIMPLIFY_CONCEPT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CONCEPTS_SIMPLIFY_CONCEPT_HPP

#include <vector>
#include <iterator>

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

            typedef typename boost::mpl::if_
                <
                    ft::is_member_function_pointer<ApplyMethod>,
                    boost::mpl::int_<1>,
                    boost::mpl::int_<0>
                >::type base_index;

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