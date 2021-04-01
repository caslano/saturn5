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
bFLKuOQC1dZehg3Qli+1HYb4FoGyldX1Rgrh4+Ao1okDLid1E/BaoFT4ZQzw/C582WNtcFEpjYxfQ+i/Vd3fQbNC0gqmjW8OEWjp/SULAv5kZEYDLzAT78Won6gkLtYX3bm+O9x0Ne1M99fjUdAy7wH+2YGJAe9Dn4Tln6R2iHF6glqk4DRtTW4GQwx4ykTc/TEjJvDpPi7E8lKkwaJa/TBP8cHZjnbgv8H5+ZfzjhzncP0BfUKaIy0zNDeJPkV7bZLxlpaFkHcBPusxUHe8jKqB0O/yC3UlpX+Psedw4t82dcYcC8dHVWBiwZGlldSHLi3u/97gWBRKR2BbBRDRZ0ZEb9gDbFAu3eUdkYrhf7gZfnQo2aGDVMWKgFJPhXPswJZBoTDQLIj6f1pWrfoaxHFzEjmQSIrP8ptAgEjz7MOZSsQaoSuJ0XbmIuQX88NI9h0U8xe+OahNZ9sW65kQ67sbynOv4rT9zszRAYVshb1jTYAHZvFpWUWf2cs6UPnbYyVdeNlAeWcob1tIorneaZtAKXbshmfeQ2+xje28ad1k5FVEV+cic9TGng==
*/