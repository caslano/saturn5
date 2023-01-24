
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_SEGMENTED_STACK_H
#define BOOST_FIBERS_SEGMENTED_STACK_H

#include <boost/config.hpp>
#include <boost/context/segmented_stack.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

#if defined(BOOST_USE_SEGMENTED_STACKS)
# if ! defined(BOOST_WINDOWS)
using segmented_stack = boost::context::segmented_stack;
using default_stack = boost::context::default_stack;
# endif
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_SEGMENTED_STACK_H

/* segmented_stack.hpp
eO/UbmodqMigJ4epPJNRaXPGUQEAz26KEY6xCGHmcLWKVO7M1bMG1lfpwZas+Qb2aWmD+PS5TTFS0C9NZeTrLfKPW8Aj+FsukEV1Uhd9lUuvicHQ0b2uOEmlTTmqNkaODtW1E+3CX3PDB5ba3PG8MyyoQ69vy8U94rFywj2f8ee8jaA0joV2lvvyRsQELvnVh3l1+McpfrKwTZxiC1ta10zgYBPz0i4uvMROk81YWWXEc7oD2m0AMs3diGWPu0BcgcNpgb0uG8uD+gze/UtbvtuHf/3XAv/b0AJ0+o6sN+52r/nAAt9Ywy8u6AgHenlaMD+/OWvFUoxbG+S80KX9fl8VuN83CwTFpvn4M7pp/m1+R3pcmBqsxy+vCdLPmT+328+H5rc/v6SuM3e+7/xmdqi3e68P1ttWj5jfXzxB+v3qT+32+5N5Qee3nM/v4qd187tuXkd6HBu0x6M8Yt9p964gSQjRupkF8hI3xr7+7l69/ttdOppYRbj6+PeIq5cgF23O/qfAa7PmqDRx470qTXTd3NYJ4v4CkpPbNE/attQZ+a7Z8u8I/wW4aTE6ZTIoJKWq6EoXcJshrfEF/FJyRgGhqr2j8w26oJKh1/kF4flWTEnKw8Fi6vz8Y9szaZv4JwASLO3TBQFiaUzPdy0AaWmRLvjJuALdOtncywow7Mm9p/zCnrx7X0fCngwdGmx575QFQE6TkUmcJAeB
*/