
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_SEGMENTED_H
#define BOOST_COROUTINES2_SEGMENTED_H

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/segmented_stack.hpp>

#include <boost/coroutine2/detail/coroutine.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {

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

#endif // BOOST_COROUTINES2_SEGMENTED_H

/* segmented_stack.hpp
vBzOg9fDc+GtcD5cCRfCR+Gf4PdwMWxGxS2BXeBNcDi8FR4Pb4Pz4O3wGngnfADeBVfDFXANvBs+D++Fr8D74GfwfvgFfBDuhA/DH+GjMBzi3g4bwqdhYzgINoHPwk56fgx8Do6Ez8OJ8CU4B+6EF8DdcBW0KPcK2k0CnA0teLaeXwcT4VKYCtfCCFwP68JX1f4gu1JeZmNfZCgwqYeh9wjTDzMK48jP5C7/eTqN+mEmYAox
*/