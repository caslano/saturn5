
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBER_DETAIL_THREAD_BARRIER_H
#define BOOST_FIBER_DETAIL_THREAD_BARRIER_H

#include <cstddef>
#include <condition_variable>
#include <mutex>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

class thread_barrier {
private:
	std::size_t             initial_;
	std::size_t             current_;
	bool                    cycle_{ true };
    std::mutex              mtx_{};
    std::condition_variable cond_{};

public:
	explicit thread_barrier( std::size_t initial) :
        initial_{ initial },
        current_{ initial_ } {
        BOOST_ASSERT ( 0 != initial);
    }

    thread_barrier( thread_barrier const&) = delete;
    thread_barrier & operator=( thread_barrier const&) = delete;

    bool wait() {
        std::unique_lock< std::mutex > lk( mtx_);
        const bool cycle = cycle_;
        if ( 0 == --current_) {
            cycle_ = ! cycle_;
            current_ = initial_;
            lk.unlock(); // no pessimization
            cond_.notify_all();
            return true;
        }
        cond_.wait( lk, [&](){ return cycle != cycle_; });
        return false;
    }
};

}}}

#endif // BOOST_FIBER_DETAIL_THREAD_BARRIER_H

/* thread_barrier.hpp
y7VnlouFrrkdsEDMZiRNa1EZXvZpFMcuG9FCVggkuMuEUZRM+l+iT/3veYBe4xiUytoyx4TlXn+pU4cBpYVML0yLtzZNmmYivZBgiLdCh0HYy7S4KTb4zB0HKAa7YqE7saSop0qWXpcBrGAUs+ZEVZlemYYSalaLer3nt6VSAa9UtiqbIZYK+IUu24o98o4rWy8Nmxg34wC9nGalTi+gzthmzoEsyA+TIRXM0BmqaL1AaaJDUjfMMjclvZfB8+fB/t4ORMfhZDoIh4dH4WB0T32l7Cl1eF4qUXa2QEbgqjL+jTOa+/VKGellGsQHfTKZi2X5IBzbzDsWrBQ6SI7W4Er1ts1LWTe3TlEzl5wfxOm8RtjVzVxmyvl5I++xdg6s7Vq1xj3v3wIMzfzFKwbsLmINAdGO4mnS//gxmuxoSuq80vWPuAgbm4zPlTFcX7r2dJ6XqpJbryO00AjlPvbSbvZ6/4O9dA97vQ17A+6KqZ7P4GLWwHeWD3ZV6Fk+9l1eSu7O8FtcSOdTKjNZpXIb6pf7jptuwHwMj4dTb989YShNo8NoGHshuIAm/QRvDhC67tPuVPglHAzD98O+d0slj2K32/8afh5jL6hyrxl9Lk2/3xqMqlK2iwmn8i4v7tHfHn0/N3nhZl7i4lNn
*/