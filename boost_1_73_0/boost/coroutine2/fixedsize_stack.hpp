
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_FIXEDSIZE_H
#define BOOST_COROUTINES2_FIXEDSIZE_H

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/fixedsize_stack.hpp>

#include <boost/coroutine2/detail/coroutine.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {

using fixedsize_stack = boost::context::fixedsize_stack;
#if !defined(BOOST_USE_SEGMENTED_STACKS)
using default_stack = boost::context::default_stack;
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_FIXEDSIZE_H

/* fixedsize_stack.hpp
qmmcXmWdUETyfQSpyeRflTEd246axh+9adR7a5K462+1EllW7IzfxMpnXE3fRtI3xEnf/FXOxp0PIEYlunTSPO04p3Qi94hyI3Pf59VKmV6vTsgnKJh7nLktpWMm6t7Yk2rYSyabZ+kwpB5pW9IOpbyG+O8to8+Ccsc3urPTQ9i5z09iv9boWNR7kdqvMfY6Pqv9cmPvjk3EKWPQ9Wm6x5XavYhdqcTJeKB2K4x/7fc8678v
*/