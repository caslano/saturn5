
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_EXCHANGE_H
#define BOOST_CONTEXT_DETAIL_EXCHANGE_H

#include <algorithm>
#include <utility>

#include <boost/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
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

#endif // BOOST_CONTEXT_DETAIL_EXCHANGE_H

/* exchange.hpp
U7hGFNlnmVSKyBi9E6ILzkyDwCLcixrh2mTG27S1lNd07mKDADsTYWcK2U6FYrUucLxwjAU6tCziZH1va+NaVBWCv1oDyzKOiNiYKTnLSVmuEN0M40Hx1uhSKkNMgDRZz72zOJ5GPoyMs2VZyBrMJA4CJ2JAVvvacG05BacMMcRVzQzyHM6LmCNJChpeZrzNLZKfksgNaKaU2g4oxdH6QvbT3BoVii94bbQlQBpETj4W7Av3NMWbyrauWjYqsxxlb5GhjaAQaO5RruJzYcQCO4S1ibgxVDFWr6mtLi9eW1Yl5c0M8BpjJZIZTaHzDVh3vBMJtUQjSpiH6hnL8C5l2ReKebsm9JJnokACsaDwECcPQbd3tE+I4Stuy4bxzTkWoFnmGH3uw4c1ZlewpsKltWPRa2HGNoPvUkupliy3xaEwcRPaTtEiw/LmUONS0pqp9eNcz/odL3DIud9WzdUKFyKxMkLwfvt6fb//hJnDHzVz6DtCvwMwptHQAhbFHboxBwvItBGVg19mGlahtG6WhOPWWBckoedaaO4GZdv3lHtiXktlCX036qMfjfroZ0Z99MyoLRedBufj2NtON/EAYdytQYJ2DukWOTjOBXwLebRFuek+Rqalw1aopBy2QFyxqmm5Ddmjzi0fSe8h
*/