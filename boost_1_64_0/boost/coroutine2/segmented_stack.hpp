
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
5sBvPTCThJrygubfWE3ZQMh1bSMjjwZ35qh9rgdq61ZDB9gS6C1vq4aRRCoM9s6j+ZUddO2I1/ouaPl8jMiVHK+yMncZCmn/dPEfVAL0xofkIfNzLUYyKWRTBHjei5LNHZOuTtBZeMJvaClIOqkrLaCk8p6j/IYL54NQ3Sysriy1gPEo8ihtl+lapVvL8SKo3hSTwpY5EZnYhquG+vbRBHI2X9hMGtOsv8qndQKsAGMJzarzIlxKvrEGAV0rTc3R2OVMbBiK9JcYnNN/2iDneKgOZp7+pj8cjeatoAeTk/KrHdokfRX2y8wpse+PZBX50P5v9/DPuSZ/CZF08kKc9ejc8XMcGG0Hl9Dgx/m7bbapReYrLGr5GTYzcZrfeGzwLGr4IuqUPhZIR6x9AESunH+dzVvlUxcqAV3VbL1nAQZQCLWFJZXGqrWR+nY6A+bwJzgyWf+alEAV9b8+b1K58vcKXql1Hkift5BHZPT58Rv8NbY9YMcNY7+CrG/7TDqljjBd2ZiX+6rx/RNrjn458PeePrF05LfwjYnIY8KFqUnb07GAvD5GMxBsKQ==
*/