// Boost.Geometry

// Copyright (c) 2017, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_DENSIFY_HPP
#define BOOST_GEOMETRY_STRATEGIES_DENSIFY_HPP


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace densify
{

namespace services
{

template <typename CSTag>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_CS
            , (types<CSTag>)
        );
};

} // namespace services

}} // namespace strategy::densify

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_DENSIFY_HPP

/* densify.hpp
MrZRg/R2I84gY0rrMmZMK3HNxNd1rQ1xBhlTWhOZui78Lf7Q+Ys0vd2IM8iY0spnxrSmlieV6lofxRlkTGl5SAt/2M4PIS11uR4WnZaXGdP65sXlHbrWMKdBxpRWAddSZb7us5deTyatMqdBxpRWITOmVTmhbKuutdBpkDGlVcSM9yv+H4lD9BFHm9MgY0qrmBnTGl47Y6eu9YTTIGNKaxJT18W1ypYf1rX2Og0yprQmM2NaSSe/GKxrfeE0yJg=
*/