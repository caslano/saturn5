// Boost.Geometry Index
//
// R-tree strategies
//
// Copyright (c) 2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_INDEX_HPP
#define BOOST_GEOMETRY_STRATEGIES_INDEX_HPP


#include <boost/geometry/core/cs.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>


namespace boost { namespace geometry { namespace strategy { namespace index
{

namespace services
{

template
<
    typename Geometry,
    typename CSTag = typename geometry::cs_tag<Geometry>::type
>
struct default_strategy
{
    /*BOOST_MPL_ASSERT_MSG
    (
        false, NOT_IMPLEMENTED_FOR_THESE_TYPES
        , (types<Geometry>)
    );*/

    typedef geometry::default_strategy type;
};


// TEMP
// Utility to get index strategy from other strategy
// In the final version this utility will probably replaced with some other mechanism
// The issue is cross-dependencies between strategies
template <typename Strategy>
struct from_strategy
{
    /*BOOST_MPL_ASSERT_MSG
    (
        false, NOT_IMPLEMENTED_FOR_THESE_TYPES
        , (types<Strategy>)
    );*/

    typedef geometry::default_strategy type;

    static inline type get(Strategy const&)
    {
        return type();
    }
};


} // namespace services


}}}} // namespace boost::geometry::strategy::index

#endif // BOOST_GEOMETRY_STRATEGIES_INDEX_HPP

/* index.hpp
5K8UoJRFI7jgsvr9qpX1pXA3j5veKIlFcElJ1RMabynA4EV4a1Xo16PO/Xs5QZR0yXytzb3xWAXzsEpaXi2vUgVNkD5bJV9DWh4kK5UOsFXTyxnOZJULdqnChBi+nTutkCxSg09RWIhekQHoL2Syl0+cV8xZm1XPANxUTxjnt9G9NE0V/tNwT0XsL60aH1WhJeemfhz0iFXdajXdiln7lM7JVHOfXoNUqcuuXZV9tJrskoLiF1G0mdrqXpXa6r2V1QLG31NV/eokWKM6urQ2KvfykspoplPGqS9EESVdi2AfJQm7LDP6ZYqOhYsvKDmuVnBcTXH5OftRSUPnSodfZBNvVnCXSuIsFRo/vIyXWX7aYlVBsNvIB2uPFVzJVa4cXq174PnLhFdyUV8zwErRJ2RUsS/XLnHiqpgPhUV79meQO5RTGrj9fd294ugl72mXr20NZzEVAUSFhqyNemJGFVu0h27Hr8aunF27d5HrLHHZ77nw9y/10hKQYZr415kwpfqMJdOwE98AaliZwk+qVCeLP17AI4Yj7trruHu2P1aGos7JElHUWFQrEqmS6PeJkeEC6RJO45ukh7ifcVnDeT7M0G5k3Z4P4k8tfIOFpzH6wok/LSX+slT+L0qhY/xfUEsDBAoAAAAIAC1n
*/