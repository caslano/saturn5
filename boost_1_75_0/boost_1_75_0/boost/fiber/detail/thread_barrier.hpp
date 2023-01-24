
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
YMFJavJ4yT82DBvsgc7S2OojvEpFlacWDUUdogKYG+j76eL9tMt/52U9mDa1GysJsuo9KKquUVK3/B0MVtuzZ6U98hMHD6jJvtHxVyDNp9TpDECmNOGNPSXEG3vBB0mYL87lkEcxIuHRHIf8uD64PUg8x9TVb7sQDCrfvkCqtiEdVCHL4jY8/o3F6JENW4e7XV9hMXpk6161tZDw8UI82j+y5ncqj8H/OwHNxYSgOf/y1DJS0ZWRiu73SUJFVxIuRDeI8PZZyl8L4+YREwwGXFfneMjnOB+h8SAh4Sc7CUJWGbUN9C2TQV0bpYbHS0d7UyScC7lx91Fhtv8d6nl+ypf/3gDSa0GDwNkzXD17Snio0hdKcFszBmjuLzYUJnxDNKkru/qRIX7JvAZ1Z399J1VvhKQskiVnIyz7d2ths51GZS6ECaFwGLXYUl9syWnJRfLrh5VJJuxI4BI7WrCqYuiSoPXe33BnsWEMz97zyDj/UPG970O+9zB9TzcIeY8IZhW07vgZvuix5vpz2grXDIZvqXHoxFjWiUC00/9pCem5v08gK8VMGEBO7jyIyIt0SptYwqYXcKdgwslo9OLMA0PkrdwPE40OIdYKVC9GP03MF2Bd1zcF8QwqrUEvspWxB2YoVYDLx1gPJ+YFU9cwUyflaocF1XiW9+vF65M18brQfOHTQknEtJycmg4G30j7vXQUdq2/hKsQslck
*/