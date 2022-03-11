
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