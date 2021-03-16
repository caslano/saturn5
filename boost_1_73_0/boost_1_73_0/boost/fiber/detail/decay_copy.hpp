
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBER_DETAIL_DECAY_COPY_H
#define BOOST_FIBER_DETAIL_DECAY_COPY_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename T >
typename std::decay< T >::type
decay_copy( T && t) {
    return std::forward< T >( t);
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBER_DETAIL_DECAY_COPY_H

/* decay_copy.hpp
3yfnVwJma0s5v3Iwt1vyPpq/3q2clpefPL4jwEzyk31zwKTcL/tOgbl8P++j9eA2GM/Wsi8WTFJr3kfn3RQwgwLk/psDZm2APL67wAxpI4/vVDBpbeT8ssAkBMr5ZYM5EMj7aD8vBFP8gNx/IUHY34J4Hz2/EQNm2oM2ZzoPka8EzI0H5XrxDHZa9dvK+Q0Fk9CW99F6PxOMXzt5PPqAiW3H+2h9TgQT/pA8HolgUh7ifXT9uxJMRojc3gowjoc=
*/