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
Pv3dX3z60l98Ojug8GnOBPO46idXcAwmt07M96tWQljJ3YvHs2sVDqmIeK90r7LrI4C0KPII46wUNGSgHullBWV4FGlK1dvlgqJ75OBD9ZP9wlVmKeeLPoupq5pj1hzszV6p5h8C5wlmq9JfsH2HoL6C0jZSFV/zisukxoirD0mh14ezZ4p6WdPmKw+vcmXHdOxQ8B8Z7UTQhUaTy5LV6NhnTeZNPn6yneL5m0/3De3hGBIFaXkeg537ghWJj6TlXohgIlfn+bFQfLdeZfIwGHJgZI8iqAiygHdEqa6hCg9f22EBRZaZd9AO30o+vrklS2FdUD0Cgk2OTMCgIxDXxaJ9nbxIlUZcS6v4NIzkZgAq6AETeL0RfmatKjAM2GtpO4s6k2MsALjTarwH+bhzotHSuoVk+OCq2rykJ5bhf2uyEE7c+xCjuJkWuvmN9T1LxmdpvIv0Lmv3woAcC64mlXR3XwXOESvbJh0K4tXT8oc9idAbXD6swNKBqB4pO+xeG+2zNrY8BcG2UotyWto8JboFfk664fW4y58G0b8tGTFzQ0mbB/DNCg8yHRcz/lCMer7Uk7AV+q14CoiNL+HviXAqv9/2YWY94zGTj+MTKPhLSI/sVzwcqq4qEUtbhWwnQ3lwv5TAc50ezV2RNikLVLn0sBaJ9mtPYNj2z0lslJD7XURMQ8gQpzmuYi1qT+9YtG7ml0+ePuhDkNlc
*/