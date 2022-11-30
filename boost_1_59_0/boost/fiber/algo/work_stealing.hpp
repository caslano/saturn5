
//          Copyright Oliver Kowalke 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FIBERS_ALGO_WORK_STEALING_H
#define BOOST_FIBERS_ALGO_WORK_STEALING_H

#include <atomic>
#include <condition_variable>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <mutex>
#include <vector>

#include <boost/config.hpp>
#include <boost/intrusive_ptr.hpp>

#include <boost/fiber/algo/algorithm.hpp>
#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/context_spinlock_queue.hpp>
#include <boost/fiber/detail/context_spmc_queue.hpp>
#include <boost/fiber/scheduler.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace algo {

class BOOST_FIBERS_DECL work_stealing : public algorithm {
private:
    static std::atomic< std::uint32_t >                     counter_;
    static std::vector< intrusive_ptr< work_stealing > >    schedulers_;

    std::uint32_t                                           id_;
    std::uint32_t                                           thread_count_;
#ifdef BOOST_FIBERS_USE_SPMC_QUEUE
    detail::context_spmc_queue                              rqueue_{};
#else
    detail::context_spinlock_queue                          rqueue_{};
#endif
    std::mutex                                              mtx_{};
    std::condition_variable                                 cnd_{};
    bool                                                    flag_{ false };
    bool                                                    suspend_;

    static void init_( std::uint32_t, std::vector< intrusive_ptr< work_stealing > > &);

public:
    work_stealing( std::uint32_t, bool = false);

    work_stealing( work_stealing const&) = delete;
    work_stealing( work_stealing &&) = delete;

    work_stealing & operator=( work_stealing const&) = delete;
    work_stealing & operator=( work_stealing &&) = delete;

    void awakened( context *) noexcept override;

    context * pick_next() noexcept override;

    virtual context * steal() noexcept {
        return rqueue_.steal();
    }

    bool has_ready_fibers() const noexcept override {
        return ! rqueue_.empty();
    }

    void suspend_until( std::chrono::steady_clock::time_point const&) noexcept override;

    void notify() noexcept override;
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_ALGO_WORK_STEALING_H

/* work_stealing.hpp
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
*/