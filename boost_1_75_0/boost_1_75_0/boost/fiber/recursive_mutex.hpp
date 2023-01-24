
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//  based on boost::interprocess::sync::interprocess_spinlock

#ifndef BOOST_FIBERS_RECURSIVE_MUTEX_H
#define BOOST_FIBERS_RECURSIVE_MUTEX_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/assert.hpp>

#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
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

class BOOST_FIBERS_DECL recursive_mutex {
private:
    friend class condition_variable;

    using wait_queue_type = context::wait_queue_t;

    detail::spinlock            wait_queue_splk_{};
    wait_queue_type             wait_queue_{};
    context                 *   owner_{ nullptr };
    std::size_t                 count_{ 0 };

public:
    recursive_mutex() = default;

    ~recursive_mutex() {
        BOOST_ASSERT( nullptr == owner_);
        BOOST_ASSERT( 0 == count_);
        BOOST_ASSERT( wait_queue_.empty() );
    }

    recursive_mutex( recursive_mutex const&) = delete;
    recursive_mutex & operator=( recursive_mutex const&) = delete;

    void lock();

    bool try_lock() noexcept;

    void unlock();
};

}}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_RECURSIVE_MUTEX_H

/* recursive_mutex.hpp
ETzWqdr9XkJFxBdG8QUd9E6XAHBH4IQ3x0MsDj87YAtZky/n57qFY8ianI7lgazJ8R7h6U3EiQ+vwOPa0AofXAH0ZsVPBObhVm+CwBYFJLoj9JqlBseZVULoNUtDr1nImEOQDDUOI6pZYRDEHK/ZVoJBGB8zcnemOcrOinMYYitH8NgMBlUOu8s0wWGvfTMAhz0h1Ze9/rAY2esHeGP7i6F/R+yMIcoaE0YBiGarIW+eKeYiRFbyb8U+LHiWrbSNYK0A5jjGTsgEF3vFRzBPuqCelufodjrtOZzawc9pfjgfCPlv/HBWgrl6ev2Dlxf2W/EjiCQLUyAuyrU8lIqBQqlcUnzGUNiblV/xI1i1F/4BiS0UZOVHg+t7jMWyB3iyFWcAhl1mxqoAtCDuUeaUxUqbDc0hg6tU/kx/Nk09pwIDxJl1BDqbTnzIL84sKlxmTomX7L4hanQbf5+LIbC1CA/yJKPy7esk9cIaz6yAZentADJ5BBjW01lh2ERRSvMXFwgemzc6QPBYO0f5B5oGXh0m6eB+oi4QhePPBJ3M+gsMjE1eYISXgbtX6ENj2+RTXAcxWdk8C7WpGIxmykWtyCZAsuFukG/WKLOnmyU1MWwOCQgLDXQfOtwuj0N1mRSswDagJiiujKYaHrg9FpBlNCLLZVHgDyn0DSTH3MsWD3295u8x6Cyp6xsxWmh2hjTHpSLSfMQfaYLf5K1n
*/