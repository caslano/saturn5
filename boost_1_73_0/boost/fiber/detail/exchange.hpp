
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
w+HwFTgO/hVOggdgKXwVXgxfg5fD1+Fa+Ca8Gr4F74SH4GPwbfhb+Df4B/ge/DN8H74H/w6dinkYxsAjMAl+BJPhx7Ab/AQOhp/CEfAzOB7648knGIBXwgS4CQbhNpgK74cZ8EGYCR+DX+J/L/wKvqP2n8I9Tvn56XdhKsRe8o0xi665Z12fln9rpLOW/4fUkwD8BMbDz2A2/BLmwa9ha+jjPtMRxsFimAhLYAO4GqbCG2AL
*/