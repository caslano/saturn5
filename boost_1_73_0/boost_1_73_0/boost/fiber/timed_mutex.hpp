
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_TIMED_MUTEX_H
#define BOOST_FIBERS_TIMED_MUTEX_H

#include <chrono>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/convert.hpp>
#include <boost/fiber/detail/spinlock.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4251)
#endif

namespace boost {
namespace fibers {

class condition_variable;

class BOOST_FIBERS_DECL timed_mutex {
private:
    friend class condition_variable;

    using wait_queue_type = context::wait_queue_t;

    detail::spinlock            wait_queue_splk_{};
    wait_queue_type             wait_queue_{};
    context                 *   owner_{ nullptr };

    bool try_lock_until_( std::chrono::steady_clock::time_point const& timeout_time) noexcept;

public:
    timed_mutex() = default;

    ~timed_mutex() {
        BOOST_ASSERT( nullptr == owner_);
        BOOST_ASSERT( wait_queue_.empty() );
    }

    timed_mutex( timed_mutex const&) = delete;
    timed_mutex & operator=( timed_mutex const&) = delete;

    void lock();

    bool try_lock();

    template< typename Clock, typename Duration >
    bool try_lock_until( std::chrono::time_point< Clock, Duration > const& timeout_time_) {
        std::chrono::steady_clock::time_point timeout_time = detail::convert( timeout_time_);
        return try_lock_until_( timeout_time);
    }

    template< typename Rep, typename Period >
    bool try_lock_for( std::chrono::duration< Rep, Period > const& timeout_duration) {
        return try_lock_until_( std::chrono::steady_clock::now() + timeout_duration);
    }

    void unlock();
};

}}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_TIMED_MUTEX_H

/* timed_mutex.hpp
n9Q6vO0oTXQoQsOgOX1d4pp5rLoXFxoSNyO+DXaWqI/oVU2QbX59dD95A+q5o9A78npO6JpVzof54A4O723CHzAGZlOVkZrGGE1yTe36akzXWq1Wna0apHYT1t0NLjF6d5MszOlMLG2MTd0b57p2d+NKt2zRh7taOqVYWIhtA7LtppBjHFxsOqQJeruzbIK4evnsDbVx+AHN1K67PrwqCtzXA+bN/sYLhIo03PLC2GVVPGqK6tpspPLnaJ1AT6MbLpjiNWYfcufaErX5/N/ssw14stXATZ++1d8pqeeUpjUwHjGbX7uWXCi+0lpDe4YRplo/Yg4Xt5GsrRhOCW+3UwSEsWRzGciTjgB+gDMF/kVlbxzk9mgcjqx5UQD/B4YJttB6Q1Rm0fr3RydwCaKHTuj8x7oG7t1zG6JzPjte3/no9b1wYsGnLqYkMERZopkfMJHWM+0BfQpOpLbpU75E27NpEOCtqWX8cMHPMZ1hqF8V2RwrltXk60FNv6jCN7M/c8Usir+ZaYhpt1FpfgMggJEbjkcD+uz0x641MiOBonp+8E+YxLhLi5x/tSV2szEenAz8s8HUNyMrH4JiG9OJ1QiOw6l/ND11T/3RhLfZE9QyBlZc03KOmjGFjtsqSZVRLGpfWoHrktMPfMz5
*/