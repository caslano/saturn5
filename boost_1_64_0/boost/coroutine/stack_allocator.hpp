
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_STACK_ALLOCATOR_H
#define BOOST_COROUTINES_STACK_ALLOCATOR_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>
#include <boost/coroutine/segmented_stack_allocator.hpp>
#include <boost/coroutine/standard_stack_allocator.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

#if defined(BOOST_USE_SEGMENTED_STACKS)
typedef segmented_stack_allocator   stack_allocator;
#else
typedef standard_stack_allocator    stack_allocator;
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_STACK_ALLOCATOR_H

/* stack_allocator.hpp
50SGTR67BtjCU54DhFIt6i+BFTowwV8aG4ixqfGvxR7MxhctJYhyZnc31mIeGCY9PwsK9mIL6p2NUnC6k5RgGrE0RWngji/JMXRNu4IO3FH02Qn3btL6eCfXyoYLNcOJ5To2GkLzK/VXhL4rmmQFgAqlk4s8rDDy3GHB0BBiRdbgTRTPKzlfM00G2eSk5ae0YEvpk/fVskbjMi9sD8w72O5GIM+23x+1bIPqBBbweWRpit7rEykQ47CtCYc8yCBzEoW6fD0Km2ChnoP4+Lf+hReu9S4quQ//sVeibDoMajEUpCLrjjKoRly0QJx1OfeweqQkEPmxXww5Sxv8rW2oHd+DQd/rk/0VucDnnXvvLRfcFCJj7i/JVdYAxuWVcobAsM18j2DtEJEkFMBVWFIW1brDJ7aCZx6eaQJhjdQRW0T0ELnu+FNSPqsypanvBgBdknkKUOG1TvcvabquRiB4UsYnebu2QkqzdB6EX59E/VK1JFvXKBOPmhGDjnW1iV9+GjEblatq2sFQDK3oXtZDNSOQpBmG5xG26j4T+xaDCYuLOyHan0EGs0b4mg==
*/