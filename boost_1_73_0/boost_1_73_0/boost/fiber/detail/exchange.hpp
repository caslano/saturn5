
//          Copyright Oliver Kowalke 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBER_DETAIL_EXCHANGE_H
#define BOOST_FIBER_DETAIL_EXCHANGE_H

#include <algorithm>
#include <utility>

#include <boost/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename T, typename U = T >
T exchange( T & t, U && nv) {
    T ov = std::move( t);
    t = std::forward< U >( nv);
    return ov;
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBER_DETAIL_EXCHANGE_H

/* exchange.hpp
2dPmTNdbdD9xOpjdvXgfXb/c9bjT6vi4XC99wfSN5H09wS0HU9jb5kzXW7Q8hj7htGL62pyPwUfP84dFob1RNudh8FH/PQtmfD++XnoiToLx6s/XM+1voWA6D+DbS8/zpwyQx5fmxzZwywfarGl+lCJOgvnoSZszzY/9yO8smBV/5tubjPgdzMTB/PjSY9TvglkXbXPeBt9YxDNPO61/PM33H31FwlkwTz1jc14GXw7iLJi5MbyPHt/5AIzzLzY=
*/