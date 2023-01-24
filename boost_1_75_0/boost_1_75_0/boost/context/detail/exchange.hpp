
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
pAnkoHcCb4LV4D0x5XBZyzsLtm6JP29pio28c5SVI/djrn7jDi796EWOrR0gEBRFzqLcQ7kcJxTTakJVlTjlmNQHlLOQCowMra5rE5BNEdwTWwGy5uGHBT9w1yW+8/zz3NzrUe0OwI8hG0N+DLI7oktQg5vg3QHCzfCuAh/GplsvUCp1FpLBqRcimu0ywm3nIkAg6JLQLwlbFwjCav36rqbvrrj/5r8kF0a0RsjS52Lpv3of3C6lwmzFqmwjAJ3lYgRAzGYz55xDKeUJOQCp9cSfex5gd90WACCkFClunqQlNH0IAzKEVFSLmjyryF69g6MPPkR25jkOuM4L9/8r2NjCKcts6xxHizXE849gr7wDeaTGlB7jBaWfkXnL2tYa80uf5LW9Fzj94NfZ3vlTptufYrB2ApnBvIoZbTbMobNShJsi+v6+EXofAQAQsrUOu4MpiWahS807EykYawc8gf2PRJ2L2jrMMQiRDBetAG89yttQCh1DgSJGD5yN+4l5QkTNm4TbRT7B1p3JNKa1CIiZhbV1yMzhqoxydw0z7jPUPSo3x9T7CKupbM3BYo41FpHBvK4wlcMIj5NQVRZjbTDjRXA3yhJqC2fODPjVv/URDg4WXL424bkXp1y86Nnerdi+cZFzFz039jT7Ew1zjc+O4Ht3BECWNVqUeG+wvkL4BfgavEW4NFQzcApiqTgodQVuzfM2BEhnu2ht
*/