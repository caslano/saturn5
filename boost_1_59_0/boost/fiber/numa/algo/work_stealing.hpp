
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FIBERS_NUMA_ALGO_WORK_STEALING_H
#define BOOST_FIBERS_NUMA_ALGO_WORK_STEALING_H

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
#include <boost/fiber/numa/pin_thread.hpp>
#include <boost/fiber/numa/topology.hpp>
#include <boost/fiber/scheduler.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace numa {
namespace algo {

class BOOST_FIBERS_DECL work_stealing : public boost::fibers::algo::algorithm {
private:
    static std::vector< intrusive_ptr< work_stealing > >    schedulers_;

    std::uint32_t                                           cpu_id_;
    std::vector< std::uint32_t >                            local_cpus_;
    std::vector< std::uint32_t >                            remote_cpus_;
#ifdef BOOST_FIBERS_USE_SPMC_QUEUE
    detail::context_spmc_queue                              rqueue_{};
#else
    detail::context_spinlock_queue                          rqueue_{};
#endif
    std::mutex                                              mtx_{};
    std::condition_variable                                 cnd_{};
    bool                                                    flag_{ false };
    bool                                                    suspend_;

    static void init_( std::vector< boost::fibers::numa::node > const&,
                       std::vector< intrusive_ptr< work_stealing > > &);

public:
    work_stealing( std::uint32_t, std::uint32_t,
                   std::vector< boost::fibers::numa::node > const&,
                   bool = false);

    work_stealing( work_stealing const&) = delete;
    work_stealing( work_stealing &&) = delete;

    work_stealing & operator=( work_stealing const&) = delete;
    work_stealing & operator=( work_stealing &&) = delete;

    virtual void awakened( context *) noexcept;

    virtual context * pick_next() noexcept;

    virtual context * steal() noexcept {
        return rqueue_.steal();
    }

    virtual bool has_ready_fibers() const noexcept {
        return ! rqueue_.empty();
    }

    virtual void suspend_until( std::chrono::steady_clock::time_point const&) noexcept;

    virtual void notify() noexcept;
};

}}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_NUMA_ALGO_WORK_STEALING_H

/* work_stealing.hpp
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
*/