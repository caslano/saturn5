// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CONCEPTS_CONVEX_HULL_CONCEPT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CONCEPTS_CONVEX_HULL_CONCEPT_HPP


#include <vector>

#include <boost/concept_check.hpp>


namespace boost { namespace geometry { namespace concepts
{


/*!
    \brief Checks strategy for convex_hull
    \ingroup convex_hull
*/
template <typename Strategy>
class ConvexHullStrategy
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    // 1) must define state_type
    typedef typename Strategy::state_type state_type;

    // 2) must define point_type
    typedef typename Strategy::point_type point_type;

    // 3) must define geometry_type
    typedef typename Strategy::geometry_type geometry_type;

    struct check_methods
    {
        static void apply()
        {
            Strategy const* str = 0;

            state_type* st = 0;
            geometry_type* sp = 0;
            std::vector<point_type> *v = 0;

            // 4) must implement a method apply, iterating over a range
            str->apply(*sp, *st);

            // 5) must implement a method result, with an output iterator
            str->result(*st, std::back_inserter(*v), true, true);
        }
    };

public :
    BOOST_CONCEPT_USAGE(ConvexHullStrategy)
    {
        check_methods::apply();
    }
#endif
};


}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_STRATEGIES_CONCEPTS_CONVEX_HULL_CONCEPT_HPP

/* convex_hull_concept.hpp
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
*/