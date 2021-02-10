// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_CODE_HPP
#define BOOST_GEOMETRY_PROJECTIONS_CODE_HPP


#include <algorithm>

#include <boost/geometry/srs/projections/dpar.hpp>


namespace boost { namespace geometry { namespace projections
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

    struct code_element
    {
        int code;
        srs::dpar::parameters<> parameters;
    };

    struct code_element_less
    {
        inline bool operator()(code_element const& l, code_element const& r) const
        {
            return l.code < r.code;
        }
    };

    template<typename RandIt>
    inline RandIt binary_find_code_element(RandIt first, RandIt last, int code)
    {
        code_element_less comp;
        code_element value;
        value.code = code;
        first = std::lower_bound(first, last, value, comp);
        return first != last && !comp(value, *first) ? first : last;
    }

}
#endif // DOXYGEN_NO_DETAIL


}}} // namespace boost::geometry::projections

#endif

/* code.hpp
BYNzCVgmbAJzgRBYM2EVjg+VHXNDB4kSSh5wGSDiEd5Eh0g5c5zKSCdDlxWyLNEk6KAoWUdm6+ELPSMJipLkV0iUxDSlF4R/jhaTCVsGa0CNoxC0QiS9GuSUeEZDe0Z+0cgo33Ccg8ZE3WsU7xr6elToXA2uO0+Qm1lrDaTWo7QekQ8GQbrXKoYcfoo4uheLOcwo0gXICPQq4hQ0PigSBDKKJrDJgLNyVix2VT6wX24fbvjK1cy8Z2dusq6tqN8HbSiTHKkxxwT7AWSuXQ87waBz+pfgXee8P+gEQ2z0sT/4cDLoX/fONkZZlrAZAu7jHSBBBWDsFHNg0ijApRtTRVvSvBv80kLlC2JyfAtSX35j+0M3Lg/BpiEgaK6ADo/EVgP77x3bVp/tKF9px3q32HzvWBPs1pb+HiZALkA7UUBGytaWp6WpAW2E3h37T7T1KCMEoLHPEHzjLCKbJNAOdDBPwDL8V000YYGwBmLpYqZtNYIJe2mwf1kEDM4JwoghhF8/Q4evh/86bLE7QVUbi8glqsgQJtC+FqZ7VUgesn7/GKdDtJuWMdB8BKPkGbBBmqOAsNEHtocnAr0x8ADQKcfPBDibjGP8XGHAIQPDKQExEd6QLV0aoIVf76D7DIX3SFti4P2Drp9J9HTg
*/