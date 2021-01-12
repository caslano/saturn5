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
47P2TpSHv6Nxvi3IV+N8s77d2fLF51d6Vm6lPLwn4v7fJVuX25tdvSMFm6sLKt9XsDN2Der38MKy+eL36oXZ88FdhfwbsEfu5rfsSG9KcjGXVNDXcffP14gcXn23xv5jAcNf1tbp7I4Uf2Ez4ZOA7wSe879O9A3Pa0r1Ts8123LAkZ/fA+cifZuojtUdFKMxyepdrwGObY/it8Ra4F2bp5GdyDppk8dxh6jN8+UNcmvgOO96
*/