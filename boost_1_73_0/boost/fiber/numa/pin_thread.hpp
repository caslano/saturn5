
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_NUMA_PIN_THREAD_H
#define BOOST_FIBERS_NUMA_PIN_THREAD_H

#include <cstdint>
#include <thread>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace numa {

BOOST_FIBERS_DECL
void pin_thread( std::uint32_t, std::thread::native_handle_type);

BOOST_FIBERS_DECL
void pin_thread( std::uint32_t cpuid);

}}}

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_NUMA_PIN_THREAD_H

/* pin_thread.hpp
B++FHeETsAvcDbvCvbAb3A97wQOwL/wUnggdXagnwSQ4DKbB5YTfA14I+8OL4Eh4MZwAL4dT4JVwEVwHl8Kr4YVwPbwC3gA3wJvgTfDn8GF4C9wJb4XPwrvhG/Bt2CGG+gF7wr/D/vAIPB1+BIvhJ7AMLiG+58PPMK+Fn8Ob4FfwNtiC8w/BlnAH9ME/qf2rav8mjIU2/UU8zIIJsC1sALtDx/0g2BIOg6lwJkyHC2EWXK7u
*/