
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
cjE6JUuclBVVhnW6DBZ3TY2ujUIxX5+Qx2r+y33pcSF9LcPF/vWEUBxIweKZS9jMX3VUEgfRIxWpZ6Kr6oRoL/6txOkxAeui+IB1PfJzZAdyXkLA2oe8gSTiv3W6hK96TlgvX52WxHNi4q2L42Ota+OD1i3wYViVEGu9iLyaEIzQW1NmZWve/vhrfLPK/i5rBKlK1zJl59avHPtXYnOsRaxJGOY/6L/PuivQBRehPEPjqxOU
*/