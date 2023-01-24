
//          Copyright Nat Goodspeed + Oliver Kowalke 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_ALGO_SHARED_WORK_H
#define BOOST_FIBERS_ALGO_SHARED_WORK_H

#include <condition_variable>
#include <chrono>
#include <deque>
#include <mutex>

#include <boost/config.hpp>

#include <boost/fiber/algo/algorithm.hpp>
#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/scheduler.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4251)
#endif

namespace boost {
namespace fibers {
namespace algo {

class BOOST_FIBERS_DECL shared_work : public algorithm {
private:
    typedef std::deque< context * >  rqueue_type;
    typedef scheduler::ready_queue_type lqueue_type;

    static rqueue_type     	rqueue_;
    static std::mutex   	rqueue_mtx_;

    lqueue_type            	lqueue_{};
    std::mutex              mtx_{};
    std::condition_variable cnd_{};
    bool                    flag_{ false };
    bool                    suspend_{ false };

public:
    shared_work() = default;

    shared_work( bool suspend) :
        suspend_{ suspend } {
    }

	shared_work( shared_work const&) = delete;
	shared_work( shared_work &&) = delete;

	shared_work & operator=( shared_work const&) = delete;
	shared_work & operator=( shared_work &&) = delete;

    void awakened( context * ctx) noexcept override;

    context * pick_next() noexcept override;

    bool has_ready_fibers() const noexcept override {
        std::unique_lock< std::mutex > lock{ rqueue_mtx_ };
        return ! rqueue_.empty() || ! lqueue_.empty();
    }

	void suspend_until( std::chrono::steady_clock::time_point const& time_point) noexcept override;

	void notify() noexcept override;
};

}}}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_ALGO_SHARED_WORK_H

/* shared_work.hpp
HrV6XMe0+KMZFz55nrqZn9aoAyh0E5FKkcEFA1oUueEhj3ULeRhZRBfecgt50SD1TpvJhqF+MV6mIHgFKuL24ImkBJpkQ27lRK1AC1hKX3rNd0Gtah9H3kxcbhHN9sNDYhlXSVGbwUyOlYOBKlFXQ9hNLPK3FC7TYs2FixFix0F2FQl2N+ZIlt4UAoaurC9gocmW3JLju+Twrl/yR2rEkt+0RFvyKEOHlvyOCbTktWG05Ea+5BTJGZfcqC35Zl4K/fGwJxzIwHnFy72DBJtN0C92PV/sRr7YGDfZ3HUCnwqj/2LXq4uNevqlLxt8l5tof82ECyw3nwW34DJJ8OY1r83SLzov5bfu8ybE6bo7NitOEpEzadYfGYzqpe/RrHhK+OwgjLGjJczPyl5mwX8zeLElIBuvbB4Yi1a77gVs1hZE5bkXY5RY/JxHic1oTsWHQ7azA8fIBAfaT4wKZD+xqCuyZxg2FkLGghEHho3daavMo/86QdhYWDNTyS9C4xnkoxloxJcBHvkE8EInlFUpKvB+lxxLaItmzjq+LfwOOw/w62TpTQNB7MoRQzKHkJL4IBCSzOVE+AQHPDhJpiQ2fXm8Vw/zKXkUt5QNBbbgUg389SQ45S4O+UPwnIfihKsx3DBn7yhSbTIOeD+u6dgEMGxhoN/Da3aPI9dkYHr4bx9p1Z3juO2jqewzg+pvTGAr4XqHgnETETsKgbh5
*/