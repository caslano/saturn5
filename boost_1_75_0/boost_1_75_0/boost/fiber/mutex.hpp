
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
7oNOTHur+T4s/cmT4N2MseGRy6Mh4PO2J7EjIzyx6ML6+LPayt8HjtxDveB4hnry3Tx9T+yeiEtYQ2msGuWTebwzKc8SlEBPwP/egvOoWIoGpuqCdWeFLN6PM9Pv2W56eDo7PVvlH6ygWBxK9IztIjeKerOHxbAGGf/NepB9lPiir5U9A0mc+4ukyvAZBG19BndL+LxtBOasKAYqjoNo9AwQ0a2KF4ywwSHBj/oNwiYjZjt8xaCMJHpsJHex+jaD8XtPICzdZhFhoeDSHwEO0BMWGNtFOLabnxEeawsHY7zDZ5A9rNZGHwUpoInUyev12r0f5Y1KG36n62TTGTYRyiXWc95yUqD5rpLQURkgX6WTlZwfPoBvrZkQ9Z7r3I813kLGml+A/GcD2q4bhe8G9rsG5DWmPmC9blR6PI5Ku3ueJ6VdcBAWuff5fsLDJJyEgHHMV6KrY1Tr9WRf6/UGzc8j43+fBk3doig6axxfGouepKbsYat/aaVq8+LTx18epT7yLsKRzOkeW0Pm9qdbewM+HOaKpw7PfAw73EPfYXOgDufu7ViHy5/Sd/gqfYfnbYnh8a/b4P0mhvcbCe/3ixN432SVv7HLrQ75R4ZLFzrkpQ+K49gqlvs4232rvOYxrLXyausrYSA1mP13CeSXDO1bX/FM+MNrHvIUoU84BYiPT7GPO7OPT3nNkfAx+Sw3I5D/50lte15GV/as
*/