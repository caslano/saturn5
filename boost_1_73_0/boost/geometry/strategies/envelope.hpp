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
DI3gh9LoXB4DCvf0ucsJLtK7C7b2zuM+uPivGpKi1Gf75DZJZ5Snu7/Prb3u4cI9pa3VcR65UXGe25bXA6S7oO+xMa/RPEwT59BL6rgd97d/ENd5UExwa1E2wqFkOme3Z1qN9A/rUHWc65Ii0dt/wGTWA/4OZeWH0cLIkJY/v2xviHc2KX/HsjUfn4BpX9dHeUcGuwd13WxgGkC5tEBnxEY6d+j7ad+ATcBX+37yWbeZ89HC
*/