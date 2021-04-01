
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
ak+n6k5Vor9CXhmES61VO3W566b6e6+gy+vg2xBQOa/DpyaA1Jg9B7aZZcsiHiqt6Aq0CgpkG3QTHYy8MD0pCAmcSR7/Efuqx6eH8nhqJZiz8GvHQW8jSbnQdYazhOIOynzHwfssU9SIFLqY0jagGq9OqbphUjyOb6Tk0Qj9wyYwm0wK+N5o8O7qVB4++8VTHjoE+ZbVFaHn4jgIB8m7NqPsYLwGYMc1SSlim/hq4Y0kmtjUvZA7La7Wzd0nUNhO9YEWhNnkTDCyX9BZZrCzkVRiX6763FQjMGCedJjEmtYDH/+P+fo1ePvwMPSchUM2Hu2lGZD1gcqw2bFgnxF8lyxIIxCB1zlZrBh4n9g0RxGKbJNceXDq5o4FruD+K+cuUhI29rqG7TMYyEUQDihR4cOkwmUjRcZbIEfI4J7J15NskhFSyQUwW2fkgXkJGwkTEbyr7KlorxK8ggU5dX9vDP+WfDZVtO2klmFMPhUGjrAmjxHI89UStQUAWx6rPuJGQXv1nF+iaXm7sCOIcURuYBK8DKAwWsKvZgU9crtCdVxbhXv1Pm9HB5Mw2Q==
*/