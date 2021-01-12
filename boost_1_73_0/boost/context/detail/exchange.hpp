
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
+DYcCf+m7eRdeDjcCufDj+Fp8EO4GH4Ez1c5ZS7n7gdRieMx9ZilmKFFpPsWznpCq5q6wdRjGp+rr8LEztFH03Z4Htacd30Q8yEmpGcw6+FSzBrMJkzs3ORQzHzMUswazAY9p1mIGYQ5wufMZs1xxN3hx89ses9rrsfEndE8zntOc6dnNPV8ZuNzmT9+JnNXz2Nufxbzp53DbHwGcyX1uhGzFRPiZi3E9MdMxCzCLMesx2zG
*/