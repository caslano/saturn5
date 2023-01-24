
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//          based on tss.hpp from boost.thread

#ifndef BOOST_FIBERS_DETAIL_FSS_H
#define BOOST_FIBERS_DETAIL_FSS_H

#include <atomic>
#include <cstddef>

#include <boost/config.hpp>
#include <boost/intrusive_ptr.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

class fss_cleanup_function {
private:
    std::atomic< std::size_t >  use_count_{ 0 };

public:
    typedef intrusive_ptr< fss_cleanup_function >   ptr_t;

    fss_cleanup_function() noexcept = default;

    virtual ~fss_cleanup_function() = default;

    virtual void operator()( void * data) = 0;

    friend inline
    void intrusive_ptr_add_ref( fss_cleanup_function * p) noexcept {
        p->use_count_.fetch_add( 1, std::memory_order_relaxed);
    }

    friend inline
    void intrusive_ptr_release( fss_cleanup_function * p) noexcept {
        if ( 1 == p->use_count_.fetch_sub( 1, std::memory_order_release) ) {
            std::atomic_thread_fence( std::memory_order_acquire);
            delete p;
        }
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif //  BOOST_FIBERS_DETAIL_FSS_H

/* fss.hpp
Qdm1j/5bfMIh59uccgd5k5Mbu+fK5eXkykU6SCHy/yPauOqR9VnANsgX1BS87FqjLTtJCa11B4xYoka/7FQcsUQy4FUSYH5iaA5AsSya+kMd3qXc1gUJvsyt7EQ281w5/LjXT6SlfGGkbiOS2YI30tjWG9TWWtYCO/oR9VJaBhckDgwLvAU5dGH53L311T7pjBTkpU7V2YRv81FdaY0PRBGhV8BmOEY5s1Yl9AoAUzzTlXIXJ+MH85NJQAFdPqAhWjL+P4gEHvkFIBNlKX+ftiyGnvGVNzHr/RbCZsuVj2RU5VX8OL2bfuZ7alVg5hlrYIUtR3M/WmuRVbTM6xhFG0kisgOAjG4Z0Loy9mH4h0gCDInwv6XiH8hafw/CyBqcrZ3K7tMQnvtN1F2glEvi/c0hwowPMQcpMGxks0nV4q7hAJ+jVURvnnI+eweQLFVQcIW13bG8OLI++/IqjlvmjWW9DHQKWus6d2SdO4LIcxh7Vj8CnUPo2040biY9DneUIZIyv+JHd1sgoa2lnblAVhIqn6B1QueOODqJRse3dH0VRw4nGUMTeCejqkhodyGUheTXfqSp7jjCnAuzGXdPgNkQDjQo50JMh6eNUJwmoZ7eUp4Xxg03dig//ZFE9UhQxapUvIsbG5dkBV+S7L8gRYxw09SviUtdE74AA2BZtklZ5EhiqchBDzYOUQLoOK/DtSzgRrAfBrGznYl/
*/