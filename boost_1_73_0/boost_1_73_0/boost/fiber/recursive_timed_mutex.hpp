
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//  based on boost::interprocess::sync::interprocess_spinlock

#ifndef BOOST_FIBERS_RECURSIVE_TIMED_MUTEX_H
#define BOOST_FIBERS_RECURSIVE_TIMED_MUTEX_H

#include <chrono>
#include <cstddef>

#include <boost/config.hpp>

#include <boost/assert.hpp>

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

class BOOST_FIBERS_DECL recursive_timed_mutex {
private:
    friend class condition_variable;

    using wait_queue_type = context::wait_queue_t;

    detail::spinlock            wait_queue_splk_{};
    wait_queue_type             wait_queue_{};
    context                 *   owner_{ nullptr };
    std::size_t                 count_{ 0 };

    bool try_lock_until_( std::chrono::steady_clock::time_point const& timeout_time) noexcept;

public:
    recursive_timed_mutex() = default;

    ~recursive_timed_mutex() {
        BOOST_ASSERT( nullptr == owner_);
        BOOST_ASSERT( 0 == count_);
        BOOST_ASSERT( wait_queue_.empty() );
    }

    recursive_timed_mutex( recursive_timed_mutex const&) = delete;
    recursive_timed_mutex & operator=( recursive_timed_mutex const&) = delete;

    void lock();

    bool try_lock() noexcept;

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

#endif // BOOST_FIBERS_RECURSIVE_TIMED_MUTEX_H

/* recursive_timed_mutex.hpp
UFJPWFlfUElOTkVEUFVCTElDS0VZLjNVVAUAAbZIJGCtV2tz2kgW/a5fcYt8GMclILHzmDiPWgXLscYYMUjEodZblJAaqxMhKerGmNnsf99zW8LGj3HyYXAZQXffZ5977qVz3qLdf+xldVgd/fQ1Nf9TvPDcCA2r4quI9cMC0+kPqv8geI7nL5jq0o3Uj+lT+iWpH7RjpKaNrXf8eTr9BXPn7CS/dVn4fMofsVJLNvK9olxX8iLVtNN7Ss/fvPmd2rT37Pkbmw6jXIqMAi3ymagubHqXmJV/pdHVVUeJDzYJTVHWuaUwTKUiVcz1KqoE4XMmY5ErkVCkKBEqruQMX2ROOhU0l5mgnj+ceINPNq1SGaeNnnWxJJUWyyyhNLoUVIlYyMtaTRlVmoo5NEB/IpWGzqWWRd6BeUFaVAvVqGEnokwVFF1GMotmMBdpSrUu1UG3Gy+rDJF0kyJW3XiTik6qF3eimsCbRbSmotSkC1oqYROft2lRJHLOT6QIi+VylkmV2jduwWCedIuKlMiyRh1EpVB1CIKCJls2n6QS3kvND1Xkiq2t0mJx6yDS2iiaL6sc5pAWnEsKJN6mZZ6Iypw3idhYabJsUv6TK7vxPaEih1fUcgLyghbNIiWVTWdeeOyPQzpzRiNnEE7I
*/