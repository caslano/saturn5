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
EKYmYN/RNwxKzkUOPK/XSpS95ixfXI54nHMDMae/H7j5eq0GM9f2po84THEZPREeGuVcaSNYVZIzITA65WPVspLhgPvNynV3B+DHvDm25VJ+Ic6n8j1XT4o+fUJZNlclrw8XutKuvkT9erBRlddQJvsuvc9ZB8xPDjwOTUlBbIThlQwCh5kQaX7iGgsItGs0JNbl8HOjXifxOP0Qbxy/2ZA2xenm32DMauf+sdwFb5swYz34pr3PsxijTSxj6mEFpVmiCSKZnFmXmWBOCFr9TGSWb6NggqGAv3Sy+cYvXdFlJhiIuKA56KkXmbhT6rkG6zrmmrY/+G9W2u1f0UzqYk6yVCbb3BltiEClgQAhuMunx2f14ENMrMLqzMS3EFCSjtzqNYeRMstgd59SiMIA4y2Mlyrb/I8rWKYwRVHoctlrhEQCN4m/kZBrDzeSZiBdanHjp3uUa5pzRbi/kk0d/Gj2XBUX7ciTDu3tl6qBWQUo3ExNIK+HfAkOJBei4obUFJKsVK9GHzvqiYJrA72IS59h9Q3DJq2rh/kl6IaEnKwJNWb0dI2jnRGTlg==
*/