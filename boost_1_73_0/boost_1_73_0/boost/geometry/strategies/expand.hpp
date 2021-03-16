// Boost.Geometry

// Copyright (c) 2018 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_EXPAND_HPP
#define BOOST_GEOMETRY_STRATEGIES_EXPAND_HPP

#include <boost/mpl/assert.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace expand { namespace services
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

}}} // namespace strategy::expand::services


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_EXPAND_HPP


/* expand.hpp
Nqn3WPVNVnqWijqXHhqKqFPqScpkzNysmCxEHZJqPVV8qdrjYVW8z6J/BgFV2M9i4QwCpis3tlGm6zYeyM8PFHoCWYXlnrLyEv/UkslFnvxc+C9b/CvXkvPzRubnwv9Z8/KzMZottPOzPcpAdlH51Cne0uJJnvyMwkk1+RleLx0rKPSUg59UWjZligda6PxRvBPMHyWKUv4ok3BRoWdqeeHU8snFXg+tLOePEt1ffk7+KPCxUKWoFP7K8kfJZWk=
*/