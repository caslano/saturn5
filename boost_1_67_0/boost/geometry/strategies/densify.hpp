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
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
*/