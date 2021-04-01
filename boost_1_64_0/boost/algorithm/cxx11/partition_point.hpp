/* 
   Copyright (c) Marshall Clow 2011-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  partition_point.hpp
/// \brief Find the partition point in a sequence
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_PARTITION_POINT_HPP
#define BOOST_ALGORITHM_PARTITION_POINT_HPP

#include <iterator>    // for std::distance, advance

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn partition_point ( ForwardIterator first, ForwardIterator last, Predicate p )
/// \brief Given a partitioned range, returns the partition point, i.e, the first element 
///     that does not satisfy p
/// 
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param p        The predicate to test the values with
/// \note           This function is part of the C++2011 standard library.
template <typename ForwardIterator, typename Predicate>
ForwardIterator partition_point ( ForwardIterator first, ForwardIterator last, Predicate p )
{
    std::size_t dist = std::distance ( first, last );
    while ( first != last ) {
        std::size_t d2 = dist / 2;
        ForwardIterator ret_val = first;
        std::advance (ret_val, d2);
        if (p (*ret_val)) {
            first = ++ret_val;
            dist -= d2 + 1;
            }
        else {
            last = ret_val;
            dist = d2;
            }
        }
    return first;
}

/// \fn partition_point ( Range &r, Predicate p )
/// \brief Given a partitioned range, returns the partition point
/// 
/// \param r        The input range
/// \param p        The predicate to test the values with
///
template <typename Range, typename Predicate>
typename boost::range_iterator<Range>::type partition_point ( Range &r, Predicate p )
{
    return boost::algorithm::partition_point (boost::begin(r), boost::end(r), p);
}


}}

#endif  // BOOST_ALGORITHM_PARTITION_POINT_HPP

/* partition_point.hpp
ZUv3iCf4QCiSliIY23no8Y/ObSKV2adJKBc8xBI9JZRK3ILh/nB3rWw3ovcs4318dZOQ/h5HNKZ5a1XRMQspq4gQ3jnR62hKRyI5eSsAtI7aZJoBl3h8b2lnLBa7l8gCdX6IQyDgd74K7heb1YtCKjkqIt+jpJIi0aqYMyZJett/3WJKZVtxsqeZL4SBD5PN00xbgfElm9qTUUsBaU70eUiojY2CcR7MV6FIR70Tzr9ZCLdAyW7XFnGccq4lNYcuFOPDEiwcoyFoTczfhH8b10Vd3onmGCUKtMTzx6A9YHPzWiyv+43hUPtUi5qqovnk35NHI+gf7wlMtrHTFqxtBxHH/05bUsCCyRK7pEWuTkoVqF93lkLXXGJOHm2rAIlNS/3KxsGGtYHin3XrB86j5A2AOEelvjUyFiJa1lBGDffQnSwEqEoSEcpV0DJ8/r6m7pfgBN5ccb58oSGTtlVYLyr86b8dKYXXaNBfCIhD4m4w3mHS1HhXH0SH5qRsLm/QqOFXosztuziM8nOIf1z+Zs4eaWva3eqX5r1L+3/dPt+tZs0zBBCU/MQPrw==
*/