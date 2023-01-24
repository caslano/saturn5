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
EYGs7dc13Gbb7xk943wkUOYlNCyLwt0Ki2+WQf3bINwn2SFbI54l/Q0h1u/6OrcyZ8xsFXlYCw0dFJHyG0KvbnyPANoPVdjdZkZG4QstNpVj+q7bINAJ3oeFDkFAxCPnYtwt3hP6B/t+0/kmff2OQrTKisu271LgPrpY1ytvsg/K6srfPazE/YRJi+mHaLsdSoEz2dxAlZNY4FXDKcXVriagoSszJ+xdQXjkka1Oa64vrIzBFEkzxjE8Ton7FykTIRcF1aT0r7qkOPwWUVSsRWVnwvW1Jhtr6SzvlAW11pVuMy+KIMMPbd6b9o7JCQwfc9xDU81emdFw3KqcyK2xZNatjTldvpZONZPB+TYo+/qNAXVYvMQ0I3Oqej9Joyge4NloDHWoC4HqIgoTz82URFrQjfSdQs7P77IG9Cc0wLK+GtNEDl0NesxfSTcXdCycHIgAuaqUQXOG6lW1V8QK/MBpFdN7qrgyq+WXvp943Pw03DLRw++R+hcS0MLi1DPDyDXKeDFC0zA2Dy3KBvuGdvwdAebhanKYB8npqzSh0vhCwNcTm48Bz/pKJEsLYKchKYkfu9w6rwmWqXG7EWOEFPAnWQbwmT7y7b7POaVA/iojZfuVuxgVKp8sw+iKbUZnlv5Br82n8Vsd2UViv+UyQs1LfKqKH+o3UzkkDoQhBFrEdWk0I+rob3qCZ067P1pFvnL4btDc7+pDBpYk
*/