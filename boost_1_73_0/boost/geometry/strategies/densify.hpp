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
PNq3AjxfDOwc2RXqucui5UHxERBV0FiNWBb4pA33XSJzcQHl3YVFUCmn9v2s21agCXKMwFGdnicrK+dxXlOGkMuP4bTsGEYGR7BWaaDa3vkDaV2jw7uMzA5369tmcI7EHt6UrRu1Ij3kSDA8gvW7W+UBzZbPL7Hgah/tOtl5s8rOdZ3NzKZuPQjg1prnsZAN2FtYT4NsZ1jH8bSOkPf0Dn3ns0z6IMuPsadxTYWjY4aBOyzA
*/