// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_ENVELOPE_HPP
#define BOOST_GEOMETRY_STRATEGIES_ENVELOPE_HPP

#include <boost/mpl/assert.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace envelope { namespace services
{

/*!
\brief Traits class binding a default envelope strategy to a coordinate system
\ingroup util
\tparam Tag tag of geometry
\tparam CSTag tag of coordinate system
\tparam CalculationType \tparam_calculation
*/
template <typename Tag, typename CSTag, typename CalculationType = void>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_TYPE
            , (types<Tag, CSTag>)
        );
};

}}} // namespace strategy::envelope::services


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_ENVELOPE_HPP


/* envelope.hpp
SeUmeUYa51/M4dW6n9gKewsqwNGawiqJlTB3jk5erSO3ZnyHLkkndClP+/dYEaiYMEcc6i+gXH/xzaxhLQmsGwyk32qThvGdtr4W3JCHcNT79C9tFJnM1OTdcMBwXoReMF5Sg2W6VVZo2U07SRlXu8zO8FNy7eMJ++dwPjAbD5azRRWd0k2rh95yb0IH8Za6jMPp6U/mx51+dGOvixFu6urCbYyKgy+6VSiFrs5n8C6Locc3EBXAw0tU3/dK/zXRzGP7Eyjw49kB6bgN0anG9LP5wRsuN+tL0tkF1oziRZGkpGwf899ZXPzYy4BpCVU185zhPSt39RvsZSMWEBfd6XbObss57bO9rDxkYmzrbcn+kCo9yGKzQzAYU6Vji3toE2XWb5m/zO9pwxV9iIhqTSiCPu7k/vxt8uTJpDozz0Wky9TWeJ+LJTL45oOH3LPClZUY04VuoBo6RFcebt3fZMdzMHCzF6eN7pqK5iiXrtxZdlJ4PTfGWBDn6FVPHmnzVp8Ld6mlti1XdAZDcxj+3dlSYck9dbzCqmKZSsPeqG/hC19CjU1Lg9Lp5NtYKvJz9jWP1jTWbxjaPX3kl3WYxt6xjr9pricYamS3NUM0glNKU5ysddxjW9WhfjsT+8pXyrOsG4J7HYN2VyJXauZURJBwfa7KdN9Gc/TnNEuu4Jg9lzGA7+x9p8eux66Dbpbuyd7NJu3N8xD2I7Tm
*/