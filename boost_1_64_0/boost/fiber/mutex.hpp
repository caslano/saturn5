
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_MUTEX_H
#define BOOST_FIBERS_MUTEX_H

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

class BOOST_FIBERS_DECL mutex {
private:
    friend class condition_variable;

    using wait_queue_type = context::wait_queue_t;

    detail::spinlock            wait_queue_splk_{};
    wait_queue_type             wait_queue_{};
    context                 *   owner_{ nullptr };

public:
    mutex() = default;

    ~mutex() {
        BOOST_ASSERT( nullptr == owner_);
        BOOST_ASSERT( wait_queue_.empty() );
    }

    mutex( mutex const&) = delete;
    mutex & operator=( mutex const&) = delete;

    void lock();

    bool try_lock();

    void unlock();
};

}}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_MUTEX_H

/* mutex.hpp
K6EFOYq4j0Ij4FdJNsn5G3HRjM78QvblyLiXthWc4i9O6Ph+tIRyyUntx94lB1lAf1vpsqSvOnM+tcRgEBEG8/9+UPoqAHjRUfpD1NLmq2CNwR0Ge2FKJ6VaN/+Ub5WyUqYpLWv+ooMiyXoq8Q4yOptT80gPpOgX8Rby46dyCoZ1cr9hwQ16YSk10FAEnyXClDCJ8YcR2HSeD04zLZo28I8jWrDGVjquGqtFLfzKhxviTelx+J8mkn34uJv+Zw2yU2csqAWZpryTliVJjFNGqxw1n5d6rbnn6PyMyhgz9djn5QW/itWX9o6z/jrIHwbzURbO4/O46IiPez6rxUd/ssAchpUPiQctV40OnSGAre2aKhlYrn32JfSFOMRzwh/txbrnRYL+u2iaSR75ToF24N2Bw0YAdH0C/MpM6L5n8WmNle+ObkrxpLT4iecjgtsEbBBndoKp0QVSMmB77T4lzXYRxg0/1CEhzPWi/0Vpc6LxPzqY0ctc33TB9uQgfOl187R7Gcmpjq6dDRusKUvFPOr82LjxAF1XJy64RwyWJWbapmevi1BnC29n5A==
*/