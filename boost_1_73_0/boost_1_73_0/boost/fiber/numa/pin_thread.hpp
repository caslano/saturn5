
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
z2wJMwukOfDSpoC/DPfv7qT75O1a2kjldLWpNiTQBJvlWdTf8Rfh/iMLofIZIZXuF1wfMqc2tMHJJsxEWlZpF+zQMpJrE6mUCZIwzMQw5McsWXUH3NtYq0xVHdhUA2oXvOj7npax1WEwdbSmzjT30wZZ/mXCKu0NWcFgcWG/7PQXxpKwF9gk/ygLorJA6bqKKViWRrpVGv6bcFl3QiWYza0D0yO4GgbndKiuLwuyoJhx7gIez7Jr1Q1KD1zBCuk=
*/