
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
yDKRMlHLxDwXtUzkyaHLRAoNWSaUg++91qhlguHC8PEx7bdDgcC9FEmv7GpdLwKzKqy442g2/EJff4tCXfCDaNE42xcg7Z8dlBdIj44v1IkfYfbxwbmPt/9yX56I0ppJsWhnoiiZ7V0ULTol1WzPo5S3c6ogXa4qaZEt7Ss6On250WU1WkjnRZfWaCGdH11ao2Wmo9Sq1Ih2RipFq16pFfWUVLNXulSIIO2Fbt0RtnInuqQkUF4ayC2fV1pT558=
*/